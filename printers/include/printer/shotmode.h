#ifndef SHOTMODE_CONFIG_H
#define SHOTMODE_CONFIG_H

#include <string>
#include <map>
#include <vector>
#include <stdint.h>
#include "datatypes.h"

/****************  ShotMode *****************
	Mode:
		0 for single shot.
		1 for multishot with relative delay.
		2 for multishot with absolute delay.
	Value: Number of prints for every trigger.
	Delays: Number of delays:
		In mode 0 is always 1.
		In mode 1 is always 2 (First delay is the delay for the first print, and the second one is the delay between prints).
		In mode 2 depends on number of prints (All the Delays are related to the trigger point).
	Repeat:
		true to print the same variable fields value for one trigger.
		false to update variable fields in the label between prints.
 ********************************************/
namespace Macsa {
	namespace Printers {
		class Delay
		{
			public:
				Delay(unsigned int	delay = 0, nDelayUnits units = nDelayUnits::UNITS_DOTS) {
					_delay = delay;
					_units = units;
				}
				unsigned int delay()const {return _delay;}
				DelayUnits units()	const {return _units;}
				bool operator == ( const Delay& other_ ) const { return  isEqual(other_); }
				bool operator != ( const Delay& other_ ) const { return !isEqual(other_); }

			private:
				uint32_t	_delay;
				DelayUnits	_units;

				bool isEqual( const Delay& other) const {return (_delay == other._delay && _units() == other._units());}
		};

		class ShotMode
		{
			public:
				ShotMode();
				ShotMode(ShootingMode mode, unsigned int numPrints, const std::vector<Delay>& delays, bool repeat);
				ShotMode(nShootingMode mode, unsigned int numPrints, const std::vector<Delay>& delays, bool repeat);

				ShootingMode mode() const;
				uint16_t numPrints() const;
				std::vector<Delay> delays() const;
				bool repeat() const;

				void clear();

				bool operator == (const ShotMode& other) const { return  equal(other); }
				bool operator != (const ShotMode& other) const { return !equal(other); }
				void operator = (const ShotMode& other);
#if __cplusplus >= 201103L
				using citDelay=std::vector<Delay>::const_iterator;
				using itDelay=std::vector<Delay>::iterator;
#else
				typedef std::vector<Delay>::const_iterator citDelay;
				typedef std::vector<Delay>::iterator itDelay;
#endif

			private:
				uint32_t	 _numPrints;
				ShootingMode _mode;
				std::vector<Delay> _delays;
				bool _repeat;

				inline void initByMode(nShootingMode mode, unsigned int numPrints, const std::vector<Delay>& delays, bool repeat);
				bool equal( const ShotMode& other_ ) const;
		};
	}
}

#endif
