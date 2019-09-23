#include "mupdate.h"

using namespace tinyxml2;

/*================================= Server ==================================*/

Macsa::MUpdate::MUpdate(Printer::TijPrinter &printer) :
	MCommandBase (printer)
{}

Macsa::MUpdate::~MUpdate()
{}

void Macsa::MUpdate::build()
{
	XMLElement *cmd = newElement(MUPDATE);
	cmd->SetAttribute(MUPDATE_PROGRESS_ATTR, _printer.updateProgress());

	std::string status = _printer.updateStatus();
	textElement(MUPDATE_STATUS, status, &cmd);
	XMLElement *versions = newElement(MUPDATE_HMI_VERSIONS, &cmd);
	std::vector<Printer::HmiVersions_t> hmiFiles = _printer.hmiBinFiles();
	for (unsigned int i = 0; i < hmiFiles.size(); i++)
	{
		XMLElement* hmi = textElement(MUPDATE_HMI_BIN, hmiFiles.at(i).path, &versions);
		hmi->SetAttribute(MUPDATE_HMI_BIN_VERSION_ATTR, hmiFiles.at(i).version.c_str());
		hmi->SetAttribute(MUPDATE_HMI_BIN_MD5SUM_ATTR, hmiFiles.at(i).md5.c_str());
	}

	setWind(&cmd);
}

bool Macsa::MUpdate::parse(const XMLElement * wind)
{
	return isNoChildrenSingleNode(wind, MUPDATE);
}

/*================================= Client ==================================*/

MProtocolClient::MUpdate::MUpdate(MPrinter &printer) :
	MProtocol::MCommandBase (printer)
{}

MProtocolClient::MUpdate::~MUpdate()
{}

bool MProtocolClient::MUpdate::parse(const XMLElement * wind)
{
	const XMLElement * pwind = getWindNode(wind);
	if(pwind != nullptr){
		if (valid(pwind))
		{
			const XMLElement * cmd = pwind->FirstChildElement(MUPDATE);
			if (cmd != nullptr)
			{
				int progress = 0;
				std::string status = "";

				cmd->QueryIntAttribute(MUPDATE_PROGRESS_ATTR, &progress);

				const XMLElement *updateStatus = cmd->FirstChildElement(MUPDATE_STATUS);
				if(updateStatus != nullptr && updateStatus->FirstChild() != nullptr) {
					const char* text = updateStatus->GetText();
					status = (text != nullptr)? text : "";
				}
				const XMLElement *hmiVersions = cmd->FirstChildElement(MUPDATE_HMI_VERSIONS);
				if (hmiVersions != nullptr){
					const XMLElement *hmiBin = hmiVersions->FirstChildElement(MUPDATE_HMI_BIN);
					while(hmiBin != nullptr){
						const char* text = hmiBin->GetText();
						std::string path = (text != nullptr)? text : "";
						const char* version = hmiBin->Attribute(MUPDATE_HMI_BIN_VERSION_ATTR);
						const char* md5 = hmiBin->Attribute(MUPDATE_HMI_BIN_MD5SUM_ATTR);
						if (version && md5){
							_printer.setHmiBinFile(path, version, md5);
						}
						hmiBin = hmiBin->NextSiblingElement(MUPDATE_HMI_BIN);
					}

				}
				_printer.setUpdateStatus(progress, status);
				return true;
			}
		}
	}
	return false;
}

void MProtocolClient::MUpdate::build()
{
	XMLElement *wind = getWind(true);
	XMLElement *cmd = _doc.NewElement(MUPDATE);
	wind->InsertEndChild(cmd);
}
