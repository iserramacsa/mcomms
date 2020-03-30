#ifndef MACSA_JETPROTOCOL_COMMANDS_ERRORS_LOGS_H
#define MACSA_JETPROTOCOL_COMMANDS_ERRORS_LOGS_H

#include "jetcommand.h"
#include "jet/datatypes.h"
#include "jet/jetlog.h"

namespace Macsa
{
	namespace JetProtocol {

		class JetErrorsLogs : public JetCommand
		{
			public:
				JetErrorsLogs(Printers::JetPrinter &printer, time_t from = 0, time_t to = time(nullptr), Printers::JetLogType type = Printers::nJetLogType::LOG_TYPE_ALL);
				virtual bool parseRequest(const tinyxml2::XMLElement* xml);
				virtual bool parseResponse(const tinyxml2::XMLElement*xml);

			private:
				time_t _from;
				time_t _to;
				Printers::JetLogType _type;

				virtual void buildRequest();
				virtual void buildResponse();

				virtual void addNewItem(const Printers::LogItem &log, tinyxml2::XMLElement **parent);
				virtual bool parseItem(const tinyxml2::XMLElement* item, Macsa::Printers::LogItem& logItem);
		};
	}
}

#endif // MACSA_MPROTOCOL_COMMANDS_ERRORS_LOGS_H
