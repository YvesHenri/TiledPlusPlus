#ifndef TPP_EVENT_DELEGATE_FUNCTOR_FUNCTOR_H
#define TPP_EVENT_DELEGATE_FUNCTOR_FUNCTOR_H

#include "..\Exception\UnboundDelegateException.h"

namespace evt
{
	// Non specialized template declaration for a functor (empty)
	template <typename>
	class Functor;

	// Specialization for a functor
	template <typename TReturn, typename... TArgs>
	class Functor<TReturn(TArgs...)>
	{
	public:
		virtual ~Functor() = default;

		virtual bool operator == (const Functor<TReturn(TArgs...)>& functor) = 0;

		virtual TReturn operator()(TArgs&&... args) = 0;
	};
}

#endif