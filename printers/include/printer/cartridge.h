#ifndef MACSA_PRINTERS_CARTRIDGE_H
#define MACSA_PRINTERS_CARTRIDGE_H

#include "tij/datatypes.h"

namespace Macsa {
	namespace Printers {
		class Cartridge
		{
			public:
				Cartridge();
				~Cartridge();

				std::string id() const;
				void setId(const std::string &id);

				uint32_t columnDistance() const;
				void setColumnDistance(const uint32_t &columnDistance);

				uint32_t adjustedCapacity() const;
				void setAdjustedCapacity(const uint32_t &adjustedCapacity);

				double voltage() const;
				void setVoltage(double voltage);

				double pulseWarmingTemp() const;
				void setPulseWarmingTemp(double pulseWarmingTemp);

				double pulseWidth() const;
				void setPulseWidth(double pulseWidth);

				bool autoconfig() const;
				void setAutoconfig(bool autoconfig);

				bool pulseWarming() const;
				void setPulseWarming(bool pulseWarming);

				void clear();

				//Operators
				void operator =  (const Cartridge& other);
				bool operator == (const Cartridge& other) const {return equal(other);}
				bool operator != (const Cartridge& other) const {return !equal(other);}

			private:
				std::string	_id;
				uint32_t	_columnDistance;
				uint32_t	_adjustedCapacity;
				double		_voltage;
				double		_pulseWarmingTemp;
				double		_pulseWidth;
				bool		_autoconfig;
				bool		_pulseWarming;

				bool equal(const Cartridge& other) const;
		};
	}
}

#endif	//MACSA_PRINTERS_CARTRIDGE_H
