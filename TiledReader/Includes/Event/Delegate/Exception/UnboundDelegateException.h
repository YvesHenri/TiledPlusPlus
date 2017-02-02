#ifndef TPP_EVENT_DELEGATE_EXCEPTION_UNBOUNDDELEGATEEXCEPTION_H
#define TPP_EVENT_DELEGATE_EXCEPTION_UNBOUNDDELEGATEEXCEPTION_H

#include <exception>

namespace evt
{
	class UnboundDelegateException final : public std::exception
	{
	public:
		UnboundDelegateException() : std::exception("Unbound delegate")
		{}

		UnboundDelegateException(const char* const message) : std::exception(message)
		{}
	};
}

#endif