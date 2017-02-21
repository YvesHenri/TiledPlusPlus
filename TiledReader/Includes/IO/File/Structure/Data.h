#ifndef TPP_IO_FILE_STRUCTURE_DATA_H
#define TPP_IO_FILE_STRUCTURE_DATA_H

#include <string>

#include "IO\File\Enum\Encoding.h"
#include "IO\File\Enum\Compression.h"
#include "Macros\API.h"

namespace tpp
{
	// Represents the <data> tag
	struct TILEDPP_API Data final
	{
		std::string value;
		tpp::Encoding encoding;
		tpp::Compression compression;
	};
}

#endif