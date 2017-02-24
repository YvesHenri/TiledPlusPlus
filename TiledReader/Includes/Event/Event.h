#ifndef TPP_EVENT_EVENT_H
#define TPP_EVENT_EVENT_H

#include <vector>

#include "Dependencies\Delegator\Delegate.h"

namespace evt
{
	// An event object whose TArgs will define the types and amount of 
	// parameters that will be signaled among the listeners (callbacks).
	template<typename... TArgs>
	class Event
	{
	public:
		void mute();
		void unmute();
		bool muted();
		void fire(TArgs... args);
		void attach(evt::Delegate<void(TArgs...)>& delegate);
		void detach(evt::Delegate<void(TArgs...)>& delegate);

	private:
		bool m_muted;
		std::vector<evt::Delegate<void(TArgs...)>> m_delegates;
	};
}

// Include the templated code implementation
#include "Inline\Event.inl"

#endif