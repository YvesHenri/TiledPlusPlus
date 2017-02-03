#include "IO\Encoding\Decoder.h"

namespace tpp
{
	// Define the lookup table
	unsigned short Decoder::lookup[255] = {
		0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,62,0,0,0,63,52,53,54,55,56,
		57,58,59,60,61,0,0,0,99,0,0,0,0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18,19,20,21,22,23,24,25,0,0,0,0,0,0,26,
		27,28,29,30,31,32,33,34,35,36,37,38,39,40,41,42,43,44,45,46,47,48,49,50,51,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
		0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
		0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0
	};

	std::string Decoder::decode(const tpp::Data& data)
	{
		std::string decoded = data.value;

		// Decode
		switch (data.encoding)
		{
		case tpp::Encoding::Base64:
			decoded = decodeBase64UsingLookup(decoded);

			// Decompress
			switch (data.compression)
			{
			case tpp::Compression::GZIP:
				decoded = decompressUsingGZIP(decoded);
				break;
			case tpp::Compression::ZLIB:
				decoded = decompressUsingZLIB(decoded);
				break;
			}
			break;
		default:
			throw std::runtime_error("Only Base64 layers can be decoded");
		}

		return decoded;
	}

	std::string Decoder::decodeBase64UsingLookup(std::string const& source)
	{
		// Length must be divisible by 4 for a base64 string to be decoded (valid)
		assert(source.size() % 4 == 0 && "Data string might be corrupted");

		// The decoded string
		std::string out;

		// Unsigned int indexes allows data to be up to 4.294.967.295 characters long. 
		// That means it supports decoding of layers with a perimeter of 1231241823 tiles. 
		// In other words, the biggest layer area it allows is 307810455 x 307810455 tiles.
		unsigned int sourceIndex = 0;
		unsigned int outIndex = 0;

		// Sizes used to determine the output length (see above for string sizes)
		unsigned int sourceLength = source.size();
		unsigned int outLength = (sourceLength + 1) / 4 * 3; // Formula: encSize = ((decSize / 3) + 1) * 4;

															 // This makes it up to 6 times faster (instead of appending the characters)
		out.resize(outLength);

		for (unsigned int i = 0; i < sourceLength; i += 4)
		{
			// Fetch the short values from the lookup and cast to characters
			unsigned char s1 = static_cast<unsigned char>(lookup[source[sourceIndex++]]);
			unsigned char s2 = static_cast<unsigned char>(lookup[source[sourceIndex++]]);
			unsigned char s3 = static_cast<unsigned char>(lookup[source[sourceIndex++]]);
			unsigned char s4 = static_cast<unsigned char>(lookup[source[sourceIndex++]]);

			// The beautiful magic!
			unsigned char d1 = ((s1 & 0x3f) << 2) | ((s2 & 0x30) >> 4);
			unsigned char d2 = ((s2 & 0x0f) << 4) | ((s3 & 0x3c) >> 2);
			unsigned char d3 = ((s3 & 0x03) << 6) | ((s4 & 0x3f) >> 0);

			out[outIndex++] = d1;

			if (s3 == static_cast<unsigned char>(99)) // 99 = 'c' (why 99?)
				break;

			out[outIndex++] = d2;

			if (s4 == static_cast<unsigned char>(99)) // 99 = 'c' (why 99?)
				break;

			out[outIndex++] = d3;
		}

		return out;
	}

	std::string Decoder::decompressUsingGZIP(const std::string& source)
	{
		return decompress(source, 16 + MAX_WBITS);
	}

	std::string Decoder::decompressUsingZLIB(const std::string& source)
	{
		return decompress(source, 15 + 32);
	}

	std::string Decoder::decompress(const std::string& source, int windowBits)
	{
		std::string decompressed;
		z_stream stream;

		stream.zalloc = Z_NULL;
		stream.zfree = Z_NULL;
		stream.opaque = Z_NULL;

		if (inflateInit2(&stream, windowBits) == Z_OK)
		{
			unsigned char out[CHUNK_SIZE] = {};

			stream.avail_in = source.size() + 1;
			stream.next_in = (unsigned char*)source.c_str();

			do
			{
				stream.next_out = out;
				stream.avail_out = CHUNK_SIZE;

				switch (inflate(&stream, Z_NO_FLUSH))
				{
				case Z_NEED_DICT:
				case Z_DATA_ERROR:
				case Z_MEM_ERROR:
					inflateEnd(&stream);
					break;
				default:
					decompressed.append((char*)out, CHUNK_SIZE - stream.avail_out);
					break;
				}
			} while (stream.avail_out == 0);

			if (inflateEnd(&stream) != Z_OK)
			{
				throw std::runtime_error("[ZLIB] Critical error. Could not end inflate");
			}
		}
		else
		{
			throw std::runtime_error("[ZLIB] Critical error. Could not intitialize inflate");
		}

		return decompressed;
	}
}