#ifndef PRINTER_TYPES_H
#define PRINTER_TYPES_H

#include <cinttypes>

namespace Macsa {
	namespace Printers {

		enum PrinterDir_n{
			R2L = 0,    //Right to Left
			L2R,        //Left to Right
			AUTO        //Input depends
		};

		enum NozzlesCol_n {
			COL_A = 0,  //Column A
			COL_B,      //Column B
			COL_BOTH    //Both
		};

		enum EncoderMode_n {
			FIXED_SPEED = 0,
			INTERNAL_ENCODER,
			EXTERNAL_ENCODER
		};

		struct Encoder_t {
			EncoderMode_n mode;
			double fixedSpeed;
			double resolution;
			double diameter;
		};

		enum Photocell_n {
			PHCELL_A = 0,	//Photocell of column A
			PHCELL_B,		//Photocell of column B
			PHCELL_EXT,		//External photocell
		};

		enum InputMode_n {
			INPUT_EDGE = 0,
			INPUT_STATUS
		};
		enum OutputType_n {
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
	}
}


#endif
