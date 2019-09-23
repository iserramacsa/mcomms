#ifndef MUPDATECOMMANDS_H
#define MUPDATECOMMANDS_H
#include "mprotocol/mcommands.h"

namespace Macsa {
	class MUpdate : public MCommandBase
	{
		public:
			MUpdate(Printer::TijPrinter& printer);
			virtual ~MUpdate();
			virtual bool parse(const tinyxml2::XMLElement*);
		private:
			virtual void build();
	};

	namespace Client {
		class MUpdate : public MCommandBase
		{
			public:
				MUpdate(Printer::TijPrinter& printer);
				virtual ~MUpdate();
				virtual bool parse(const tinyxml2::XMLElement*);
			private:
				virtual void build();
		};
	}
}

#endif // MUPDATECOMMANDS_H
