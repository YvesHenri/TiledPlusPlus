#ifndef TPP_EVENT_EVENT_IMPL
#define TPP_EVENT_EVENT_IMPL

namespace evt
{
	template <typename... TArgs>
	void Event<TArgs...>::attach(evt::Delegate<void(TArgs...)>& delegate)
	{
		auto& iter = std::find(m_delegates.begin(), m_delegates.end(), delegate);

		// Avoid replication
		if (iter == m_delegates.end())
			m_delegates.emplace_back(std::move(delegate));
	}

	template <typename... TArgs>
	void Event<TArgs...>::detach(evt::Delegate<void(TArgs...)>& delegate)
	{
		auto& iter = std::find(m_delegates.begin(), m_delegates.end(), delegate);

		// Make sure it exists
		if (iter != m_delegates.end())
			m_delegates.erase(iter);
	}

	template<typename... TArgs>
	void Event<TArgs...>::fire(TArgs... args)
	{
		if (!m_muted)
			for (auto& delegate : m_delegates)
				delegate.invoke(args...);
	}

	template<typename... TArgs>
	void Event<TArgs...>::mute()
	{
		m_muted = true;
	}

	template<typename... TArgs>
	void Event<TArgs...>::unmute()
	{
		m_muted = false;
	}

	template<typename... TArgs>
	bool Event<TArgs...>::muted()
	{
		return m_muted;
	}
}

#endif