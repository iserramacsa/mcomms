#ifndef MFILESCOMMANDS_H
#define MFILESCOMMANDS_H

#include "mcommands.h"

namespace Macsa {
	namespace MProtocol {
		class MGetFilesList : public MCommandBase
		{
			public:
				MGetFilesList(Printers::Printer& printer);
				virtual std::string commandName() const;
				virtual bool parse(const tinyxml2::XMLElement*);
	#if defined (MSERVER)
			private:
				virtual void build();
	#elif defined (MCLIENT)
			public:
				virtual void build();
				void setFilter(const std::string &filter);
	#endif
			private:
				std::string _filter;
	#if defined (MCLIENT)
				void splitFilePwd(const std::string& pwd, std::string& drive, std::string& folder, std::string& file);
				void insertFileToPrinterData(const std::string& pwd);
	#endif

		};
	}
}
#endif // MFILESCOMMANDS_H
