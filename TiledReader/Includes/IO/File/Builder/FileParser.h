#ifndef FILE_PARSER_PUGIPARSER_H
#define FILE_PARSER_PUGIPARSER_H

#include <sstream>

#include "Event\Event.h"
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
		tpp::TileSets parseTileSets(const pugi::xml_node& mapNode);
		tpp::Layers parseLayers(const pugi::xml_node& mapNode);
		tpp::Object parseObject(const pugi::xml_node& objectNode, const tpp::ObjectLayer* objectLayer);
		tpp::PropertySet parseProperties(const pugi::xml_node& propertiesNode);
		tpp::TileLayer* parseTileLayer(const pugi::xml_node& tileLayerNode);
		tpp::ImageLayer* parseImageLayer(const pugi::xml_node& imageLayerNode);
		tpp::ObjectLayer* parseObjectLayer(const pugi::xml_node& objectLayerNode);

	public:
		evt::Event<tpp::Tile*> onTileParsed;
		evt::Event<tpp::Object*> onObjectParsed;
		evt::Event<tpp::Header*> onHeaderParsed;
		evt::Event<tpp::TileSet*> onTileSetParsed;
		evt::Event<tpp::TileLayer*> onTileLayerParsed;
		evt::Event<tpp::ImageLayer*> onImageLayerParsed;
		evt::Event<tpp::ObjectLayer*> onObjectLayerParsed;

	private:
		tpp::FileMetadata m_metadata;
	};
}

#endif