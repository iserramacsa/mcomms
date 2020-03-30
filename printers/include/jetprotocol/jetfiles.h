#ifndef MACSA_JETPROTOCOL_FILES_COMMANDS_H
#define MACSA_JETPROTOCOL_FILES_COMMANDS_H

#include "jetcommand.h"
#include "printer/files.h"

namespace Macsa {
	namespace JetProtocol {
		/**
		 * @brief The GetFilesList command class
		 */
		class JetGetFilesList : public JetCommand
		{
			public:
				JetGetFilesList(Printers::JetPrinter& printer);
				virtual bool parseResponse(const tinyxml2::XMLElement*xml);
				virtual bool parseRequest(const tinyxml2::XMLElement* xml);

			private:
				virtual void buildRequest();
				virtual void buildResponse();

				virtual void parseDirectory(const tinyxml2::XMLElement* xmlNode, Printers::Directory *directory);
				virtual void parseSubdirectory(const tinyxml2::XMLElement* xmlNode, Printers::Directory *parent);
				virtual void parseFiles(const tinyxml2::XMLElement* xmlNode, Printers::Directory *directory);
		};

		/**
		 * @brief The GetUSBMessages command class
		 */
		class JetGetUSBFiles : public JetCommand
		{
			public:
				JetGetUSBFiles(Printers::JetPrinter& printer);
				virtual bool parseResponse(const tinyxml2::XMLElement*xml);
				virtual bool parseRequest(const tinyxml2::XMLElement* xml);

			private:
				virtual void buildRequest();
				virtual void buildResponse();

				void parseUsbMessageFile(const tinyxml2::XMLElement* eMessage, Printers::Drive* usb) const;
		};

		/**
		 * @brief The GetInstalledFonts command class
		 */
		class JetGetFonts : public JetCommand
		{
			public:
				JetGetFonts(Printers::JetPrinter& printer);
				virtual bool parseResponse(const tinyxml2::XMLElement*xml);
				virtual bool parseRequest(const tinyxml2::XMLElement* xml);

			private:
				virtual void buildRequest();
				virtual void buildResponse();

				void parseUsbMessageFile(const tinyxml2::XMLElement* eMessage, Printers::Drive* usb) const;
		};
	}
}

#endif // MACSA_JETPROTOCOL_FILES_COMMANDS_H
