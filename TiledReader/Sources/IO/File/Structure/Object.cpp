#include "IO\File\Structure\Object.h"

namespace tpp
{
	Object::Object()
		: shape(Shape::Rectangle)
		, id(0U)
		, x(0)
		, y(0)
		, rotation(0)
		, image(0)
		, owner(0)
		, width(0U)
		, height(0U)
		, tileGid(0U)
		, isVisible(true)
		, isRotated(false)
		, name("")
		, type("")
	{}
}