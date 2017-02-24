#ifndef TPP_EVENT_DELEGATE_FUNCTOR_MEMBERCONSTFUNCTIONFUNCTOR_H
#define TPP_EVENT_DELEGATE_FUNCTOR_MEMBERCONSTFUNCTIONFUNCTOR_H

#include "Functor.h"

namespace evt
{
	// Non specialized template declaration (empty)
	template <typename>
	class MemberConstFunctionFunctor;

	// Specialization for member const functions
	template <class TClass, typename TReturn, typename... TArgs>
	class MemberConstFunctionFunctor<TReturn(TClass::*)(TArgs...) const> final : public evt::Functor<TReturn(TArgs...)>
	{
	private:
		using MemberConstInstance = const TClass*;
		using MemberConstFunction = TReturn(TClass::*)(TArgs...) const;

	public:
		explicit MemberConstFunctionFunctor(const MemberConstFunction function, const MemberConstInstance instance);

		bool	operator == (const evt::Functor<TReturn(TArgs...)>& functor) override;
		TReturn operator ()(TArgs&&... args) override;

	private:
		const MemberConstInstance m_instance;
		const MemberConstFunction m_function;
	};
}

#include "Inline\MemberConstFunctionFunctor.inl"

#endif