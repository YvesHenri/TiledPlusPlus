#ifndef FILE_PARSER_IPARSER_H
#define FILE_PARSER_IPARSER_H

#include "File\File.h"

namespace tpp
{
	class TILEDPP_API IParser
	{
	public:
		virtual ~IParser() = default;

		virtual tpp::File parseFile(std::string path) = 0;
	};
}

#endif