#ifndef FILE_PARSER_PUGIPARSER_H
#define FILE_PARSER_PUGIPARSER_H

#include "File\Parser\IParser.h"
#include "Dependencies\Pugi\pugixml.hpp"

namespace tpp
{
	class PugiParser final : public tpp::IParser
	{
	public:
		tpp::File parseFile(std::string path) override;

	private:
		tpp::Header parseHeader(const pugi::xml_node& node);
		tpp::TileSet parseTileSet(const pugi::xml_node& node);
	};
}

#endif