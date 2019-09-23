#ifndef MCONFIGCOMMANDS_H
#define MCONFIGCOMMANDS_H
#include "mcommands.h"

namespace Macsa {
	namespace MProtocol {
		class MGetConfig : public MCommandBase
		{
			public:
				MGetConfig(Printers::Printer& printer);
				virtual std::string commandName() const;
				virtual bool parse(const tinyxml2::XMLElement* );

	#if defined (MSERVER)
			private:
				tinyxml2::XMLElement* getPrinterGenerals();
				tinyxml2::XMLElement* getPrinterConnections();
				tinyxml2::XMLElement* getPrinterBoards();
				virtual void build();
	#elif defined (MCLIENT)
			public:
				virtual void build();
	#endif

		};

		class MSetConfig : public MCommandBase
		{
			public:
				MSetConfig(Printers::Printer& printer);
				virtual std::string commandName() const;
				virtual bool parse(const tinyxml2::XMLElement *);

			private:
				virtual void build();
		};
	}
}

#endif // MCONFIGCOMMANDS_H
