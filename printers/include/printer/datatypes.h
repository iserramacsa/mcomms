#ifndef MACSA_PRINTERS_DATA_TYPES_H
#define MACSA_PRINTERS_DATA_TYPES_H

#include <cinttypes>
#include <string>
#include <stdint.h>

#define DIR_RIGHT_TO_LEFT	"RL"
#define DIR_LEFT_TO_RIGHT	"LR"
#define DIR_AUTO			"AUTO"

#define SHOOTING_MODE_ONCE	"SingleShot"
#define SHOOTING_MODE_REL	"MultiShotRelative"
#define SHOOTING_MODE_ABS	"MultiShotAbsolute"

#define NOZZLES_COL_A		"COL_A"
#define NOZZLES_COL_B		"COL_B"
#define NOZZLES_COL_BOTH	"BOTH"

#define ENCODER_MODE_FIXED		"FixedSpeed"
#define ENCODER_MODE_INTERNAL	"Internal"
#define ENCODER_MODE_EXTERNAL	"External"

#define PHOTOCELL_A		"FTC1"
#define PHOTOCELL_B		"FTC2"
#define PHOTOCELL_EXT	"FTCEXT"

#define INPUT_MODE_EDGE		"Edge"
#define INPUT_MODE_STATE	"State"

#define OUTPUT_TYPE_STATE		"State"
#define OUTPUT_TYPE_ONPULSE		"OnPulse"
#define OUTPUT_TYPE_OFFPULSE	"OffPulse"
#define OUTPUT_TYPE_MAXON		"MaxOn"
#define OUTPUT_TYPE_MAXOFF		"MaxOff"

#define BCD_MODE_USER   "USER_MODE"
#define BCD_MODE_BCD_1  "BCD_MODE_1"
#define BCD_MODE_BCD_2  "BCD_MODE_2"

#define DELAY_UNIT_MM	"mm"
#define DELAY_UNIT_DOTS	"dts"

namespace Macsa {
	namespace Printers {

		class BCDMode
		{
			public:
				enum N{
					USER_MODE = 0,
					BCD_MODE_1,
					BCD_MODE_2
				};
				enum N operator()() const {return _val;}
				bool operator == (const BCDMode& other) const {return _val == other._val;}
				bool operator != (const BCDMode& other) const {return _val != other._val;}
				void operator = (const BCDMode& other){_val = other._val;}
				void operator = (enum N v){_val = v;}
				void operator = (const std::string& val){
					if (val.compare(BCD_MODE_USER) == 0)
						_val = USER_MODE;
					else if (val.compare(BCD_MODE_BCD_1) == 0)
						_val = BCD_MODE_1;
					else if (val.compare(BCD_MODE_BCD_2) == 0)
						_val = BCD_MODE_2;
				}
				std::string toString() const {
					switch (_val) {
						case USER_MODE:  return BCD_MODE_USER;
						case BCD_MODE_1: return BCD_MODE_BCD_1;
						case BCD_MODE_2: return BCD_MODE_BCD_2;
					}
				}
			private:
				N _val;
		};

		class PrinterDir
		{
			public:
				enum N{
					R2L = 0,    //Right to Left
					L2R,        //Left to Right
					AUTO        //Input depends
				};
				enum N operator()() const {return _val;}
				bool operator == (const PrinterDir& other) const {return _val == other._val;}
				bool operator != (const PrinterDir& other) const {return _val != other._val;}
				void operator = (const PrinterDir& other){_val = other._val;}
				void operator = (enum N v){_val = v;}
				void operator = (const std::string& val){
					if (val.compare(DIR_RIGHT_TO_LEFT) == 0)
						_val = R2L;
					else if (val.compare(DIR_RIGHT_TO_LEFT) == 0)
						_val = L2R;
					else if (val.compare(DIR_RIGHT_TO_LEFT) == 0)
						_val = AUTO;
				}
				std::string toString() const {
					switch (_val) {
						case R2L:  return DIR_RIGHT_TO_LEFT;
						case L2R:  return DIR_LEFT_TO_RIGHT;
						case AUTO: return DIR_AUTO;
					}
				}
			private:
				N _val;
		};

		class ShootingMode
		{
			public:
				enum N{
					SINGLE_SHOT = 0, // for single shot.
					MULTI_SHOT_REL,  // for multishot with relative delay.
					MULTI_SHOT_ABS   // for multishot with absolute delay.
				};
				enum N operator()() const {return _val;}
				bool operator == (const ShootingMode& other) const {return _val == other._val;}
				bool operator != (const ShootingMode& other) const {return _val != other._val;}
				void operator = (const ShootingMode& other){_val = other._val;}
				void operator = (enum N v){_val = v;}
				void operator = (const std::string& val){
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
				}
			private:
				N _val;
		};

		class NozzlesCol
		{
			public:
				enum N{
					COL_A = 0,  //Column A
					COL_B,      //Column B
					COL_BOTH    //Both
				};
				enum N operator()() const {return _val;}
				bool operator == (const NozzlesCol& other) const {return _val == other._val;}
				bool operator != (const NozzlesCol& other) const {return _val != other._val;}
				void operator = (const NozzlesCol& other){_val = other._val;}
				void operator = (enum N v){_val = v;}
				void operator = (const std::string& val){
					if (val.compare(NOZZLES_COL_A) == 0)
						_val = COL_A;
					else if (val.compare(NOZZLES_COL_B) == 0)
						_val = COL_B;
					else if (val.compare(NOZZLES_COL_BOTH) == 0)
						_val = COL_BOTH;
				}
				std::string toString() const {
					switch (_val) {
						case COL_A:		return NOZZLES_COL_A;
						case COL_B:		return NOZZLES_COL_B;
						case COL_BOTH:	return NOZZLES_COL_BOTH;
					}
				}
			private:
				N _val;
		};

		class DelayUnits {
			public:
				enum N {
					UNITS_MM = 0,
					UNITS_DOTS,
				};
				enum N operator()() const {return _val;}
				bool operator == (const DelayUnits& other) const {return _val == other._val;}
				bool operator != (const DelayUnits& other) const {return _val != other._val;}
				void operator = (const DelayUnits& other){_val = other._val;}
				void operator = (enum N v){_val = v;}
				void operator = (const std::string& v) {
					if (v.compare(DELAY_UNIT_MM) == 0)
						_val = UNITS_MM;
					else if (v.compare(DELAY_UNIT_DOTS) == 0)
						_val = UNITS_DOTS;
				}
				std::string toString() const {
					switch (_val) {
						case UNITS_MM:	 return DELAY_UNIT_MM;
						case UNITS_DOTS: return DELAY_UNIT_DOTS;
					}
				}
			private:
				N _val;
		};

		class EncoderMode
		{
			public:
				enum N{
					FIXED_SPEED = 0,
					INTERNAL_ENCODER,
					EXTERNAL_ENCODER
				};
				enum N operator()() const {return _val;}
				bool operator == (const EncoderMode& other) const {return _val == other._val;}
				bool operator != (const EncoderMode& other) const {return _val != other._val;}
				void operator = (const EncoderMode& other){_val = other._val;}
				void operator = (enum N v){_val = v;}
				void operator = (const std::string& val){
					if (val.compare(ENCODER_MODE_FIXED) == 0)
						_val = FIXED_SPEED;
					else if (val.compare(ENCODER_MODE_INTERNAL) == 0)
						_val = INTERNAL_ENCODER;
					else if (val.compare(ENCODER_MODE_EXTERNAL) == 0)
						_val = EXTERNAL_ENCODER;
				}
				std::string toString() const {
					switch (_val) {
						case FIXED_SPEED:		return ENCODER_MODE_FIXED;
						case INTERNAL_ENCODER:	return ENCODER_MODE_INTERNAL;
						case EXTERNAL_ENCODER:	return ENCODER_MODE_EXTERNAL;
					}
				}
			private:
				N _val;
		};

		class Photocell
		{
			public:
				enum N{
					PHCELL_A = 0,	//Photocell of column A
					PHCELL_B,		//Photocell of column B
					PHCELL_EXT,		//External photocell
				};
				enum N operator()() const {return _val;}
				bool operator == (const Photocell& other) const {return _val == other._val;}
				bool operator != (const Photocell& other) const {return _val != other._val;}
				void operator = (const Photocell& other){_val = other._val;}
				void operator = (enum N v){_val = v;}
				void operator = (const std::string& val){
					if (val.compare(PHOTOCELL_A) == 0)
						_val = PHCELL_A;
					else if (val.compare(PHOTOCELL_B) == 0)
						_val = PHCELL_B;
					else if (val.compare(PHOTOCELL_EXT) == 0)
						_val = PHCELL_EXT;
				}
				std::string toString() const {
					switch (_val) {
						case PHCELL_A:	 return PHOTOCELL_A;
						case PHCELL_B:	 return PHOTOCELL_B;
						case PHCELL_EXT: return PHOTOCELL_EXT;
					}
				}
			private:
				N _val;
		};

		class InputMode
		{
			public:
				enum N {
					INPUT_EDGE = 0,
					INPUT_STATUS
				};
				enum N operator()() const {return _val;}
				bool operator == (const InputMode& other) const {return _val == other._val;}
				bool operator != (const InputMode& other) const {return _val != other._val;}
				void operator = (const InputMode& other){_val = other._val;}
				void operator = (enum N v){_val = v;}
				void operator = (const std::string& val){
					if (val.compare(INPUT_MODE_EDGE) == 0)
						_val = INPUT_EDGE;
					else if (val.compare(INPUT_MODE_STATE) == 0)
						_val = INPUT_STATUS;
				}
				std::string toString() const {
					switch (_val) {
						case INPUT_EDGE:	 return INPUT_MODE_EDGE;
						case INPUT_STATUS:	 return INPUT_MODE_STATE;
					}
				}
			private:
				N _val;
		};


		class OutputType
		{
			public:
				enum N {
					OUTPUT_STATE = 0,	// Set the output state. The output remain in this state until the state would be changed.
										//		The TIME configuration is not taken into consideration.
					OUTPUT_ONPULSE,		// The output change the state to ON, waits the time specified and return to OFF.
					OUTPUT_OFFPULSE,	// The output change the state to OFF, waits the time specified and return to ON.
					OUTPUT_MAXON,		// The behaviour is the same as the 'State' type,
										//		except the electronics takes the time as maximum to mantain the output in ON state,
										//		afterwards the output returns to OFF.
					OUTPUT_MAXOFF		//	The behaviour is the same as the 'State' type,
										//		except the electronics takes the time as maximum to mantain the output in OFF state
										//		afterwards the output returns to ON.
				};
				enum N operator()() const {return _val;}
				bool operator == (const OutputType& other) const {return _val == other._val;}
				bool operator != (const OutputType& other) const {return _val != other._val;}
				void operator = (const OutputType& other){_val = other._val;}
				void operator = (enum N v){_val = v;}
				void operator = (const std::string& val){
					if (val.compare(OUTPUT_TYPE_STATE   ) == 0)
						_val = OUTPUT_STATE;
					else if (val.compare(OUTPUT_TYPE_ONPULSE ) == 0)
						_val = OUTPUT_ONPULSE;
					else if (val.compare(OUTPUT_TYPE_OFFPULSE) == 0)
						_val = OUTPUT_OFFPULSE;
					else if (val.compare(OUTPUT_TYPE_MAXON   ) == 0)
						_val = OUTPUT_MAXON;
					else if (val.compare(OUTPUT_TYPE_MAXOFF  ) == 0)
						_val = OUTPUT_MAXOFF;
				}
				std::string toString() const {
					switch (_val) {
						case OUTPUT_STATE:		return OUTPUT_TYPE_STATE;
						case OUTPUT_ONPULSE:	return OUTPUT_TYPE_ONPULSE;
						case OUTPUT_OFFPULSE:	return OUTPUT_TYPE_OFFPULSE;
						case OUTPUT_MAXON:		return OUTPUT_TYPE_MAXON;
						case OUTPUT_MAXOFF:		return OUTPUT_TYPE_MAXOFF;
					}
				}
			private:
				N _val;
		};

		enum LoggerLevel {
			LOG_ERROR=0,
			LOG_WARNING,
			LOG_INFO,
			LOG_DEBUG,
			LOG_DISABLED
		};


	}
}


#endif
