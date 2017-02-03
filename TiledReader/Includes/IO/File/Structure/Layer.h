#pragma once

#include "IO\File\Structure\PropertySet.h"

namespace tpp
{
	class TILEDPP_API Layer
	{
	public:
		Layer();

		bool isVisible;
		bool isOpaque;

		double opacity;

		int x;
		int y;

		std::string name;
		tpp::PropertySet properties;
	};
}