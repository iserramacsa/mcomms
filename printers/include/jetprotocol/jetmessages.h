#ifndef  MACSA_JETPROTOCOL_MESSAGES_COMMANDS_H
#define  MACSA_JETPROTOCOL_MESSAGES_COMMANDS_H

#include "jetcommand.h"
#include <string>

namespace Macsa {
	namespace JetProtocol {

		class JetSetCurrentMessage : public JetCommand
		{
			public:
				JetSetCurrentMessage(Printers::JetPrinter& printer, unsigned int messageNumber);
				JetSetCurrentMessage(Printers::JetPrinter& printer);
				virtual bool parseRequest(const tinyxml2::XMLElement* xml);
				virtual bool parseResponse(const tinyxml2::XMLElement*xml);

			private:
				virtual void buildRequest();
				virtual void buildResponse();

				unsigned int _msgNumber;
		};

		class JetSendMessage : public JetCommand
		{
			public:
				JetSendMessage(Printers::JetPrinter& printer, const Printers::Message& message, const std::vector<char> &content, bool raw);
				JetSendMessage(Printers::JetPrinter& printer);
				virtual bool parseRequest(const tinyxml2::XMLElement* xml);
				virtual bool parseResponse(const tinyxml2::XMLElement*xml);

			private:
				virtual void buildRequest();
				virtual void buildResponse();

				Printers::Message _message;
				std::vector<char> _content;
				bool _raw;
		};

		class JetResetCurrentGroup : public JetCommand
		{
			public:
				JetResetCurrentGroup(Printers::JetPrinter& printer);
				virtual bool parseRequest(const tinyxml2::XMLElement* xml);
				virtual bool parseResponse(const tinyxml2::XMLElement*xml);

			private:
				virtual void buildRequest();
				virtual void buildResponse();
		};

		class JetGetMessages : public JetCommand
		{
			public:
				JetGetMessages(Printers::JetPrinter& printer, const std::string& groupName);
				JetGetMessages(Printers::JetPrinter& printer);
				virtual bool parseRequest(const tinyxml2::XMLElement* xml);
				virtual bool parseResponse(const tinyxml2::XMLElement*xml);

			private:
				virtual void buildRequest();
				virtual void buildResponse();

				std::string _group;
		};

		class JetCreateMessagesGroup : public JetCommand
		{
			public:
				JetCreateMessagesGroup(Printers::JetPrinter& printer, const std::string& groupName);
				JetCreateMessagesGroup(Printers::JetPrinter& printer);
				virtual bool parseRequest(const tinyxml2::XMLElement* xml);
				virtual bool parseResponse(const tinyxml2::XMLElement*xml);

			private:
				virtual void buildRequest();
				virtual void buildResponse();

				std::string _group;
		};

		class JetSendMessageGroup : public JetCommand
		{
			public:
				JetSendMessageGroup(Printers::JetPrinter& printer, const std::string& groupName, const Printers::Message& message, const std::vector<char> &content, bool raw);
				JetSendMessageGroup(Printers::JetPrinter& printer);
				virtual bool parseRequest(const tinyxml2::XMLElement* xml);
				virtual bool parseResponse(const tinyxml2::XMLElement*xml);

			private:
				virtual void buildRequest();
				virtual void buildResponse();

				std::string _group;
				Printers::Message _message;
				std::vector<char> _content;
				bool _raw;
		};

		class JetDeleteMessagesGroup : public JetCommand
		{
			public:
				JetDeleteMessagesGroup(Printers::JetPrinter& printer, const std::string& groupName);
				JetDeleteMessagesGroup(Printers::JetPrinter& printer);
				virtual bool parseRequest(const tinyxml2::XMLElement* xml);
				virtual bool parseResponse(const tinyxml2::XMLElement*xml);

			private:
				virtual void buildRequest();
				virtual void buildResponse();

				std::string _group;
		};
	}
}

#endif  //MACSA_MPROTOCOL_COMMANDS_SET_CURRENT_MESSAGE_H
