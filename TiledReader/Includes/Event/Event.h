#ifndef TPP_EVENT_EVENT_H
#define TPP_EVENT_EVENT_H

#include <vector>

#include "Dependencies\Delegator\Delegate\Includes\Delegate.h"

namespace evt
{
	// An event object whose TArgs will define the types and amount of 
	// parameters that will be signaled among the listeners (callbacks).
	template<typename... TArgs>
	class Event
	{
	public:
		bool muted();
		void mute();
		void unmute();
		void fire(TArgs... args);
		void attach(Delegate<void(TArgs...)>& delegate);
		void detach(Delegate<void(TArgs...)>& delegate);

	private:
		bool m_muted;
		std::vector<Delegate<void(TArgs...)>> m_delegates;
	};
}

// Include the templated code implementation
#include "Inline\Event.inl"

#endif