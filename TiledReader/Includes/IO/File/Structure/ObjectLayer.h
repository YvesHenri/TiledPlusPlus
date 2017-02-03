#ifndef TPP_STRUCTURE_OBJECTGROUP_H
#define TPP_STRUCTURE_OBJECTGROUP_H

#include "IO\File\Structure\Color.h"
#include "IO\File\Structure\Object.h"
#include "IO\File\Structure\Layer.h"

namespace tpp
{
	// Represents the <objectgroup> tag.
	// Objects are stored by their ids, since they may have no names.
	struct TILEDPP_API ObjectLayer final : public tpp::Layer
	{
		ObjectLayer();

		tpp::Color color;

		std::map<unsigned int, tpp::Object> objects;
	};
}

#endif