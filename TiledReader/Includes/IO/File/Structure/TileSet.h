#ifndef TPP_IO_FILE_STRUCTURE_TILESET_H
#define TPP_IO_FILE_STRUCTURE_TILESET_H

#include <memory>

#include "IO\File\Structure\Tile.h"
#include "IO\File\Structure\Image.h"
#include "IO\File\Structure\Animation.h"
#include "IO\File\Structure\PropertySet.h"

namespace tpp
{
	// Represents the </tileset> tag
	struct TILEDPP_API TileSet final
	{
		TileSet();

		unsigned int firstTileId;
		unsigned int lastTileId;
		unsigned int tilesCount;
		unsigned int tileWidth;
		unsigned int tileHeight;
		unsigned int columns;

		tpp::Image image;
		std::string name;

		std::vector<tpp::Tile> rtiles;
		std::vector<std::shared_ptr<tpp::Tile>> tiles;

		std::map<unsigned int, tpp::Animation> animations;
		std::map<unsigned int, tpp::PropertySet> tileProperties;
	};
}

#endif