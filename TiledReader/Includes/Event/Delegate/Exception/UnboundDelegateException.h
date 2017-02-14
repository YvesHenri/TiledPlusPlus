#ifndef TPP_EVENT_DELEGATE_EXCEPTION_UNBOUNDDELEGATEEXCEPTION_H
#define TPP_EVENT_DELEGATE_EXCEPTION_UNBOUNDDELEGATEEXCEPTION_H

#include <exception>

#include "Macros\API.h"

// non dll - interface class 'std::exception' used as base for dll - interface class 'evt::UnboundDelegateException'
#pragma warning(disable: 4275)

namespace evt
{
	class TILEDPP_API UnboundDelegateException final : public std::exception
	{
	public:
		UnboundDelegateException() : std::exception("Unbound delegate")
		{}

		UnboundDelegateException(const char* message) : std::exception(message)
		{}
	};
}

#endif