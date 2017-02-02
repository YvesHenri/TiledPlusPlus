#ifndef TPP_STRUCTURE_IMAGELAYER_H
#define TPP_STRUCTURE_IMAGELAYER_H

#include "File\Structure\Image.h"
#include "File\Structure\Layer.h"

namespace tpp
{
	// Represents the <imagelayer> tag
	struct ImageLayer final : public tpp::Layer
	{
		ImageLayer();

		tpp::Image image;
	};
}

#endif