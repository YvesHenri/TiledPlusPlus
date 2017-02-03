#include "IO\File\Structure\Tile.h"

namespace tpp
{
	Tile::Tile()
		: id(4294967295U) // -1
		, gid(0U)
		, x(0)
		, y(0)
		, index(0U)
		, width(0U)
		, height(0U)
		, set(0)
		, owner(0)
		, isFlippedHorizontally(false)
		, isFlippedVertically(false)
		, isFlippedDiagonally(false)
	{}
}