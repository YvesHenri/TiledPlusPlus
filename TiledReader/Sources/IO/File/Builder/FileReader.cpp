#include "IO\File\Builder\FileReader.h"

namespace tpp
{
	FileReader::FileReader(const tpp::FileReaderSettings& settings)
	{
		m_settings = settings;
		m_parser.onHeaderParsed.attach(evt::Delegate<void(tpp::Header*)>(&FileReader::onHeaderParsed, this));
		m_parser.onObjectParsed.attach(evt::Delegate<void(tpp::Object*)>(&FileReader::onObjectParsed, this));
		m_parser.onTileParsed.attach(evt::Delegate<void(tpp::Tile*)>(&FileReader::onTileParsed, this));
		m_parser.onTileSetParsed.attach(evt::Delegate<void(tpp::TileSet*)>(&FileReader::onTileSetParsed, this));
		m_parser.onTileLayerParsed.attach(evt::Delegate<void(tpp::TileLayer*)>(&FileReader::onTileLayerParsed, this));
		m_parser.onImageLayerParsed.attach(evt::Delegate<void(tpp::ImageLayer*)>(&FileReader::onImageLayerParsed, this));
		m_parser.onObjectLayerParsed.attach(evt::Delegate<void(tpp::ObjectLayer*)>(&FileReader::onObjectLayerParsed, this));
	}

	tpp::File FileReader::read(const tpp::Path& path)
	{
		return read(path.getFileFullPath());
	}

	tpp::File FileReader::read(const std::string& path)
	{
		tpp::FileMetadata metadata = m_parser.parseMetadata(path);

		// Here, we should have received the parse events and dispatched them accordingly
		return tpp::File(path, metadata);
	}

	void FileReader::onHeaderParsed(tpp::Header* header)
	{
		onHeaderRead.fire(*header);
	}

	void FileReader::onTileParsed(tpp::Tile* tile)
	{
		// Ignore textureless tiles (if set in the settings)
		if ((m_settings.skipTexturelessTiles && tile->gid > 0U) || !m_settings.skipTexturelessTiles)
		{
			// Check flip flags
			tile->isFlippedHorizontally = (tile->gid & tpp::Tile::FLIPPED_HORIZONTALLY) != 0;
			tile->isFlippedVertically = (tile->gid & tpp::Tile::FLIPPED_VERTICALLY) != 0;
			tile->isFlippedDiagonally = (tile->gid & tpp::Tile::FLIPPED_DIAGONALLY) != 0;

			// Remove flip flags (if any)
			tile->gid &= ~tpp::Tile::FLIPPED_HORIZONTALLY;
			tile->gid &= ~tpp::Tile::FLIPPED_VERTICALLY;
			tile->gid &= ~tpp::Tile::FLIPPED_DIAGONALLY;

			// Tile sets might have different tile sizes, however its only used for positioning the texture
			tile->width = tile->owner->tileWidth;
			tile->height = tile->owner->tileHeight;

			// Calculate the position and apply layer offset (if any) to it
			tile->x = tile->owner->x + ((tile->index % tile->owner->width) * tile->width);
			tile->y = tile->owner->y + ((tile->index / tile->owner->width) * tile->height);

			// Retrieve the set and the tile id
			//m_sets.resolve(tile) {
			//	tile.set = &m_sets[m_setLookup[tile.gid]];
			//	tile.id = tile.gid - tile.set->firstTileId;
			//}

			tile->owner->tiles.emplace_back(*tile);
		}

		onTileRead.fire(*tile);
	}

	void FileReader::onObjectParsed(tpp::Object* object)
	{
		bool valid = false;

		// Dont calculate points if the object is not visible (if set in the settings)
		if ((m_settings.skipInvisibleObjects && object->isVisible) || !m_settings.skipInvisibleObjects)
		{
			// Create/parse the points accordingly
			if (object->shape == tpp::Shape::Ellipse)
			{
				// Some ellipses dont have sizes. Impossible to compute bounds (skip)
				valid = object->width > 0U && object->height > 0U;

				if (valid)
				{
					static const float pi = 3.141592654f;
					static const unsigned int points = 20; // Smoothing factor

					// Calculates all the points
					for (unsigned int i = 0; i < points; i++)
					{
						float angle = i * 2.f * pi / points - pi / 2.f;

						// Apply layer offset to the center of this ellipse
						int cx = object->x + object->width / 2 + object->owner->x;
						int cy = object->y + object->height / 2 + object->owner->y;

						// Use ellipse equation for each point
						int x = static_cast<int>(std::cos(angle) * object->width / 2);
						int y = static_cast<int>(std::sin(angle) * object->height / 2);

						object->points.emplace_back(cx + x, cy + y);
					}
				}
			}
			else if (object->shape == tpp::Shape::Rectangle)
			{
				// Some rectangles dont have sizes. Impossible to compute bounds (skip)
				valid = object->width > 0U && object->height > 0U;

				if (valid)
				{
					// If this object references a tile's texture, update position
					if (object->tileGid) {
						//m_sets.resolve(object) {
						//	object->image = &m_sets[m_setLookup[object->tileGid]].image;
						//	object->y -= static_cast<int>(object->height);
						//}
					}

					// Apply layer offset to each edge of this rectangle
					int ox = object->x + object->owner->x;
					int oy = object->y + object->owner->y;

					object->points.emplace_back(ox, oy);
					object->points.emplace_back(ox + object->width, oy);
					object->points.emplace_back(ox + object->width, oy + object->height);
					object->points.emplace_back(ox, oy + object->height);
				}
			}
			else
			{
				// Object must be at least a line
				valid = object->points.size() >= 2U;

				if (valid)
				{
					// Apply layer offset to each point, if any (avoid useless loop)
					if (object->owner->x || object->owner->y)
					{
						for (auto& point : object->points)
						{
							point.x += object->owner->x;
							point.y += object->owner->y;
						}
					}
				}
			}
		}

		// If object contains valid points, apply layer offsets, rotation and store them
		if (valid)
		{
			// Before storing, apply rotation (if any)
			if (object->isRotated)
			{
				float rad = object->rotation * 0.0174532925f; // Degrees to radians (std::cos & std::sin)
				float cos = std::cos(rad);
				float sin = std::sin(rad);

				// Anchor point (top left)
				int ax = object->points[0].x;
				int ay = object->points[0].y;

				// Rotate points relative to the anchor
				for (auto& point : object->points)
				{
					// Current position before transformations
					int x = point.x;
					int y = point.y;

					// Multiply point by the combination of Translate(x,y) * Rotate(angle) * Translate(-x,-y) matrix
					point.x = static_cast<int>(x * cos - y * sin + (ax * (1 - cos) + ay * sin));
					point.y = static_cast<int>(x * sin + y * cos + (ay * (1 - cos) - ax * sin));
				}
			}
		}

		onObjectRead.fire(*object);
	}

	void FileReader::onTileSetParsed(tpp::TileSet* set)
	{
		onTileSetRead.fire(*set);
	}

	void FileReader::onTileLayerParsed(tpp::TileLayer* tileLayer)
	{
		// Create a tile outside the loop to speed up things. It will be reused as many times as needed
		tpp::Tile tile;
		std::string decoded = tpp::Decoder::decode(tileLayer->data.value, tileLayer->data.compression, tileLayer->data.encoding);

		for (unsigned int index = 0; index < tileLayer->area; index++)
		{
			// Reserves 4 bytes for each tile, since encoded tile gids are composed by 4 bytes
			unsigned int encodingIndex = index * 4;

			// Decodes the gid by shifting left each byte of a gid (see 'Tiled' main page: mapeditor.org)
			tile.gid = static_cast<unsigned char>(decoded[encodingIndex])
				| static_cast<unsigned char>(decoded[encodingIndex + 1]) << 8
				| static_cast<unsigned char>(decoded[encodingIndex + 2]) << 16
				| static_cast<unsigned char>(decoded[encodingIndex + 3]) << 24;

			tile.index = index;
			tile.owner = tileLayer;

			// Reuse the function. Let it set positions, owner, etc
			onTileParsed(&tile);
		}

		onTileLayerRead.fire(*tileLayer);
	}

	void FileReader::onImageLayerParsed(tpp::ImageLayer* imageLayer)
	{
		onImageLayerRead.fire(*imageLayer);
	}

	void FileReader::onObjectLayerParsed(tpp::ObjectLayer* objectLayer)
	{
		onObjectLayerRead.fire(*objectLayer);
	}
}