#ifndef TPP_STRUCTURE_TILELAYER_H
#define TPP_STRUCTURE_TILELAYER_H

#include <vector>

#include "File\Structure\Data.h"
#include "File\Structure\Tile.h"
#include "File\Structure\Layer.h"

namespace tpp
{
	// Represents the <layer> tag
	struct TileLayer final : public tpp::Layer
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