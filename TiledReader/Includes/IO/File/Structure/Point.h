#ifndef TPP_IO_FILE_STRUCTURE_POINT_H
#define TPP_IO_FILE_STRUCTURE_POINT_H

#include "Macros\API.h"

namespace tpp
{
	struct TILEDPP_API Point final
	{
		Point();
		Point(int x, int y);

		int x;
		int y;
	};
}

#endif