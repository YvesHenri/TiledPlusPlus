#include "IO\File\Builder\FileParser.h"

namespace tpp
{
	tpp::FileMetadata FileParser::parseMetadata(const std::string& path)
	{
		pugi::xml_document document;
		pugi::xml_parse_result result;

		// Load text into a pugi struct
		result = document.load_file(path.c_str());

		// Check whether the loading has succeed
		if (result.status == pugi::xml_parse_status::status_ok)
		{
			pugi::xml_node mapNode = document.child("map");

			// Validate and parse in order
			if (mapNode)
			{
				tpp::FileMetadata metadata;

				// Do not copy data. Instead, we'll move for faster processing
				metadata.header = std::move(parseHeader(mapNode));
				metadata.sets = std::move(parseTextures(mapNode));
				metadata.layers = std::move(parseLayers(mapNode));

				return metadata;
			}
			else {
				throw std::runtime_error("File does not have a <map> tag!");
			}
		}
		else {
			throw std::runtime_error(result.description());
		}
	}

	// Optimized - TODO: Check layer names validation (counting)
	tpp::Header FileParser::parseHeader(const pugi::xml_node& mapNode)
	{
		tpp::Header header;

		header.width = mapNode.attribute("width").as_int();
		header.height = mapNode.attribute("height").as_int();
		header.tileWidth = mapNode.attribute("tilewidth").as_int();
		header.tileHeight = mapNode.attribute("tileheight").as_int();

		// Orientation (since 0.9). Default: Orthogonal
		const std::string orientation = mapNode.attribute("orientation").as_string("orthogonal");

		if (orientation == "orthogonal")
			header.orientation = tpp::Orientation::Orthogonal;
		else if (orientation == "isometric")
			header.orientation = tpp::Orientation::Isometric;
		else if (orientation == "staggered")
			header.orientation = tpp::Orientation::Staggered;
		else if (orientation == "hexagonal")
			header.orientation = tpp::Orientation::Hexagonal;

		// Render order (since 0.10). Default: RightDown
		const std::string renderOrder = mapNode.attribute("renderorder").as_string("right-down");

		if (renderOrder == "right-down")
			header.renderOrder = tpp::RenderOrder::RightDown;
		else if (renderOrder == "right-up")
			header.renderOrder = tpp::RenderOrder::RightUp;
		else if (renderOrder == "left-down")
			header.renderOrder = tpp::RenderOrder::LeftDown;
		else if (renderOrder == "left-up")
			header.renderOrder = tpp::RenderOrder::LeftUp;

		// Number of sprite sheets used
		for (const auto& setNode : mapNode.children("tileset"))
			header.tileSetsCount++;

		// Number of image layers
		for (const auto& imageLayerNode : mapNode.children("imagelayer"))
			header.imageLayersCount++;

		// Number of tile layers
		for (const auto& tileLayerNode : mapNode.children("layer"))
		{
			header.tileLayersCount++;
			header.tilesCount += header.width * header.height;
		}

		// Number of object layers
		for (const auto& objectLayerNode : mapNode.children("objectgroup"))
		{
			header.objectLayersCount++;
			for (const auto& objectNode : objectLayerNode.children("object"))
				header.objectsCount++;
		}

		return header;
	}

	// Optimized
	tpp::PropertySet FileParser::parseProperties(const pugi::xml_node& propertiesNode)
	{
		tpp::PropertySet properties;

		for (const auto& propertyNode : propertiesNode.children("property"))
		{
			std::string name = propertyNode.attribute("name").as_string();
			std::string value = propertyNode.attribute("value").as_string();

			properties.add(name, value);
		}

		return properties;
	}

	// Optimized
	tpp::TileSets FileParser::parseTextures(const pugi::xml_node& mapNode)
	{
		tpp::TileSets sets;

		for (const auto& setNode : mapNode.children("tileset"))
		{
			tpp::TileSet set;

			set.name = setNode.attribute("name").as_string();
			set.firstTileId = setNode.attribute("firstgid").as_uint();
			set.tileWidth = setNode.attribute("tilewidth").as_uint();
			set.tileHeight = setNode.attribute("tileheight").as_uint();
			set.image.source = setNode.child("image").attribute("source").as_string();
			set.image.width = setNode.child("image").attribute("width").as_uint();
			set.image.height = setNode.child("image").attribute("height").as_uint();
			set.image.transparency = setNode.child("image").attribute("trans").as_string();

			// Tiles count and last tile id (since 0.13)
			if (setNode.attribute("tilecount"))
			{
				set.tilesCount = setNode.attribute("tilecount").as_uint();
				set.lastTileId = set.firstTileId + set.tilesCount - 1;
			}
			// If no tilecount was specified, calcule it through the precalculed image sizes
			else
			{
				set.tilesCount = (set.image.width / set.tileWidth) * (set.image.height / set.tileHeight);
				set.lastTileId = set.firstTileId + set.tilesCount - 1;
			}

			// Check for internal tiles properties/animations
			for (const auto& tileNode : setNode.children("tile"))
			{
				unsigned int id = tileNode.attribute("id").as_uint();

				// Properties
				if (tileNode.child("properties"))
				{
					tpp::PropertySet properties = parseProperties(tileNode.child("properties"));

					set.tileProperties.emplace(id, std::move(properties));
				}

				// Animations
				if (tileNode.child("animation"))
				{
					tpp::Animation animation;

					for (const auto& animationFrame : tileNode.child("animation").children("frame"))
					{
						tpp::Frame frame;

						frame.duration = animationFrame.attribute("duration").as_uint();
						frame.tileGid = animationFrame.attribute("tileid").as_uint();

						// Store the frame
						animation.frames.emplace_back(std::move(frame));
					}

					// Store the animation
					set.animations.emplace(id, std::move(animation));
				}
			}

			sets.emplace_back(set);
		}

		return sets;
	}

	tpp::Layers FileParser::parseLayers(const pugi::xml_node& mapNode)
	{
		tpp::Layers layers;

		// We dont know which layer comes first, so we traverse the XML file
		for (const auto& node : mapNode.children())
		{
			// Check whichever layer this is and build it
			if (strcmp(node.name(), "layer") == 0)
				layers.emplace_back(parseTileLayers(node));
			else if (strcmp(node.name(), "imagelayer") == 0)
				layers.emplace_back(parseImageLayers(node));
			else if (strcmp(node.name(), "objectgroup") == 0)
				layers.emplace_back(parseObjectLayers(node));
		}

		return layers;
	}

	tpp::ImageLayer* FileParser::parseImageLayers(const pugi::xml_node& imageLayerNode)
	{
		tpp::ImageLayer* imageLayer = new tpp::ImageLayer;

		imageLayer->x = imageLayerNode.attribute("x").as_int(); // Deprecated at 0.15
		imageLayer->y = imageLayerNode.attribute("y").as_int(); // Deprecated at 0.15
		imageLayer->name = imageLayerNode.attribute("name").as_string();
		imageLayer->opacity = imageLayerNode.attribute("opacity").as_double(1.0); // Defaults to 1.0
		imageLayer->isOpaque = !imageLayerNode.attribute("opacity").empty(); // Defaults to false
		imageLayer->isVisible = strcmp(imageLayerNode.attribute("visible").as_string("1"), "1") == 0; // Defaults to true
		imageLayer->image.source = imageLayerNode.child("image").attribute("source").as_string();
		imageLayer->image.transparency = imageLayerNode.child("image").attribute("trans").as_string();

		// Offset X. Override deprecated value (Since 0.15)
		if (imageLayerNode.attribute("offsetx"))
			imageLayer->x = imageLayerNode.attribute("offsetx").as_int();

		// Offset Y. Override deprecated value (Since 0.15)
		if (imageLayerNode.attribute("offsety"))
			imageLayer->y = imageLayerNode.attribute("offsety").as_int();

		// Properties (if any)
		if (imageLayerNode.child("properties"))
		{
			tpp::PropertySet properties = parseProperties(imageLayerNode.child("properties"));

			imageLayer->properties = std::move(properties);
		}

		return imageLayer;
	}

	tpp::TileLayer* FileParser::parseTileLayers(const pugi::xml_node& tileLayerNode)
	{
		tpp::TileLayer* tileLayer = new tpp::TileLayer;

		tileLayer->x = tileLayerNode.attribute("x").as_int(); // Deprecated at 0.14
		tileLayer->y = tileLayerNode.attribute("y").as_int(); // Deprecated at 0.14
		tileLayer->name = tileLayerNode.attribute("name").as_string();
		tileLayer->width = tileLayerNode.attribute("width").as_uint();
		tileLayer->height = tileLayerNode.attribute("height").as_uint();
		tileLayer->area = tileLayer->width * tileLayer->height;
		tileLayer->opacity = tileLayerNode.attribute("opacity").as_double(1.0); // Defaults to 1.0
		tileLayer->isOpaque = !tileLayerNode.attribute("opacity").empty(); // Defaults to false
		tileLayer->isVisible = strcmp(tileLayerNode.attribute("visible").as_string("1"), "1") == 0; // Defaults to true

		// Offset X. Override deprecated value (Since 0.14)
		if (tileLayerNode.attribute("offsetx"))
			tileLayer->x = tileLayerNode.attribute("offsetx").as_int();

		// Offset Y. Override deprecated value (Since 0.14)
		if (tileLayerNode.attribute("offsety"))
			tileLayer->y = tileLayerNode.attribute("offsety").as_int();

		// Encoding. If layer is encoded, it contains data and might have compression as well
		if (tileLayerNode.child("data").attribute("encoding"))
		{
			const std::string data = tileLayerNode.child("data").text().as_string(); // Untrimmed!
			const std::string encoding = tileLayerNode.child("data").attribute("encoding").as_string();
			const std::string compression = tileLayerNode.child("data").attribute("compression").as_string();

			// Encoding. Default: None
			if (encoding == "csv")
				tileLayer->data.encoding = tpp::Encoding::CSV;
			else if (encoding == "base64")
				tileLayer->data.encoding = tpp::Encoding::Base64;

			// Compression. Default: None
			if (compression == "gzip")
				tileLayer->data.compression = tpp::Compression::GZIP;
			else if (compression == "zlib")
				tileLayer->data.compression = tpp::Compression::ZLIB;

			// Data. Trim left ('\n', '', '' and '') and right ('\n', '' and '')
			tileLayer->data.value = std::string(data.begin() + 4, data.end() - 3);
		}
		else
			throw std::runtime_error("Unsupported encoding. Decoded layers are deprecated.");

		// Properties (if any)
		if (tileLayerNode.child("properties"))
		{
			tpp::PropertySet properties = parseProperties(tileLayerNode.child("properties"));
		
			tileLayer->properties = std::move(properties);
		}

		return tileLayer;
	}

	tpp::ObjectLayer* FileParser::parseObjectLayers(const pugi::xml_node& objectLayerNode)
	{
		tpp::ObjectLayer* objectLayer = new tpp::ObjectLayer;

		objectLayer->x = objectLayerNode.attribute("x").as_int(); // Deprecated at 0.14
		objectLayer->y = objectLayerNode.attribute("y").as_int(); // Deprecated at 0.14
		objectLayer->name = objectLayerNode.attribute("name").as_string();
		objectLayer->color = objectLayerNode.attribute("color").as_string();
		objectLayer->opacity = objectLayerNode.attribute("opacity").as_double(1.0); // Defaults to 1.0
		objectLayer->isOpaque = !objectLayerNode.attribute("opacity").empty(); // Defaults to false
		objectLayer->isVisible = objectLayerNode.attribute("visible").as_string("1") == "1"; // Defaults to true

		// Offset X. Override deprecated value (Since 0.14)
		if (objectLayerNode.attribute("offsetx"))
			objectLayer->x = objectLayerNode.attribute("offsetx").as_int();

		// Offset Y. Override deprecated value (Since 0.14)
		if (objectLayerNode.attribute("offsety"))
			objectLayer->y = objectLayerNode.attribute("offsety").as_int();

		// Properties (if any)
		if (objectLayerNode.child("properties"))
		{
			tpp::PropertySet properties = parseProperties(objectLayerNode.child("properties"));

			objectLayer->properties = std::move(properties);
		}

		// Objects
		/*for (const auto& objectNode : objectLayerNode.children("object"))
			buildObject(objectNode);*/

		return objectLayer;
	}
}