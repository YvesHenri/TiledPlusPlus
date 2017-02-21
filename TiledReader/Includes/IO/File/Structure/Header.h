#ifndef TPP_IO_FILE_STRUCTURE_HEADER_H
#define TPP_IO_FILE_STRUCTURE_HEADER_H

#include "IO\File\Structure\Color.h"
#include "IO\File\Enum\Orientation.h"
#include "IO\File\Enum\RenderOrder.h"
#include "IO\File\Enum\StaggerAxis.h"
#include "IO\File\Enum\StaggerIndex.h"
#include "Macros\API.h"

namespace tpp
{
	// Represents the </map> tag
	struct TILEDPP_API Header final
	{
		Header();

		unsigned int width;
		unsigned int height;
		unsigned int tileWidth;
		unsigned int tileHeight;
		unsigned int hexSideLength;
		unsigned int tilesCount;
		unsigned int objectsCount;
		unsigned int tileSetsCount;
		unsigned int tileLayersCount;
		unsigned int imageLayersCount;
		unsigned int objectLayersCount;

		tpp::Color backgroundColor;
		tpp::Orientation orientation;
		tpp::RenderOrder renderOrder;
		tpp::StaggerAxis staggerAxis;
		tpp::StaggerIndex staggerIndex;
	};
}

#endif