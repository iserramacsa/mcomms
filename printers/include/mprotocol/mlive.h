#ifndef MLIVE_COMMANDS_H
#define MLIVE_COMMANDS_H

#include "mcommands.h"

namespace Macsa
{
	namespace MProtocol {
		class MLive : public MCommandBase
		{
			public:
				MLive(Printers::Printer& printer);
				virtual std::string commandName() const;
				virtual bool parse(const tinyxml2::XMLElement*);
	#if defined (MSERVER)
			private:
				virtual void build();
	#elif defined (MCLIENT)
			public:
				virtual void build();
	#endif
		};
	}
}

#endif // MLIVE_COMMANDS_H
