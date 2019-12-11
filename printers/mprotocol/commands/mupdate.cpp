#include "mprotocol/mupdate.h"
#include "mprotocol/mprotocol.h"
#include "mtools.h"

using namespace Macsa;
using namespace Macsa::MProtocol;
using namespace tinyxml2;

MUpdate::MUpdate(Printers::TIJPrinter &printer):
	MCommand(MUPDATE, printer)
{}

MUpdate::~MUpdate()
{}

bool MUpdate::parseRequest(const XMLElement *xml)
{
	return parseSingleCommand(xml);
}

bool MUpdate::parseResponse(const XMLElement *xml)
{
	//	const XMLElement * pwind = getWindNode(wind);
	//	if(pwind != nullptr){
	//		if (valid(pwind))
	//		{
	//			const XMLElement * cmd = pwind->FirstChildElement(MUPDATE);
	//			if (cmd != nullptr)
	//			{
	//				int progress = 0;
	//				std::string status = "";

	//				cmd->QueryIntAttribute(MUPDATE_PROGRESS_ATTR, &progress);

	//				const XMLElement *updateStatus = cmd->FirstChildElement(MUPDATE_STATUS);
	//				if(updateStatus != nullptr && updateStatus->FirstChild() != nullptr) {
	//					const char* text = updateStatus->GetText();
	//					status = (text != nullptr)? text : "";
	//				}
	//				const XMLElement *hmiVersions = cmd->FirstChildElement(MUPDATE_HMI_VERSIONS);
	//				if (hmiVersions != nullptr){
	//					const XMLElement *hmiBin = hmiVersions->FirstChildElement(MUPDATE_HMI_BIN);
	//					while(hmiBin != nullptr){
	//						const char* text = hmiBin->GetText();
	//						std::string path = (text != nullptr)? text : "";
	//						const char* version = hmiBin->Attribute(MUPDATE_HMI_BIN_VERSION_ATTR);
	//						const char* md5 = hmiBin->Attribute(MUPDATE_HMI_BIN_MD5SUM_ATTR);
	//						if (version && md5){
	//							_printer.setHmiBinFile(path, version, md5);
	//						}
	//						hmiBin = hmiBin->NextSiblingElement(MUPDATE_HMI_BIN);
	//					}

	//				}
	//				_printer.setUpdateStatus(progress, status);
	//				return true;
	//			}
	//		}
	//	}

	return false;
}

void MUpdate::buildRequest()
{
//	getNewCommandNode();
}

void MUpdate::buildResponse()
{
//	XMLElement* cmd = getNewCommandNode();
	//	cmd->SetAttribute(MUPDATE_PROGRESS_ATTR, _printer.updateProgress());

	//	std::string status = _printer.updateStatus();
	//	textElement(MUPDATE_STATUS, status, &cmd);
	//	XMLElement *versions = newElement(MUPDATE_HMI_VERSIONS, &cmd);
	//	std::vector<Printer::HmiVersions_t> hmiFiles = _printer.hmiBinFiles();
	//	for (unsigned int i = 0; i < hmiFiles.size(); i++)
	//	{
	//		XMLElement* hmi = textElement(MUPDATE_HMI_BIN, hmiFiles.at(i).path, &versions);
	//		hmi->SetAttribute(MUPDATE_HMI_BIN_VERSION_ATTR, hmiFiles.at(i).version.c_str());
	//		hmi->SetAttribute(MUPDATE_HMI_BIN_MD5SUM_ATTR, hmiFiles.at(i).md5.c_str());
	//	}
}

