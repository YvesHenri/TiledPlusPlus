#ifndef TPP_STRUCTURE_OBJECT_H
#define TPP_STRUCTURE_OBJECT_H

#include <string>
#include <vector>

#include "File\Enum\Shape.h"
#include "File\Structure\Point.h"
#include "File\Structure\Image.h"
#include "File\Structure\PropertySet.h"

namespace tpp
{
	// Forward declare the owner of this object
	struct ObjectLayer;

	// Represents the <object> tag
	struct Object
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