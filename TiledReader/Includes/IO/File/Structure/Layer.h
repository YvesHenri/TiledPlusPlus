#pragma once

#include "IO\File\Enum\Material.h"
#include "IO\File\Structure\PropertySet.h"

namespace tpp
{
	class TILEDPP_API Layer
	{
	public:
		Layer(tpp::Material material);
		virtual ~Layer() {
			printf("~Layer \n");
		}

		bool isVisible;
		bool isOpaque;
		
		double opacity;
		
		int x;
		int y;
		
		std::string name;
		tpp::PropertySet properties;
		
		const tpp::Material material;
	};
}