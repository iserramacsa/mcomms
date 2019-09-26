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

			access:
				virtual void build();

			private:
				tinyxml2::XMLElement* getPrinterGenerals();
				tinyxml2::XMLElement* getPrinterConnections();
				tinyxml2::XMLElement* getPrinterBoards();
		};

		class MSetConfig : public MCommandBase
		{
			public:
				MSetConfig(Printers::Printer& printer);
				virtual std::string commandName() const;
				virtual bool parse(const tinyxml2::XMLElement *);
			access:
				virtual void build();
		};

		class MSetDateTime : public MSetConfig
		{
			public:
				MSetDateTime(Printers::Printer& printer);
			access:
				virtual void build() override;

		};

	}
}

#endif // MCONFIGCOMMANDS_H
