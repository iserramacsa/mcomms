#include "mprotocol/mfiles.h"
#include "mprotocol/mprotocol.h"
#include "printer/files.h"
#include "mtools.h"
#include "base64.h"

#include <sstream>

#define SLASH_CHAR '/'
#define DRIVE_CHARS "//"

using namespace Macsa::MProtocol;
using namespace tinyxml2;

//=============		GET FILES LIST		=============//
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
	XMLElement* cmd = newCommandNode();
	_error = Printers::ErrorCode_n::SUCCESS;

	cmd->SetAttribute(MFILES_GET_LIST_TYPE_ATTR, _filter.c_str());

	Printers::PrinterFiles* rootfs = _printer.files();
	std::vector<std::string> drives = rootfs->getDrives();
	for (std::vector<std::string>::const_iterator d = drives.begin(); d != drives.end(); d++)
	{
		createChildNode(MFILES_GET_LIST, &cmd);
		cmd->SetAttribute(MFILES_DEVICE_UNIT_ATTR, d->c_str());
	}
	std::vector<std::string> files = rootfs->getAllFiles(_filter);
	for (std::vector<std::string>::const_iterator f = files.begin(); f != files.end(); f++)
	{
		createChildNode(MFILES_FILE_PATH, &cmd);
		cmd->SetAttribute(MFILES_FILE_PATH_ATTR, f->c_str());
	}

	addWindError(_error);
}

bool MGetFilesList::parseRequest(const XMLElement *xml)
{
	const XMLElement* cmd = getCommand(xml, _id);
	bool valid = false;
	if  (cmd != nullptr) {
		valid = (cmd != nullptr && cmd->NoChildren());
		if (valid){
			_filter = "*.*";
			const char* filter = cmd->Attribute(MFILES_GET_LIST_TYPE_ATTR);
			if (filter != nullptr) {
				_filter = filter;
			}
		}
	}

	return valid;
}

bool MGetFilesList::parseResponse(const XMLElement *xml)
{
	const XMLElement * cmd = getCommand(xml, _id);
	bool valid = (cmd != nullptr);
	if (valid) {
		if (std::string(cmd->Value()).compare(MFILES_GET_LIST) == 0)
		{
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

//=============		COPY FILES		=============//
MCopyFile::MCopyFile(Macsa::Printers::TIJPrinter &printer, const std::string &sourceFilename, const std::string &targetFilename)  :
	MCommand(MFILES_COPY, printer)
{
	_sourceFilename = sourceFilename;
	_targetFilename = targetFilename;
}

void MCopyFile::buildRequest()
{
	XMLElement* cmd = newCommandNode();
	if (cmd != nullptr) {
		cmd->SetAttribute(MFILES_SOURCE_PATH_ATTR, _sourceFilename.c_str());
		cmd->SetAttribute(MFILES_TARGET_PATH_ATTR, _targetFilename.c_str());
	}
}

bool MCopyFile::parseRequest(const XMLElement *xml)
{
	const XMLElement* cmd = getCommand(xml, _id);
	bool valid = (cmd != nullptr);
	if (valid) {
		_sourceFilename = cmd->Attribute(MFILES_SOURCE_PATH_ATTR, "");
		_targetFilename = cmd->Attribute(MFILES_TARGET_PATH_ATTR, "");
	}

	return valid;
}

void MCopyFile::buildResponse()
{
	newCommandNode();
	_error = Printers::ErrorCode_n::FILE_NOT_FOUND;
	Printers::IFilesManager * filesManager = _printer.files()->filesManager();
	if (filesManager != nullptr){
		//TODO: move out from command class ??
		_error = filesManager->copyFile(_sourceFilename, _targetFilename);
	}
	addWindError(_error);
}

bool MCopyFile::parseResponse(const XMLElement *xml)
{
	const XMLElement* cmd = getCommand(xml, _id);
	bool valid = (cmd != nullptr);
	if (valid) {
		_error = getCommandError(xml);
	}
	return valid;
}

std::string MCopyFile::sourceFilename() const
{
	return _sourceFilename;
}

std::string MCopyFile::targetFilename() const
{
	return _targetFilename;
}

//=============		COPY FILES		=============//
MMoveFile::MMoveFile(Macsa::Printers::TIJPrinter &printer, const std::string &sourceFilename, const std::string &targetFilename) :
	MCommand(MFILES_MOVE, printer)
{
	_sourceFilename = sourceFilename;
	_targetFilename = targetFilename;
}

void MMoveFile::buildRequest()
{
	XMLElement* cmd = newCommandNode();
	if (cmd != nullptr) {
		cmd->SetAttribute(MFILES_SOURCE_PATH_ATTR, _sourceFilename.c_str());
		cmd->SetAttribute(MFILES_TARGET_PATH_ATTR, _targetFilename.c_str());
	}
}

bool MMoveFile::parseRequest(const XMLElement *xml)
{
	const XMLElement* cmd = getCommand(xml, _id);
	bool valid = (cmd != nullptr);
	if (valid) {
		_sourceFilename = cmd->Attribute(MFILES_SOURCE_PATH_ATTR, "");
		_targetFilename = cmd->Attribute(MFILES_TARGET_PATH_ATTR, "");
	}
	return valid;
}

void MMoveFile::buildResponse()
{
	newCommandNode();
	_error = Printers::ErrorCode_n::FILE_NOT_FOUND;
	Printers::IFilesManager * filesManager = _printer.files()->filesManager();
	if (filesManager != nullptr){
		//TODO: move out from command class ??
		_error = filesManager->moveFile(_sourceFilename, _targetFilename);
	}
	addWindError(_error);
}

bool MMoveFile::parseResponse(const XMLElement *xml)
{
	bool valid = false;
	const XMLElement* cmd = getCommand(xml, _id);
	valid = (cmd != nullptr);
	if (valid) {
		_error = getCommandError(xml);
	}
	return valid;
}

std::string MMoveFile::sourceFilename() const
{
	return _sourceFilename;
}

std::string MMoveFile::targetFilename() const
{
	return _targetFilename;
}

//=============		DELETE FILE		=============//
MDeleteFile::MDeleteFile(Macsa::Printers::TIJPrinter &printer, const std::string &filename):
	MCommand(MFILES_DELETE, printer)
{
	_filename = filename;
}

void MDeleteFile::buildRequest()
{
	XMLElement* cmd = newCommandNode();
	if (cmd != nullptr) {
		cmd->SetAttribute(MFILES_FILE_FILEPATH_ATTR, _filename.c_str());
	}
}

bool MDeleteFile::parseRequest(const XMLElement *xml)
{
	const XMLElement* cmd = getCommand(xml, _id);
	bool valid = (cmd != nullptr);
	if (valid) {
		_filename = cmd->Attribute(MFILES_FILE_FILEPATH_ATTR, "");
	}
	return valid;
}

void MDeleteFile::buildResponse()
{
	newCommandNode();
	_error = Printers::ErrorCode_n::FILE_NOT_FOUND;
	Printers::IFilesManager * filesManager = _printer.files()->filesManager();
	if (filesManager != nullptr){
		//TODO: move out from command class ??
		_error = filesManager->deleteFile(_filename);
	}
	addWindError(_error);
}

bool MDeleteFile::parseResponse(const XMLElement *xml)
{
	bool valid = false;
	const XMLElement* cmd = getCommand(xml, _id);
	valid = (cmd != nullptr);
	if (valid) {
		_error = getCommandError(xml);
	}
	return valid;
}

std::string MDeleteFile::filename() const
{
	return _filename;
}


//=============		FILE CONTENT COMMAND BASE		=============//
MFileContentCommand::MFileContentCommand(const std::string &command, Printers::TIJPrinter &printer, const std::string &filename, bool raw, const std::vector<uint8_t> &content) :
	MCommand(command, printer)
{
	_filename = filename;
	_content = content;
	_raw = raw;
}

bool MFileContentCommand::raw() const
{
	return _raw;
}

std::string MFileContentCommand::filename() const
{
	return _filename;
}

std::vector<uint8_t> MFileContentCommand::content() const
{
	return _content;
}

void MFileContentCommand::setContent(const std::vector<uint8_t> &content)
{
	_content = content;
}

std::string MFileContentCommand::contentToString(const std::vector<uint8_t> content, bool raw) const
{
	std::stringstream out;
	if (raw) {
		out << OPEN_CDATA;
		for (std::vector<uint8_t>::const_iterator it = content.begin(); it != content.end(); it++) {
			out << std::to_string(*it);
		}
		out << CLOSE_CDATA;
	}
	else {
		const char* plainData = reinterpret_cast<const char*>(&content[0]);

		int len = Base64encode_len(static_cast<int>(content.size()));
		char* encodeData = new char[len + 1];
		if(encodeData) {
			Base64encode(encodeData, plainData, static_cast<int>(content.size()));

			out << encodeData;
			delete[]  encodeData;
		}
	}
	return out.str();
}

std::vector<uint8_t> MFileContentCommand::contentFromString(const char *data, bool raw) const
{
	std::vector<uint8_t> content;

	if (raw && data != nullptr) {
		unsigned int len = strlen(data);
		for (unsigned int i = 0; i < len; i++) {
			content.push_back(static_cast<uint8_t>(*(data + i)));
		}
	}
	else if (data != nullptr) {
		int decodedLen = Base64decode_len(data);
		char* decodedData = new char[decodedLen + 1];
		Base64decode(decodedData, data);
		for (int i = 0; i < decodedLen; i++) {
			content.push_back(static_cast<uint8_t>(*(decodedData + i)));
		}
		delete[]  decodedData;
	}

	return content;
}

//=============		GET FILE		=============//
MGetFile::MGetFile(Macsa::Printers::TIJPrinter &printer, const std::string &filename, bool raw) :
	MFileContentCommand(MFILES_GET, printer, filename, raw)
{}

void MGetFile::buildRequest()
{
	XMLElement* cmd = newCommandNode();
	if (cmd != nullptr) {
		cmd->SetAttribute(MFILES_FILE_FILEPATH_ATTR, _filename.c_str());
		cmd->SetAttribute(MFILES_FILE_RAW_ATTR, MTools::toString(_raw).c_str());
	}
}

bool MGetFile::parseRequest(const XMLElement *xml)
{
	const XMLElement* cmd = getCommand(xml, _id);
	bool valid = (cmd != nullptr);
	if (valid) {
		_filename = cmd->Attribute(MFILES_FILE_FILEPATH_ATTR, "");
		_raw = MTools::boolfromString(cmd->Attribute(MFILES_FILE_RAW_ATTR, "false"));
	}
	return valid;
}

void MGetFile::buildResponse()
{
	XMLElement * cmd = newCommandNode();
	_error = Printers::ErrorCode_n::FILE_NOT_FOUND;
	Printers::IFilesManager * filesManager = _printer.files()->filesManager();
	if (filesManager != nullptr){
		//TODO: move out from command class ??
		std::vector<uint8_t> data;
		_error = filesManager->getFile(_filename, data);
		XMLText* content = _doc.NewText(MFILES_FILE_CONTENT);
		if (content){
			content->SetCData(_raw);
			content->SetValue(contentToString(data, _raw).c_str());
			cmd->InsertEndChild(content);
		}
	}
	addWindError(_error);
}

bool MGetFile::parseResponse(const XMLElement *xml)
{
	bool valid = false;
	const XMLElement* cmd = getCommand(xml, _id);
	valid = (cmd != nullptr);
	if (valid) {
		_error = getCommandError(xml);
		const XMLText* content = dynamic_cast<const XMLText*>(cmd->FirstChild());
		if (content) {
			_raw = content->CData();
			_content.clear();
			_content = contentFromString(content->Value(), _raw);
		}
	}
	return valid;
}

//=============		SET FILE		=============//
 ///TODO!!!
MSetFile::MSetFile(Macsa::Printers::TIJPrinter &printer, const std::string &filename, const std::vector<uint8_t> &content, bool raw) :
	MFileContentCommand(MFILES_SET, printer, filename, raw, content)
{
	_filename = filename;
	_raw = raw;
	_content = content;
}

void MSetFile::buildRequest()
{
	XMLElement* cmd = newCommandNode();
	if (cmd != nullptr) {
		cmd->SetAttribute(MFILES_FILE_FILEPATH_ATTR, _filename.c_str());
		cmd->SetAttribute(MFILES_FILE_RAW_ATTR, MTools::toString(_raw).c_str());

	}
}

bool MSetFile::parseRequest(const XMLElement *xml)
{
	const XMLElement* cmd = getCommand(xml, _id);
	bool valid = (cmd != nullptr);
	if (valid) {
		_filename = cmd->Attribute(MFILES_FILE_FILEPATH_ATTR, "");
		_raw = MTools::boolfromString(cmd->Attribute(MFILES_FILE_RAW_ATTR, "false"));
	}
	return valid;
}

void MSetFile::buildResponse()
{
	XMLElement * cmd = newCommandNode();
	_error = Printers::ErrorCode_n::FILE_NOT_FOUND;
	Printers::IFilesManager * filesManager = _printer.files()->filesManager();
	if (filesManager != nullptr){
		//TODO: move out from command class ??
		std::vector<uint8_t> data;
		_error = filesManager->getFile(_filename, data);
		XMLText* content = _doc.NewText(MFILES_FILE_CONTENT);
		if (content){
			content->SetCData(_raw);
			content->SetValue(contentToString(data, _raw).c_str());
			cmd->InsertEndChild(content);
		}
	}
	addWindError(_error);
}

bool MSetFile::parseResponse(const XMLElement *xml)
{
	bool valid = false;
	const XMLElement* cmd = getCommand(xml, _id);
	valid = (cmd != nullptr);
	if (valid) {
		_error = getCommandError(xml);
		const XMLText* content = dynamic_cast<const XMLText*>(cmd->FirstChild());
		if (content) {
			_raw = content->CData();
			_content.clear();
			_content = contentFromString(content->Value(), _raw);
		}
	}
	return valid;
}

