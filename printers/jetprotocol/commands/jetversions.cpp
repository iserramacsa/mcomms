#include "jetprotocol/jetversions.h"
#include "jetprotocol/jetprotocol.h"

using namespace Macsa;
using namespace Macsa::JetProtocol;
using namespace tinyxml2;

JetGetVersions::JetGetVersions(Printers::JetPrinter &printer) :
	JetCommand(CMD_GET_PRINTER_VERSIONS, printer)
{}

void JetGetVersions::buildRequest()
{
	newCommandWind();
}

bool JetGetVersions::parseRequest(const XMLElement *xml)
{
	return isValidWind(xml);
}

void JetGetVersions::buildResponse()
{
	/*XMLElement* cmd =*/ newCommandWind();
	setCommandError(_error);
	//Todo: fill with fonts files
}

bool JetGetVersions::parseResponse(const XMLElement *xml)
{
	bool valid = isValidWind(xml);
	if (valid) {
		parseCommandError();
		if (_error == Printers::nJetErrorCode::COMMAND_OK)
		{
			_printer.clearLibrariesVersions();
			const XMLElement* ePCVersions = xml->FirstChildElement(JET_PC_TAG);
			if (ePCVersions){
				std::map<std::string,std::string> versions;
				for (const XMLElement* eLibrary = ePCVersions->FirstChildElement(JET_ITEM_TAG);
					 eLibrary != nullptr;
					 eLibrary = eLibrary->NextSiblingElement(JET_ITEM_TAG))
				{
					std::string library = getTextAttribute(eLibrary, FILENAME_ATTRIBUTE);
					std::string version = getTextAttribute(eLibrary, VERSION_ATTRIBUTE);
					if (library.length() && version.length()) {
						versions.insert(std::pair<std::string, std::string>(library, version));
					}
				}
				_printer.setLibrariesVersions(versions);
			}
			const XMLElement* eBoards = xml->FirstChildElement(JET_BOARDS_LIST);
			if (eBoards) {
				const XMLElement* ePrinthead = eBoards->FirstChildElement(JET_PRINTHEAD_TAG);
				if (ePrinthead) {
					std::string id = getTextAttribute(ePrinthead, ID_ATTRIBUTE);
					std::string version = getTextAttribute(ePrinthead, VERSION_ATTRIBUTE);
					if (id.length() && version.length()) {
						Printers::JetBoard ph =_printer.board(Printers::nJetBoardType::PRINTHEAD_BOARD, 0);
						ph.setVersion(version);
					}
				}
				const XMLElement* eSignal = eBoards->FirstChildElement(JET_SIGNAL_TAG);
				if (eSignal) {
					std::string id = getTextAttribute(ePrinthead, ID_ATTRIBUTE);
					std::string version = getTextAttribute(ePrinthead, VERSION_ATTRIBUTE);
					if (id.length() && version.length()) {
						Printers::JetBoard signalsBoard =_printer.board(Printers::nJetBoardType::SIGNALS_BOARD, 0);
						signalsBoard.setVersion(version);
					}
				}
			}
		}
	}
	return valid;
}
