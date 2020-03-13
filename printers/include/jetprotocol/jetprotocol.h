#ifndef MACSA_MPROTOCOL_DEFINITIONS_H
#define MACSA_MPROTOCOL_DEFINITIONS_H

#include "printer/printer.h"
#include <string>

namespace  Macsa {
	namespace  JetProtocol {

		#define JET_PROTOCOL_TCP_PORT	9100
		#define JET_PROTOCOL_UDP_PORT	9000

		#define JETWIND						"WIND"
		//Attributes
		#define COMMAND_ATTRIBUTE			"Command"
		#define VALUE_ATTRIBUTE				"Value"
		#define NAME_ATTRIBUTE				"Name"

		//Commands
		#define CMD_GET_COUNTERS            "GetCounters"
		#define CMD_SET_COUNTERS            "SetCounters"
		#define CMD_RESET_COUNTERS          "ResetCounters"
		#define CMD_SET_OUTPUT              "SetOutput"
		#define CMD_GET_SSCC                "GetSSCC"
		#define CMD_INC_SSCC                "Inc_SSCC"
		#define CMD_GET_DATETIME            "GetDateTime"
		#define CMD_SET_DATETIME            "SetDateTime"
		#define CMD_GET_PAUSE               "GetPause"
		#define CMD_SET_PAUSE               "SetPause"
		#define CMD_GET_LOGS                "GetLogs"
		#define CMD_GET_USB_MSG             "GetUSBMessages"
		#define CMD_GET_FILES_LIST          "GetFileDirectoryListing"
		#define CMD_GET_STATUS              "GetStatus"
		#define CMD_GET_PRINTER_VERSIONS    "GetPrinterVersionInfo"
		#define CMD_GET_INSTALLED_FONTS     "GetInstalledFonts"
		#define CMD_GET_MESSAGE_NUM         "MessageNumber"
		#define CMD_SEND_MESSAGE            "SendMessage"
		#define CMD_RESET_MESSAGE           "ResetMessages"
		#define CMD_GET_MESSAGE             "GetMessages"
		#define CMD_CREATE_MESSAGE_GROUP    "MessageGroup"
		#define CMD_SEN_MESSAGE_TO_GROUP    "MessageGroupFile"
		#define CMD_DELETE_MESSAGE_GROUP    "DeleteMessageGroup"
		#define CMD_SET_MESSAGE_VARIABLE    "SetVariable"
		#define CMD_SET_MESSAGE_VARIABLES   "SetVariables"
		#define CMD_GET_MESSAGE_USER_FIELD  "GetUserInputFields"
		#define CMD_SET_MESSAGE_USER_FIELD  "SetUserInputFields"
		#define CMD_SET_PRINT_DIR           "PrinterDirection"
		#define CMD_SET_PRINT_INVERT        "BitmapInverted"
		#define CMD_SET_PRINTHEAD_ENABLE    "PrintHeadsEnabled"
		#define CMD_GET_PRINT_SPEED         "GetPrintSpeed"
		#define CMD_SET_PRINT_SPEED         "SetPrintSpeed"
		#define CMD_GET_PRINT_DELAY         "GetPrintDelay"
		#define CMD_SET_PRINT_DELAY         "SetPrintDelay"
		#define CMD_GET_HOR_RESOLUTION      "GetHorizontalResolution"
		#define CMD_SET_HOR_RESOLUTION      "SetHorizontalResolution"
		#define CMD_GET_CONFIG              "GetPrinterConfig"
		#define CMD_SET_CONFIG              "SetPrinterConfig"
		#define CMD_RESET_INK_ALARM         "ResetINKAlarm"
		#define CMD_GET_NISX_MESSAGE		"GetNisXMessage"
		#define CMD_SET_NISX_MESSAGE		"SetNisXElement"
	} //namespace Protocol
}//namespace Macsa

#endif
