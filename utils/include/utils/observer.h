#ifndef MACSA_UTILS_OBSERVER_H
#define MACSA_UTILS_OBSERVER_H

/**
 * @brief The Notifier-Observer classes, is a pair of classes that work together in order
 * to notify events between objects.
 *    ______________          ______________
 *   |              |1      n|              |
 *   |   Notifier   |<>------|   Observer   |
 *   |______________|        |______________|
 *
 */

#include <vector>
#include <functional>
#include <algorithm>
#include <thread>

namespace Macsa {
	namespace Utils {
		static unsigned idSeed = 0;
		template <class T> class Notifier;
		///
		/// \brief The Observer class. The observer class is the dependent part of this pair of classes.
		/// During the construction of the class, a pointer to a Notifier of this kind of observers has to
		/// be passed as a parameter.
		/// This class is the base of all the observers of the code.
		///
		template <class T>
		class Observer
		{
			public:
				///
				/// \brief Observer. Observer constructor
				/// \param target. Pointer to the Notifier of this kind of observer
				///
				Observer(Notifier<T>* target) :
					_id(idSeed++),
					_target(target)
				{
					if (_target != nullptr) {
						_target->attach(static_cast<T*>(this));
					}
				}
				///
				/// \brief ~Observer. Observer destructor, calls to notifier to detach this observer
				///
				virtual ~Observer() {
					if (_target != nullptr) {
						_target->detach(static_cast<T*>(this));
					}
				}
				///
				/// \brief id. Unique identifier of the observer
				///
				inline unsigned id() const{ return _id;}
				///
				/// \brief notifierDestroyed. Function called by notifier if it's destroyed
				/// to avoid detaching from dereferenced notifier
				///
				inline void notifierDestroyed(){ _target = nullptr;}
				///
				/// \brief Comparision operator
				/// \param other. Reference to another observer
				/// \return true if observer is equal than this, otherwise return false
				///
				virtual inline bool operator == (const Observer& other) const { return (_id == other._id);}
				///
				/// \brief Comparision operator
				/// \param other. Reference to another observer
				/// \return true if observer is NOT equal than this, otherwise return false
				///
				virtual inline bool operator != (const Observer& other) const { return (_id != other._id);}

			private:
				///
				/// \brief Unique identifier of the implemented object
				///
				const unsigned _id;
				///
				/// \brief Reference to the notifier to attach/detach
				///
				Notifier<T>* _target;
		};

		///
		/// \brief The Notifier class is the independent part of this pair of classes.
		/// This class has the algorithm needed to notify any kind of observers defined by T.
		/// This class is the base of all the notifiers of the code.
		///
		template<class T>
		class Notifier
		{
			public:
				///
				/// \brief Notifier constructor. Default constructor
				///
				Notifier(){}

				///
				/// \brief Notifier destructor. Notifies to the attached observer than
				/// the notifier will be destroyed
				///
				virtual ~Notifier(){ notifyDestruction(); }

				///
				/// \brief Attach the observer to this object, if is not attached yet.
				/// \param observer to attach.
				///
				inline void attach(T* observer)
				{
					if (observer && !exist(observer)) {
						_observers.push_back(observer);
					}
				}

				///
				/// \brief Detach the observer from this object, if exist.
				/// \param observer to detach.
				///
				inline void detach(T* observer)
				{
#ifdef ARMSTONE_A9
					typename std::vector<T*>::iterator ob  = find(observer);
#else
					typename std::vector<T*>::const_iterator ob  = find(observer);
#endif
					if (ob != _observers.end()) {
						_observers.erase(ob);
					}
				}

			protected:
				///
				/// \brief _observers. List of the attached observers.
				///
				std::vector<T*> _observers;

				///
				/// \brief notifyObservers. Main function to notify all the attached observers.
				/// This method allows to call all kind of callbacks of type <void(const Args& ...)> in the
				/// observer's specialization (T). This method creates and detaches one thread for any observer
				/// attached and runs the callback in this thread.
				/// \param callback. Reference to a function member of the observer T.
				/// \param arg. List of arguments reference to pass to the callback.
				///
				template<typename... Args>
				void notifyObservers(std::function<void(T*, const Args& ... )>&callback,  const Args&... arg)
				{
					for (typename std::vector<T*>::iterator ob = _observers.begin(); ob != _observers.end(); ob++)
					{
						std::function<void(const Args&...)> cb = std::bind(callback, (*ob), arg...);
						std::thread t(cb, arg...);
						t.detach();
					}
				}

				///
				/// \brief notifyDestruction. Notifies to the attached observer that this notifies will be destroyed
				///
				inline void notifyDestruction()
				{
					for (typename std::vector<T*>::const_iterator ob = _observers.begin(); ob != _observers.end(); ob++)
					{
						T* observer = (*ob);
						reinterpret_cast<Observer<T> *>(observer)->notifierDestroyed(); //dynamic_cast<Observer<T> *>()
					}
				}
				///
				/// \brief exist. Check if the passed observer is already in the list.
				/// \param observer. Pointer to an observer to check if exist.
				/// \return True if the observer was found in the list, false if not
				///
				inline bool exist(const T* observer) const {return (find(observer) != _observers.end());}
				///
				/// \brief find. Helper method. Looks for an observer in the member list
				/// and returns a const iterator to this observer if was found
				/// \param target. Pointer to an observer
				/// \return const iterator to _observer list if is found, otherwise return end iterator
				///
				inline typename std::vector<T*>::const_iterator find(const T * target) const {
					auto predicate = [&](T* observer) {
						bool found = false;
						if (target != nullptr && observer != nullptr) {
							found = ((*target) == (*observer));
						}
						return found;
					};
					return  find_if(_observers.begin(), _observers.end(), predicate);
				}
#ifdef ARMSTONE_A9
				//Normal iterator implementation required by GCC 4.7.2
				inline typename std::vector<T*>::iterator find(const T * target) {
					auto predicate = [&](T* observer) {
						bool found = false;
						if (target != nullptr && observer != nullptr) {
							found = ((*target) == (*observer));
						}
						return found;
					};
					return  find_if(_observers.begin(), _observers.end(), predicate);
				}
#endif

			private:
				Notifier(const Notifier&){} //Hides the copy constructor

		};
	}
}

#endif //MACSA_UTILS_OBSERVER_H
