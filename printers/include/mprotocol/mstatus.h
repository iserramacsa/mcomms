#ifndef MACSA_MPROTOCOL_COMMANDS_STATUS_H
#define MACSA_MPROTOCOL_COMMANDS_STATUS_H

#include "mcommands.h"

namespace Macsa {
	namespace MProtocol {

		class MGetStatus : public MCommand
		{
			public:
				MGetStatus(Printers::TIJPrinter& printer);
				virtual bool parseRequest(const tinyxml2::XMLElement* xml);
				virtual bool parseResponse(const tinyxml2::XMLElement* xml);

			private:
				virtual void buildRequest();
				virtual void buildResponse();

				void countersToXml(const Printers::Board& board, tinyxml2::XMLElement **parent);
				void errorsToXml(const Printers::Board& board, tinyxml2::XMLElement **parent);
				void inputsToXml(const Printers::Board& board, tinyxml2::XMLElement **parent);
				void outputsToXml(const Printers::Board& board, tinyxml2::XMLElement **parent);
				void propertiesToXml(const Printers::Board& board, tinyxml2::XMLElement **parent);

				void countersFromXml(const tinyxml2::XMLElement *parent, Printers::Board& board);
				void errorsFromXml(const tinyxml2::XMLElement *parent, Printers::Board& board);
				void inputsFromXml(const tinyxml2::XMLElement *parent, Printers::Board& board);
				void outputsFromXml(const tinyxml2::XMLElement *parent, Printers::Board& board);
				void propertiesFromXml(const tinyxml2::XMLElement *parent, Printers::Board& board);
		};
	}
}

#endif // MSTATUS_COMMANDS_H
