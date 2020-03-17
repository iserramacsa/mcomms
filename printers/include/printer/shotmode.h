#ifndef SHOTMODE_CONFIG_H
#define SHOTMODE_CONFIG_H

#include <string>
#include <map>
#include <vector>
#include <stdint.h>
#include "utils/smartenum.h"

#define SHOOTING_MODE_ONCE	"SingleShot"
#define SHOOTING_MODE_REL	"MultiShotRelative"
#define SHOOTING_MODE_ABS	"MultiShotAbsolute"

#define DELAY_UNIT_MM	"mm"
#define DELAY_UNIT_DOTS	"dts"

namespace Macsa {
	namespace Printers {

		enum nDelayUnits {
			UNITS_MM = 0,
			UNITS_DOTS,
		};
		class DelayUnits : public Utils::SmartEnum<nDelayUnits>
		{
			public:
				DelayUnits() {_val = UNITS_DOTS;}
				virtual void operator = (const enum nDelayUnits& v){_val = v;}
				virtual void operator = (const std::string& v) {
					if (v.compare(DELAY_UNIT_MM) == 0)
						_val = UNITS_MM;
					else if (v.compare(DELAY_UNIT_DOTS) == 0)
						_val = UNITS_DOTS;
				}
				virtual std::string toString() const {
					switch (_val) {
						case UNITS_MM:	 return DELAY_UNIT_MM;
						case UNITS_DOTS: return DELAY_UNIT_DOTS;
					}
					return "";
				}

				virtual std::vector<std::string> stringList() const
				{
					std::vector<std::string> list;
					list.push_back(DELAY_UNIT_MM);
					list.push_back(DELAY_UNIT_DOTS);
					return list;
				}
		};

		enum nShootingMode{
			SINGLE_SHOT = 0, // for single shot.
			MULTI_SHOT_REL,  // for multishot with relative delay.
			MULTI_SHOT_ABS   // for multishot with absolute delay.
		};
		class ShootingMode : public Utils::SmartEnum<nShootingMode>
		{
			public:
				ShootingMode() : SmartEnum() {_val = SINGLE_SHOT;}
				virtual void operator = (const enum nShootingMode& v){_val = v;}
				virtual void operator = (const std::string& val){
					if (val.compare(SHOOTING_MODE_ONCE) == 0)
						_val = SINGLE_SHOT;
					else if (val.compare(SHOOTING_MODE_REL) == 0)
						_val = MULTI_SHOT_REL;
					else if (val.compare(SHOOTING_MODE_ABS) == 0)
						_val = MULTI_SHOT_ABS;
				}
				std::string toString() const {
					switch (_val) {
						case SINGLE_SHOT:		return SHOOTING_MODE_ONCE;
						case MULTI_SHOT_REL:	return SHOOTING_MODE_REL;
						case MULTI_SHOT_ABS:	return SHOOTING_MODE_ABS;
					}
					return "";
				}

				virtual std::vector<std::string> stringList() const
				{
					std::vector<std::string> list;
					list.push_back(SHOOTING_MODE_ONCE);
					list.push_back(SHOOTING_MODE_REL);
					list.push_back(SHOOTING_MODE_ABS);
					return list;
				}
		};

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
