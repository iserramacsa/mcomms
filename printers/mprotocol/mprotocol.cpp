#include "mprotocol/mprotocol.h"

using namespace Macsa::MProtocol;

std::string MTools::toLower(std::string &str)
{
	for (std::string::iterator c = str.begin(); c != str.end(); c++){
		*c = static_cast<char>(std::tolower(*c));
	}
	return str;
}

std::string MTools::toLower(const std::string &str)
{
	std::string s = str;
	for (std::string::iterator c = s.begin(); c != s.end(); c++){
		*c = static_cast<char>(std::tolower(*c));
	}
	return s;
}

std::string MTools::toUpper(std::string &str)
{
	for (std::string::iterator c = str.begin(); c != str.end(); c++){
		*c = static_cast<char>(std::toupper(*c));
	}
	return str;
}

std::string MTools::toUpper(const std::string &str)
{
	std::string s = str;
	for (std::string::iterator c = s.begin(); c != s.end(); c++){
		*c = static_cast<char>(std::toupper(*c));
	}
	return s;
}

std::string MTools::toString(bool value)
{
	return (value ? "true" : "false");
}

std::string MErrorCode::toString()
{
	switch (_code) {
		case Success:					return "SUCCESS";

			// FILES ERRORS
		case FileNotFound:				return "FILE.NOT_FOUND";
		case FileAlreadyExist:			return "FILE.ALREADY_EXIST";
		case FileCopyFail:				return "FILE.COPY_FAIL";
		case FileDeleteFail:			return "FILE.DELETE_FAIL";
		case FileMoveFail:				return "FILE.MOVE_FAIL";
		case FileMoveIncomplete:		return "FILE.MOVE_INCOMPLETE";
		case FileReadCanNot:			return "FILE.READ_CAN_NOT";
		case FileWriteCanNot:			return "FILE.WRITE_CAN_NOT";
		case FileWriteIncomplete:		return "FILE.WRITE_INCOMPLETE";
		case FileUserDataNotFound:		return "FILE.USER_DATA_NOT_FOUND";
		case FileInUse:					return "FILE.IN_USE";

			// PARAMS ERRORS
		case ParamBoardIdNotFound:		return "PARAM.BOARD_ID_NOT_FOUND";
		case ParamCounterIdNotFound:	return "PARAM.COUNTER_ID_NOT_FOUND";
		case ParamCounterValueRejected:	return "PARAM.COUNTER_VALUE_REJECTED";
		case ParamOutputIdNotFound:		return "PARAM.OUTPUT_ID_NOT_FOUND";
		case ParamCantSetMsgInBcdMode:	return "PARAM.CANT_SET_MSG_IN_BCD_MODE";
		case ParamBoardIsEnabled:		return "PARAM.BOARD_IS_ENABLED";
		case ParamBoardIsNotEnabled:	return "PARAM.BOARD_IS_NOT_ENABLED";
		case ParamCannotChangeAdapter:	return "PARAM.CANNOT_CHANGE_ADAPTER";
		case ParamInvalidIpAddress:		return "PARAM.INVALID_IP_ADDRESS";
		case ParamInvalidMaskAddress:	return "PARAM.INVALID_MASK_ADDRESS";
		case ParamInvalidGatewayAddress:return "PARAM.INVALID_GATEWAY_ADDRESS";
		case ParamInvalidPropCount:		return "PARAM.INVALID_PROP_COUNT";

			// OTHER GENERIC ERRORS
		case GenUnexpectedTag:			return "GEN.UNEXPECTED_TAG";
		case GenNotImplemented:			return "GEN.NOT_IMPLEMENTED";
		case GenLockTimeout:			return "GEN.LOCK_TIMEOUT";

			// NEOTIJ ERRORS
		case PcaNotdetected:			return "PCA.NOTDETECTED";
		case PhOvertemp:				return "PH.OVERTEMP";
		case GenOverspeed:				return "GEN.OVERSPEED";
		case MsgFormaterror:			return "MSG.FORMATERROR";
		case MsgNoexist:				return "MSG.NOEXIST";
		case PhNocartridge:				return "PH.NOCARTRIDGE";
		case SmcInvalid:				return "SMC.INVALID";
		case PhGenfault:				return "PH.GENFAULT";
		case SmcCartridgeEmpty:			return "SMC.CARTRIDGE_EMPTY";
		case SmcCartridgeOutofdate:		return "SMC.CARTRIDGE_OUTOFDATE";
		case SmcCartridgeNearend:		return "SMC.CARTRIDGE_NEAREND";
		case SmcCartridgeInvalid:		return "SMC.UNRECOGNIZED_DATA";
		case SmcInitializingCartridge:	return "PH.INITIALIZING_CARTRIDGE";
		case SmcHostInvalid:			return "SMC.HOST_SMARTCARD";

		case UnknownError:				return "UNKNOWN";
	}
	return "UNKNOWN";
}

MErrorCode::code_n MErrorCode::fromString(const std::string &code)
{
	if (code.compare("SUCCESS") == 0) {	return Success;}

	// FILES ERRORS
	if (code.compare("FILE.NOT_FOUND")				== 0) {	return FileNotFound;}
	if (code.compare("FILE.ALREADY_EXIST")			== 0) {	return FileAlreadyExist;}
	if (code.compare("FILE.COPY_FAIL")				== 0) {	return FileCopyFail;}
	if (code.compare("FILE.DELETE_FAIL")			== 0) {	return FileDeleteFail;}
	if (code.compare("FILE.MOVE_FAIL")				== 0) {	return FileMoveFail;}
	if (code.compare("FILE.MOVE_INCOMPLETE")		== 0) {	return FileMoveIncomplete;}
	if (code.compare("FILE.READ_CAN_NOT")			== 0) {	return FileReadCanNot;}
	if (code.compare("FILE.WRITE_CAN_NOT")			== 0) {	return FileWriteCanNot;}
	if (code.compare("FILE.WRITE_INCOMPLETE")		== 0) {	return FileWriteIncomplete;}
	if (code.compare("FILE.USER_DATA_NOT_FOUND")	== 0) {	return FileUserDataNotFound;}
	if (code.compare("FILE.IN_USE") 				== 0) {	return FileInUse;}

	// PARAMS ERRORS
	if (code.compare("PARAM.BOARD_ID_NOT_FOUND")		== 0) {	return ParamBoardIdNotFound;}
	if (code.compare("PARAM.COUNTER_ID_NOT_FOUND")		== 0) {	return ParamCounterIdNotFound;}
	if (code.compare("PARAM.COUNTER_VALUE_REJECTED")	== 0) {	return ParamCounterValueRejected;}
	if (code.compare("PARAM.OUTPUT_ID_NOT_FOUND")		== 0) {	return ParamOutputIdNotFound;}
	if (code.compare("PARAM.CANT_SET_MSG_IN_BCD_MODE")	== 0) {	return ParamCantSetMsgInBcdMode;}
	if (code.compare("PARAM.BOARD_IS_ENABLED")			== 0) {	return ParamBoardIsEnabled;}
	if (code.compare("PARAM.BOARD_IS_NOT_ENABLED")		== 0) {	return ParamBoardIsNotEnabled;}
	if (code.compare("PARAM.CANNOT_CHANGE_ADAPTER")		== 0) {	return ParamCannotChangeAdapter;}
	if (code.compare("PARAM.INVALID_IP_ADDRESS")		== 0) {	return ParamInvalidIpAddress;}
	if (code.compare("PARAM.INVALID_MASK_ADDRESS")		== 0) {	return ParamInvalidMaskAddress;}
	if (code.compare("PARAM.INVALID_GATEWAY_ADDRESS")	== 0) {	return ParamInvalidGatewayAddress;}
	if (code.compare("PARAM.INVALID_PROP_COUNT")		== 0) {	return ParamInvalidPropCount;}

	// OTHER GENERIC ERRORS
	if (code.compare("GEN.UNEXPECTED_TAG") 	== 0) {		return GenUnexpectedTag;}
	if (code.compare("GEN.NOT_IMPLEMENTED") == 0) {		return GenNotImplemented;}
	if (code.compare("GEN.LOCK_TIMEOUT") 	== 0) {		return GenLockTimeout;}

	// NEOTIJ ERRORS
	if (code.compare("PCA.NOTDETECTED") 			== 0) {		return PcaNotdetected;}
	if (code.compare("PH.OVERTEMP") 				== 0) {		return PhOvertemp;}
	if (code.compare("GEN.OVERSPEED") 				== 0) {		return GenOverspeed;}
	if (code.compare("MSG.FORMATERROR") 			== 0) {		return MsgFormaterror;}
	if (code.compare("MSG.NOEXIST") 				== 0) {		return MsgNoexist;}
	if (code.compare("PH.NOCARTRIDGE")				== 0) {		return PhNocartridge;}
	if (code.compare("SMC.INVALID") 				== 0) {		return SmcInvalid;}
	if (code.compare("PH.GENFAULT") 				== 0) {		return PhGenfault;}
	if (code.compare("SMC.CARTRIDGE_EMPTY") 		== 0) {		return SmcCartridgeEmpty;}
	if (code.compare("SMC.CARTRIDGE_OUTOFDATE") 	== 0) {		return SmcCartridgeOutofdate;}
	if (code.compare("SMC.CARTRIDGE_NEAREND") 		== 0) {		return SmcCartridgeNearend;}
	if (code.compare("SMC.UNRECOGNIZED_DATA") 		== 0) {		return SmcCartridgeInvalid;}
	if (code.compare("PH.INITIALIZING_CARTRIDGE") 	== 0) {		return SmcInitializingCartridge;}
	if (code.compare("SMC.HOST_SMARTCARD") 			== 0) {		return SmcHostInvalid;}

	return UnknownError;
}


bool MTools::boolfromString(const std::string &value)
{
	return (toLower(value).compare("true") == 0);
}
