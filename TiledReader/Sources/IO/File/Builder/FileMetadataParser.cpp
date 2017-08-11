#include "IO\File\Builder\FileMetadataParser.h"

namespace tpp
{
	tpp::FileMetadata FileMetadataParser::parseMetadata(const std::string& path)
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

				// Save the data internally because some functions depend on some metadata's values
				m_metadata.header = std::move(parseHeader(mapNode));
				m_metadata.sets = std::move(parseTileSets(mapNode));
				m_metadata.layers = std::move(parseLayers(mapNode));
				
				// Do not copy data. Instead, we'll move for faster processing
				metadata.header = std::move(m_metadata.header);
				metadata.sets = std::move(m_metadata.sets);
				metadata.layers = std::move(m_metadata.layers);

				return metadata;
			}
			else
				throw std::runtime_error("File does not have a <map> tag!");
		}
		else
			throw std::runtime_error(result.description());
	}

	tpp::Header FileMetadataParser::parseHeader(const pugi::xml_node& mapNode)
	{
		tpp::Header header;

		header.width = mapNode.attribute("width").as_uint();
		header.height = mapNode.attribute("height").as_uint();
		header.tileWidth = mapNode.attribute("tilewidth").as_uint();
		header.tileHeight = mapNode.attribute("tileheight").as_uint();
		header.hexSideLength = mapNode.attribute("hexsidelength").as_uint(); // Since 0.11
		header.backgroundColor = mapNode.attribute("backgroundcolor").as_string();

		// Enumerations
		const std::string orientation = mapNode.attribute("orientation").as_string("orthogonal");
		const std::string renderOrder = mapNode.attribute("renderorder").as_string("right-down");
		const std::string staggerAxis = mapNode.attribute("staggeraxis").as_string("none");
		const std::string staggerIndex = mapNode.attribute("staggerindex").as_string("none");

		// Orientation (since 0.9). Default: Orthogonal
		if (orientation == "orthogonal")
			header.orientation = tpp::Orientation::Orthogonal;
		else if (orientation == "isometric")
			header.orientation = tpp::Orientation::Isometric;
		else if (orientation == "staggered")
			header.orientation = tpp::Orientation::Staggered;
		else if (orientation == "hexagonal")
			header.orientation = tpp::Orientation::Hexagonal;

		// Render order (since 0.10). Default: RightDown
		if (renderOrder == "right-down")
			header.renderOrder = tpp::RenderOrder::RightDown;
		else if (renderOrder == "right-up")
			header.renderOrder = tpp::RenderOrder::RightUp;
		else if (renderOrder == "left-down")
			header.renderOrder = tpp::RenderOrder::LeftDown;
		else if (renderOrder == "left-up")
			header.renderOrder = tpp::RenderOrder::LeftUp;

		// Stagger axis (since 0.11). Default: None
		if (staggerAxis == "x")
			header.staggerAxis = tpp::StaggerAxis::X;
		else if (staggerAxis == "y")
			header.staggerAxis = tpp::StaggerAxis::Y;

		// Stagger index (since 0.11). Default: None
		if (staggerIndex == "odd")
			header.staggerIndex = tpp::StaggerIndex::Odd;
		else if (staggerIndex == "even")
			header.staggerIndex = tpp::StaggerIndex::Even;

		// Properties
		if (mapNode.child("properties"))
		{
			tpp::PropertySet properties = parseProperties(mapNode.child("properties"));

			header.properties = std::move(properties);
		}

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

		onHeaderParsed.fire(&header);

		return header;
	}

	tpp::PropertySet FileMetadataParser::parseProperties(const pugi::xml_node& propertiesNode)
	{
		tpp::PropertySet properties;

		for (const auto& propertyNode : propertiesNode.children("property"))
		{
			std::string name = propertyNode.attribute("name").as_string();
			std::string value = propertyNode.attribute("value").as_string();
			std::string type = propertyNode.attribute("type").as_string("string"); // Since 0.16

			properties.emplace(name, value, type);
		}

		return properties;
	}

	tpp::TileSets FileMetadataParser::parseTileSets(const pugi::xml_node& mapNode)
	{
		tpp::TileSets sets;

		sets.reserve(m_metadata.header.tileSetsCount);

		for (const auto& setNode : mapNode.children("tileset"))
		{
			tpp::TileSet set;

			set.name = setNode.attribute("name").as_string();
			set.firstTileId = setNode.attribute("firstgid").as_uint();
			set.tileWidth = setNode.attribute("tilewidth").as_uint();
			set.tileHeight = setNode.attribute("tileheight").as_uint();
			set.columns = setNode.attribute("columns").as_uint(); // Since 0.15
			set.image.source = setNode.child("image").attribute("source").as_string();
			set.image.width = setNode.child("image").attribute("width").as_uint();
			set.image.height = setNode.child("image").attribute("height").as_uint();
			set.image.transparency = setNode.child("image").attribute("trans").as_string();

			// Columns count. If the value could not be previously retrieved, calculate it (since 0.15)
			if (set.columns == 0U && set.image.width > 0U && set.tileWidth > 0U)
				set.columns = set.image.width / set.tileWidth;

			// Tiles count and last tile id (since 0.13)
			if (setNode.attribute("tilecount"))
			{
				set.tilesCount = setNode.attribute("tilecount").as_uint();
				set.lastTileId = set.firstTileId + set.tilesCount - 1U;
			}
			// If no tilecount was specified, calculate it
			else
			{
				set.tilesCount = (set.image.width / set.tileWidth) * (set.image.height / set.tileHeight);
				set.lastTileId = set.firstTileId + set.tilesCount - 1U;
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

						animation.frames.emplace_back(std::move(frame));
					}

					set.animations.emplace(id, std::move(animation));
				}
			}

			onTileSetParsed.fire(&set);
			sets.emplace_back(std::move(set));
		}

		return sets;
	}

	tpp::Layers FileMetadataParser::parseLayers(const pugi::xml_node& mapNode)
	{
		tpp::Layers layers;

		// We dont know which layer comes first, so we traverse the XML file
		for (const auto& node : mapNode.children())
		{
			if (strcmp(node.name(), "layer") == 0)
				layers.emplace_back(parseTileLayer(node));
			else if (strcmp(node.name(), "imagelayer") == 0)
				layers.emplace_back(parseImageLayer(node));
			else if (strcmp(node.name(), "objectgroup") == 0)
				layers.emplace_back(parseObjectLayer(node));
		}

		return layers;
	}

	tpp::ImageLayer* FileMetadataParser::parseImageLayer(const pugi::xml_node& imageLayerNode)
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

		onImageLayerParsed.fire(imageLayer);

		return imageLayer;
	}

	tpp::TileLayer* FileMetadataParser::parseTileLayer(const pugi::xml_node& tileLayerNode)
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
		tileLayer->tileWidth = tileLayerNode.parent().attribute("tilewidth").as_uint();
		tileLayer->tileHeight = tileLayerNode.parent().attribute("tileheight").as_uint();
		
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
			std::string::const_iterator ltrim = data.begin() + data.find_first_not_of(" \t\n");
			std::string::const_iterator rtrim = data.begin() + data.find_last_not_of(" \t\n") + 1U;

			tileLayer->data.value = std::string(ltrim, rtrim);
		}
		else
			throw std::runtime_error("Unsupported encoding. Decoded tile layers are deprecated.");

		// Properties (if any)
		if (tileLayerNode.child("properties"))
		{
			tpp::PropertySet properties = parseProperties(tileLayerNode.child("properties"));
		
			tileLayer->properties = std::move(properties);
		}

		onTileLayerParsed.fire(tileLayer);

		return tileLayer;
	}

	tpp::ObjectLayer* FileMetadataParser::parseObjectLayer(const pugi::xml_node& objectLayerNode)
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
		for (const auto& objectNode : objectLayerNode.children("object"))
		{
			tpp::Object object = parseObject(objectNode, objectLayer);

			objectLayer->objects.emplace(object.id, std::move(object));
		}

		onObjectLayerParsed.fire(objectLayer);

		return objectLayer;
	}

	tpp::Object FileMetadataParser::parseObject(const pugi::xml_node& objectNode, const tpp::ObjectLayer* objectLayer)
	{
		tpp::Object object;

		object.x = objectNode.attribute("x").as_int();
		object.y = objectNode.attribute("y").as_int();
		object.id = objectNode.attribute("id").as_uint(objectNode.hash_value()); // Since 0.11
		object.name = objectNode.attribute("name").as_string();
		object.type = objectNode.attribute("type").as_string();
		object.width = objectNode.attribute("width").as_uint();
		object.height = objectNode.attribute("height").as_uint();
		object.tileGid = objectNode.attribute("gid").as_uint();
		object.rotation = objectNode.attribute("rotation").as_int(); // Since 0.10
		object.isRotated = !objectNode.attribute("rotation").empty();
		object.isVisible = strcmp(objectNode.attribute("visible").as_string("1"), "1") == 0; // Since 0.9
		object.owner = const_cast<tpp::ObjectLayer*>(objectLayer); // Safe casting (param value is non-const)

		// Points
		for (const auto& childNode : objectNode.children())
		{
			std::string points;

			if (childNode.name() == "ellipse")
			{
				object.shape = tpp::Shape::Ellipse;
				break; // This shape has no points to be parsed
			}
			else if (childNode.name() == "polygon")
			{
				object.shape = tpp::Shape::Polygon;
				points = childNode.attribute("points").as_string();
			}
			else if (childNode.name() == "polyline")
			{
				object.shape = tpp::Shape::Polyline;
				points = childNode.attribute("points").as_string();
			}
			else {
				continue; // Properties
			}

			// Check if there are points to be parsed (polygon or polyline)
			if (!points.empty())
			{
				std::string point;
				std::istringstream sepparator(points);

				while (sepparator >> point)
				{
					int px = std::stoi(point.substr(0U, point.find_first_of(",")));
					int py = std::stoi(point.substr(point.find_first_of(",") + 1U));

					// The parsed points are relative to the object's position (top left)
					object.points.emplace_back(object.x + px, object.y + py);
				}
			}
		}

		// Properties (if any)
		if (objectNode.child("properties"))
		{
			tpp::PropertySet properties = parseProperties(objectNode.child("properties"));

			object.properties = std::move(properties);
		}

		onObjectParsed.fire(&object);

		return object;
	}
}