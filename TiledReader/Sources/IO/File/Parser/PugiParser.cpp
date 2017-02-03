#include "IO\File\Parser\PugiParser.h"

namespace tpp
{
	tpp::FileMetadata PugiParser::parseMetadata(std::string path)
	{
		pugi::xml_document document;
		pugi::xml_parse_result result;

		// Load text into a pugi struct
		result = document.load_file(path.c_str());

		// Check whether the loading has succeed
		if (result.status == pugi::xml_parse_status::status_ok)
		{
			pugi::xml_node node = document.child("map");

			// Validate and parse in order
			if (node)
			{
				tpp::FileMetadata metadata;

				metadata.header = parseHeader(node);
				metadata.imageLayers.swap(std::vector<tpp::ImageLayer>(metadata.header.imageLayersCount));
				metadata.objectLayers.swap(std::vector<tpp::ObjectLayer>(metadata.header.objectLayersCount));
				metadata.tileLayers.swap(std::vector<tpp::TileLayer>(metadata.header.tileLayersCount));
				metadata.tileSets.swap(std::vector<tpp::TileSet>(metadata.header.tileSetsCount));

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

	tpp::Header PugiParser::parseHeader(const pugi::xml_node& node)
	{
		tpp::Header header;

		header.width = node.attribute("width").as_int();
		header.height = node.attribute("height").as_int();
		header.tileWidth = node.attribute("tileWidth").as_int();
		header.tileHeight = node.attribute("tileHeight").as_int();

		// Orientation (since 0.9). Default: Orthogonal
		const std::string orientation = node.attribute("orientation").as_string("orthogonal");

		if (orientation == "orthogonal") {
			header.orientation = tpp::Orientation::Orthogonal;
		}
		else if (orientation == "isometric") {
			header.orientation = tpp::Orientation::Isometric;
		}
		else if (orientation == "staggered") {
			header.orientation = tpp::Orientation::Staggered;
		}
		else if (orientation == "hexagonal") {
			header.orientation = tpp::Orientation::Hexagonal;
		}

		// Render order (since 0.10). Default: RightDown
		const std::string renderOrder = node.attribute("renderorder").as_string("right-down");

		if (renderOrder == "right-down") {
			header.renderOrder = tpp::RenderOrder::RightDown;
		}
		else if (renderOrder == "right-up") {
			header.renderOrder = tpp::RenderOrder::RightUp;
		}
		else if (renderOrder == "left-down") {
			header.renderOrder = tpp::RenderOrder::LeftDown;
		}
		else if (renderOrder == "left-up") {
			header.renderOrder = tpp::RenderOrder::LeftUp;
		}

		return header;
	}

	tpp::TileSet PugiParser::parseTileSet(const pugi::xml_node& node)
	{
		tpp::TileSet set;

		return set;
	}
}