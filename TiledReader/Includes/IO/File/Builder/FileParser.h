#ifndef FILE_PARSER_PUGIPARSER_H
#define FILE_PARSER_PUGIPARSER_H

#include "IO\File\FileMetadata.h"
#include "Dependencies\Pugi\pugixml.hpp"

namespace tpp
{
	// XML parser. It uses/requires the pugixml lib.
	class TILEDPP_API FileParser final
	{
	public:
		tpp::FileMetadata parseMetadata(const std::string& path);

	private:
		tpp::Header parseHeader(const pugi::xml_node& mapNode);
		tpp::TileSets parseTextures(const pugi::xml_node& mapNode);
		tpp::PropertySet parseProperties(const pugi::xml_node& propertiesNode);
		tpp::Layers parseLayers(const pugi::xml_node& mapNode);
		tpp::TileLayer* parseTileLayers(const pugi::xml_node& tileLayerNode);
		tpp::ImageLayer* parseImageLayers(const pugi::xml_node& imageLayerNode);
		tpp::ObjectLayer* parseObjectLayers(const pugi::xml_node& objectLayerNode);
	};
}

#endif