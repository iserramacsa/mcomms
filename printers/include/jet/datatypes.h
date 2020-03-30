#ifndef MACSA_JET_PRINTER_DATA_TYPES_H
#define MACSA_JET_PRINTER_DATA_TYPES_H

#include "utils/smartenum.h"

//#ifndef UNKNOWN
//#define UNKNOWN				"Unknown"
//#endif

/// IdJet Printers Models
#define JET_ID_NEO_17		"Neo17"
#define JET_ID_NEO_36		"Neo36"
#define JET_ID_NEO_50		"Neo50"
#define JET_ID_NEO_70		"Neo70"
#define JET_ID_NEO_100		"Neo100"
#define JET_ID_NEO_140		"Neo140"
#define JET_ID_NEO_17D		"Neo17DUO"
#define JET_ID_NEO_50D		"Neo50DUO"
#define JET_ID_NEO_70D		"Neo70DUO"

///Printhead OVERLAPPING_TYPE operating modes
#define OVERLAPPING_TYPE_BOTH_PH	"Both Printheads"
#define OVERLAPPING_TYPE_UPPER_PH	"Only Upper Printheads"
#define OVERLAPPING_TYPE_LOWER_PH	"Only Lower Printheads"
#define OVERLAPPING_TYPE_PIXELS		"One Pixel per Printhead"

#define TRIGGER_CANCEL_PRINT	"Trigger cancels current print and starts new one"
#define TRIGGER_SKIPPED_PRINT	"During a print the received triggers will be ignored"

#define IPv4 "IPv4"
#define IPv6 "IPv6"

#define JET_BOARD_PRINTHEAD "PH"
#define JET_BOARD_SIGNALS	"SIGNAL"

#define PRINTER_DIR_RL		"Right To Left"
#define PRINTER_DIR_LR		"Left To Right"

#define PH_ENABLE_MODE_BOTH		"Enable upper and lower printheads"
#define PH_ENABLE_MODE_UPPER	"Enable only upper printhead"
#define PH_ENABLE_MODE_LOWER	"Enable only lower printhead"

#define JET_LOG_TYPE_INFO		"Info"
#define JET_LOG_TYPE_WARN		"Warning"
#define JET_LOG_TYPE_ERR		"Error"
#define JET_LOG_TYPE_SUCCESS	"Ok"
#define JET_LOG_TYPE_ALL		"All"

#define ERROR_CODE_COMMAND_OK						"Ok"
#define ERROR_CODE_INVALID_COMMAND					"Object reference not set to an instance of an object."
#define ERROR_CODE_NOT_CONNECTED					"Printer not Connected"
#define ERROR_CODE_CHECKSUM_ERROR					"Checksum Error"
#define ERROR_CODE_INVALID_MESSAGE_GROUP			"MessageGroupNoExists"
#define ERROR_CODE_INVALID_PRINTHEAD				"Incorrect PrintHead"
#define ERROR_CODE_INVALID_OUTPUT_ID				"Wrong Output"
#define ERROR_CODE_INVALID_OUTPUT_PULSE				"Wrong Pulse"
#define ERROR_CODE_INVALID_MSG_NUMBER				"Message not found"
#define ERROR_CODE_INVALID_MSG_VARIABLE				"Variable not found"
#define ERROR_CODE_INVALID_DATETIME_VALUE			"Wrong Date Time Value"
#define ERROR_CODE_USB_NOT_CONNECTED				"USB Not Connected"
#define ERROR_CODE_INVALID_EVENT_TYPE				"Wrong Event Type"
#define ERROR_CODE_INVALID_VALUE					"WrongValue"
#define ERROR_CODE_INVALID_IP						"WrongIPValue"
#define ERROR_CODE_INVALID_PRINTHEAD_ID				"WrongPrintHeadId"
#define ERROR_CODE_INVALID_NET_ADAPTER				"WrongNetAdapter"
#define ERROR_CODE_INVALID_NET_MASK					"WrongNetMask"
#define ERROR_CODE_INVALID_GATEWAY					"WrongGateway"
#define ERROR_CODE_INVALID_DNS						"WrongDNS"
#define ERROR_CODE_INVALID_PULSES					"WrongPulses"
#define ERROR_CODE_INVALID_WHEEL					"WrongWheel"
#define ERROR_CODE_INVALID_ABC						"WrongABC"
#define ERROR_CODE_INVALID_MAX_TIME_PRINT			"WrongMaxTimePrint"
#define ERROR_CODE_INVALID_OVERLAPPING_TYPE			"WrongOverlappingType"
#define ERROR_CODE_INVALID_HORIZONTAL_RESOLUTION	"WrongHorizontalResolution"
#define ERROR_CODE_INVALID_DEFAULT_FONT				"WrongDefaultFont"
#define ERROR_CODE_INVALID_LAMP_CONTROL_TIME		"WrongLampControlTime"
#define ERROR_CODE_INVALID_XR_OFFSET				"WrongXROffset"
#define ERROR_CODE_INVALID_PHOTOCELL_FILTER			"WrongStPrintFilter"
#define ERROR_CODE_INVALID_PRINT_MODE				"WrongPrintMode"
#define ERROR_CODE_INVALID_IP_ADDR_TYPE				"WrongIPType"
#define ERROR_CODE_IP_ALREADY_CONFIGURED			"IPAlreadyConfigured"
#define ERROR_CODE_IP_NO_PING_RESPONSE				"NoPing"
#define ERROR_CODE_PRINTHEAD_NOT_ASSIGNED			"PrintheadNotAssigned"
#define ERROR_CODE_SPECIFIC_NISX_COMMAND			"SpecificNisXCommand"
#define ERROR_CODE_MESSAGE_NUMBER_NOT_FOUND			"MessageNumberNoExists"
#define ERROR_CODE_MISSING_FILENAME_ATTRIBUTTE		"MissingFileNameAttribute"
#define ERROR_CODE_NISX_INVALID_FORMAT				"NisXInvalidFormat"
#define ERROR_CODE_NISX_PARSING_ERROR				"NisXParsingError"
#define ERROR_CODE_UNKNOWN							"UNKNOWN"


#define JET_CONFIG_ITEM_PH_ID						"PH_ID"
#define JET_CONFIG_ITEM_PH_IP_ADDRESS				"PH_IP_ADDRESS"
#define JET_CONFIG_ITEM_PRINTERDIRECTION			"PRINTERDIRECTION"
#define JET_CONFIG_ITEM_BITMAPINVERTED				"BITMAPINVERTED"
#define JET_CONFIG_ITEM_PRINTSPEED					"PRINTSPEED"
#define JET_CONFIG_ITEM_PRINTDELAY					"PRINTDELAY"
#define JET_CONFIG_ITEM_HORIZONTAL_RESOLUTION		"HORIZONTAL_RESOLUTION"
#define JET_CONFIG_ITEM_ENCODER_ENABLED				"ENCODER.ENABLED"
#define JET_CONFIG_ITEM_ENCODER_PULSES				"ENCODER.PULSES"
#define JET_CONFIG_ITEM_ENCODER_WHEEL				"ENCODER.WHEEL"
#define JET_CONFIG_ITEM_ENCODER_ABC_PITCH			"ENCODER.ABC_PITCH"
#define JET_CONFIG_ITEM_PRINTINGLIST				"PRINTINGLIST"
#define JET_CONFIG_ITEM_FIFO						"FIFO"
#define JET_CONFIG_ITEM_DELAY_IN_POINTS				"DELAY_IN_POINTS"
#define JET_CONFIG_ITEM_STB_INC_SSCC				"STB_INC_SSCC"
#define JET_CONFIG_ITEM_SEND_IMG_AFTER_PRINT		"SEND_IMG_AFTER_PRINT"
#define JET_CONFIG_ITEM_STB_RESET_PRINTING_LIST		"STB_RESET_PRINTING_LIST"
#define JET_CONFIG_ITEM_LINE_ID						"LINE_ID"
#define JET_CONFIG_ITEM_MACHINE_ID					"MACHINE_ID"
#define JET_CONFIG_ITEM_MAX_PRINT_TIME				"MAX_PRINT_TIME"
#define JET_CONFIG_ITEM_OPTIMIZE_BARCODE			"OPTIMIZE_BARCODE"
#define JET_CONFIG_ITEM_OVERLAPPING_TYPE			"OVERLAPPING_TYPE"
#define JET_CONFIG_ITEM_DEFAULT_FONT				"DEFAULT_FONT"
#define JET_CONFIG_ITEM_LAMP_CONTROL				"LAMP_CONTROL"
#define JET_CONFIG_ITEM_LAMP_CONTROL_TIME			"LAMP_CONTROL.TIME"
#define JET_CONFIG_ITEM_XROFFSET					"XROFFSET"
#define JET_CONFIG_ITEM_CELL_FILTER					"CELL_FILTER"
#define JET_CONFIG_ITEM_PRINT_MODE					"PRINT_MODE"
#define JET_CONFIG_ITEM_NETWORK_ADAPTER				"NETWORK_ADAPTER"
#define JET_CONFIG_ITEM_NET_IP_ADDRESS_VALUE		"NET_IP_ADDRESS_VALUE"
#define JET_CONFIG_ITEM_NET_IP_ADDRESS_TYPE			"NET_IP_ADDRESS_TYPE"
#define JET_CONFIG_ITEM_NET_IP_ADDRESS_MASK			"NET_IP_ADDRESS_MASK"
#define JET_CONFIG_ITEM_NET_GATEWAY_VALUE			"NET_GATEWAY_VALUE"
#define JET_CONFIG_ITEM_NET_GATEWAY_TYPE			"NET_GATEWAY_TYPE"
#define JET_CONFIG_ITEM_NET_DNS						"NET_DNS"
#define JET_CONFIG_ITEM_NET_DNS_TYPE				"NET_DNS_TYPE"


namespace Macsa {
	namespace Printers {

		enum nJetPrinterType
		{
			ID_NEO_17 = 0,
			ID_NEO_36,
			ID_NEO_50,
			ID_NEO_70,
			ID_NEO_100,
			ID_NEO_140,
			ID_NEO_17D,
			ID_NEO_50D,
			ID_NEO_70D
		};
		class JetPrinterType : public Utils::SmartEnum<nJetPrinterType>
		{
			public:
				JetPrinterType() : SmartEnum() {_val = ID_NEO_17;}
				JetPrinterType(nJetPrinterType n) : SmartEnum() {_val = n;}
				virtual ~JetPrinterType(){}
				virtual void operator = (const enum nJetPrinterType& v){_val = v;}
				virtual void operator = (const std::string& val) {
					if(val.compare(JET_ID_NEO_17 ) == 0)
						_val = ID_NEO_17;
					else if(val.compare(JET_ID_NEO_36 ) == 0)
						_val = ID_NEO_36;
					else if(val.compare(JET_ID_NEO_50 ) == 0)
						_val = ID_NEO_50;
					else if(val.compare(JET_ID_NEO_70 ) == 0)
						_val = ID_NEO_70;
					else if(val.compare(JET_ID_NEO_100) == 0)
						_val = ID_NEO_100;
					else if(val.compare(JET_ID_NEO_140) == 0)
						_val = ID_NEO_140;
					else if(val.compare(JET_ID_NEO_17D) == 0)
						_val = ID_NEO_17D;
					else if(val.compare(JET_ID_NEO_50D) == 0)
						_val = ID_NEO_50D;
					else if(val.compare(JET_ID_NEO_70D) == 0)
						_val = ID_NEO_70D;
				}

				virtual std::string toString() const {
					switch (_val) {
						case ID_NEO_17:	 return JET_ID_NEO_17;
						case ID_NEO_36:	 return JET_ID_NEO_36;
						case ID_NEO_50:	 return JET_ID_NEO_50;
						case ID_NEO_70:	 return JET_ID_NEO_70;
						case ID_NEO_100: return JET_ID_NEO_100;
						case ID_NEO_140: return JET_ID_NEO_140;
						case ID_NEO_17D: return JET_ID_NEO_17D;
						case ID_NEO_50D: return JET_ID_NEO_50D;
						case ID_NEO_70D: return JET_ID_NEO_70D;
					}
					return "";
				}

				virtual std::vector<std::string> stringList() const
				{
					std::vector<std::string> list;
					list.push_back(JET_ID_NEO_17);
					list.push_back(JET_ID_NEO_36);
					list.push_back(JET_ID_NEO_50);
					list.push_back(JET_ID_NEO_70);
					list.push_back(JET_ID_NEO_100);
					list.push_back(JET_ID_NEO_140);
					list.push_back(JET_ID_NEO_17D);
					list.push_back(JET_ID_NEO_50D);
					list.push_back(JET_ID_NEO_70D);
					return list;
				}
		};

		enum nJetBoardType {
			PRINTHEAD_BOARD = 0,
			SIGNALS_BOARD
		};
		class JetBoardType : public Utils::SmartEnum<nJetBoardType>
		{
			public:
				JetBoardType() : SmartEnum() {_val = PRINTHEAD_BOARD;}
				JetBoardType(nJetBoardType n) : SmartEnum() {_val = n;}
				JetBoardType(const std::string& name) : SmartEnum() {*this = name;}
				virtual ~JetBoardType(){}
				virtual void operator = (const enum nJetBoardType& v){_val = v;}
				virtual void operator = (const std::string& val){
					if (val.compare(JET_BOARD_PRINTHEAD) == 0)
						_val = PRINTHEAD_BOARD;
					else if (val.compare(JET_BOARD_SIGNALS) == 0)
						_val = SIGNALS_BOARD;
				}
				virtual std::string toString() const {
					switch (_val) {
						case PRINTHEAD_BOARD: return JET_BOARD_PRINTHEAD;
						case SIGNALS_BOARD:	  return JET_BOARD_SIGNALS;
					}
					return "";
				}
				virtual std::vector<std::string> stringList() const
				{
					std::vector<std::string> list;
					list.push_back(JET_BOARD_PRINTHEAD);
					list.push_back(JET_BOARD_SIGNALS);
					return list;
				}
		};


		enum nPHEnableMode{
			ENABLE_BOTH = 0,
			ENABLE_UPPER,
			ENABLE_LOWER,
		};
		class PHEnableMode : public Utils::SmartEnum<nPHEnableMode>
		{
			public:
				PHEnableMode() : SmartEnum() {_val = ENABLE_BOTH;}
				PHEnableMode(nPHEnableMode n) : SmartEnum() {_val = n;}
				virtual ~PHEnableMode(){}
				virtual void operator = (const enum nPHEnableMode& v){_val = v;}
				virtual void operator = (const std::string& val){
					if (val.compare(PH_ENABLE_MODE_BOTH) == 0)
						_val = ENABLE_BOTH;
					else if (val.compare(PH_ENABLE_MODE_UPPER) == 0)
						_val = ENABLE_UPPER;
					else if (val.compare(PH_ENABLE_MODE_LOWER) == 0)
						_val = ENABLE_LOWER;
				}
				virtual std::string toString() const {
					switch (_val) {
						case ENABLE_BOTH: return PH_ENABLE_MODE_BOTH;
						case ENABLE_UPPER: return PH_ENABLE_MODE_UPPER;
						case ENABLE_LOWER: return PH_ENABLE_MODE_LOWER;
					}
					return "";
				}
				virtual std::vector<std::string> stringList() const
				{
					std::vector<std::string> list;
					list.push_back(PH_ENABLE_MODE_BOTH);
					list.push_back(PH_ENABLE_MODE_UPPER);
					list.push_back(PH_ENABLE_MODE_LOWER);
					return list;
				}
		};

		enum nOverlappingMode{
			OVERLAPPING_BOTH = 0,
			OVERLAPPING_UPPER,
			OVERLAPPING_LOWER,
			OVERLAPPING_PIXEL
		};
		class OverlappingMode : public Utils::SmartEnum<nOverlappingMode>
		{
			public:
				OverlappingMode() : SmartEnum() {_val = OVERLAPPING_BOTH;}
				OverlappingMode(nOverlappingMode n) : SmartEnum() {_val = n;}
				virtual ~OverlappingMode(){}
				virtual void operator = (const enum nOverlappingMode& v){_val = v;}
				virtual void operator = (const std::string& val){
					if (val.compare(OVERLAPPING_TYPE_BOTH_PH) == 0)
						_val = OVERLAPPING_BOTH;
					else if (val.compare(OVERLAPPING_TYPE_UPPER_PH) == 0)
						_val = OVERLAPPING_UPPER;
					else if (val.compare(OVERLAPPING_TYPE_LOWER_PH) == 0)
						_val = OVERLAPPING_LOWER;
					else if (val.compare(OVERLAPPING_TYPE_PIXELS) == 0)
						_val = OVERLAPPING_PIXEL;
				}
				virtual std::string toString() const {
					switch (_val) {
						case OVERLAPPING_BOTH: return OVERLAPPING_TYPE_BOTH_PH;
						case OVERLAPPING_UPPER: return OVERLAPPING_TYPE_UPPER_PH;
						case OVERLAPPING_LOWER: return OVERLAPPING_TYPE_LOWER_PH;
						case OVERLAPPING_PIXEL: return OVERLAPPING_TYPE_PIXELS;
					}
					return "";
				}
				virtual std::vector<std::string> stringList() const
				{
					std::vector<std::string> list;
					list.push_back(OVERLAPPING_TYPE_BOTH_PH );
					list.push_back(OVERLAPPING_TYPE_UPPER_PH);
					list.push_back(OVERLAPPING_TYPE_LOWER_PH);
					list.push_back(OVERLAPPING_TYPE_PIXELS	);
					return list;
				}
		};

		enum nTriggerMode{
			NEW_PRINT_ON_TRIGGER = 0,
			SKIP_TRIGGER_ON_PRINTING
		};
		class TriggerMode : public Utils::SmartEnum<nTriggerMode>
		{
			public:
				TriggerMode() : SmartEnum() {_val = NEW_PRINT_ON_TRIGGER;}
				TriggerMode(nTriggerMode n) : SmartEnum() {_val = n;}
				virtual ~TriggerMode(){}
				virtual void operator = (const enum nTriggerMode& v){_val = v;}
				virtual void operator = (const std::string& val){
					if (val.compare(TRIGGER_CANCEL_PRINT) == 0)
						_val = NEW_PRINT_ON_TRIGGER;
					else if (val.compare(TRIGGER_SKIPPED_PRINT) == 0)
						_val = SKIP_TRIGGER_ON_PRINTING;
				}
				virtual std::string toString() const {
					switch (_val) {
						case NEW_PRINT_ON_TRIGGER: return TRIGGER_CANCEL_PRINT;
						case SKIP_TRIGGER_ON_PRINTING: return TRIGGER_SKIPPED_PRINT;
					}
					return "";
				}
				virtual std::vector<std::string> stringList() const
				{
					std::vector<std::string> list;
					list.push_back(TRIGGER_CANCEL_PRINT );
					list.push_back(TRIGGER_SKIPPED_PRINT);
					return list;
				}
		};

		enum nIpVersion{
			IP_V4 = 0,
			IP_V6
		};
		class IpVersion : public Utils::SmartEnum<nIpVersion>
		{
			public:
				IpVersion() : SmartEnum() {_val = IP_V4;}
				IpVersion(nIpVersion n) : SmartEnum() {_val = n;}
				virtual ~IpVersion(){}
				virtual void operator = (const enum nIpVersion& v){_val = v;}
				virtual void operator = (const std::string& val){
					if (val.compare(IPv4) == 0)
						_val = IP_V4;
					else if (val.compare(IPv6) == 0)
						_val = IP_V6;
				}
				virtual std::string toString() const {
					switch (_val) {
						case IP_V4: return IPv4;
						case IP_V6: return IPv6;
					}
					return "";
				}
				virtual std::vector<std::string> stringList() const
				{
					std::vector<std::string> list;
					list.push_back(IPv4);
					list.push_back(IPv6);
					return list;
				}
		};


		enum nPrintDirection{
			PRINTDIR_LR = 0,
			PRINTDIR_RL
		};
		class PrintDirection : public Utils::SmartEnum<nPrintDirection>
		{
			public:
				PrintDirection() : SmartEnum() {_val = PRINTDIR_LR;}
				PrintDirection(nPrintDirection n) : SmartEnum() {_val = n;}
				virtual ~PrintDirection(){}
				virtual void operator = (const enum nPrintDirection& v){_val = v;}
				virtual void operator = (const std::string& val){
					if (val.compare(PRINTER_DIR_LR) == 0)
						_val = PRINTDIR_LR;
					else if (val.compare(PRINTER_DIR_RL) == 0)
						_val = PRINTDIR_RL;
				}
				virtual std::string toString() const {
					switch (_val) {
						case PRINTDIR_LR: return PRINTER_DIR_LR;
						case PRINTDIR_RL: return PRINTER_DIR_RL;
					}
					return "";
				}
				virtual std::vector<std::string> stringList() const
				{
					std::vector<std::string> list;
					list.push_back(PRINTER_DIR_LR);
					list.push_back(PRINTER_DIR_RL);
					return list;
				}
		};


		enum nJetLogType {
			LOG_TYPE_ALL = 0,
			LOG_TYPE_INFO,
			LOG_TYPE_WARN,
			LOG_TYPE_ERR,
			LOG_TYPE_SUCCESS,
		};
		class JetLogType : public Utils::SmartEnum<nJetLogType>
		{
			public:
				JetLogType() : SmartEnum() {_val = LOG_TYPE_ALL;}
				JetLogType(nJetLogType n) : SmartEnum() {_val = n;}
				virtual ~JetLogType(){}
				virtual void operator = (const enum nJetLogType& v){_val = v;}
				virtual void operator = (const std::string& val){
					if (val.compare(JET_LOG_TYPE_ALL) == 0)
						_val = LOG_TYPE_ALL;
					else if (val.compare(JET_LOG_TYPE_INFO) == 0)
						_val = LOG_TYPE_INFO;
					else if (val.compare(JET_LOG_TYPE_WARN) == 0)
						_val = LOG_TYPE_WARN;
					else if (val.compare(JET_LOG_TYPE_ERR) == 0)
						_val = LOG_TYPE_ERR;
					else if (val.compare(JET_LOG_TYPE_SUCCESS) == 0)
						_val = LOG_TYPE_SUCCESS;
				}
				virtual std::string toString() const {
					switch (_val) {
						case LOG_TYPE_ALL: return JET_LOG_TYPE_ALL;
						case LOG_TYPE_INFO: return JET_LOG_TYPE_INFO;
						case LOG_TYPE_WARN: return JET_LOG_TYPE_WARN;
						case LOG_TYPE_ERR: return JET_LOG_TYPE_ERR;
						case LOG_TYPE_SUCCESS: return JET_LOG_TYPE_SUCCESS;
					}
					return "";
				}
				virtual std::vector<std::string> stringList() const
				{
					std::vector<std::string> list;
					list.push_back(JET_LOG_TYPE_ALL);
					list.push_back(JET_LOG_TYPE_INFO);
					list.push_back(JET_LOG_TYPE_WARN);
					list.push_back(JET_LOG_TYPE_ERR);
					list.push_back(JET_LOG_TYPE_SUCCESS);
					return list;
				}
		};




		enum nJetErrorCode {
			COMMAND_OK	= 0,						// No error
			INVALID_COMMAND = 1,
			PRINTER_NOT_CONNECTED = 2,
			CHECKSUM_ERROR = 3,
			INVALID_MESSAGE_GROUP = 4,
			INVALID_PRINTHEAD = 5,
			INVALID_OUTPUT_ID = 6,
			INVALID_OUTPUT_PULSE = 7,
			INVALID_MSG_NUMBER = 8,
			INVALID_MSG_VARIABLE = 9,

			INVALID_DATETIME_VALUE = 13,
			USB_NOT_CONNECTED = 14,
			INVALID_EVENT_TYPE = 15,
			INVALID_VALUE = 16,
			INVALID_IP = 17,
			INVALID_PRINTHEAD_ID = 18,

			INVALID_NET_ADAPTER = 20,
			INVALID_NET_MASK = 21,
			INVALID_GATEWAY = 22,
			INVALID_DNS = 23,
			INVALID_PULSES = 24,
			INVALID_WHEEL = 25,
			INVALID_ABC = 26,
			INVALID_MAX_TIME_PRINT = 27,
			INVALID_OVERLAPPING_TYPE = 28,
			INVALID_HORIZONTAL_RESOLUTION = 29,

			INVALID_DEFAULT_FONT = 30,
			INVALID_LAMP_CONTROL_TIME = 31,
			INVALID_XR_OFFSET = 32,
			INVALID_PHOTOCELL_FILTER = 33,
			INVALID_PRINT_MODE = 34,
			INVALID_IP_ADDR_TYPE = 35,
			IP_ALREADY_CONFIGURED = 36,
			IP_NO_PING_RESPONSE = 37,
			PRINTHEAD_NOT_ASSIGNED = 38,

			SPECIFIC_NISX_COMMAND = 40,
			MESSAGE_NUMBER_NOT_FOUND = 41,

			MISSING_FILENAME_ATTRIBUTTE = 44,
			NISX_INVALID_FORMAT = 45,
			NISX_PARSING_ERROR = 46,

			COMMAND_UNKOWN_ERROR				//Last error for unknown code
		};
		class JetErrorCode : public Utils::SmartEnum<nJetErrorCode>
		{
			public:
				JetErrorCode() : SmartEnum() {_val = COMMAND_UNKOWN_ERROR;}
				JetErrorCode(nJetErrorCode n) : SmartEnum() {_val = n;}
				virtual ~JetErrorCode(){}
				virtual void operator = (const enum nJetErrorCode& v){_val = v;}
				virtual void operator = (const std::string& val){
					if (val.compare(ERROR_CODE_COMMAND_OK) == 0)
						_val = COMMAND_OK;
					else if (val.compare(ERROR_CODE_INVALID_COMMAND) == 0)
						_val = INVALID_COMMAND;
					else if (val.compare(ERROR_CODE_NOT_CONNECTED) == 0)
						_val = PRINTER_NOT_CONNECTED;
					else if (val.compare(ERROR_CODE_CHECKSUM_ERROR) == 0)
						_val = CHECKSUM_ERROR;
					else if (val.compare(ERROR_CODE_INVALID_MESSAGE_GROUP) == 0)
						_val = INVALID_MESSAGE_GROUP;
					else if (val.compare(ERROR_CODE_INVALID_PRINTHEAD) == 0)
						_val = INVALID_PRINTHEAD;
					else if (val.compare(ERROR_CODE_INVALID_OUTPUT_ID) == 0)
						_val = INVALID_OUTPUT_ID;
					else if (val.compare(ERROR_CODE_INVALID_OUTPUT_PULSE) == 0)
						_val = INVALID_OUTPUT_PULSE;
					else if (val.compare(ERROR_CODE_INVALID_MSG_NUMBER) == 0)
						_val = INVALID_MSG_NUMBER;
					else if (val.compare(ERROR_CODE_INVALID_MSG_VARIABLE) == 0)
						_val = INVALID_MSG_VARIABLE;
					else if (val.compare(ERROR_CODE_INVALID_DATETIME_VALUE) == 0)
						_val = INVALID_DATETIME_VALUE;
					else if (val.compare(ERROR_CODE_USB_NOT_CONNECTED) == 0)
						_val = USB_NOT_CONNECTED;
					else if (val.compare(ERROR_CODE_INVALID_EVENT_TYPE) == 0)
						_val = INVALID_EVENT_TYPE;
					else if (val.compare(ERROR_CODE_INVALID_VALUE) == 0)
						_val = INVALID_VALUE;
					else if (val.compare(ERROR_CODE_INVALID_IP) == 0)
						_val = INVALID_IP;
					else if (val.compare(ERROR_CODE_INVALID_PRINTHEAD_ID) == 0)
						_val = INVALID_PRINTHEAD_ID;
					else if (val.compare(ERROR_CODE_INVALID_NET_ADAPTER) == 0)
						_val = INVALID_NET_ADAPTER;
					else if (val.compare(ERROR_CODE_INVALID_NET_MASK) == 0)
						_val = INVALID_NET_MASK;
					else if (val.compare(ERROR_CODE_INVALID_GATEWAY) == 0)
						_val = INVALID_GATEWAY;
					else if (val.compare(ERROR_CODE_INVALID_DNS) == 0)
						_val = INVALID_DNS;
					else if (val.compare(ERROR_CODE_INVALID_PULSES) == 0)
						_val = INVALID_PULSES;
					else if (val.compare(ERROR_CODE_INVALID_WHEEL) == 0)
						_val = INVALID_WHEEL;
					else if (val.compare(ERROR_CODE_INVALID_ABC) == 0)
						_val = INVALID_ABC;
					else if (val.compare(ERROR_CODE_INVALID_MAX_TIME_PRINT) == 0)
						_val = INVALID_MAX_TIME_PRINT;
					else if (val.compare(ERROR_CODE_INVALID_OVERLAPPING_TYPE) == 0)
						_val = INVALID_OVERLAPPING_TYPE;
					else if (val.compare(ERROR_CODE_INVALID_HORIZONTAL_RESOLUTION) == 0)
						_val = INVALID_HORIZONTAL_RESOLUTION;
					else if (val.compare(ERROR_CODE_INVALID_DEFAULT_FONT) == 0)
						_val = INVALID_DEFAULT_FONT;
					else if (val.compare(ERROR_CODE_INVALID_LAMP_CONTROL_TIME) == 0)
						_val = INVALID_LAMP_CONTROL_TIME;
					else if (val.compare(ERROR_CODE_INVALID_XR_OFFSET) == 0)
						_val = INVALID_XR_OFFSET;
					else if (val.compare(ERROR_CODE_INVALID_PHOTOCELL_FILTER) == 0)
						_val = INVALID_PHOTOCELL_FILTER;
					else if (val.compare(ERROR_CODE_INVALID_PRINT_MODE) == 0)
						_val = INVALID_PRINT_MODE;
					else if (val.compare(ERROR_CODE_INVALID_IP_ADDR_TYPE) == 0)
						_val = INVALID_IP_ADDR_TYPE;
					else if (val.compare(ERROR_CODE_IP_ALREADY_CONFIGURED) == 0)
						_val = IP_ALREADY_CONFIGURED;
					else if (val.compare(ERROR_CODE_IP_NO_PING_RESPONSE) == 0)
						_val = IP_NO_PING_RESPONSE;
					else if (val.compare(ERROR_CODE_PRINTHEAD_NOT_ASSIGNED) == 0)
						_val = PRINTHEAD_NOT_ASSIGNED;
					else if (val.compare(ERROR_CODE_SPECIFIC_NISX_COMMAND) == 0)
						_val = SPECIFIC_NISX_COMMAND;
					else if (val.compare(ERROR_CODE_MESSAGE_NUMBER_NOT_FOUND) == 0)
						_val = MESSAGE_NUMBER_NOT_FOUND;
					else if (val.compare(ERROR_CODE_MISSING_FILENAME_ATTRIBUTTE) == 0)
						_val = MISSING_FILENAME_ATTRIBUTTE;
					else if (val.compare(ERROR_CODE_NISX_INVALID_FORMAT) == 0)
						_val = NISX_INVALID_FORMAT;
					else if (val.compare(ERROR_CODE_NISX_PARSING_ERROR) == 0)
						_val = NISX_PARSING_ERROR;
					else if (val.compare(ERROR_CODE_UNKNOWN) == 0)
						_val = COMMAND_UNKOWN_ERROR;
				}
				virtual std::string toString() const {
					switch (_val) {
						case COMMAND_OK:					return ERROR_CODE_COMMAND_OK;
						case PRINTER_NOT_CONNECTED:			return ERROR_CODE_NOT_CONNECTED;
						case CHECKSUM_ERROR: 				return ERROR_CODE_CHECKSUM_ERROR;
						case INVALID_MESSAGE_GROUP: 		return ERROR_CODE_INVALID_MESSAGE_GROUP;
						case INVALID_PRINTHEAD: 			return ERROR_CODE_INVALID_PRINTHEAD;
						case INVALID_OUTPUT_ID: 			return ERROR_CODE_INVALID_OUTPUT_ID;
						case INVALID_OUTPUT_PULSE: 			return ERROR_CODE_INVALID_OUTPUT_PULSE;
						case INVALID_MSG_NUMBER: 			return ERROR_CODE_INVALID_MSG_NUMBER;
						case INVALID_MSG_VARIABLE: 			return ERROR_CODE_INVALID_MSG_VARIABLE;
						case INVALID_DATETIME_VALUE: 		return ERROR_CODE_INVALID_DATETIME_VALUE;
						case USB_NOT_CONNECTED: 			return ERROR_CODE_USB_NOT_CONNECTED;
						case INVALID_EVENT_TYPE: 			return ERROR_CODE_INVALID_EVENT_TYPE;
						case INVALID_VALUE: 				return ERROR_CODE_INVALID_VALUE;
						case INVALID_IP: 					return ERROR_CODE_INVALID_IP;
						case INVALID_PRINTHEAD_ID: 			return ERROR_CODE_INVALID_PRINTHEAD_ID;
						case INVALID_NET_ADAPTER: 			return ERROR_CODE_INVALID_NET_ADAPTER;
						case INVALID_NET_MASK: 				return ERROR_CODE_INVALID_NET_MASK;
						case INVALID_GATEWAY: 				return ERROR_CODE_INVALID_GATEWAY;
						case INVALID_DNS: 					return ERROR_CODE_INVALID_DNS;
						case INVALID_PULSES: 				return ERROR_CODE_INVALID_PULSES;
						case INVALID_WHEEL: 				return ERROR_CODE_INVALID_WHEEL;
						case INVALID_ABC: 					return ERROR_CODE_INVALID_ABC;
						case INVALID_MAX_TIME_PRINT: 		return ERROR_CODE_INVALID_MAX_TIME_PRINT;
						case INVALID_OVERLAPPING_TYPE: 		return ERROR_CODE_INVALID_OVERLAPPING_TYPE;
						case INVALID_HORIZONTAL_RESOLUTION: return ERROR_CODE_INVALID_HORIZONTAL_RESOLUTION;
						case INVALID_DEFAULT_FONT: 			return ERROR_CODE_INVALID_DEFAULT_FONT;
						case INVALID_LAMP_CONTROL_TIME: 	return ERROR_CODE_INVALID_LAMP_CONTROL_TIME;
						case INVALID_XR_OFFSET: 			return ERROR_CODE_INVALID_XR_OFFSET;
						case INVALID_PHOTOCELL_FILTER: 		return ERROR_CODE_INVALID_PHOTOCELL_FILTER;
						case INVALID_PRINT_MODE: 			return ERROR_CODE_INVALID_PRINT_MODE;
						case INVALID_IP_ADDR_TYPE: 			return ERROR_CODE_INVALID_IP_ADDR_TYPE;
						case IP_ALREADY_CONFIGURED: 		return ERROR_CODE_IP_ALREADY_CONFIGURED;
						case IP_NO_PING_RESPONSE: 			return ERROR_CODE_IP_NO_PING_RESPONSE;
						case PRINTHEAD_NOT_ASSIGNED: 		return ERROR_CODE_PRINTHEAD_NOT_ASSIGNED;
						case SPECIFIC_NISX_COMMAND: 		return ERROR_CODE_SPECIFIC_NISX_COMMAND;
						case MESSAGE_NUMBER_NOT_FOUND: 		return ERROR_CODE_MESSAGE_NUMBER_NOT_FOUND;
						case MISSING_FILENAME_ATTRIBUTTE: 	return ERROR_CODE_MISSING_FILENAME_ATTRIBUTTE;
						case NISX_INVALID_FORMAT: 			return ERROR_CODE_NISX_INVALID_FORMAT;
						case NISX_PARSING_ERROR:			return ERROR_CODE_NISX_PARSING_ERROR;
						default:							return ERROR_CODE_UNKNOWN;
					}
					return "";
				}

				virtual std::vector<std::string> stringList() const
				{
					std::vector<std::string> list;
					list.push_back(ERROR_CODE_COMMAND_OK);
					list.push_back(ERROR_CODE_NOT_CONNECTED);
					list.push_back(ERROR_CODE_CHECKSUM_ERROR);
					list.push_back(ERROR_CODE_INVALID_MESSAGE_GROUP);
					list.push_back(ERROR_CODE_INVALID_PRINTHEAD);
					list.push_back(ERROR_CODE_INVALID_OUTPUT_ID);
					list.push_back(ERROR_CODE_INVALID_OUTPUT_PULSE);
					list.push_back(ERROR_CODE_INVALID_MSG_NUMBER);
					list.push_back(ERROR_CODE_INVALID_MSG_VARIABLE);
					list.push_back(ERROR_CODE_INVALID_DATETIME_VALUE);
					list.push_back(ERROR_CODE_USB_NOT_CONNECTED);
					list.push_back(ERROR_CODE_INVALID_EVENT_TYPE);
					list.push_back(ERROR_CODE_INVALID_VALUE);
					list.push_back(ERROR_CODE_INVALID_IP);
					list.push_back(ERROR_CODE_INVALID_PRINTHEAD_ID);
					list.push_back(ERROR_CODE_INVALID_NET_ADAPTER);
					list.push_back(ERROR_CODE_INVALID_NET_MASK);
					list.push_back(ERROR_CODE_INVALID_GATEWAY);
					list.push_back(ERROR_CODE_INVALID_DNS);
					list.push_back(ERROR_CODE_INVALID_PULSES);
					list.push_back(ERROR_CODE_INVALID_WHEEL);
					list.push_back(ERROR_CODE_INVALID_ABC);
					list.push_back(ERROR_CODE_INVALID_MAX_TIME_PRINT);
					list.push_back(ERROR_CODE_INVALID_OVERLAPPING_TYPE);
					list.push_back(ERROR_CODE_INVALID_HORIZONTAL_RESOLUTION);
					list.push_back(ERROR_CODE_INVALID_DEFAULT_FONT);
					list.push_back(ERROR_CODE_INVALID_LAMP_CONTROL_TIME);
					list.push_back(ERROR_CODE_INVALID_XR_OFFSET);
					list.push_back(ERROR_CODE_INVALID_PHOTOCELL_FILTER);
					list.push_back(ERROR_CODE_INVALID_PRINT_MODE);
					list.push_back(ERROR_CODE_INVALID_IP_ADDR_TYPE);
					list.push_back(ERROR_CODE_IP_ALREADY_CONFIGURED);
					list.push_back(ERROR_CODE_IP_NO_PING_RESPONSE);
					list.push_back(ERROR_CODE_PRINTHEAD_NOT_ASSIGNED);
					list.push_back(ERROR_CODE_SPECIFIC_NISX_COMMAND);
					list.push_back(ERROR_CODE_MESSAGE_NUMBER_NOT_FOUND);
					list.push_back(ERROR_CODE_MISSING_FILENAME_ATTRIBUTTE);
					list.push_back(ERROR_CODE_NISX_INVALID_FORMAT);
					list.push_back(ERROR_CODE_NISX_PARSING_ERROR);
					return list;
				}
		};

		enum nJetConfigItem{
			CONFIG_ITEM_PH_ID = 0,
			CONFIG_ITEM_PH_IP_ADDRESS,
			CONFIG_ITEM_PRINTERDIRECTION,
			CONFIG_ITEM_BITMAPINVERTED,
			CONFIG_ITEM_PRINTSPEED,
			CONFIG_ITEM_PRINTDELAY,
			CONFIG_ITEM_HORIZONTAL_RESOLUTION,
			CONFIG_ITEM_ENCODER_ENABLED,
			CONFIG_ITEM_ENCODER_PULSES,
			CONFIG_ITEM_ENCODER_WHEEL,
			CONFIG_ITEM_ENCODER_ABC_PITCH,
			CONFIG_ITEM_PRINTINGLIST,
			CONFIG_ITEM_FIFO,
			CONFIG_ITEM_DELAY_IN_POINTS,
			CONFIG_ITEM_STB_INC_SSCC,
			CONFIG_ITEM_SEND_IMG_AFTER_PRINT,
			CONFIG_ITEM_STB_RESET_PRINTING_LIST,
			CONFIG_ITEM_LINE_ID,
			CONFIG_ITEM_MACHINE_ID,
			CONFIG_ITEM_MAX_PRINT_TIME,
			CONFIG_ITEM_OPTIMIZE_BARCODE,
			CONFIG_ITEM_OVERLAPPING_TYPE,
			CONFIG_ITEM_DEFAULT_FONT,
			CONFIG_ITEM_LAMP_CONTROL,
			CONFIG_ITEM_LAMP_CONTROL_TIME,
			CONFIG_ITEM_XROFFSET,
			CONFIG_ITEM_CELL_FILTER,
			CONFIG_ITEM_PRINT_MODE,
			CONFIG_ITEM_NETWORK_ADAPTER,
			CONFIG_ITEM_NET_IP_ADDRESS_VALUE,
			CONFIG_ITEM_NET_IP_ADDRESS_TYPE,
			CONFIG_ITEM_NET_IP_ADDRESS_MASK,
			CONFIG_ITEM_NET_GATEWAY_VALUE,
			CONFIG_ITEM_NET_GATEWAY_TYPE,
			CONFIG_ITEM_NET_DNS,
			CONFIG_ITEM_NET_DNS_TYPE,
			CONFIG_ITEM_INVALID
		};
		class JetConfigItem : public Utils::SmartEnum<nJetConfigItem>
		{
			public:
				JetConfigItem() : SmartEnum() {_val = CONFIG_ITEM_INVALID;}
				JetConfigItem(nJetConfigItem n) : SmartEnum() {_val = n;}
				virtual ~JetConfigItem(){}
				virtual void operator = (const enum nJetConfigItem& v){_val = v;}
				virtual void operator = (const std::string& val){
					if (val.compare(JET_CONFIG_ITEM_PH_ID) == 0)						_val = CONFIG_ITEM_PH_ID;
					else if (val.compare(JET_CONFIG_ITEM_PH_IP_ADDRESS) == 0)			_val = CONFIG_ITEM_PH_IP_ADDRESS;
					else if (val.compare(JET_CONFIG_ITEM_PRINTERDIRECTION) == 0)		_val = CONFIG_ITEM_PRINTERDIRECTION;
					else if (val.compare(JET_CONFIG_ITEM_BITMAPINVERTED) == 0)			_val = CONFIG_ITEM_BITMAPINVERTED;
					else if (val.compare(JET_CONFIG_ITEM_PRINTSPEED) == 0)				_val = CONFIG_ITEM_PRINTSPEED;
					else if (val.compare(JET_CONFIG_ITEM_PRINTDELAY) == 0)				_val = CONFIG_ITEM_PRINTDELAY;
					else if (val.compare(JET_CONFIG_ITEM_HORIZONTAL_RESOLUTION) == 0)	_val = CONFIG_ITEM_HORIZONTAL_RESOLUTION;
					else if (val.compare(JET_CONFIG_ITEM_ENCODER_ENABLED) == 0)			_val = CONFIG_ITEM_ENCODER_ENABLED;
					else if (val.compare(JET_CONFIG_ITEM_ENCODER_PULSES) == 0)			_val = CONFIG_ITEM_ENCODER_PULSES;
					else if (val.compare(JET_CONFIG_ITEM_ENCODER_WHEEL) == 0)			_val = CONFIG_ITEM_ENCODER_WHEEL;
					else if (val.compare(JET_CONFIG_ITEM_ENCODER_ABC_PITCH) == 0)		_val = CONFIG_ITEM_ENCODER_ABC_PITCH;
					else if (val.compare(JET_CONFIG_ITEM_PRINTINGLIST) == 0)			_val = CONFIG_ITEM_PRINTINGLIST;
					else if (val.compare(JET_CONFIG_ITEM_FIFO) == 0)					_val = CONFIG_ITEM_FIFO;
					else if (val.compare(JET_CONFIG_ITEM_DELAY_IN_POINTS) == 0)			_val = CONFIG_ITEM_DELAY_IN_POINTS;
					else if (val.compare(JET_CONFIG_ITEM_STB_INC_SSCC) == 0)			_val = CONFIG_ITEM_STB_INC_SSCC;
					else if (val.compare(JET_CONFIG_ITEM_SEND_IMG_AFTER_PRINT) == 0)	_val = CONFIG_ITEM_SEND_IMG_AFTER_PRINT;
					else if (val.compare(JET_CONFIG_ITEM_STB_RESET_PRINTING_LIST) == 0)	_val = CONFIG_ITEM_STB_RESET_PRINTING_LIST;
					else if (val.compare(JET_CONFIG_ITEM_LINE_ID) == 0)					_val = CONFIG_ITEM_LINE_ID;
					else if (val.compare(JET_CONFIG_ITEM_MACHINE_ID) == 0)				_val = CONFIG_ITEM_MACHINE_ID;
					else if (val.compare(JET_CONFIG_ITEM_MAX_PRINT_TIME) == 0)			_val = CONFIG_ITEM_MAX_PRINT_TIME;
					else if (val.compare(JET_CONFIG_ITEM_OPTIMIZE_BARCODE) == 0)		_val = CONFIG_ITEM_OPTIMIZE_BARCODE;
					else if (val.compare(JET_CONFIG_ITEM_OVERLAPPING_TYPE) == 0)		_val = CONFIG_ITEM_OVERLAPPING_TYPE;
					else if (val.compare(JET_CONFIG_ITEM_DEFAULT_FONT) == 0)			_val = CONFIG_ITEM_DEFAULT_FONT;
					else if (val.compare(JET_CONFIG_ITEM_LAMP_CONTROL) == 0)			_val = CONFIG_ITEM_LAMP_CONTROL;
					else if (val.compare(JET_CONFIG_ITEM_LAMP_CONTROL_TIME) == 0)		_val = CONFIG_ITEM_LAMP_CONTROL_TIME;
					else if (val.compare(JET_CONFIG_ITEM_XROFFSET) == 0)				_val = CONFIG_ITEM_XROFFSET;
					else if (val.compare(JET_CONFIG_ITEM_CELL_FILTER) == 0)				_val = CONFIG_ITEM_CELL_FILTER;
					else if (val.compare(JET_CONFIG_ITEM_PRINT_MODE) == 0)				_val = CONFIG_ITEM_PRINT_MODE;
					else if (val.compare(JET_CONFIG_ITEM_NETWORK_ADAPTER) == 0)			_val = CONFIG_ITEM_NETWORK_ADAPTER;
					else if (val.compare(JET_CONFIG_ITEM_NET_IP_ADDRESS_VALUE) == 0)	_val = CONFIG_ITEM_NET_IP_ADDRESS_VALUE;
					else if (val.compare(JET_CONFIG_ITEM_NET_IP_ADDRESS_TYPE) == 0)		_val = CONFIG_ITEM_NET_IP_ADDRESS_TYPE;
					else if (val.compare(JET_CONFIG_ITEM_NET_IP_ADDRESS_MASK) == 0)		_val = CONFIG_ITEM_NET_IP_ADDRESS_MASK;
					else if (val.compare(JET_CONFIG_ITEM_NET_GATEWAY_VALUE) == 0)		_val = CONFIG_ITEM_NET_GATEWAY_VALUE;
					else if (val.compare(JET_CONFIG_ITEM_NET_GATEWAY_TYPE) == 0)		_val = CONFIG_ITEM_NET_GATEWAY_TYPE;
					else if (val.compare(JET_CONFIG_ITEM_NET_DNS) == 0)					_val = CONFIG_ITEM_NET_DNS;
					else if (val.compare(JET_CONFIG_ITEM_NET_DNS_TYPE) == 0)			_val = CONFIG_ITEM_NET_DNS_TYPE;
				}
				virtual std::string toString() const {
					switch (_val) {
						case CONFIG_ITEM_PH_ID:						return JET_CONFIG_ITEM_PH_ID;
						case CONFIG_ITEM_PH_IP_ADDRESS:				return JET_CONFIG_ITEM_PH_IP_ADDRESS;
						case CONFIG_ITEM_PRINTERDIRECTION:			return JET_CONFIG_ITEM_PRINTERDIRECTION;
						case CONFIG_ITEM_BITMAPINVERTED:			return JET_CONFIG_ITEM_BITMAPINVERTED;
						case CONFIG_ITEM_PRINTSPEED:				return JET_CONFIG_ITEM_PRINTSPEED;
						case CONFIG_ITEM_PRINTDELAY:				return JET_CONFIG_ITEM_PRINTDELAY;
						case CONFIG_ITEM_HORIZONTAL_RESOLUTION:		return JET_CONFIG_ITEM_HORIZONTAL_RESOLUTION;
						case CONFIG_ITEM_ENCODER_ENABLED:			return JET_CONFIG_ITEM_ENCODER_ENABLED;
						case CONFIG_ITEM_ENCODER_PULSES:			return JET_CONFIG_ITEM_ENCODER_PULSES;
						case CONFIG_ITEM_ENCODER_WHEEL:				return JET_CONFIG_ITEM_ENCODER_WHEEL;
						case CONFIG_ITEM_ENCODER_ABC_PITCH:			return JET_CONFIG_ITEM_ENCODER_ABC_PITCH;
						case CONFIG_ITEM_PRINTINGLIST:				return JET_CONFIG_ITEM_PRINTINGLIST;
						case CONFIG_ITEM_FIFO:						return JET_CONFIG_ITEM_FIFO;
						case CONFIG_ITEM_DELAY_IN_POINTS:			return JET_CONFIG_ITEM_DELAY_IN_POINTS;
						case CONFIG_ITEM_STB_INC_SSCC:				return JET_CONFIG_ITEM_STB_INC_SSCC;
						case CONFIG_ITEM_SEND_IMG_AFTER_PRINT:		return JET_CONFIG_ITEM_SEND_IMG_AFTER_PRINT;
						case CONFIG_ITEM_STB_RESET_PRINTING_LIST:	return JET_CONFIG_ITEM_STB_RESET_PRINTING_LIST;
						case CONFIG_ITEM_LINE_ID:					return JET_CONFIG_ITEM_LINE_ID;
						case CONFIG_ITEM_MACHINE_ID:				return JET_CONFIG_ITEM_MACHINE_ID;
						case CONFIG_ITEM_MAX_PRINT_TIME:			return JET_CONFIG_ITEM_MAX_PRINT_TIME;
						case CONFIG_ITEM_OPTIMIZE_BARCODE:			return JET_CONFIG_ITEM_OPTIMIZE_BARCODE;
						case CONFIG_ITEM_OVERLAPPING_TYPE:			return JET_CONFIG_ITEM_OVERLAPPING_TYPE;
						case CONFIG_ITEM_DEFAULT_FONT:				return JET_CONFIG_ITEM_DEFAULT_FONT;
						case CONFIG_ITEM_LAMP_CONTROL:				return JET_CONFIG_ITEM_LAMP_CONTROL;
						case CONFIG_ITEM_LAMP_CONTROL_TIME:			return JET_CONFIG_ITEM_LAMP_CONTROL_TIME;
						case CONFIG_ITEM_XROFFSET:					return JET_CONFIG_ITEM_XROFFSET;
						case CONFIG_ITEM_CELL_FILTER:				return JET_CONFIG_ITEM_CELL_FILTER;
						case CONFIG_ITEM_PRINT_MODE:				return JET_CONFIG_ITEM_PRINT_MODE;
						case CONFIG_ITEM_NETWORK_ADAPTER:			return JET_CONFIG_ITEM_NETWORK_ADAPTER;
						case CONFIG_ITEM_NET_IP_ADDRESS_VALUE:		return JET_CONFIG_ITEM_NET_IP_ADDRESS_VALUE;
						case CONFIG_ITEM_NET_IP_ADDRESS_TYPE:		return JET_CONFIG_ITEM_NET_IP_ADDRESS_TYPE;
						case CONFIG_ITEM_NET_IP_ADDRESS_MASK:		return JET_CONFIG_ITEM_NET_IP_ADDRESS_MASK;
						case CONFIG_ITEM_NET_GATEWAY_VALUE:			return JET_CONFIG_ITEM_NET_GATEWAY_VALUE;
						case CONFIG_ITEM_NET_GATEWAY_TYPE:			return JET_CONFIG_ITEM_NET_GATEWAY_TYPE;
						case CONFIG_ITEM_NET_DNS:					return JET_CONFIG_ITEM_NET_DNS;
						case CONFIG_ITEM_NET_DNS_TYPE:				return JET_CONFIG_ITEM_NET_DNS_TYPE;
						case CONFIG_ITEM_INVALID:					return "";
					}
					return "";
				}

				virtual std::vector<std::string> stringList() const
				{
					std::vector<std::string> list;
					list.push_back(JET_CONFIG_ITEM_PH_ID);
					list.push_back(JET_CONFIG_ITEM_PH_IP_ADDRESS);
					list.push_back(JET_CONFIG_ITEM_PRINTERDIRECTION);
					list.push_back(JET_CONFIG_ITEM_BITMAPINVERTED);
					list.push_back(JET_CONFIG_ITEM_PRINTSPEED);
					list.push_back(JET_CONFIG_ITEM_PRINTDELAY);
					list.push_back(JET_CONFIG_ITEM_HORIZONTAL_RESOLUTION);
					list.push_back(JET_CONFIG_ITEM_ENCODER_ENABLED);
					list.push_back(JET_CONFIG_ITEM_ENCODER_PULSES);
					list.push_back(JET_CONFIG_ITEM_ENCODER_WHEEL);
					list.push_back(JET_CONFIG_ITEM_ENCODER_ABC_PITCH);
					list.push_back(JET_CONFIG_ITEM_PRINTINGLIST);
					list.push_back(JET_CONFIG_ITEM_FIFO);
					list.push_back(JET_CONFIG_ITEM_DELAY_IN_POINTS);
					list.push_back(JET_CONFIG_ITEM_STB_INC_SSCC);
					list.push_back(JET_CONFIG_ITEM_SEND_IMG_AFTER_PRINT);
					list.push_back(JET_CONFIG_ITEM_STB_RESET_PRINTING_LIST);
					list.push_back(JET_CONFIG_ITEM_LINE_ID);
					list.push_back(JET_CONFIG_ITEM_MACHINE_ID);
					list.push_back(JET_CONFIG_ITEM_MAX_PRINT_TIME);
					list.push_back(JET_CONFIG_ITEM_OPTIMIZE_BARCODE);
					list.push_back(JET_CONFIG_ITEM_OVERLAPPING_TYPE);
					list.push_back(JET_CONFIG_ITEM_DEFAULT_FONT);
					list.push_back(JET_CONFIG_ITEM_LAMP_CONTROL);
					list.push_back(JET_CONFIG_ITEM_LAMP_CONTROL_TIME);
					list.push_back(JET_CONFIG_ITEM_XROFFSET);
					list.push_back(JET_CONFIG_ITEM_CELL_FILTER);
					list.push_back(JET_CONFIG_ITEM_PRINT_MODE);
					list.push_back(JET_CONFIG_ITEM_NETWORK_ADAPTER);
					list.push_back(JET_CONFIG_ITEM_NET_IP_ADDRESS_VALUE);
					list.push_back(JET_CONFIG_ITEM_NET_IP_ADDRESS_TYPE);
					list.push_back(JET_CONFIG_ITEM_NET_IP_ADDRESS_MASK);
					list.push_back(JET_CONFIG_ITEM_NET_GATEWAY_VALUE);
					list.push_back(JET_CONFIG_ITEM_NET_GATEWAY_TYPE);
					list.push_back(JET_CONFIG_ITEM_NET_DNS);
					list.push_back(JET_CONFIG_ITEM_NET_DNS_TYPE);
					return list;
				}
		};
	}
}


#endif //MACSA_JET_PRINTER_DATA_TYPES_H
