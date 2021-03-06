#ifndef TPP_EVENT_DELEGATE_FUNCTOR_MEMBERFUNCTIONFUNCTOR_IMPL
#define TPP_EVENT_DELEGATE_FUNCTOR_MEMBERFUNCTIONFUNCTOR_IMPL

namespace evt
{
	template <class TClass, typename TReturn, typename... TArgs>
	MemberFunctionFunctor<TReturn(TClass::*)(TArgs...)>::MemberFunctionFunctor(const MemberFunction function, const MemberInstance instance)
		: m_function(function)
		, m_instance(instance)
	{}

	template <class TClass, typename TReturn, typename... TArgs>
	bool MemberFunctionFunctor<TReturn(TClass::*)(TArgs...)>::operator==(const evt::Functor<TReturn(TArgs...)>& functor)
	{
		try
		{
			const MemberFunctionFunctor& member = dynamic_cast<const MemberFunctionFunctor&>(functor);

			return m_function == member.m_function && m_instance == member.m_instance;
		}
		catch (const std::bad_cast&)
		{
			return false;
		}
	}

	template <class TClass, typename TReturn, typename... TArgs>
	TReturn MemberFunctionFunctor<TReturn(TClass::*)(TArgs...)>::operator()(TArgs&&... args)
	{
		if (m_function == nullptr || m_instance == nullptr)
			throw evt::UnboundDelegateException();

		return (m_instance->*m_function)(std::forward<TArgs>(args)...);
	}
}

#endif