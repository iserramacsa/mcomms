#ifndef MSTATUS_COMMANDS_H
#define MSTATUS_COMMANDS_H

#include "mcommands.h"

namespace Macsa {
	namespace MProtocol {
		class MGetStatus : public MCommandBase
		{
			public:
				MGetStatus(Printers::Printer &printer);
				virtual std::string commandName() const;
				virtual bool parse(const tinyxml2::XMLElement *);
			private:
				virtual void build();

		};
	}
}

#endif // MLIVE_COMMANDS_H
