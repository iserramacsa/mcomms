#ifndef MACSA_JETCOUNTERS_COMMANDS_H
#define MACSA_JETCOUNTERS_COMMANDS_H

#include "jetcommands.h"

namespace Macsa{
	namespace JetProtocol {
		///
		/// \brief The JetGetCounters class is the class to get the .
		/// Based on a xml structure, this interface
		///
		class JetGetCounters : public JetCommand
		{
			public:
				JetGetCounters(Printers::JetPrinter& printer);
				virtual ~JetGetCounters();

				virtual bool parseRequest(const tinyxml2::XMLElement* xml);
				virtual bool parseResponse(const tinyxml2::XMLElement* xml);

			protected:
				virtual void buildRequest();
				virtual void buildResponse();
		};

		class JetSetCounters : public JetCommand
		{
			public:
				JetSetCounters(Printers::JetPrinter& printer);
				virtual ~JetSetCounters();

				virtual bool parseRequest(const tinyxml2::XMLElement* xml);
				virtual bool parseResponse(const tinyxml2::XMLElement* xml);

			protected:
				virtual void buildRequest();
				virtual void buildResponse();
		};

		class JetResetCounters : public JetCommand
		{
			public:
				JetResetCounters(Printers::JetPrinter& printer);
				virtual ~JetResetCounters();

				virtual bool parseRequest(const tinyxml2::XMLElement* xml);
				virtual bool parseResponse(const tinyxml2::XMLElement* xml);

			protected:
				virtual void buildRequest();
				virtual void buildResponse();
		};
	}
}

#endif // JETPROTOCOLCOMMANDS_H
