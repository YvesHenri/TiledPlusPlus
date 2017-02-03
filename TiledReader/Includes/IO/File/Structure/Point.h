#ifndef TPP_STRUCTURE_POINT_H
#define TPP_STRUCTURE_POINT_H

#include "Macros\Exporter.h"

namespace tpp
{
	struct TILEDPP_API Point
	{
		Point();
		Point(int x, int y);

		int x;
		int y;
	};
}

#endif