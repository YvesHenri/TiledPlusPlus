#pragma once

#include "File\Structure\PropertySet.h"

namespace tpp
{
	class Layer
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