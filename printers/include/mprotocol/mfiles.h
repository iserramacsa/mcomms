#ifndef MFILESCOMMANDS_H
#define MFILESCOMMANDS_H

#include "mcommands.h"

namespace Macsa {
	namespace MProtocol {
		/**
		 * @brief The GETCONFIG command class
		 */
		class MGetFilesList : public MCommand
		{
			public:
				MGetFilesList(Printers::TIJPrinter& printer, const std::string& filter = "");
				virtual bool parseResponse(const tinyxml2::XMLElement*xml);
				virtual bool parseRequest(const tinyxml2::XMLElement* xml);

				std::string filter() const;

			private:
				std::string _filter;

				virtual void buildRequest();
				virtual void buildResponse();

				void splitFilePwd(const std::string& pwd, std::string& drive, std::string& folder, std::string& file);
				void insertFileToPrinterData(const std::string& pwd);
		};
	}
}
#endif // MFILESCOMMANDS_H
