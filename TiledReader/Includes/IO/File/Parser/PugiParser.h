#ifndef FILE_PARSER_PUGIPARSER_H
#define FILE_PARSER_PUGIPARSER_H

#include "IO\File\Parser\IParser.h"
#include "Dependencies\Pugi\pugixml.hpp"

namespace tpp
{
	class TILEDPP_API PugiParser final : public tpp::IParser
	{
	public:
		tpp::FileMetadata parseMetadata(std::string path) override;

	private:
		tpp::Header parseHeader(const pugi::xml_node& node);
		tpp::TileSet parseTileSet(const pugi::xml_node& node);
	};
}

#endif