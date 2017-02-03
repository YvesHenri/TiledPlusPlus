#ifndef TPP_STRUCTURE_IMAGELAYER_H
#define TPP_STRUCTURE_IMAGELAYER_H

#include "IO\File\Structure\Image.h"
#include "IO\File\Structure\Layer.h"

namespace tpp
{
	// Represents the <imagelayer> tag
	struct TILEDPP_API ImageLayer final : public tpp::Layer
	{
		ImageLayer();

		tpp::Image image;
	};
}

#endif