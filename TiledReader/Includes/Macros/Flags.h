#ifndef TPP_MACROS_FLAGS_H
#define TPP_MACROS_FLAGS_H

#include <type_traits>

// Adds the C++14 feature for older compilers (C++11+) for detecting the underlying type
namespace ut
{
	template <typename T>
	using Value = typename std::underlying_type<T>::type;
}

// Checks whether the given param is a valid integral type
#define BITWISEABLE_ENUM_CLASS_ASSERT_INTEGRAL(Integral) \
static_assert(std::is_integral<Integral>::value, "Invalid integral type"); \

// Enables [copy] operators such as: enum = enum | Enum::Value
#define BITWISEABLE_ENUM_CLASS_COPY_DEFAULT_BINARY_OPERATOR(Operator, Enum) \
inline Enum operator Operator (Enum lhs, Enum rhs) \
{ \
	return static_cast<Enum>(static_cast<ut::Value<Enum>>(lhs) Operator static_cast<ut::Value<Enum>>(rhs)); \
}

// Enables [ref] operators such as: enum |= Enum::Value
#define BITWISEABLE_ENUM_CLASS_REF_DEFAULT_BINARY_OPERATOR(Operator, Enum) \
inline Enum& operator Operator= (Enum& lhs, Enum rhs) \
{ \
	lhs = static_cast<Enum>(static_cast<ut::Value<Enum>>(lhs) Operator static_cast<ut::Value<Enum>>(rhs)); \
	return lhs; \
}

// Enables [copy] operators such as: enum = enum | 0x20000000
#define \
BITWISEABLE_ENUM_CLASS_COPY_INTEGRAL_L_BINARY_OPERATOR(Operator, Enum, Integral) \
BITWISEABLE_ENUM_CLASS_ASSERT_INTEGRAL(Integral) \
inline Enum operator Operator (Enum lhs, Integral rhs) \
{ \
	return static_cast<Enum>(static_cast<ut::Value<Enum>>(lhs) Operator static_cast<ut::Value<Enum>>(rhs)); \
}

// Enables [copy] operators such as: 0x20000000 = 0x20000000 | Enum::Value
#define \
BITWISEABLE_ENUM_CLASS_COPY_INTEGRAL_R_BINARY_OPERATOR(Operator, Integral, Enum) \
BITWISEABLE_ENUM_CLASS_ASSERT_INTEGRAL(Integral) \
inline Integral operator Operator (Integral lhs, Enum rhs) \
{ \
	return static_cast<Integral>(static_cast<ut::Value<Enum>>(lhs) Operator static_cast<ut::Value<Enum>>(rhs)); \
}

// Enables [ref] operators such as: enum |= 0x20000000
#define \
BITWISEABLE_ENUM_CLASS_REF_INTEGRAL_L_BINARY_OPERATOR(Operator, Enum, Integral) \
BITWISEABLE_ENUM_CLASS_ASSERT_INTEGRAL(Integral) \
inline Enum& operator Operator= (Enum& lhs, Integral rhs) \
{ \
	lhs = static_cast<Enum>(static_cast<ut::Value<Enum>>(lhs) Operator static_cast<ut::Value<Enum>>(rhs)); \
	return lhs; \
}

// Enables [ref] operators such as: 0x20000000 |= Enum::Value
#define \
BITWISEABLE_ENUM_CLASS_REF_INTEGRAL_R_BINARY_OPERATOR(Operator, Integral, Enum) \
BITWISEABLE_ENUM_CLASS_ASSERT_INTEGRAL(Integral) \
inline Integral& operator Operator= (Integral& lhs, Enum rhs) \
{ \
	lhs = static_cast<Integral>(static_cast<ut::Value<Enum>>(lhs) Operator static_cast<ut::Value<Enum>>(rhs)); \
	return lhs; \
}

// Enables the negation operator
#define BITWISEABLE_ENUM_CLASS_NEGATION_UNARY_OPERATOR(Enum) \
inline Enum operator ~ (Enum value) \
{ \
	return static_cast<Enum>(~static_cast<ut::Value<Enum>>(value)); \
}

// Defines a safe signature for a typed enum class
#define \
BITWISEABLE_ENUM_CLASS_DEFINITION(Enum, Integral) \
BITWISEABLE_ENUM_CLASS_ASSERT_INTEGRAL(Integral) \
enum class Enum : Integral

// Defines an enum class with all the bitwise operators and a given integral type (inheritance).
#define \
BITWISEABLE_ENUM_CLASS_I(Enum, Integral) \
BITWISEABLE_ENUM_CLASS_DEFINITION(Enum, Integral); \
BITWISEABLE_ENUM_CLASS_NEGATION_UNARY_OPERATOR(Enum) \
BITWISEABLE_ENUM_CLASS_COPY_DEFAULT_BINARY_OPERATOR(|, Enum) \
BITWISEABLE_ENUM_CLASS_COPY_DEFAULT_BINARY_OPERATOR(^, Enum) \
BITWISEABLE_ENUM_CLASS_COPY_DEFAULT_BINARY_OPERATOR(&, Enum) \
BITWISEABLE_ENUM_CLASS_REF_DEFAULT_BINARY_OPERATOR(|, Enum) \
BITWISEABLE_ENUM_CLASS_REF_DEFAULT_BINARY_OPERATOR(^, Enum) \
BITWISEABLE_ENUM_CLASS_REF_DEFAULT_BINARY_OPERATOR(&, Enum) \
BITWISEABLE_ENUM_CLASS_COPY_INTEGRAL_L_BINARY_OPERATOR(|, Enum, Integral) \
BITWISEABLE_ENUM_CLASS_COPY_INTEGRAL_R_BINARY_OPERATOR(|, Integral, Enum) \
BITWISEABLE_ENUM_CLASS_COPY_INTEGRAL_L_BINARY_OPERATOR(^, Enum, Integral) \
BITWISEABLE_ENUM_CLASS_COPY_INTEGRAL_R_BINARY_OPERATOR(^, Integral, Enum) \
BITWISEABLE_ENUM_CLASS_COPY_INTEGRAL_L_BINARY_OPERATOR(&, Enum, Integral) \
BITWISEABLE_ENUM_CLASS_COPY_INTEGRAL_R_BINARY_OPERATOR(&, Integral, Enum) \
BITWISEABLE_ENUM_CLASS_REF_INTEGRAL_L_BINARY_OPERATOR(|, Enum, Integral) \
BITWISEABLE_ENUM_CLASS_REF_INTEGRAL_R_BINARY_OPERATOR(|, Integral, Enum) \
BITWISEABLE_ENUM_CLASS_REF_INTEGRAL_L_BINARY_OPERATOR(^, Enum, Integral) \
BITWISEABLE_ENUM_CLASS_REF_INTEGRAL_R_BINARY_OPERATOR(^, Integral, Enum) \
BITWISEABLE_ENUM_CLASS_REF_INTEGRAL_L_BINARY_OPERATOR(&, Enum, Integral) \
BITWISEABLE_ENUM_CLASS_REF_INTEGRAL_R_BINARY_OPERATOR(&, Integral, Enum) \
BITWISEABLE_ENUM_CLASS_DEFINITION(Enum, Integral)

// Defines an (unsigned) enum class with all the bitwise operators.
#define BITWISEABLE_ENUM_CLASS(Enum) BITWISEABLE_ENUM_CLASS_I(Enum, unsigned)

#endif