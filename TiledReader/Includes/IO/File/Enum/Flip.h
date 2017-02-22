#ifndef TPP_ENUM_FLIP_H
#define TPP_ENUM_FLIP_H

#include "Macros\Flags.h"

namespace tpp
{
	// The </tile> flip type
	BITWISEABLE_ENUM_CLASS(Flip)
	{
		Diagonal = 0x20000000U,
		Vertical = 0x40000000U,
		Horizontal = 0x80000000U
	};
}

#endif