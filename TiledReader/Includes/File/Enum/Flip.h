#ifndef TPP_ENUM_FLIP_H
#define TPP_ENUM_FLIP_H

namespace tpp
{
	// The <tile/> flip type
	enum class Flip : unsigned
	{
		Diagonal = 0x20000000,
		Vertical = 0x40000000,
		Horizontal = 0x80000000
	};
}

#endif