#pragma once

#include <memory>

#include "IO\File\File.h"
#include "IO\File\Builder\FileParser.h"
#include "IO\Compression\Decoder.h"

namespace tpp
{
	// Reads a TMX file. This behaves like the Director in the builder pattern.
	class TILEDPP_API FileReader final
	{
	public:
		FileReader() = default;
		~FileReader() = default;

		tpp::File read(const std::string& path);

	private:
		void decompress(tpp::TileLayer& layer);

	private:
		tpp::FileParser m_parser;
	};
}