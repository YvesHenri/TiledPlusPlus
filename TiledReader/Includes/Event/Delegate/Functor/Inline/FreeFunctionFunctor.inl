#ifndef FREE_FUNCTION_FUNCTOR_IMPL
#define FREE_FUNCTION_FUNCTOR_IMPL

namespace evt
{
	template <typename TReturn, typename... TArgs>
	FreeFunctionFunctor<TReturn(TArgs...)>::FreeFunctionFunctor(const FreeFunction function)
		: m_function(function)
	{}

	template <typename TReturn, typename... TArgs>
	bool FreeFunctionFunctor<TReturn(TArgs...)>::operator==(const evt::Functor<TReturn(TArgs...)>& functor)
	{
		try
		{
			const FreeFunctionFunctor& free = dynamic_cast<const FreeFunctionFunctor&>(functor);

			return m_function == free.m_function;
		}
		catch (const std::bad_cast&)
		{
			return false;
		}
	}

	template <typename TReturn, typename... TArgs>
	TReturn FreeFunctionFunctor<TReturn(TArgs...)>::operator()(TArgs&&... args)
	{
		if (m_function == nullptr)
			throw evt::UnboundDelegateException();

		return m_function(std::forward<TArgs>(args)...);
	}
}

#endif