#ifndef MACSA_PRINTERS_ENCODER_H
#define MACSA_PRINTERS_ENCODER_H

#include "utils/smartenum.h"

#define ENCODER_MODE_FIXED		"FixedSpeed"
#define ENCODER_MODE_INTERNAL	"Internal"
#define ENCODER_MODE_EXTERNAL	"External"

namespace Macsa {
	namespace Printers {

		enum nEncoderMode{
			FIXED_SPEED = 0,
			INTERNAL_ENCODER,
			EXTERNAL_ENCODER
		};
		class EncoderMode : public Utils::SmartEnum<nEncoderMode>
		{
			public:
				EncoderMode() { _val = FIXED_SPEED; }
				EncoderMode(const std::string& val){*this = val;}
				EncoderMode(const EncoderMode& val){*this = val;}
				virtual nEncoderMode operator = (const enum nEncoderMode& v){_val = v; return _val;}
				virtual nEncoderMode operator = (const std::string& val){
					if (val.compare(ENCODER_MODE_FIXED) == 0)
						_val = FIXED_SPEED;
					else if (val.compare(ENCODER_MODE_INTERNAL) == 0)
						_val = INTERNAL_ENCODER;
					else if (val.compare(ENCODER_MODE_EXTERNAL) == 0)
						_val = EXTERNAL_ENCODER;
					return _val;
				}
				std::string toString() const {
					switch (_val) {
						case FIXED_SPEED:		return ENCODER_MODE_FIXED;
						case INTERNAL_ENCODER:	return ENCODER_MODE_INTERNAL;
						case EXTERNAL_ENCODER:	return ENCODER_MODE_EXTERNAL;
					}
					return "";
				}

				virtual std::vector<std::string> stringList() const
				{
					std::vector<std::string> list;
					list.push_back(ENCODER_MODE_FIXED);
					list.push_back(ENCODER_MODE_INTERNAL);
					list.push_back(ENCODER_MODE_EXTERNAL);
					return list;
				}
		};

		class Encoder
		{
			public:
				Encoder();					//Constructor to set internal encoder by default
				Encoder(double fixedspeed); //Constructor to set fixed speed by default
				Encoder(double resolution, double diameter, double abcPitch = 0); //Constructor to set external encoder by default
				~Encoder();

				inline EncoderMode mode() const { return _mode;}
				inline void setMode(const EncoderMode &value) { _mode = value;}
				inline void setMode(const nEncoderMode &value) { _mode = value;}
				inline void setMode(const std::string &value) { _mode = value;}

				inline double fixedSpeed() const { return _fixedSpeed;}
				inline void setFixedSpeed(double value) { _fixedSpeed = value; }

				inline double resolution() const { return _resolution; }
				inline void setResolution(double value) { _resolution = value; }

				inline double diameter() const { return _diameter; }
				inline void setDiameter(double value) { _diameter = value; }

				inline double abcPitch() const { return _abcPitch; }
				inline void setAbcPitch(double abcPitch) { _abcPitch = abcPitch; }

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
				double _abcPitch;

				bool equal(const Encoder& other) const;
		};
	}
}

#endif	//MACSA_PRINTERS_ENCODER_H
