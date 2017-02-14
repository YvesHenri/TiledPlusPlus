#include "IO\File\Structure\PropertySet.h"

namespace tpp
{
	unsigned int PropertySet::size() const
	{
		return m_properties.size();
	}

	bool PropertySet::isEmpty()
	{
		return m_properties.empty();
	}

	bool PropertySet::has(const std::string& key)
	{
		return m_properties.find(key) != m_properties.end();
	}	

	void PropertySet::add(const std::string& key, const std::string& value)
	{
		m_properties.emplace(key, value); // Calls in-place tpp::Property(value)
	}

	std::map<std::string, tpp::Property>::iterator PropertySet::begin()
	{
		return m_properties.begin();
	}

	std::map<std::string, tpp::Property>::iterator PropertySet::end()
	{
		return m_properties.end();
	}

	std::map<std::string, tpp::Property>::const_iterator PropertySet::begin() const
	{
		return m_properties.begin();
	}

	std::map<std::string, tpp::Property>::const_iterator PropertySet::end() const
	{
		return m_properties.end();
	}

	tpp::Property& PropertySet::operator[](const char* key)
	{
		return m_properties[key];
	}

	tpp::Property& PropertySet::operator[](const std::string& key)
	{
		return m_properties[key];
	}
}