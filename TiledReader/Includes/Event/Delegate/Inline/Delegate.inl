#ifndef DELEGATE_IMPL
#define DELEGATE_IMPL

namespace evt
{
	template <typename TReturn, typename... TArgs>
	evt::Delegate<TReturn(TArgs...)>::Delegate()
	{
		reset();
	}

	template <typename TReturn, typename... TArgs>
	evt::Delegate<TReturn(TArgs...)>::Delegate(TReturn(*freeFunction)(TArgs...))
	{
		reset(freeFunction);
	}

	template <typename TReturn, typename... TArgs>
	template <class TClass>
	evt::Delegate<TReturn(TArgs...)>::Delegate(TReturn(TClass::*memberFunction)(TArgs...), TClass* instance)
	{
		reset(memberFunction, instance);
	}

	template <typename TReturn, typename... TArgs>
	template <class TClass>
	evt::Delegate<TReturn(TArgs...)>::Delegate(TReturn(TClass::*memberConstFunction)(TArgs...) const, TClass* instance)
	{
		reset(memberConstFunction, instance);
	}

	template <typename TReturn, typename... TArgs>
	void evt::Delegate<TReturn(TArgs...)>::reset()
	{
		m_functor.reset();
	}

	template <typename TReturn, typename... TArgs>
	void evt::Delegate<TReturn(TArgs...)>::reset(Delegate* delegate)
	{
		m_functor = delegate->m_functor;
	}

	template <typename TReturn, typename... TArgs>
	void evt::Delegate<TReturn(TArgs...)>::reset(TReturn(*freeFunction)(TArgs...))
	{
		m_functor.reset(new FreeFunctionFunctor<TReturn(TArgs...)>(freeFunction));
	}

	template <typename TReturn, typename... TArgs>
	template <typename TClass>
	void evt::Delegate<TReturn(TArgs...)>::reset(TReturn(TClass::*memberFunction)(TArgs...), TClass* instance)
	{
		m_functor.reset(new MemberFunctionFunctor<TReturn(TClass::*)(TArgs...)>(memberFunction, instance));
	}

	template <typename TReturn, typename... TArgs>
	template <typename TClass>
	void evt::Delegate<TReturn(TArgs...)>::reset(TReturn(TClass::*memberConstFunction)(TArgs...) const, TClass* instance)
	{
		m_functor.reset(new MemberConstFunctionFunctor<TReturn(TClass::*)(TArgs...) const>(memberConstFunction, instance));
	}

	template <typename TReturn, typename... TArgs>
	TReturn evt::Delegate<TReturn(TArgs...)>::invoke(TArgs&&... args)
	{
		if (!m_functor)
			throw evt::UnboundDelegateException();

		m_functor->operator()(std::forward<TArgs>(args)...);
	}

	template <typename TReturn, typename... TArgs>
	bool evt::Delegate<TReturn(TArgs...)>::operator==(const Delegate& delegate)
	{
		TFunctor* self = m_functor.get();
		TFunctor* target = delegate.m_functor.get();

		bool areBothEmpty = self == nullptr && target == nullptr;
		bool areBothValid = self != nullptr && target != nullptr;
		bool areBothEqual = areBothValid && (*self == *target);

		return areBothEmpty || areBothEqual;
	}
}

#endif