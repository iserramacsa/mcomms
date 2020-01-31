#ifndef MACSA_SIGNALS_H
#define MACSA_SIGNALS_H

#include <vector>
#include <functional>

namespace MacsaUtils {
	namespace Signals {

		template<typename... Args> class Signal;
		template<typename... Args> class Slot;

		template<typename... Args>
		class Signal{
			public:
				using SlotType = Slot<Args ...>;
				using CallbackType = std::function<void(Args ...)>;

			public:
				Signal(){}
				~Signal() { disconnectAll();}

				// Move constructor: makes every slot remember this one.
//				Signal(Signal&& other) :
//					_slots {std::move(other._slots)},
//					forgot{other.forgot}
//				{
//					other._slots.clear(); // make sure it forgets every slot
//					for (SlotType *slot : _slots)
//						slot->remember(this);
//				}

				void disconnectAll()
				{

				}

			private:
				std::vector<SlotType*> _slots;
		};

		template<typename... Args>
		class Slot
		{
			public:
				using SignalType = Signal<Args...>;
				using CallbackType = typename SignalType::CallbackType;
				friend class Signal<Args...>;

			public:
				// Default constructor: not connected, no callback
				Slot() noexcept :
					_signal{nullptr}
				{}

			private:
				SignalType _signal;
				CallbackType _callback;
		};
	}
}

#endif //MACSA_SIGNALS_H
