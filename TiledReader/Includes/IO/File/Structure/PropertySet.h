#ifndef TPP_STRUCTURE_PROPERTYSET_H
#define TPP_STRUCTURE_PROPERTYSET_H

#include <map>

#include "IO\File\Structure\Property.h"

namespace tpp
{
	// Simple std::map wrapper for the <properties> tag
	class TILEDPP_API PropertySet final
	{
	public:
		unsigned int size() const;

		bool isEmpty();
		bool has(const std::string& key);
		void add(const std::string& key, const std::string& value);
		void emplace(const std::string& name, const std::string& value, const std::string& type);

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