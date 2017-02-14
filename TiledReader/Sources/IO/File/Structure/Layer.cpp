#include "IO\File\Structure\Layer.h"

namespace tpp
{
	Layer::Layer(tpp::Material material)
		: name("")
		, opacity(1.0)
		, isVisible(true)
		, isOpaque(false)
		, x(0)
		, y(0)
		, material(material)
	{}
}