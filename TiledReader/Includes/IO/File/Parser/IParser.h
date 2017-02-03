#ifndef FILE_PARSER_IPARSER_H
#define FILE_PARSER_IPARSER_H

#include "IO\File\FileMetadata.h"

namespace tpp
{
	class TILEDPP_API IParser
	{
	public:
		virtual ~IParser() = default;

		virtual tpp::FileMetadata parseMetadata(std::string path) = 0;
	};
}

#endif