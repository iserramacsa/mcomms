#ifndef M_PROTOCOL_DEFINITIONS_H
#define M_PROTOCOL_DEFINITIONS_H

#include "printer/printer.h"
#include <string>

namespace  Macsa {
	namespace  MProtocol {

#define M_PROTOCOL_PORT	9991

#define MWIND				"WIND"
#define MWIND_ID_ATTR		"id"

#define MERROR				"ERROR"
#define MERROR_CODE_ATTR	"Code"

#define MLIVE				"LIVE"
#define MLIVE_DT_ATTR		"DateTime"
#define MLIVE_STATUS_ATTR	"StatusChanged"
#define MLIVE_CONFIG_ATTR	"ConfigChanged"
#define MLIVE_FILES_ATTR	"FilesChanged"
#define MLIVE_FONTS_ATTR	"FontsChanged"
#define MLIVE_ERRORS_ATTR	"HaveError"


#define MSTATUS				"STATUS"
#define MSTATUS_DT				"DATETIME"
#define MSTATUS_VERSION			"VERSIONS"
#define MSTATUS_VERSION_CTRL		"CONTROLLER"
#define MSTATUS_VERSION_FPGA		"FPGA"
#define MSTATUS_VERSION_API			"API"


#define MCONFIG_GET				"GETCONFIGURATION"
#define MCONFIG_SET				"SETCONFIGURATION"
#define MCONFIG_GENERAL				"GENERAL"
#define MCONFIG_GENERAL_DT				MSTATUS_DT
#define MCONFIG_GENERAL_LOG				"LOG"
#define MCONFIG_GENERAL_LOG_ERR_ATTR 		"traceErrors"
#define MCONFIG_GENERAL_LOG_WARN_ATTR 		"traceWarnings"
#define MCONFIG_GENERAL_LOG_INFO_ATTR 		"traceInfos"
#define MCONFIG_GENERAL_LOG_SAVE_ERR_ATTR 	"saveErrors"
#define MCONFIG_GENERAL_LOG_SAVE_WARN_ATTR 	"saveWarnings"
#define MCONFIG_GENERAL_LOG_SAVE_INFO_ATTR 	"saveInfos"
#define MCONFIG_GENERAL_LOG_COMMS 			"traceComDetails"

#define MCONFIG_CONNECTIONS			"CONNECTIONS"
#define MCONFIG_CONN_NETWORK			"NETWORK"
#define MCONFIG_CONN_NETWORK_ADAPTER		"ADAPTER"
#define MCONFIG_CONN_NETWORK_IP					"IP_ADDRESS"
#define MCONFIG_CONN_NETWORK_SUBNET				"SUBNET_MASK"
#define MCONFIG_CONN_NETWORK_GATEWAY			"GATEWAY"
#define MCONFIG_CONN_NETWORK_DHCP				"DHCP"
#define MCONFIG_CONN_NETWORK_HOSTNAME			"HOSTNAME"
#define MCONFIG_CONN_NETWORK_TCPPORT			"TCP_PORT"
#define MCONFIG_CONN_BLUETOOTH			"BLUETOOTH"
#define MCONFIG_CONN_BLUETOOTH_DEVNAME		"DEVICE_NAME"
#define MCONFIG_CONN_BLUETOOTH_VISIBILITY	"VISIBILITY"
#define MCONFIG_CONN_BLUETOOTH_PASSWORD		"PASSWORD"

#define MPRINTER_BOARDS_LIST	"BOARDS"
#define MPRINTER_BOARD			"BOARD"
#define MPRINTER_BOARD_ID_ATTR	"id"
#define MPRINTER_BOARD_TYPE			"TYPE"
#define MPRINTER_BOARD_ENABLED		"ENABLED"
#define MPRINTER_BOARD_PRINTING		"PRINTING"
#define MPRINTER_BOARD_AUTOSTART	"AUTOSTART"
#define MPRINTER_BOARD_CURRENT_MSG	"CURRENT_MESSAGE"

#define MPRINTER_BOARD_BCD_MODE		"BCD_MODE"
#define MPRINTER_BOARD_BCD_STATUS	"BCD_STATUS"
#define MPRINTER_BOARD_COUNTERS		"COUNTERS"
#define MPRINTER_BOARD_COUNT_ID_ATTR	"id"
#define MPRINTER_BOARD_COUNT_VAL_ATTR	"Value"

#define MPRINTER_BOARD_ERRORS_LIST		"ERRORS"
#define MPRINTER_BOARD_ERROR 			"ERROR"
#define MPRINTER_BOARD_ERR_TYPE_ATTR	"Type"
#define MPRINTER_BOARD_ERR_PRIO_ATTR	"Priority"
#define MPRINTER_BOARD_ERR_CODE_ATTR	"ErrorCode"

#define MPRINTER_BOARD_INPUTS_LIST		"INPUTS"
#define MPRINTER_BOARD_INPUT 			"INPUT"
#define MPRINTER_BOARD_OUTPUTS_LIST		"OUTPUTS"
#define MPRINTER_BOARD_OUTPUT 			"OUTPUT"
#define MPRINTER_BOARD_IO_ID_ATTR		"id"
#define MPRINTER_BOARD_IO_DESCRIPT_ATTR	"Descriptor"
#define MPRINTER_BOARD_IO_VAL_ATTR		"Value"

#define MPRINTER_BOARD_PROPERTIES_LIST	"PROPERTIES"
#define MPRINTER_BOARD_PROPERTY			"PROPERTY"
#define MPRINTER_BOARD_PROPERTY_KEY_ATTR	"Key"
#define MPRINTER_BOARD_PROPERTY_VALUE_ATTR	"Value"


#define FONTS_FILTER	".ttf"
#define NISX_FILTER		".nisx"
#define IMG_FILTER		".png,.jpg,.jpeg,.bmp"
#define NO_FILTER		"*.*"

#define MFILES_GET_LIST				"GETFILESLIST"
#define MFILES_GET_LIST_TYPE_ATTR	"type"
#define MFILES_DEVICE_UNIT			"UNIT"
#define MFILES_DEVICE_UNIT_ATTR		"Name"
#define MFILES_FILE_PATH			"FILE"
#define MFILES_FILE_PATH_ATTR		"Path"

#define MUPDATE					"UPDATE"
#define MUPDATE_PROGRESS_ATTR	"Progress"
#define MUPDATE_STATUS			"STATUS"
#define MUPDATE_HMI_VERSIONS	"HMI_VERSIONS"
#define MUPDATE_HMI_BIN				"HMI"
#define MUPDATE_HMI_BIN_VERSION_ATTR	"Version"
#define MUPDATE_HMI_BIN_MD5SUM_ATTR		"MD5"


		class MErrorCode{
			public:
				enum code_n
				{
					Success						, // No error

					// FILES ERRORS
					FileNotFound				, // the specified file not exist
					FileAlreadyExist			, // in move or copy operations, if the file already exist...
					FileCopyFail				, // copy file operation error
					FileDeleteFail				, // delete file operation error
					FileMoveFail				, // move operation error
					FileMoveIncomplete			, // move operation has copied the source to target, but not delete the source
					FileReadCanNot				, // can't read the file
					FileWriteCanNot				, // can't write the file
					FileWriteIncomplete			, // the write on the file is not complete
					FileUserDataNotFound		, // the name of a user-name-value is not found
					FileInUse					, // the file is currenty in use

					// PARAMS ERRORS
					ParamBoardIdNotFound		, // The BoardId specified by the command was not found
					ParamCounterIdNotFound		, // The CounterId specified by the command was not found
					ParamCounterValueRejected	, // The device has rejected the counter modification
					ParamOutputIdNotFound		, // The output id specified by the command was not found
					ParamCantSetMsgInBcdMode	, // Is not posible set a manual current message if the board is in Bcd mode
					ParamBoardIsEnabled			, // the command requires a enabled board
					ParamBoardIsNotEnabled		, // the command requires a disabled board
					ParamCannotChangeAdapter	, // The server can not change the adapter settings
					ParamInvalidIpAddress		, // The ip is invalid
					ParamInvalidMaskAddress		, // The mask is invalid
					ParamInvalidGatewayAddress	, // The Gateway is invalid
					ParamInvalidPropCount		, // The client can not change the number of properties


					// OTHER GENERIC ERRORS
					GenUnexpectedTag			, // generic xml error

					GenNotImplemented			, // informs that operation is not implemented on the server
					GenLockTimeout				, // Lock data fail

					// NEOTIJ ERRORS
					PcaNotdetected				, // "PCA.NOTDETECTED"				"No connection with PCA"
					PhOvertemp					, // "PH.OVERTEMP"					"Printhead over temperature"
					GenOverspeed				, // "GEN.OVERSPEED"				"Overspeed"
					MsgFormaterror				, // "MSG.FORMATERROR"				"NISX format error"
					MsgNoexist					, // "MSG.NOEXIST"					"Message doesn't exist"
					PhNocartridge				, // "PH.NOCARTRIDGE"				"No cartridge loaded"
					SmcInvalid					, // "SMC.INVALID"					"No valid smartcard on cartridge"
					PhGenfault					, // "PH.GENFAULT"					"Cartridge fault - not valid"
					SmcCartridgeEmpty			, // "SMC.CARTRIDGE_EMPTY"			"Cartridge empty"
					SmcCartridgeOutofdate		, // "SMC.CARTRIDGE_OUTOFDATE"		"Cartridge out of expiration date"
					SmcCartridgeNearend			, // "SMC.CARTRIDGE_NEAREND"		"Cartridge near empty"
					SmcCartridgeInvalid			, // "SMC.UNRECOGNIZED_DATA"		"Cartridge invalid Data"
					SmcInitializingCartridge	, // "PH.INITIALIZING_CARTRIDGE"	"Initializing cartridge "
					SmcHostInvalid,				  // "SMC.HOST_SMARTCARD"			"Invalid Host Smart Card"

					UnknownError
				};
				MErrorCode(code_n code){_code = code;}
				std::string toString();
				code_n fromString(const std::string& code);
			private:
				code_n _code;
		};

		class MTools {
			public:
			static std::string toLower(std::string& str);
			static std::string toLower(const std::string& str);
			static std::string toUpper(std::string& str);
			static std::string toUpper(const std::string& str);

			static std::string toString(bool value);
			static std::string toString(const MErrorCode& code);

			static bool boolfromString(const std::string& value);
		};
	}
}

#endif
