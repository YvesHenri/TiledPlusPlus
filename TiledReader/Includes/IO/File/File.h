#ifndef TPP_FILE_FILE_H
#define TPP_FILE_FILE_H

#include <string>

#include "IO\Path\Path.h"
#include "IO\File\FileMetadata.h"
#include "Macros\Exporter.h"

namespace tpp
{
	// Represents a Tiled's TMX file. This object is immutable. This class is final.
	class TILEDPP_API File final
	{
	public:
		File() {};
		File(std::string path, tpp::FileMetadata metadata);

		const std::string& getName();
		const std::string& getPath();
		const std::string& getFullPath();
		const tpp::Header& getHeader();
		const tpp::TileSets& getTileSets();
		const tpp::TileLayers& getTileLayers();
		const tpp::ImageLayers& getImageLayers();
		const tpp::ObjectLayers& getObjectLayers();

	private:
		bool isParsable() const;
		bool isValidExtension() const;

	private:
		std::string m_name;
		std::string m_path;
		std::string m_fullPath;
		std::string m_extension;
		tpp::FileMetadata m_metadata;
	};
}

#endif