#ifndef MACSA_MPROTOCOL_COMMANDS_STATUS_H
#define MACSA_MPROTOCOL_COMMANDS_STATUS_H

#include "jetcommand.h"

namespace Macsa {
	namespace JetProtocol {
		/**
		 * @brief The JetGetStatus class
		 */
		class JetGetStatus : public JetCommand
		{
			public:
				JetGetStatus(Printers::JetPrinter &printer);
				virtual ~JetGetStatus();
				virtual bool parseRequest(const tinyxml2::XMLElement* xml);
				virtual bool parseResponse(const tinyxml2::XMLElement* xml);

			private:
				virtual void buildRequest();
				virtual void buildResponse();

				void parsePrintheadsTemperature(const tinyxml2::XMLElement* ePrintheads);
				void parseInkLevels(const tinyxml2::XMLElement* eTanks);
				void parseCurrentMessage(const tinyxml2::XMLElement* eCmd);
				void parseNetworkStatus(const tinyxml2::XMLElement* eNetwork);
		};

		/**
		 * @brief The JetGetIOStatus class
		 */
		class JetGetIOStatus : public JetCommand
		{
			public:
				JetGetIOStatus(Printers::JetPrinter& printer);
				virtual ~JetGetIOStatus();
				virtual bool parseRequest(const tinyxml2::XMLElement* xml);
				virtual bool parseResponse(const tinyxml2::XMLElement* xml);

			private:
				virtual void buildRequest();
				virtual void buildResponse();
		};

		/**
		 * @brief The JetGetErrors class
		 */
		class JetGetErrors : public JetCommand
		{
			public:
				JetGetErrors(Printers::JetPrinter& printer);
				virtual ~JetGetErrors();
				virtual bool parseRequest(const tinyxml2::XMLElement* xml);
				virtual bool parseResponse(const tinyxml2::XMLElement* xml);

			private:
				virtual void buildRequest();
				virtual void buildResponse();
		};
	}
}

#endif // MSTATUS_COMMANDS_H
