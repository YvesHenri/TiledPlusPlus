#ifndef TPP_STRUCTURE_PROPERTY_H
#define TPP_STRUCTURE_PROPERTY_H

#include <map>
#include <string>
#include <limits>

namespace tpp
{
	class Property
	{
	public:
		Property();
		Property(std::string value);

		int asInt() const;
		long asLong() const;
		bool asBool() const;
		short asShort() const;
		float asFloat() const;
		double asDouble() const;

		std::string asString() const;

	private:
		std::string m_value;
	};
}

#endif