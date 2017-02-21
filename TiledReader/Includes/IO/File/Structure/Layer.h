#ifndef TPP_IO_FILE_STRUCTURE_LAYER_H
#define TPP_IO_FILE_STRUCTURE_LAYER_H

#include "IO\File\Enum\Material.h"
#include "IO\File\Structure\PropertySet.h"

namespace tpp
{
	class TILEDPP_API Layer
	{
	public:
		Layer(tpp::Material material);
		virtual ~Layer() = default;

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

#endif