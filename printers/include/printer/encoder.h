#ifndef MACSA_PRINTERS_ENCODER_H
#define MACSA_PRINTERS_ENCODER_H

#include "datatypes.h"

namespace Macsa {
	namespace Printers {
		class Encoder
		{
			public:
				Encoder();					//Constructor to set internal encoder by default
				Encoder(double fixedspeed); //Constructor to set fixed speed by default
				Encoder(double resolution, double diameter); //Constructor to set external encoder by default
				~Encoder();

				EncoderMode mode() const;
				void setMode(const EncoderMode &value);

				double fixedSpeed() const;
				void setFixedSpeed(double value);

				double resolution() const;
				void setResolution(double value);

				double diameter() const;
				void setDiameter(double value);

				void clear();

				//Operators
				void operator = (const Encoder& other);
				bool operator == (const Encoder& other) const {return equal(other);}
				bool operator != (const Encoder& other) const {return !equal(other);}

			private:
				EncoderMode _mode;
				double _fixedSpeed;
				double _resolution;
				double _diameter;
				bool equal(const Encoder& other) const;
		};
	}
}

#endif	//MACSA_PRINTERS_STATUS_H
