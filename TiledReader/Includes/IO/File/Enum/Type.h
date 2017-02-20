#pragma once

namespace tpp
{
	// Represents the </property.type> types
	enum class Type
	{
		String,
		Int,
		Float,
		Bool,
		Color, // Since 0.17
		File // Since 0.17
	};
}