﻿#ifndef MACSA_JETPROTOCOL_SET_OUTPUT_COMMAND_H
#define MACSA_JETPROTOCOL_SET_OUTPUT_COMMAND_H

#include "jetcommand.h"
#include "jet/jetio.h"
namespace Macsa{
	namespace JetProtocol {
		///
		/// \brief The JetSetOutput is the command class to set the outputs status
		/// of jet printers
		///
		class JetSetOutput : public JetCommand
		{
			public:
				JetSetOutput(Printers::JetPrinter& printer);
				JetSetOutput(Printers::JetPrinter& printer, const Printers::JetIO& output);
				virtual ~JetSetOutput();
				virtual bool parseRequest(const tinyxml2::XMLElement* xml);
				virtual bool parseResponse(const tinyxml2::XMLElement*xml);

			protected:
				virtual void buildRequest();
				virtual void buildResponse();

			private:
				Printers::JetIO* _output;
		};
	}
}

#endif // MACSA_JETPROTOCOL_PAUSE_COMMAND_H
