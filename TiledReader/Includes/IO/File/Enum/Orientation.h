#ifndef TPP_ENUM_ORIENTATION_H
#define TPP_ENUM_ORIENTATION_H

namespace tpp
{
	// The </map> orientation
	enum class Orientation
	{
		Orthogonal,
		Isometric,
		Hexagonal, // Since 0.11
		Staggered
	};
}

#endif