#ifndef TPP_FILE_FILE_H
#define TPP_FILE_FILE_H

#include <vector>
#include <string>

#include "File\Path.h"
#include "File\Structure\Header.h"
#include "File\Structure\ImageLayer.h"
#include "File\Structure\TileLayer.h"
#include "File\Structure\ObjectLayer.h"
#include "File\Structure\Tileset.h"
#include "Macros\Exporter.h"

namespace tpp
{
	// Type aliases for known collections
	using TileSets = std::vector<tpp::TileSet>;
	using TileLayers = std::vector<tpp::TileLayer>;
	using ImageLayers = std::vector<tpp::ImageLayer>;
	using ObjectLayers = std::vector<tpp::ObjectLayer>;

	// Represents a Tiled's TMX file. This object is immutable. This class is final.
	class TILEDPP_API File final
	{
	public:
		File(std::string path);

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
		tpp::Header m_header;
		tpp::TileSets m_tileSets;
		tpp::TileLayers m_tileLayers;
		tpp::ImageLayers m_imageLayers;
		tpp::ObjectLayers m_objectLayers;
	};
}

#endif