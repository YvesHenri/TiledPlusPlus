#ifndef TPP_STRUCTURE_HEADER_H
#define TPP_STRUCTURE_HEADER_H

#include "File\Enum\Orientation.h"
#include "File\Enum\RenderOrder.h"

namespace tpp
{
	// Represents the <map> tag
	struct Header
	{
		Header();

		unsigned int width;
		unsigned int height;
		unsigned int tileWidth;
		unsigned int tileHeight;
		unsigned int tilesCount;
		unsigned int objectsCount;
		unsigned int tileSetsCount;
		unsigned int tileLayersCount;
		unsigned int imageLayersCount;
		unsigned int objectLayersCount;

		tpp::Orientation orientation;
		tpp::RenderOrder renderOrder;
	};
}

#endif