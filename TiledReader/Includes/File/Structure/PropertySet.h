#ifndef TPP_STRUCTURE_PROPERTYSET_H
#define TPP_STRUCTURE_PROPERTYSET_H

#include <map>

#include "File\Structure\Property.h"

namespace tpp
{
	// Simple std::map wrapper for the <properties> tag
	class PropertySet
	{
	public:
		unsigned int size() const;

		bool isEmpty() const;
		bool has(std::string key);
		void add(std::string key, std::string value);

		std::map<std::string, tpp::Property>::iterator begin();
		std::map<std::string, tpp::Property>::iterator end();
		std::map<std::string, tpp::Property>::const_iterator begin() const;
		std::map<std::string, tpp::Property>::const_iterator end() const;

		tpp::Property& operator[](const char* key);
		tpp::Property& operator[](const std::string& key);

	private:
		std::map<std::string, tpp::Property> m_properties;
	};
}

#endif