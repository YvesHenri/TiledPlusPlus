#include "IO\File\Structure\Property.h"

namespace tpp
{
	Property::Property(const std::string& value)
		: m_value(value)
	{}

	int Property::asInt() const
	{
		// Never throws exceptions. Defaults to 0
		return std::stoi(m_value);
	}

	long Property::asLong() const
	{
		// Never throws exceptions. Defaults to 0L
		return std::stol(m_value);
	}

	float Property::asFloat() const
	{
		// Never throws exceptions. Defaults to 0.0F
		return std::stof(m_value);
	}

	double Property::asDouble() const
	{
		// Never throws exceptions. Defaults to 0.0
		return std::stod(m_value);
	}

	short Property::asShort() const
	{
		int intValue = std::stoi(m_value);

		if (intValue > std::numeric_limits<short>::max()) {
			intValue = 0; // Error
		}

		// Defaults to 0
		return static_cast<short>(intValue);
	}

	bool Property::asBool() const
	{
		// Defaults to false
		return _stricmp(m_value.c_str(), "1") == 0
			|| _stricmp(m_value.c_str(), "true") == 0;
	}

	std::string Property::asString() const
	{
		return m_value;
	}
}