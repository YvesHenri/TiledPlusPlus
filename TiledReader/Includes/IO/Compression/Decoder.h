#pragma once

#include <sstream>
#include <assert.h>

#include "IO\File\Enum\Encoding.h"
#include "IO\File\Enum\Compression.h"
#include "Dependencies\Miniz\miniz.h"
#include "Macros\API.h"

// ZLIB stuff
#define CHUNK_SIZE 32768
#define ENABLE_ZLIB_GZIP 32

namespace tpp
{
	// Helper class to decode a tile layer's <data> (if its encoded/compressed)
	class TILEDPP_API Decoder
	{
	public:
		static std::string decode(const std::string& data, tpp::Compression compression, tpp::Encoding encoding);

	private:
		static std::string decodeCSV(const std::string& source);
		static std::string decodeBase64UsingLookup(const std::string& source);
		static std::string decompressUsingGZIP(const std::string& source);
		static std::string decompressUsingZLIB(const std::string& source);
		static std::string decompress(const std::string& source, int windowBits);

		// The base64 lookup table. A short table uses 0.51kb (510 bytes), against 1.02kb (1024 bytes) for chars
		static unsigned short lookup[255];
	};
}