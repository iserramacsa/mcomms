#ifndef MACSA_UTILS_OBSERVER_H
#define MACSA_UTILS_OBSERVER_H

#include <vector>
#include <functional>
#include <algorithm>
#include <thread>

//#include <iostream> //Debug


namespace Macsa {
	namespace Utils {
		static unsigned idSeed = 0;
		template <class T> class Notifier;
		template <class T>
		class Observer
		{
			public:
				Observer(Notifier<T>* target) :
					_id(idSeed++),
					_target(target)
				{
					if (_target != nullptr) {
						_target->attach(static_cast<T*>(this));
					}
				}

				virtual ~Observer() {
					if (_target != nullptr) {
						_target->detach(static_cast<T*>(this));
					}
				}

				inline unsigned id() const{ return _id;}

				inline void notifierDestroyed(){ _target = nullptr;}
				virtual inline bool operator == (const Observer& other) const { return (_id == other._id);}
				virtual inline bool operator != (const Observer& other) const { return (_id != other._id);}

			private:
				const unsigned _id;
				Notifier<T>* _target;
		};

		template<class T>
		class Notifier
		{
			public:
				Notifier(){}
				virtual ~Notifier(){ /*notifyDestruction();*/ }
				inline void attach(T* observer)
				{
					if (observer && !exist(observer)) {
//						std::cout << __func__ << " Observer: " << observer->id() << std::endl;
						_observers.push_back(observer);
					}
				}

				inline void detach(T* observer)
				{
					typename std::vector<T*>::const_iterator ob = find(observer);
					if  (ob != _observers.end()) {
//						std::cout << __func__ << " Observer: " << observer->id() << std::endl;
						_observers.erase(ob);
					}
				}

			protected:
				std::vector<T*> _observers;

				template<typename... Args>
				void notifyObservers(std::function<void(T*, const Args& ... )>&callback,  const Args&... arg)
				{
					for (typename std::vector<T*>::iterator ob = _observers.begin(); ob != _observers.end(); ob++)
					{
//						std::cout << "Th: " << std::this_thread::get_id() << " " << __func__ << std::endl;
						std::function<void(const Args&...)> cb = std::bind(callback, (*ob), arg...);
						std::thread t(cb, arg...);
						t.detach();
					}
				}

				inline void notifyDestruction()
				{
					for (typename std::vector<T*>::iterator ob = _observers.begin(); ob != _observers.end(); ob++)
					{
						dynamic_cast<Observer<T> *>((*ob))->notifierDestroyed();
					}
				}

				inline bool exist(const T* observer) const {return (find(observer) != _observers.end());}
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

			private:
				Notifier(const Notifier&){}

		};
	}
}

#endif //MACSA_UTILS_OBSERVER_H
