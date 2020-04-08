#include "jetprotocol/jetfiles.h"
#include "jetprotocol/jetprotocol.h"

#include <sstream>

using namespace Macsa::JetProtocol;
using namespace Macsa::Printers;
using namespace tinyxml2;

#define DEFAULT_DRIVE		""
#define DEFAULT_DIRECTORY	""
#define DEFAULT_USB_DRIVE   "USB"

/**************		GET FILES LIST		**************/
JetGetFilesList::JetGetFilesList(Printers::JetPrinter &printer) :
	JetCommand(CMD_GET_FILES_LIST, printer)
{}

void JetGetFilesList::buildRequest()
{
	newCommandWind();
}

bool JetGetFilesList::parseRequest(const XMLElement *xml)
{
	return isValidWind(xml);
}

bool JetGetFilesList::parseResponse(const XMLElement *xml)
{
	bool valid = isValidWind(xml);

	if (valid) {
		parseCommandError(xml);
		if (_error == nJetErrorCode::COMMAND_OK) {//JET_FILE_TAG
			PrinterFiles* rootfs = _printer.files();
			if (rootfs) {
				if(!rootfs->getDrive(DEFAULT_DRIVE)) {
					rootfs->addNewDrive(DEFAULT_DRIVE);
				}

				for (const XMLElement* eDirectory = xml->FirstChildElement(JET_DIRECTORY_TAG); eDirectory != nullptr;
					 eDirectory = eDirectory->NextSiblingElement(JET_DIRECTORY_TAG))
				{
					std::string directoryName = getTextAttribute(eDirectory, NAME_ATTRIBUTE, "");
					if (rootfs->directoryExist(DEFAULT_DRIVE, directoryName) || rootfs->addNewDirectory(DEFAULT_DRIVE, directoryName)) {
						Directory* directory = rootfs->getDrive(DEFAULT_DRIVE)->getDirectory(directoryName);
						parseDirectory(eDirectory, directory);
					}
				}
				if (xml->FirstChildElement(JET_FILE_TAG) != nullptr) {
					Directory* root = nullptr;
					if (rootfs->directoryExist(DEFAULT_DRIVE, DEFAULT_DIRECTORY) || rootfs->addNewDirectory(DEFAULT_DRIVE, DEFAULT_DIRECTORY)) {
						if (rootfs->getDrive(DEFAULT_DRIVE)) {
							root = rootfs->getDrive(DEFAULT_DRIVE)->getDirectory(DEFAULT_DIRECTORY);
							if(root) {
								root->clear();
							}
						}
					}
					parseFiles(xml, root);
				}
			}
		}
	}

	return valid;
}

void JetGetFilesList::buildResponse()
{
	newCommandWind();
	setCommandError(_error);
	//Todo fill with files
}

void JetGetFilesList::parseDirectory(const XMLElement *xmlNode, Directory *directory)
{
	if (xmlNode && directory) {
		directory->clear();
		parseSubdirectory(xmlNode, directory);
		parseFiles(xmlNode, directory);
	}
}

void JetGetFilesList::parseSubdirectory(const XMLElement *xmlNode, Directory *parent)
{
	if (xmlNode && parent) {
		for (const XMLElement* eSubdirectory = xmlNode->FirstChildElement(JET_DIRECTORY_TAG); eSubdirectory != nullptr;
			 eSubdirectory = eSubdirectory->NextSiblingElement(JET_DIRECTORY_TAG))
		{
			std::string name = getTextAttribute(eSubdirectory, NAME_ATTRIBUTE, "");
			if (name.length() > 0) {
				if (parent->getSubdirectory(name) || parent->addSubdirectory(name)) {
					Directory* subdir = parent->getSubdirectory(name);
					parseDirectory(eSubdirectory, subdir);
				}
			}
		}
	}
}

void JetGetFilesList::parseFiles(const XMLElement *xmlNode, Directory *directory)
{
	if (directory) {
		for (const XMLElement* eFile = xmlNode->FirstChildElement(JET_FILE_TAG); eFile != nullptr;
			 eFile = eFile->NextSiblingElement(JET_FILE_TAG))
		{
			std::string filename = getTextAttribute(xmlNode, NAME_ATTRIBUTE, "");
			directory->addEmptyFile(filename);
		}
	}
}


/**************		GET USB FILES LIST		**************/
JetGetUSBFiles::JetGetUSBFiles(JetPrinter &printer) :
	JetCommand(CMD_GET_USB_MSG, printer)
{}

void JetGetUSBFiles::buildRequest()
{
	newCommandWind();
}

bool JetGetUSBFiles::parseRequest(const XMLElement *xml)
{
	return isValidWind(xml);
}

void JetGetUSBFiles::buildResponse()
{
	/*XMLElement* cmd =*/ newCommandWind();
	setCommandError(_error);
	//Todo: fill with usb files
}

bool JetGetUSBFiles::parseResponse(const XMLElement *xml)
{
	bool valid = isValidWind(xml);
	if (valid) {
		parseCommandError(xml);
		if (_error == Printers::nJetErrorCode::USB_NOT_CONNECTED)
		{
			PrinterFiles* rootfs = _printer.files();
			if (rootfs) {
				if (rootfs->driveExist(DEFAULT_USB_DRIVE)) {
					_printer.files()->removeDrive(DEFAULT_USB_DRIVE);
				}
			}
		}
		else if (_error == Printers::nJetErrorCode::COMMAND_OK)
		{
			PrinterFiles* rootfs = _printer.files();
			if (rootfs) {
				Drive* usbDrive = nullptr;
				if (!rootfs->driveExist(DEFAULT_USB_DRIVE)) {
					rootfs->addNewDrive(DEFAULT_USB_DRIVE);
				}
				usbDrive = _printer.files()->getDrive(DEFAULT_USB_DRIVE);
				if (usbDrive){
					usbDrive->clear();
					usbDrive->setDescription(getTextAttribute(xml, NAME_ATTRIBUTE, "no name"));
					for (const XMLElement* eMessage = xml->FirstChildElement(JET_MESSAGE_TAG); eMessage != nullptr;
						 eMessage = eMessage->NextSiblingElement(JET_MESSAGE_TAG))
					{
						parseUsbMessageFile(eMessage, usbDrive);
					}
				}
			}
		}
	}
	return valid;
}

void JetGetUSBFiles::parseUsbMessageFile(const XMLElement *eMessage, Drive *usb) const
{
	if (eMessage != nullptr && usb != nullptr) {
		std::string filename = getTextAttribute(eMessage, NAME_ATTRIBUTE, "");
		std::string directory = getTextAttribute(eMessage, MESSAGE_GROUP_ATTRIBUTE, "");
		if (filename.length()) {
			if (!usb->getDirectory(directory)) {
				usb->addEmptyDirectory(directory);
			}
			Directory* dir = usb->getDirectory(directory);
			if (dir) {
				dir->addEmptyFile(filename);
			}
		}
	}
}

/**************		GET INSTALLED FONTS		**************/
JetGetFonts::JetGetFonts(JetPrinter &printer) :
	JetCommand(CMD_GET_INSTALLED_FONTS, printer)
{

}

void JetGetFonts::buildRequest()
{
	newCommandWind();
}

bool JetGetFonts::parseRequest(const XMLElement *xml)
{
	return isValidWind(xml);
}

void JetGetFonts::buildResponse()
{
	/*XMLElement* cmd =*/ newCommandWind();
	setCommandError(_error);
	//Todo: fill with fonts files
}

bool JetGetFonts::parseResponse(const XMLElement *xml)
{
	bool valid = isValidWind(xml);
	if (valid) {
		parseCommandError(xml);
		if (_error == Printers::nJetErrorCode::COMMAND_OK)
		{
			PrinterFiles* rootfs = _printer.files();
			if (rootfs) {
				if(!rootfs->getDrive(DEFAULT_DRIVE)) {
					rootfs->addNewDrive(DEFAULT_DRIVE);
				}
				Drive* drive = rootfs->getDrive(DEFAULT_DRIVE);
				if (drive){
					if (!drive->getDirectory(FONTS_DIRECTORY)) {
						drive->addEmptyDirectory(FONTS_DIRECTORY);
					}
					Directory* fontsDir = drive->getDirectory(FONTS_DIRECTORY);
					fontsDir->clear();
					for (const XMLElement* eFont = xml->FirstChildElement(JET_FONT_TAG);
						 eFont != nullptr; eFont = eFont->NextSiblingElement(JET_FONT_TAG))
					{
						const char* fontName = eFont->GetText();
						if (fontName && strlen(fontName) > 0) {
							fontsDir->addEmptyFile(fontName);
						}
					}
				}
			}
		}
	}
	return valid;
}
