#ifndef TPP_STRUCTURE_DATA_H
#define TPP_STRUCTURE_DATA_H

#include <string>

#include "File\Enum\Encoding.h"
#include "File\Enum\Compression.h"

namespace tpp
{
	// Represents the <data> tag
	struct Data
	{
		Data();

		std::string value;
		tpp::Encoding encoding;
		tpp::Compression compression;
	};
}

#endif