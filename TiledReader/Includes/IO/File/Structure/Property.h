#ifndef TPP_IO_FILE_STRUCTURE_PROPERTY_H
#define TPP_IO_FILE_STRUCTURE_PROPERTY_H

#include <string>
#include <limits>

#include "Macros\API.h"

namespace tpp
{
	class TILEDPP_API Property final
	{
	public:
		Property() = default;
		Property(const std::string& value);

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