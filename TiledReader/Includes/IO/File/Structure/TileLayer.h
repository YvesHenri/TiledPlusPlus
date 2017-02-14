#ifndef TPP_STRUCTURE_TILELAYER_H
#define TPP_STRUCTURE_TILELAYER_H

#include <vector>

#include "IO\File\Structure\Data.h"
#include "IO\File\Structure\Tile.h"
#include "IO\File\Structure\Layer.h"

namespace tpp
{
	// Represents the <layer> tag
	struct TILEDPP_API TileLayer final : public tpp::Layer
	{
		TileLayer();
		
		unsigned int area;
		unsigned int width;
		unsigned int height;

		tpp::Data data;
		std::vector<tpp::Tile> tiles;
	};
}

#endif