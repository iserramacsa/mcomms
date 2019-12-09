#include "mprotocol/mfiles.h"
#include "printer/files.h"
#include "mtools.h"

#define SLASH_CHAR '/'
#define DRIVE_CHARS "//"

using namespace Macsa::MProtocol;
using namespace tinyxml2;

MGetFilesList::MGetFilesList(Printers::TIJPrinter &printer, const std::string &filter) :
	MCommand(MFILES_GET_LIST, printer)
{
	_filter = filter;
}

void MGetFilesList::buildRequest()
{
	XMLElement* cmd = newCommandNode();
	if (cmd != nullptr && filter().length()) {
		cmd->SetAttribute(MFILES_GET_LIST_TYPE_ATTR, filter().c_str());
	}
}

void MGetFilesList::buildResponse()
{
	XMLElement* eCmd = newCommandNode();
	_error = Printers::ErrorCode_n::SUCCESS;

	eCmd->SetAttribute(MFILES_GET_LIST_TYPE_ATTR, _filter.c_str());
	//TODO: Insert requested files (create files server)

	_tools.addWindError(_error);
}

bool MGetFilesList::parseRequest(const XMLElement *xml)
{
	bool valid = false;
	int id  = MTools::XML::getWindId(xml);
	if(id != -1) {
		const XMLElement *cmd = xml->FirstChildElement(commandName().c_str());
		valid = (cmd != nullptr && cmd->NoChildren());
		if (valid){
			_filter ="*.*";
			const char* filter = cmd->Attribute(MFILES_GET_LIST_TYPE_ATTR);
			if (filter != nullptr){
				_filter = filter;
			}
		}
	}

	return valid;
}

bool MGetFilesList::parseResponse(const XMLElement *xml)
{
	bool valid = false;
	int id  = MTools::XML::getWindId(xml);
	if(id != -1) {
		_id = static_cast<unsigned int>(id);
		const XMLElement * cmd = xml->FirstChildElement();
		if (std::string(cmd->Value()).compare(MFILES_GET_LIST) == 0)
		{
			valid = true; //TODO: Refactor
			std::vector<std::string> exts;
			const char* filter = cmd->Attribute(MFILES_GET_LIST_TYPE_ATTR);
			if (filter != nullptr && strlen(filter) > 1) {
				std::string f = filter;
				size_t coma = 0;
				while ((coma = f.find_first_of(",", coma)) != f.npos)
				{
					exts.push_back(f.substr(0, coma));
					f = f.substr(coma + 1);
				}
				if (f.length()) {
					exts.push_back(f);
				}
			}

			/* Update active units*/
			std::vector<std::string> drives;
			const XMLElement * unit = cmd->FirstChildElement(MFILES_DEVICE_UNIT);
			while (unit != nullptr) {
				const char* drive = unit->Attribute(MFILES_DEVICE_UNIT_ATTR);
				if (drive != nullptr) {
					drives.push_back(drive);
				}
				unit = unit->NextSiblingElement(MFILES_DEVICE_UNIT);
			}
			/* remove all filtered files */
			_printer.files()->updateDrives(drives);
			for (unsigned int i = 0; i < drives.size(); ++i) {
				_printer.files()->clearFilesOfType(drives.at(i), exts);
			}

			/* Insert new files */
			const XMLElement * xmlfile = cmd->FirstChildElement(MFILES_FILE_PATH);
			while (xmlfile != nullptr) {
				const char* path = xmlfile->Attribute(MFILES_FILE_PATH_ATTR);
				if (path != nullptr) {
					insertFileToPrinterData(path);
				}
				xmlfile = xmlfile->NextSiblingElement(MFILES_FILE_PATH);
			}
		}
	}
	return valid;
}

std::string MGetFilesList::filter() const
{
	return _filter;
}

void MGetFilesList::splitFilePwd(const std::string &pwd, std::string &drive, std::string &folder, std::string &file)
{
	drive.clear();
	folder.clear();
	file = pwd;
	std::vector<std::string> s;

	size_t slash = file.find(DRIVE_CHARS);
	if(slash != file.npos) {
		drive = file.substr(0, slash + strlen(DRIVE_CHARS));
		file = file.substr(slash + strlen(DRIVE_CHARS));
	}
	slash = file.find_last_of(SLASH_CHAR);
	if(slash != file.npos) {
		folder = file.substr(0, slash);
		file = file.substr(slash + 1);
	}
}

void MGetFilesList::insertFileToPrinterData(const std::string &pwd)
{
	std::string drive, folder, file;
	splitFilePwd(pwd, drive, folder, file);

	if (!_printer.files()->driveExist(drive)) {
		_printer.files()->addNewDrive(drive);
	}
	if (!_printer.files()->folderExist(drive, folder)) {
		_printer.files()->addNewFolder(drive, folder);
	}
	_printer.files()->addNewFile(drive, folder, file);
}

