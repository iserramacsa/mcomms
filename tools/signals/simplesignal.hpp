/*
  This software is in the public domain.
  Do whatever you want with it.
 */
#ifndef SIMPLE_SIGNALPP_H__
#define SIMPLE_SIGNALPP_H__


#include <vector>
#include <algorithm>
#include <stdexcept>
#include <utility>
#include <functional>

namespace simpsig {

    template<typename... Args> class Signal;
    template<typename... Args> class Slot;

    template<typename... Args>
    class Signal {
    public:
        using slot_type = Slot<Args...>;
        using callback_type = std::function<void(Args...)>;

    private:
        std::vector<slot_type*> slots;
        bool forgot = false; // true if slots contain any nullptr
        bool enabled = true;
        bool stopping = false;

        // This is a convenience accessor, it does not guarantee invariants.
        void remember(slot_type *slot)
        {
            slots.push_back(slot);
        }

        // This is a convenience accessor, it does not guarantee invariants.
        void remember(slot_type *slot, size_t idx)
        {
            if (idx<slots.size() && !slots[idx])
                // position is available
                slots[idx] = slot;
            else
                slots.insert(slots.begin()+idx, slot);
        }


        size_t indexOf(const slot_type* slot) const
        {
            size_t off = std::distance(slots.begin(),
                                       std::find(slots.begin(), slots.end(), slot));
            if (off == slots.size())
                throw std::logic_error{"Slot is not connected to this Signal"};
            return off;
        }


        /*
         * This is a convenience accessor, it does not guarantee invariants.
         * Replace a given entry by nullptr, so the trigger() loop doesn't break.
         */
        void forget(slot_type *slot) noexcept
        {
            auto i = std::find(slots.begin(), slots.end(), slot);
            if (i != slots.end()) {
                forgot = true;
                *i = nullptr;
            }
        }


        // Removes forgotten signals.
        void purge() noexcept
        {
            if (forgot) {
                slots.erase(std::remove(slots.begin(),
                                        slots.end(),
                                        nullptr),
                            slots.end());
                forgot = false;
            }
        }

    public:

        Signal() = default;


        ~Signal()
        {
            disconnectAll();
        }


        // Move constructor: makes every slot remember this one.
        Signal(Signal&& other) :
            slots {std::move(other.slots)},
            forgot{other.forgot}
        {
            other.slots.clear(); // make sure it forgets every slot
            for (slot_type *slot : slots)
                slot->remember(this);
        }


        // Move assignment: makes every slot remember this one.
        Signal& operator=(Signal&& other)
        {
            if (&other != this) {
                disconnectAll();
                slots = std::move(other.slots);
                other.slots.clear(); // make sure it forgets every slot
                forgot = other.forgot;
                for (slot_type *slot : slots)
                    slot->remember(this);
            }
            return *this;
        }

        template<typename... T>
        void trigger(T&&... args)
        {
            purge(); // removes forgotten entries.
            if (enabled) {
                stopping = false;
                for (const slot_type *slot : slots) {
                    slot->notify(std::forward<T>(args)...);
                    if (stopping)
                        break;
                }
            }
        }


        // Sane as trigger()
        template<typename... T>
        void operator()(T&&... args)
        {
            trigger(std::forward<T>(args)...);
        }


        // Convenient way to construct a Slot connected to this Signal.
        slot_type connect(callback_type callback)
        {
            return slot_type{*this, std::move(callback)};
        }

        // Convenient way to construct a Slot connected to this Signal.
        slot_type connectFirst(callback_type callback)
        {
            return slot_type{*this, std::move(callback), 0};
        }

        slot_type connectAt(callback_type callback, size_t idx)
        {
            return slot_type{*this, std::move(callback), idx};
        }

        slot_type connectBefore(callback_type callback, const slot_type& s)
        {
            return slot_type{*this, std::move(callback), indexOf(&s)};
        }


        void disconnectAll()
        {
            for (slot_type *slot : slots)
                if (slot)
                    slot->forget();
            slots.clear();
        }


        size_t size() const
        {
            return slots.size();
        }


        void enable()
        {
            enabled = true;
        }

        void disable()
        {
            enabled = false;
        }

        bool isEnabled() const
        {
            return enabled;
        }


        void stop()
        {
            stopping = true;
        }


        // Forbid copying.
        Signal(const Signal&) = delete;
        Signal& operator=(const Signal&) = delete;


        friend Slot<Args...>;
    };


    template<typename... Args>
    class Slot {
    public:
        using signal_type = Signal<Args...>;
        using callback_type = typename signal_type::callback_type;

    private:
        signal_type  *sig;
        callback_type callback;
        bool enabled = true;


        void remember(signal_type* s)
        {
            sig = s;
        }


        void forget()
        {
            sig = nullptr;
        }

    public:

        // Default constructor: not connected, no callback
        Slot() noexcept :
            sig{nullptr}
        {}


        /**
         * Normal constructor, connected to signal, and with callback
         */
        Slot(signal_type& s, callback_type func) :
            sig{&s},
            callback{std::move(func)}
        {
            sig->remember(this);
        }


        // Constructor, connected to signal, and with callback, at a specific index
        Slot(signal_type& s, callback_type func, size_t idx) :
            sig{&s},
            callback{std::move(func)}
        {
            sig->remember(this, idx);
        }


        // Move constructor
        Slot(Slot&& other) :
            sig{other.sig},
            callback{std::move(other.callback)},
            enabled{other.enabled}
        {
            if (sig) {
                size_t other_idx = other.index();
                other.disconnect();
                sig->remember(this, other_idx);
            }
        }


        // Move assignment
        Slot& operator=(Slot&& other)
        {
            if (this == &other)
                return *this;

            disconnect();
            sig = other.sig;

            if (sig) {
                size_t other_idx = other.index();
                other.disconnect();
                sig->remember(this, other_idx);
            }

            callback = std::move(other.callback);
            enabled = other.enabled;

            return *this;
        }


        ~Slot()
        {
            disconnect();
        }


        void disconnect()
        {
            if (sig)
                sig->forget(this);
            sig = nullptr;
        }


        // called by Signal
        template<typename... T>
        void notify(T&&... args) const
        {
            if (enabled)
                callback(std::forward<T>(args)...);
        }


        void enable()
        {
            enabled = true;
        }


        void disable()
        {
            enabled = false;
        }


        bool isEnabled() const
        {
            return enabled;
        }


        size_t index() const
        {
            if (!sig)
                throw std::logic_error{"Slot has no index because it's not connected"};
            return sig->indexOf(this);
        }


        // forbid copying
        Slot(const Slot&) = delete;
        Slot& operator=(const Slot&) = delete;


        friend class Signal<Args...>;
    };

}


#endif
