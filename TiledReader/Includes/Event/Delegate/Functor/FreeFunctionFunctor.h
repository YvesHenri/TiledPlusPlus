#ifndef TPP_EVENT_DELEGATE_FUNCTOR_FREEFUNCTIONFUNCTOR_H
#define TPP_EVENT_DELEGATE_FUNCTOR_FREEFUNCTIONFUNCTOR_H

#include "Functor.h"

namespace evt
{
	// Non specialized template declaration for a free function functor (empty)
	template <typename>
	class FreeFunctionFunctor;

	// Specialization for free functions functor
	template <typename TReturn, typename... TArgs>
	class FreeFunctionFunctor<TReturn(TArgs...)> final : public evt::Functor<TReturn(TArgs...)>
	{
	private:
		using FreeFunction = TReturn(*)(TArgs...);

	public:
		explicit FreeFunctionFunctor(const FreeFunction function);

		bool	operator == (const evt::Functor<TReturn(TArgs...)>& functor) override;
		TReturn operator ()(TArgs&&... args) override;

	private:
		const FreeFunction m_function;
	};
}

#include "Inline\FreeFunctionFunctor.inl"

#endif