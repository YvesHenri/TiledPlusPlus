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
		bool handle = true;

		// Building blank tiles (no texture/gid) is pointless and costly. Check whether to ignore them
		if (m_settings.skipHandlingBlankTiles && tile->gid == 0U)
			handle = false;

		if (handle)
		{
			// Check flip flags (this will also reset the previous values, since it reuses a tpp::Tile object)
			tile->isFlippedDiagonally = (tpp::Flip::Diagonal & tile->gid) == tpp::Flip::Diagonal;
			tile->isFlippedVertically = (tpp::Flip::Vertical & tile->gid) == tpp::Flip::Vertical;
			tile->isFlippedHorizontally = (tpp::Flip::Horizontal & tile->gid) == tpp::Flip::Horizontal;

			// Remove the embed flip flags (if set)
			tile->gid &= ~tpp::Flip::Diagonal;
			tile->gid &= ~tpp::Flip::Vertical;
			tile->gid &= ~tpp::Flip::Horizontal;

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
			//for (int i = tileset_count - 1; i >= 0; --i) {
			//	Tileset *tileset = tilesets[i];
			//
			//	if (tileset->first_gid() <= global_tile_id) {
			//		tiles[y][x] = tileset->tileAt(global_tile_id - tileset->first_gid());
			//		break;
			//	}
			//}

			// Storing tiles can be very costly and might not be useful (when tile events are used and a "copy" of tpp::File is not needed)
			if (m_settings.storeTilesAfterRead)
			{
				tile->owner->tiles.emplace_back(std::move(*tile)); // Is moving really necessary here?
				//tile->owner->tiles.emplace_back(new tpp::Tile);
			}

			onTileRead.fire(*tile);
		}
	}

	void FileReader::onObjectParsed(tpp::Object* object)
	{
		bool handle = true;

		// Calculating the points is a bit costly and might not be useful
		if (m_settings.skipHandlingHiddenObjects && !object->isVisible)
			handle = false;

		if (handle)
		{
			bool valid = false;

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

			// If object contains valid points, apply layer offsets and rotation
			if (valid && object->isRotated)
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

			onObjectRead.fire(*object);
		}
	}

	void FileReader::onTileSetParsed(tpp::TileSet* set)
	{
		onTileSetRead.fire(*set);
	}

	void FileReader::onTileLayerParsed(tpp::TileLayer* tileLayer)
	{
		tpp::Tile tile; // Allocating a single time (outside the loop) makes it much faster
		std::string decoded = tpp::Decoder::decode(tileLayer->data.value, tileLayer->data.compression, tileLayer->data.encoding);

		// If tiles should be stored, reserve space for faster insertion and also to prevent reallocations
		if (m_settings.storeTilesAfterRead)
			tileLayer->tiles.reserve(tileLayer->area);

		// Dispatch the tiles after decoding/decompressing the layer
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

			// Reuse the function. Let it set positions, etc
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