#ifndef TPP_STRUCTURE_OBJECT_H
#define TPP_STRUCTURE_OBJECT_H

#include <vector>

#include "IO\File\Enum\Shape.h"
#include "IO\File\Structure\Point.h"
#include "IO\File\Structure\Image.h"
#include "IO\File\Structure\PropertySet.h"

namespace tpp
{
	// Forward declare the owner of this object
	struct ObjectLayer;

	// Represents the <object> tag
	struct TILEDPP_API Object final
	{
		Object();

		int x;
		int y;
		int rotation; // Clockwise, in degrees

		unsigned int id;
		unsigned int tileGid; // If this object references a tpp::Tile's texture
		unsigned int width;
		unsigned int height;

		bool isRotated;
		bool isVisible;

		std::string name;
		std::string type;
		tpp::Shape shape;
		tpp::Image* image; // If this object references a tpp::Tile's texture
		tpp::ObjectLayer* owner;
		tpp::PropertySet properties;
		std::vector<tpp::Point> points;
	};
}

#endif