#ifndef MACSA_MPROTOCOL_COMMANDS_STATUS_H
#define MACSA_MPROTOCOL_COMMANDS_STATUS_H

#include "mcommands.h"

namespace Macsa {
	namespace MProtocol {

		/**
		 * @brief The MStatusCommand class
		 */
		class MStatusCommand : public MCommand
		{
			public:
				MStatusCommand(std::string command, Printers::TijPrinter& printer);
				virtual ~MStatusCommand();

			protected:
				void countersToXml(const Printers::Board& board, tinyxml2::XMLElement **parent);
				void errorsToXml(const Printers::Board& board, tinyxml2::XMLElement **parent);
				void inputsToXml(const Printers::Board& board, tinyxml2::XMLElement **parent);
				void outputsToXml(const Printers::Board& board, tinyxml2::XMLElement **parent);
				void propertiesToXml(const Printers::Board& board, tinyxml2::XMLElement **parent);

				void countersFromXml(const tinyxml2::XMLElement *parent, Printers::Board& board) const;
				void errorsFromXml(const tinyxml2::XMLElement *parent, Printers::Board& board) const;
				void inputsFromXml(const tinyxml2::XMLElement *parent, Printers::Board& board) const;
				void outputsFromXml(const tinyxml2::XMLElement *parent, Printers::Board& board) const;
				void propertiesFromXml(const tinyxml2::XMLElement *parent, Printers::Board& board) const;
		};

		/**
		 * @brief The MGetStatus class
		 */
		class MGetStatus : public MStatusCommand
		{
			public:
				MGetStatus(Printers::TijPrinter& printer);
				virtual ~MGetStatus();
				virtual bool parseRequest(const tinyxml2::XMLElement* xml);
				virtual bool parseResponse(const tinyxml2::XMLElement* xml);

			private:
				virtual void buildRequest();
				virtual void buildResponse();
		};

		/**
		 * @brief The MGetIOStatus class
		 */
		class MGetIOStatus : public MStatusCommand
		{
			public:
				MGetIOStatus(Printers::TijPrinter& printer);
				virtual ~MGetIOStatus();
				virtual bool parseRequest(const tinyxml2::XMLElement* xml);
				virtual bool parseResponse(const tinyxml2::XMLElement* xml);

			private:
				virtual void buildRequest();
				virtual void buildResponse();
		};

		/**
		 * @brief The MGetErrors class
		 */
		class MGetErrors : public MStatusCommand
		{
			public:
				MGetErrors(Printers::TijPrinter& printer);
				virtual ~MGetErrors();
				virtual bool parseRequest(const tinyxml2::XMLElement* xml);
				virtual bool parseResponse(const tinyxml2::XMLElement* xml);

			private:
				virtual void buildRequest();
				virtual void buildResponse();
		};
	}
}

#endif // MSTATUS_COMMANDS_H
