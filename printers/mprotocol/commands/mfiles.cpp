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
MGetFilesList::MGetFilesList(Printers::TijPrinter &printer, const std::string &filter) :
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
	_error = Printers::nErrorCode::SUCCESS;

	cmd->SetAttribute(MFILES_GET_LIST_TYPE_ATTR, _filter.c_str());

	Printers::PrinterFiles* rootfs = _printer.files();
	std::vector<std::string> drives = rootfs->getDrives();
	for (std::vector<std::string>::const_iterator d = drives.begin(); d != drives.end(); d++)
	{
		createChildNode(MFILES_GET_LIST, &cmd);
		cmd->SetAttribute(ATTRIBUTE_NAME, d->c_str());
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
			_filter = getTextAttribute(cmd, MFILES_GET_LIST_TYPE_ATTR, "*.*");
		}
	}

	return valid;
}

bool MGetFilesList::parseResponse(const XMLElement *xml)
{
	_attributes.clear();
	const XMLElement * cmd = getCommand(xml, _id);
	bool valid = (cmd != nullptr);
	if (valid) {
		_error = getCommandError(xml);
		if (std::string(cmd->Value()).compare(MFILES_GET_LIST) == 0)
		{
			std::vector<std::string> exts;
			std::string filter = getTextAttribute(cmd, MFILES_GET_LIST_TYPE_ATTR, "");
			_attributes[MFILES_GET_LIST_TYPE_ATTR] = filter;

			if (filter.length() > 1) {
				size_t coma = 0;
				while ((coma = filter.find_first_of(",", coma)) != filter.npos)
				{
					exts.push_back(filter.substr(0, coma));
					filter = filter.substr(coma + 1);
				}
				if (filter.length()) {
					exts.push_back(filter);
				}
			}

			/* Update active units*/
			std::vector<std::string> drives;
			const XMLElement * unit = cmd->FirstChildElement(MFILES_DEVICE_UNIT);
			while (unit != nullptr) {
				std::string drive = getTextAttribute(unit, ATTRIBUTE_NAME);
				if (drive.length()) {
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
				std::string path = getTextAttribute(xmlfile, MFILES_FILE_PATH_ATTR);
				if (path.length()) {
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

void MGetFilesList::insertFileToPrinterData(const std::string &pwd)
{
	std::string drive, folder, file;
	std::vector<std::string>folders;
	_printer.files()->splitFilepath(pwd, drive, folders, file);

	if (!_printer.files()->driveExist(drive)) {
		_printer.files()->addNewDrive(drive);
	}
	for (uint i = 0; i < folders.size(); i++){
		if (i > 0) {
			folder += "/";
		}
		folder += folders.at(i);
	}
	if (!_printer.files()->folderExist(drive, folder)) {
		_printer.files()->addNewFolder(drive, folder);
	}
	_printer.files()->addNewFile(drive, folder, file);
}

//=============		COPY FILES		=============//
MCopyFile::MCopyFile(Macsa::Printers::TijPrinter &printer, const std::string &sourceFilename, const std::string &targetFilename)  :
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
		_sourceFilename = getTextAttribute(cmd, MFILES_SOURCE_PATH_ATTR);
		_targetFilename = getTextAttribute(cmd, MFILES_TARGET_PATH_ATTR);
	}

	return valid;
}

void MCopyFile::buildResponse()
{
	newCommandNode();
	_error = Printers::nErrorCode::FILE_NOT_FOUND;
	Printers::IFilesManager * filesManager = _printer.files()->filesManager();
	if (filesManager != nullptr){
		//TODO: move out from command class ??
		_error = filesManager->copyFile(_sourceFilename, _targetFilename);
	}
	addWindError(_error);
}

bool MCopyFile::parseResponse(const XMLElement *xml)
{
	_attributes.clear();
	const XMLElement* cmd = getCommand(xml, _id);
	bool valid = (cmd != nullptr);
	if (valid) {
		_error = getCommandError(xml);
//		_params[MFILES_GET_LIST_TYPE_ATTR] = filter;
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
MMoveFile::MMoveFile(Macsa::Printers::TijPrinter &printer, const std::string &sourceFilename, const std::string &targetFilename) :
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
		_sourceFilename = getTextAttribute(cmd, MFILES_SOURCE_PATH_ATTR);
		_targetFilename = getTextAttribute(cmd, MFILES_TARGET_PATH_ATTR);
	}
	return valid;
}

void MMoveFile::buildResponse()
{
	newCommandNode();
	_error = Printers::nErrorCode::FILE_NOT_FOUND;
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
MDeleteFile::MDeleteFile(Macsa::Printers::TijPrinter &printer, const std::string &filename):
	MCommand(MFILES_DELETE, printer)
{
	_filename = filename;
}

void MDeleteFile::buildRequest()
{
	XMLElement* cmd = newCommandNode();
	if (cmd != nullptr) {
		cmd->SetAttribute(ATTRIBUTE_FILEPATH, _filename.c_str());
	}
}

bool MDeleteFile::parseRequest(const XMLElement *xml)
{
	const XMLElement* cmd = getCommand(xml, _id);
	bool valid = (cmd != nullptr);
	if (valid) {
		_filename = getTextAttribute(cmd, ATTRIBUTE_FILEPATH);
	}
	return valid;
}

void MDeleteFile::buildResponse()
{
	newCommandNode();
	_error = Printers::nErrorCode::FILE_NOT_FOUND;
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
MFileContentCommand::MFileContentCommand(const std::string &command, Printers::TijPrinter &printer,
										 const std::string &filename, bool raw,
										 const std::vector<uint8_t> &content) :
	MCommand(command, printer)
{
	_filename = filename;
	_content = content;
	_raw = raw;
}

MFileContentCommand::~MFileContentCommand()
{}

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
MGetFile::MGetFile(Macsa::Printers::TijPrinter &printer, const std::string &filename, bool raw) :
	MFileContentCommand(MFILES_GET, printer, filename, raw)
{}

void MGetFile::buildRequest()
{
	XMLElement* cmd = newCommandNode();
	if (cmd != nullptr) {
		cmd->SetAttribute(ATTRIBUTE_FILEPATH, _filename.c_str());
		cmd->SetAttribute(MFILES_FILE_RAW_ATTR, MTools::toString(_raw).c_str());
	}
}

bool MGetFile::parseRequest(const XMLElement *xml)
{
	const XMLElement* cmd = getCommand(xml, _id);
	bool valid = (cmd != nullptr);
	if (valid) {
		_filename = getTextAttribute(cmd, ATTRIBUTE_FILEPATH);
		_raw = getBoolAttribute(cmd, MFILES_FILE_RAW_ATTR);
	}
	return valid;
}

void MGetFile::buildResponse()
{
	XMLElement * cmd = newCommandNode();
	_error = Printers::nErrorCode::FILE_NOT_FOUND;
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
	_attributes.clear();
	const XMLElement* cmd = getCommand(xml, _id);
	valid = (cmd != nullptr);
	if (valid)
	{
		_error = getCommandError(xml);
		if (_error == Printers::nErrorCode::SUCCESS)
		{
			_content.clear();
			std::string pwd = getTextAttribute(cmd, ATTRIBUTE_FILEPATH, "");
			if (pwd.length() && _printer.files() && _printer.files()->getFile(pwd) != nullptr)
			{
				const XMLElement* contentNode = cmd->FirstChildElement();
				if (dynamic_cast<const XMLText*>(contentNode->FirstChild()))
				{
					std::string drive = pwd.substr(0, pwd.find("//") + 2);
					_attributes[MFILES_DEVICE_UNIT] = drive;
					_attributes[MFILES_FILE_PATH] = pwd;

					const XMLText* content = dynamic_cast<const XMLText*>(contentNode->FirstChild());
					_raw = content->CData();
					_content = contentFromString(content->Value(), _raw);
					_printer.files()->setFile(pwd, _content);
				}
			}
		}
	}
	return valid;
}

//=============		SET FILE		=============//
 ///TODO!!!
MSetFile::MSetFile(Macsa::Printers::TijPrinter &printer, const std::string &filename, const std::vector<uint8_t> &content, bool raw) :
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
		cmd->SetAttribute(ATTRIBUTE_FILEPATH, _filename.c_str());
		cmd->SetAttribute(MFILES_FILE_RAW_ATTR, MTools::toString(_raw).c_str());

	}
}

bool MSetFile::parseRequest(const XMLElement *xml)
{
	const XMLElement* cmd = getCommand(xml, _id);
	bool valid = (cmd != nullptr);
	if (valid) {
		_filename = getTextAttribute(cmd, ATTRIBUTE_FILEPATH);
		_raw = getBoolAttribute(cmd, MFILES_FILE_RAW_ATTR);
	}
	return valid;
}

void MSetFile::buildResponse()
{
	XMLElement * cmd = newCommandNode();
	_error = Printers::nErrorCode::FILE_NOT_FOUND;
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

