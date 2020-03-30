#ifndef MACSA_JETPROTOCOL_STATUS_SINGLE_COMMAND_H
#define MACSA_JETPROTOCOL_STATUS_SINGLE_COMMAND_H

#include "jetcommand.h"

namespace Macsa{
	namespace JetProtocol {
		///
		/// \brief The GetSSCC command class
		///
		class JetGetSSCC : public JetCommand
		{
			public:
				JetGetSSCC(Printers::JetPrinter& printer);
				virtual bool parseRequest(const tinyxml2::XMLElement* xml);
				virtual bool parseResponse(const tinyxml2::XMLElement*xml);

			protected:
				virtual void buildRequest();
				virtual void buildResponse();
		};

		///
		/// \brief The IncrementSSCC command class
		///
		class JetIncrementSSCC : public JetCommand
		{
			public:
				JetIncrementSSCC(Printers::JetPrinter& printer);
				virtual bool parseRequest(const tinyxml2::XMLElement* xml);
				virtual bool parseResponse(const tinyxml2::XMLElement*xml);

			protected:
				virtual void buildRequest();
				virtual void buildResponse();
		};

		///
		/// \brief The GetDatetime command class.
		///
		class JetGetDatetime : public JetCommand
		{
			public:
				JetGetDatetime(Printers::JetPrinter& printer);
				virtual bool parseRequest(const tinyxml2::XMLElement* xml);
				virtual bool parseResponse(const tinyxml2::XMLElement*xml);

			protected:
				virtual void buildRequest();
				virtual void buildResponse();
		};

		///
		/// \brief The SetDatetime command class
		///
		class JetSetDatetime : public JetCommand
		{
			public:
				JetSetDatetime(Printers::JetPrinter& printer, time_t time);
				JetSetDatetime(Printers::JetPrinter& printer);
				virtual bool parseRequest(const tinyxml2::XMLElement* xml);
				virtual bool parseResponse(const tinyxml2::XMLElement*xml);

			protected:
				time_t _time;
				virtual void buildRequest();
				virtual void buildResponse();
		};
	}
}

#endif // MACSA_JETPROTOCOL_PAUSE_COMMAND_H
