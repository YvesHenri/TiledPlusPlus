#ifndef TPP_FILE_FILE_H
#define TPP_FILE_FILE_H

#include <string>

#include "IO\Path\Path.h"
#include "IO\File\FileMetadata.h"
#include "Macros\API.h"

namespace tpp
{
	// Represents a Tiled's TMX file. This object is immutable.
	class TILEDPP_API File final
	{
	public:
		File() = default;
		File(tpp::File&&) = default;
		File(const tpp::File&) = delete;
		File(const tpp::Path& path, tpp::FileMetadata& metadata);

		File& operator = (tpp::File&&) = default;
		File& operator = (const tpp::File&) = delete;

		const tpp::Path& getPath() const;
		const tpp::Header& getHeader() const;
		const tpp::Layers& getLayers() const;
		const tpp::TileSets& getTileSets() const;

	private:
		tpp::Path m_path;
		tpp::FileMetadata m_metadata;
	};
}

#endif