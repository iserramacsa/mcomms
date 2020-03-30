#ifndef MACSA_TIJ_PRINTER_DATA_TYPES_H
#define MACSA_TIJ_PRINTER_DATA_TYPES_H

#include "utils/smartenum.h"

//#ifndef UNKNOWN
//#define UNKNOWN				"Unknown"
//#endif

#define DIR_RIGHT_TO_LEFT	"RL"
#define DIR_LEFT_TO_RIGHT	"LR"
#define DIR_AUTO			"AUTO"

#define NOZZLES_COL_A		"COL_A"
#define NOZZLES_COL_B		"COL_B"
#define NOZZLES_COL_BOTH	"COL_BOTH"

#define PHOTOCELL_A		"FTC1"
#define PHOTOCELL_B		"FTC2"
#define PHOTOCELL_EXT	"FTCEXT"

#define INPUT_MODE_EDGE		"Edge"
#define INPUT_MODE_STATE	"State"

#define BOARD_TYPE_PRINTHEAD	"PH"
#define BOARD_TYPE_SIGNAL		"SIGNAL"

#define OUTPUT_TYPE_STATE		"State"
#define OUTPUT_TYPE_ONPULSE		"OnPulse"
#define OUTPUT_TYPE_OFFPULSE	"OffPulse"
#define OUTPUT_TYPE_MAXON		"MaxOn"
#define OUTPUT_TYPE_MAXOFF		"MaxOff"

#define BCD_MODE_USER   "Mode0"
#define BCD_MODE_BCD_1  "Mode1"
#define BCD_MODE_BCD_2  "Mode2"

#define ERROR_TYPE_INFO		"Information"
#define ERROR_TYPE_WARN		"Warning"
#define ERROR_TYPE_ERR		"Error"
#define ERROR_TYPE_INVALID	"Invalid"

#define ERROR_CODE_SUCCCESS							"SUCCESS"
#define ERROR_CODE_FILEOT_FOUND						"FILE.NOT_FOUND"
#define ERROR_CODE_FILE_ALREADY_EXIST				"FILE.ALREADY_EXIST"
#define ERROR_CODE_FILE_COPY_FAIL					"FILE.COPY_FAIL"
#define ERROR_CODE_FILE_DELETE_FAIL					"FILE.DELETE_FAIL"
#define ERROR_CODE_FILE_MOVE_FAIL					"FILE.MOVE_FAIL"
#define ERROR_CODE_FILE_MOVE_INCOMPLETED			"FILE.MOVE_INCOMPLETE"
#define ERROR_CODE_FILE_READ_FAIL					"FILE.READ_CANOT"
#define ERROR_CODE_FILE_WRITE_FAIL					"FILE.WRITE_CANOT"
#define ERROR_CODE_FILE_WRITE_INCOMPLETED			"FILE.WRITE_INCOMPLETE"
#define ERROR_CODE_FILE_USER_DATAOT_FOUND			"FILE.USER_DATAOT_FOUND"
#define ERROR_CODE_FILE_IN_USE						"FILE.IN_USE"
#define ERROR_CODE_PARAM_BOARD_IDOT_FOUND			"PARAM.BOARD_IDOT_FOUND"
#define ERROR_CODE_PARAM_COUNTER_IDOT_FOUND		    "PARAM.COUNTER_IDOT_FOUND"
#define ERROR_CODE_PARAM_COUNTER_VALUE_REJECTED		"PARAM.COUNTER_VALUE_REJECTED"
#define ERROR_CODE_PARAM_OUTPUT_IDOT_FOUND		    "PARAM.OUTPUT_IDOT_FOUND"
#define ERROR_CODE_PARAM_BCD_INVALID_MODE			"PARAM.CANT_SET_MSG_IN_BCD_MODE"
#define ERROR_CODE_PARAM_BOARD_IS_ENABLED			"PARAM.BOARD_IS_ENABLED"
#define ERROR_CODE_PARAM_BOARD_IS_DISABLED			"PARAM.BOARD_ISOT_ENABLED"
#define ERROR_CODE_PARAM_CHANGE_ADAPTER_FAILS		"PARAM.CANNOT_CHANGE_ADAPTER"
#define ERROR_CODE_PARAM_INVALID_IP_ADDRESS			"PARAM.INVALID_IP_ADDRESS"
#define ERROR_CODE_PARAM_INVALID_MASK_ADDRESS		"PARAM.INVALID_MASK_ADDRESS"
#define ERROR_CODE_PARAM_INVALID_GATEWAY_ADDRESS	"PARAM.INVALID_GATEWAY_ADDRESS"
#define ERROR_CODE_PARAM_INVALID_PROP_COUNT			"PARAM.INVALID_PROP_COUNT"
#define ERROR_CODE_GENERIC_UNEXPECTED_TAG			"GEN.UNEXPECTED_TAG"
#define ERROR_CODE_GENERICOT_IMPLEMENTED			"GEN.NOT_IMPLEMENTED"
#define ERROR_CODE_GENERIC_LOCK_TIMEOUT				"GEN.LOCK_TIMEOUT"
#define ERROR_CODE_PH_PCAOT_DETECTED				"PCA.NOTDETECTED"
#define ERROR_CODE_PH_OVERTEMP						"PH.OVERTEMP"
#define ERROR_CODE_PH_OVERSPEED						"GEN.OVERSPEED"
#define ERROR_CODE_MSG_FORMAT_ERROR					"MSG.FORMATERROR"
#define ERROR_CODE_MSGOEXIST						"MSG.NOEXIST"
#define ERROR_CODE_PHO_CARTRIDGE					"PH.NOCARTRIDGE"
#define ERROR_CODE_PH_SC_INVALID					"SMC.INVALID"
#define ERROR_CODE_PH_GENERIC_FAULT					"PH.GENFAULT"
#define ERROR_CODE_PH_SC_CARTRIDGE_EMPTY			"SMC.CARTRIDGE_EMPTY"
#define ERROR_CODE_PH_SC_CARTRIDGE_OUT_OF_DATE		"SMC.CARTRIDGE_OUTOFDATE"
#define ERROR_CODE_PH_SC_CARTRIDGEEAR_END			"SMC.CARTRIDGEEAREND"
#define ERROR_CODE_PH_SC_UNRECOGNIZED_DATA			"SMC.UNRECOGNIZED_DATA"
#define ERROR_CODE_PH_SC_INITIALIZING				"PH.INITIALIZING_CARTRIDGE"
#define ERROR_CODE_PH_SC_HOST_SMARTCARD_FAIL		"SMC.HOST_SMARTCARD"
#define ERROR_CODE_UNKNOWN							"UNKNOWN"

#define LOG_LEVEL_ERROR		"Errors"
#define LOG_LEVEL_WARNING	"Warnings"
#define LOG_LEVEL_INFO		"Info"
#define LOG_LEVEL_DEBUG		"Debug"
#define LOG_LEVEL_DISABLED	"Disabled"

namespace Macsa {
	namespace Printers {
		enum nBCDMode{
			USER_MODE = 0,
			BCD_MODE_1,
			BCD_MODE_2
		};
		class BCDMode : public Utils::SmartEnum<nBCDMode>
		{
			public:
				virtual void operator = (const enum nBCDMode& v){_val = v;}
				virtual void operator = (const std::string& val){
					if (val.compare(BCD_MODE_USER) == 0)
						_val = USER_MODE;
					else if (val.compare(BCD_MODE_BCD_1) == 0)
						_val = BCD_MODE_1;
					else if (val.compare(BCD_MODE_BCD_2) == 0)
						_val = BCD_MODE_2;
				}

				virtual std::string toString() const {
					switch (_val) {
						case USER_MODE:  return BCD_MODE_USER;
						case BCD_MODE_1: return BCD_MODE_BCD_1;
						case BCD_MODE_2: return BCD_MODE_BCD_2;
					}
					return "";
				}

				virtual std::vector<std::string> stringList() const
				{
					std::vector<std::string> list;
					list.push_back(BCD_MODE_USER);
					list.push_back(BCD_MODE_BCD_1);
					list.push_back(BCD_MODE_BCD_2);
					return list;
				}
		};

		enum nPrinterDir{
			R2L = 0,    //Right to Left
			L2R,        //Left to Right
			AUTO        //Input depends
		};
		class PrinterDir : public Utils::SmartEnum<nPrinterDir>
		{
			public:
				virtual void operator = (const enum nPrinterDir& v){_val = v;}
				virtual void operator = (const std::string& val){
					if (val.compare(DIR_RIGHT_TO_LEFT) == 0)
						_val = R2L;
					else if (val.compare(DIR_RIGHT_TO_LEFT) == 0)
						_val = L2R;
					else if (val.compare(DIR_RIGHT_TO_LEFT) == 0)
						_val = AUTO;
				}
				virtual std::string toString() const {
					switch (_val) {
						case R2L:  return DIR_RIGHT_TO_LEFT;
						case L2R:  return DIR_LEFT_TO_RIGHT;
						case AUTO: return DIR_AUTO;
					}
					return "";
				}

				virtual std::vector<std::string> stringList() const
				{
					std::vector<std::string> list;
					list.push_back(DIR_RIGHT_TO_LEFT);
					list.push_back(DIR_LEFT_TO_RIGHT);
					list.push_back(DIR_AUTO);
					return list;
				}
		};


		enum nNozzlesCol{
			COL_A = 0,  //Column A
			COL_B,      //Column B
			COL_BOTH    //Both
		};
		class NozzlesCol : public Utils::SmartEnum<nNozzlesCol>
		{
			public:
				NozzlesCol() {_val = COL_A;}
				virtual void operator = (const enum nNozzlesCol& v){_val = v;}
				virtual void operator = (const std::string& val){
					if (val.compare(NOZZLES_COL_A) == 0)
						_val = COL_A;
					else if (val.compare(NOZZLES_COL_B) == 0)
						_val = COL_B;
					else if (val.compare(NOZZLES_COL_BOTH) == 0)
						_val = COL_BOTH;
				}
				virtual std::string toString() const {
					switch (_val) {
						case COL_A:		return NOZZLES_COL_A;
						case COL_B:		return NOZZLES_COL_B;
						case COL_BOTH:	return NOZZLES_COL_BOTH;
					}
					return "";
				}

				virtual std::vector<std::string> stringList() const
				{
					std::vector<std::string> list;
					list.push_back(NOZZLES_COL_A);
					list.push_back(NOZZLES_COL_B);
					list.push_back(NOZZLES_COL_BOTH);
					return list;
				}
		};



		enum nPhotocell{
			PHCELL_A = 0,	//Photocell of column A
			PHCELL_B,		//Photocell of column B
			PHCELL_EXT,		//External photocell
		};
		class Photocell : public Utils::SmartEnum<nPhotocell>
		{
			public:
				Photocell() {_val = PHCELL_A;}
				virtual void operator = (const enum nPhotocell& v){_val = v;}
				virtual void operator = (const std::string& val){
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
					return "";
				}

				virtual std::vector<std::string> stringList() const
				{
					std::vector<std::string> list;
					list.push_back(PHOTOCELL_A);
					list.push_back(PHOTOCELL_B);
					list.push_back(PHOTOCELL_EXT);
					return list;
				}
		};

		enum nInputMode {
			INPUT_EDGE = 0,
			INPUT_STATUS
		};
		class InputMode : public Utils::SmartEnum<nInputMode>
		{
			public:
				InputMode() {_val = INPUT_EDGE;}
				virtual void operator = (const enum nInputMode& v){_val = v;}
				virtual void operator = (const std::string& val){
					if (val.compare(INPUT_MODE_EDGE) == 0)
						_val = INPUT_EDGE;
					else if (val.compare(INPUT_MODE_STATE) == 0)
						_val = INPUT_STATUS;
				}
				virtual std::string toString() const {
					switch (_val) {
						case INPUT_EDGE:	 return INPUT_MODE_EDGE;
						case INPUT_STATUS:	 return INPUT_MODE_STATE;
					}
					return "";
				}

				virtual std::vector<std::string> stringList() const
				{
					std::vector<std::string> list;
					list.push_back(INPUT_MODE_EDGE);
					list.push_back(INPUT_MODE_STATE);
					return list;
				}
		};


		enum nOutputType {
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
		class OutputType : public Utils::SmartEnum<nOutputType>
		{
			public:
				OutputType(){_val = OUTPUT_ONPULSE;}
				virtual void operator = (const enum nOutputType& v){_val = v;}
				virtual void operator = (const std::string& val){
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
					return "";
				}

				virtual std::vector<std::string> stringList() const
				{
					std::vector<std::string> list;
					list.push_back(OUTPUT_TYPE_STATE);
					list.push_back(OUTPUT_TYPE_ONPULSE);
					list.push_back(OUTPUT_TYPE_OFFPULSE);
					list.push_back(OUTPUT_TYPE_MAXON);
					list.push_back(OUTPUT_TYPE_MAXOFF);
					return list;
				}
		};

		enum nErrorType {
			INVALID = -1,
			INFORMATION = 0,
			WARNING,
			ERROR
		};
		class ErrorType : public Utils::SmartEnum<nErrorType>
		{
			public:
				virtual void operator = (const enum nErrorType& v){_val = v;}
				virtual void operator = (const std::string& val){
					if (val.compare(ERROR_TYPE_INFO) == 0)
						_val = INFORMATION;
					else if (val.compare(ERROR_TYPE_WARN) == 0)
						_val = WARNING;
					else if (val.compare(ERROR_TYPE_ERR) == 0)
						_val = ERROR;
					else
						_val = INVALID;
				}
				virtual std::string toString() const {
					switch (_val) {
						case INFORMATION:	return ERROR_TYPE_INFO;
						case WARNING:		return ERROR_TYPE_WARN;
						case ERROR:			return ERROR_TYPE_ERR;
						default: 			return ERROR_TYPE_INVALID;
					}
					return "";
				}

				virtual std::vector<std::string> stringList() const
				{
					std::vector<std::string> list;
					list.push_back(ERROR_TYPE_INFO);
					list.push_back(ERROR_TYPE_WARN);
					list.push_back(ERROR_TYPE_ERR);
					list.push_back(ERROR_TYPE_INVALID);
					return list;
				}
		};

		enum nErrorCode {
			SUCCESS	= 0					, // No error
			// FILES ERRORS
			FILE_NOT_FOUND				, // the specified file not exist
			FILE_ALREADY_EXIST			, // in move or copy operations, if the file already exist...
			FILE_COPY_FAIL				, // copy file operation error
			FILE_DELETE_FAIL			, // delete file operation error
			FILE_MOVE_FAIL				, // move operation error
			FILE_MOVE_INCOMPLETED		, // move operation has copied the source to target, but not delete the source
			FILE_READ_ERROR				, // can't read the file
			FILE_WRITE_ERROR			, // can't write the file
			FILE_WRITE_INCOMPLETED		, // the write on the file is not complete
			FILE_USER_DATAOT_FOUND	, // the name of a user-name-value is not found
			FILE_IN_USE					, // the file is currenty in use

			// PARAMS ERRORS
			PARAM_BOARD_IDOT_FOUND	 , // The BoardId specified by the command was not found
			PARAM_COUNTER_IDOT_FOUND	 , // The CounterId specified by the command was not found
			PARAM_COUNTER_VALUE_REJECTED , // The device has rejected the counter modification
			PARAM_OUTPUT_IDOT_FOUND	 , // The output id specified by the command was not found
			PARAM_INVALID_BCD_MODE		 , // Is not posible set a manual current message if the board is in Bcd mode
			PARAM_BOARD_IS_ENABLED		 , // the command requires a enabled board
			PARAM_BOARD_IS_DISABLED		 , // the command requires a disabled board
			PARAM_CHANGE_ADAPTER_FAIL	 , // The server can not change the adapter settings
			PARAM_INVALID_IP_ADDRESS	 , // The ip is invalid
			PARAM_INVALID_MASK_ADDRESS	 , // The mask is invalid
			PARAM_INVALID_GATEWAY_ADDRESS, // The Gateway is invalid
			PARAM_INVALID_PROP_COUNT	 , // The client can not change the number of properties

			// OTHER GENERIC ERRORS
			GEN_UNEXPECTED_TAG			, // generic xml error
			GENOT_IMPLEMENTED			, // informs that operation is not implemented on the server
			GEN_LOCK_TIMEOUT			, // Lock data fail

			// NEOTIJ ERRORS
			PCAOT_DETECTED			, // "PCA.NOTDETECTED"				"No connection with PCA"
			PH_OVERTEMP					, // "PH.OVERTEMP"					"Printhead over temperature"
			GEN_OVERSPEED				, // "GEN.OVERSPEED"				"Overspeed"
			MSG_FORMAT_ERROR			, // "MSG.FORMATERROR"				"NISX format error"
			MSGO_EXIST				, // "MSG.NOEXIST"					"Message doesn't exist"
			PHO_CARTRIDGE				, // "PH.NOCARTRIDGE"				"No cartridge loaded"
			SMC_INVALID					, // "SMC.INVALID"					"No valid smartcard on cartridge"
			PH_GEN_FAULT				, // "PH.GENFAULT"					"Cartridge fault - not valid"
			SMC_CARTRIDGE_EMPTY			, // "SMC.CARTRIDGE_EMPTY"			"Cartridge empty"
			SMC_CARTRIDGE_OUT_OF_DATE	, // "SMC.CARTRIDGE_OUTOFDATE"		"Cartridge out of expiration date"
			SMC_CARTRIDGEEAR_END		, // "SMC.CARTRIDGEEAREND"		"Cartridge near empty"
			SMC_CARTRIDGE_INVALID		, // "SMC.UNRECOGNIZED_DATA"		"Cartridge invalid Data"
			SMC_INITIALIZING_CARTRIDGE	, // "PH.INITIALIZING_CARTRIDGE"	"Initializing cartridge "
			SMC_HOST_INVALID			, // "SMC.HOST_SMARTCARD"			"Invalid Host Smart Card"

			UNKOWN_ERROR				//Last error for unknown code
		};
		class ErrorCode : public Utils::SmartEnum<nErrorCode>
		{
			public:
				ErrorCode() : SmartEnum() {_val = UNKOWN_ERROR;}
				ErrorCode(nErrorCode n) : SmartEnum() {_val = n;}
				virtual ~ErrorCode(){}
				virtual void operator = (const enum nErrorCode& v){_val = v;}
				virtual void operator = (const std::string& val){
					if (val.compare(ERROR_CODE_SUCCCESS) == 0)
						_val = SUCCESS;
					else if (val.compare(ERROR_CODE_FILEOT_FOUND) == 0)
						_val = FILE_NOT_FOUND;
					else if (val.compare(ERROR_CODE_FILE_ALREADY_EXIST) == 0)
						_val = FILE_ALREADY_EXIST;
					else if (val.compare(ERROR_CODE_FILE_COPY_FAIL) == 0)
						_val = FILE_COPY_FAIL;
					else if (val.compare(ERROR_CODE_FILE_DELETE_FAIL) == 0)
						_val = FILE_DELETE_FAIL;
					else if (val.compare(ERROR_CODE_FILE_MOVE_FAIL) == 0)
						_val = FILE_MOVE_FAIL;
					else if (val.compare(ERROR_CODE_FILE_MOVE_INCOMPLETED) == 0)
						_val = FILE_MOVE_INCOMPLETED;
					else if (val.compare(ERROR_CODE_FILE_READ_FAIL) == 0)
						_val = FILE_READ_ERROR;
					else if (val.compare(ERROR_CODE_FILE_WRITE_FAIL) == 0)
						_val = FILE_WRITE_ERROR;
					else if (val.compare(ERROR_CODE_FILE_WRITE_INCOMPLETED) == 0)
						_val = FILE_WRITE_INCOMPLETED;
					else if (val.compare(ERROR_CODE_FILE_USER_DATAOT_FOUND) == 0)
						_val = FILE_USER_DATAOT_FOUND;
					else if (val.compare(ERROR_CODE_FILE_IN_USE) == 0)
						_val = FILE_IN_USE;
					else if (val.compare(ERROR_CODE_PARAM_BOARD_IDOT_FOUND) == 0)
						_val = PARAM_BOARD_IDOT_FOUND;
					else if (val.compare(ERROR_CODE_PARAM_COUNTER_IDOT_FOUND) == 0)
						_val = PARAM_COUNTER_IDOT_FOUND;
					else if (val.compare(ERROR_CODE_PARAM_COUNTER_VALUE_REJECTED) == 0)
						_val = PARAM_COUNTER_VALUE_REJECTED;
					else if (val.compare(ERROR_CODE_PARAM_OUTPUT_IDOT_FOUND) == 0)
						_val = PARAM_OUTPUT_IDOT_FOUND;
					else if (val.compare(ERROR_CODE_PARAM_BCD_INVALID_MODE) == 0)
						_val = PARAM_INVALID_BCD_MODE;
					else if (val.compare(ERROR_CODE_PARAM_BOARD_IS_ENABLED) == 0)
						_val = PARAM_BOARD_IS_ENABLED;
					else if (val.compare(ERROR_CODE_PARAM_BOARD_IS_DISABLED) == 0)
						_val = PARAM_BOARD_IS_DISABLED;
					else if (val.compare(ERROR_CODE_PARAM_CHANGE_ADAPTER_FAILS) == 0)
						_val = PARAM_CHANGE_ADAPTER_FAIL;
					else if (val.compare(ERROR_CODE_PARAM_INVALID_IP_ADDRESS) == 0)
						_val = PARAM_INVALID_IP_ADDRESS;
					else if (val.compare(ERROR_CODE_PARAM_INVALID_MASK_ADDRESS) == 0)
						_val = PARAM_INVALID_MASK_ADDRESS;
					else if (val.compare(ERROR_CODE_PARAM_INVALID_GATEWAY_ADDRESS) == 0)
						_val = PARAM_INVALID_GATEWAY_ADDRESS;
					else if (val.compare(ERROR_CODE_PARAM_INVALID_PROP_COUNT) == 0)
						_val = PARAM_INVALID_PROP_COUNT;
					else if (val.compare(ERROR_CODE_GENERIC_UNEXPECTED_TAG) == 0)
						_val = GEN_UNEXPECTED_TAG;
					else if (val.compare(ERROR_CODE_GENERICOT_IMPLEMENTED) == 0)
						_val = GENOT_IMPLEMENTED;
					else if (val.compare(ERROR_CODE_GENERIC_LOCK_TIMEOUT) == 0)
						_val = GEN_LOCK_TIMEOUT;
					else if (val.compare(ERROR_CODE_PH_PCAOT_DETECTED) == 0)
						_val = PCAOT_DETECTED;
					else if (val.compare(ERROR_CODE_PH_OVERTEMP) == 0)
						_val = PH_OVERTEMP;
					else if (val.compare(ERROR_CODE_PH_OVERSPEED) == 0)
						_val = GEN_OVERSPEED;
					else if (val.compare(ERROR_CODE_MSG_FORMAT_ERROR) == 0)
						_val = MSG_FORMAT_ERROR;
					else if (val.compare(ERROR_CODE_MSGOEXIST) == 0)
						_val = MSGO_EXIST;
					else if (val.compare(ERROR_CODE_PHO_CARTRIDGE) == 0)
						_val = PHO_CARTRIDGE;
					else if (val.compare(ERROR_CODE_PH_SC_INVALID) == 0)
						_val = SMC_INVALID;
					else if (val.compare(ERROR_CODE_PH_GENERIC_FAULT) == 0)
						_val = PH_GEN_FAULT;
					else if (val.compare(ERROR_CODE_PH_SC_CARTRIDGE_EMPTY) == 0)
						_val = SMC_CARTRIDGE_EMPTY;
					else if (val.compare(ERROR_CODE_PH_SC_CARTRIDGE_OUT_OF_DATE) == 0)
						_val = SMC_CARTRIDGE_OUT_OF_DATE;
					else if (val.compare(ERROR_CODE_PH_SC_CARTRIDGEEAR_END) == 0)
						_val = SMC_CARTRIDGEEAR_END;
					else if (val.compare(ERROR_CODE_PH_SC_UNRECOGNIZED_DATA) == 0)
						_val = SMC_CARTRIDGE_INVALID;
					else if (val.compare(ERROR_CODE_PH_SC_INITIALIZING) == 0)
						_val = SMC_INITIALIZING_CARTRIDGE;
					else if (val.compare(ERROR_CODE_PH_SC_HOST_SMARTCARD_FAIL) == 0)
						_val = SMC_HOST_INVALID;
					else if (val.compare(ERROR_CODE_UNKNOWN) == 0)
						_val = UNKOWN_ERROR;
				}
				virtual std::string toString() const {
					switch (_val) {
						case SUCCESS:						return ERROR_CODE_SUCCCESS;
							// FILES ERRORS
						case FILE_NOT_FOUND:				return ERROR_CODE_FILEOT_FOUND;
						case FILE_ALREADY_EXIST:			return ERROR_CODE_FILE_ALREADY_EXIST;
						case FILE_COPY_FAIL:				return ERROR_CODE_FILE_COPY_FAIL;
						case FILE_DELETE_FAIL:				return ERROR_CODE_FILE_DELETE_FAIL;
						case FILE_MOVE_FAIL:				return ERROR_CODE_FILE_MOVE_FAIL;
						case FILE_MOVE_INCOMPLETED:			return ERROR_CODE_FILE_MOVE_INCOMPLETED;
						case FILE_READ_ERROR:				return ERROR_CODE_FILE_READ_FAIL;
						case FILE_WRITE_ERROR:				return ERROR_CODE_FILE_WRITE_FAIL;
						case FILE_WRITE_INCOMPLETED:		return ERROR_CODE_FILE_WRITE_INCOMPLETED;
						case FILE_USER_DATAOT_FOUND:		return ERROR_CODE_FILE_USER_DATAOT_FOUND;
						case FILE_IN_USE:					return ERROR_CODE_FILE_IN_USE;
							// PARAMS ERRORS
						case PARAM_BOARD_IDOT_FOUND:		return ERROR_CODE_PARAM_BOARD_IDOT_FOUND;
						case PARAM_COUNTER_IDOT_FOUND:	return ERROR_CODE_PARAM_COUNTER_IDOT_FOUND;
						case PARAM_COUNTER_VALUE_REJECTED:	return ERROR_CODE_PARAM_COUNTER_VALUE_REJECTED;
						case PARAM_OUTPUT_IDOT_FOUND:		return ERROR_CODE_PARAM_OUTPUT_IDOT_FOUND;
						case PARAM_INVALID_BCD_MODE:		return ERROR_CODE_PARAM_BCD_INVALID_MODE;
						case PARAM_BOARD_IS_ENABLED:		return ERROR_CODE_PARAM_BOARD_IS_ENABLED;
						case PARAM_BOARD_IS_DISABLED:		return ERROR_CODE_PARAM_BOARD_IS_DISABLED;
						case PARAM_CHANGE_ADAPTER_FAIL:		return ERROR_CODE_PARAM_CHANGE_ADAPTER_FAILS;
						case PARAM_INVALID_IP_ADDRESS:		return ERROR_CODE_PARAM_INVALID_IP_ADDRESS;
						case PARAM_INVALID_MASK_ADDRESS:	return ERROR_CODE_PARAM_INVALID_MASK_ADDRESS;
						case PARAM_INVALID_GATEWAY_ADDRESS:	return ERROR_CODE_PARAM_INVALID_GATEWAY_ADDRESS;
						case PARAM_INVALID_PROP_COUNT:		return ERROR_CODE_PARAM_INVALID_PROP_COUNT;
							// OTHER GENERIC ERRORS
						case GEN_UNEXPECTED_TAG:			return ERROR_CODE_GENERIC_UNEXPECTED_TAG;
						case GENOT_IMPLEMENTED:			return ERROR_CODE_GENERICOT_IMPLEMENTED;
						case GEN_LOCK_TIMEOUT:				return ERROR_CODE_GENERIC_LOCK_TIMEOUT;
							// NEOTIJ ERRORS
						case PCAOT_DETECTED:				return ERROR_CODE_PH_PCAOT_DETECTED;
						case PH_OVERTEMP:					return ERROR_CODE_PH_OVERTEMP;
						case GEN_OVERSPEED:					return ERROR_CODE_PH_OVERSPEED;
						case MSG_FORMAT_ERROR:				return ERROR_CODE_MSG_FORMAT_ERROR;
						case MSGO_EXIST:					return ERROR_CODE_MSGOEXIST;
						case PHO_CARTRIDGE:				return ERROR_CODE_PHO_CARTRIDGE;
						case SMC_INVALID:					return ERROR_CODE_PH_SC_INVALID;
						case PH_GEN_FAULT:					return ERROR_CODE_PH_GENERIC_FAULT;
						case SMC_CARTRIDGE_EMPTY:			return ERROR_CODE_PH_SC_CARTRIDGE_EMPTY;
						case SMC_CARTRIDGE_OUT_OF_DATE:		return ERROR_CODE_PH_SC_CARTRIDGE_OUT_OF_DATE;
						case SMC_CARTRIDGEEAR_END:		return ERROR_CODE_PH_SC_CARTRIDGEEAR_END;
						case SMC_CARTRIDGE_INVALID:			return ERROR_CODE_PH_SC_UNRECOGNIZED_DATA;
						case SMC_INITIALIZING_CARTRIDGE:	return ERROR_CODE_PH_SC_INITIALIZING;
						case SMC_HOST_INVALID:				return ERROR_CODE_PH_SC_HOST_SMARTCARD_FAIL;

						default:							return ERROR_CODE_UNKNOWN;
					}
					return "";
				}

				virtual std::vector<std::string> stringList() const
				{
					std::vector<std::string> list;
					list.push_back(ERROR_CODE_SUCCCESS);
					list.push_back(ERROR_CODE_FILEOT_FOUND);
					list.push_back(ERROR_CODE_FILE_ALREADY_EXIST);
					list.push_back(ERROR_CODE_FILE_COPY_FAIL);
					list.push_back(ERROR_CODE_FILE_DELETE_FAIL);
					list.push_back(ERROR_CODE_FILE_MOVE_FAIL);
					list.push_back(ERROR_CODE_FILE_MOVE_INCOMPLETED);
					list.push_back(ERROR_CODE_FILE_READ_FAIL);
					list.push_back(ERROR_CODE_FILE_WRITE_FAIL);
					list.push_back(ERROR_CODE_FILE_WRITE_INCOMPLETED);
					list.push_back(ERROR_CODE_FILE_USER_DATAOT_FOUND);
					list.push_back(ERROR_CODE_FILE_IN_USE);
					list.push_back(ERROR_CODE_PARAM_BOARD_IDOT_FOUND);
					list.push_back(ERROR_CODE_PARAM_COUNTER_IDOT_FOUND);
					list.push_back(ERROR_CODE_PARAM_COUNTER_VALUE_REJECTED);
					list.push_back(ERROR_CODE_PARAM_OUTPUT_IDOT_FOUND);
					list.push_back(ERROR_CODE_PARAM_BCD_INVALID_MODE);
					list.push_back(ERROR_CODE_PARAM_BOARD_IS_ENABLED);
					list.push_back(ERROR_CODE_PARAM_BOARD_IS_DISABLED);
					list.push_back(ERROR_CODE_PARAM_CHANGE_ADAPTER_FAILS);
					list.push_back(ERROR_CODE_PARAM_INVALID_IP_ADDRESS);
					list.push_back(ERROR_CODE_PARAM_INVALID_MASK_ADDRESS);
					list.push_back(ERROR_CODE_PARAM_INVALID_GATEWAY_ADDRESS);
					list.push_back(ERROR_CODE_PARAM_INVALID_PROP_COUNT);
					list.push_back(ERROR_CODE_GENERIC_UNEXPECTED_TAG);
					list.push_back(ERROR_CODE_GENERICOT_IMPLEMENTED);
					list.push_back(ERROR_CODE_GENERIC_LOCK_TIMEOUT);
					list.push_back(ERROR_CODE_PH_PCAOT_DETECTED);
					list.push_back(ERROR_CODE_PH_OVERTEMP);
					list.push_back(ERROR_CODE_PH_OVERSPEED);
					list.push_back(ERROR_CODE_MSG_FORMAT_ERROR);
					list.push_back(ERROR_CODE_MSGOEXIST);
					list.push_back(ERROR_CODE_PHO_CARTRIDGE);
					list.push_back(ERROR_CODE_PH_SC_INVALID);
					list.push_back(ERROR_CODE_PH_GENERIC_FAULT);
					list.push_back(ERROR_CODE_PH_SC_CARTRIDGE_EMPTY);
					list.push_back(ERROR_CODE_PH_SC_CARTRIDGE_OUT_OF_DATE);
					list.push_back(ERROR_CODE_PH_SC_CARTRIDGEEAR_END);
					list.push_back(ERROR_CODE_PH_SC_UNRECOGNIZED_DATA);
					list.push_back(ERROR_CODE_PH_SC_INITIALIZING);
					list.push_back(ERROR_CODE_PH_SC_HOST_SMARTCARD_FAIL);
					list.push_back(ERROR_CODE_UNKNOWN);
					return list;
				}
		};

		enum nLoggerLevel {
			LOG_ERROR=0,
			LOG_WARNING,
			LOG_INFO,
			LOG_DEBUG,
			LOG_DISABLED
		};
		class LoggerLevel : public Utils::SmartEnum<nLoggerLevel>
		{
			public:
				LoggerLevel(){_val = LOG_DISABLED;}
				void operator = (const enum nLoggerLevel& v){_val = v;}
				void operator = (const std::string& val){
					if (val.compare(LOG_LEVEL_ERROR) == 0)
						_val = LOG_ERROR;
					else if (val.compare(LOG_LEVEL_WARNING) == 0)
						_val = LOG_WARNING;
					else if (val.compare(LOG_LEVEL_INFO) == 0)
						_val = LOG_INFO;
					else if (val.compare(LOG_LEVEL_DEBUG) == 0)
						_val = LOG_DEBUG;
					else
						_val = LOG_DISABLED;
				}


				std::string toString() const {
					switch (_val) {
						case LOG_ERROR:		return LOG_LEVEL_ERROR;
						case LOG_WARNING:	return LOG_LEVEL_WARNING;
						case LOG_INFO:		return LOG_LEVEL_INFO;
						case LOG_DEBUG:		return LOG_LEVEL_DEBUG;
						case LOG_DISABLED:	return LOG_LEVEL_DISABLED;
					}
					return "";
				}

				virtual std::vector<std::string> stringList() const
				{
					std::vector<std::string> list;
					list.push_back(LOG_LEVEL_ERROR);
					list.push_back(LOG_LEVEL_WARNING);
					list.push_back(LOG_LEVEL_INFO);
					list.push_back(LOG_LEVEL_DEBUG);
					list.push_back(LOG_LEVEL_DISABLED);
					return list;
				}
		};
	}
}


#endif
