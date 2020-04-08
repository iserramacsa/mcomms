#ifndef MACSA_JETPROTOCOL_COMMANDS_SINGLE_CONFIG_H
#define MACSA_JETPROTOCOL_COMMANDS_SINGLE_CONFIG_H
#include "jetcommand.h"
#include "jet/datatypes.h"

namespace Macsa {
	namespace JetProtocol {
		/**
		 * @brief The Generic class for single command
		 */
		class JetSingleSetConfigBase : public JetCommand
		{
			public:
				JetSingleSetConfigBase(const std::string command, Printers::JetPrinter& printer);

				virtual bool parseRequest(const tinyxml2::XMLElement* xml) = 0;
				virtual bool parseResponse(const tinyxml2::XMLElement*xml);

			private:
				virtual void buildRequest() = 0;
				virtual void buildResponse();

				Printers::PrintDirection _direction;
		};

		/**
		 * @brief The SetPrintDirection command class
		 */
		class JetSetPrintDirection : public JetSingleSetConfigBase
		{
			public:
				JetSetPrintDirection(Printers::JetPrinter& printer, Printers::PrintDirection direction);
				JetSetPrintDirection(Printers::JetPrinter& printer);
				virtual bool parseRequest(const tinyxml2::XMLElement* xml);

			private:
				Printers::PrintDirection _direction;

				virtual void buildRequest();
		};
		/**
		 * @brief The SetPrintDirection command class
		 */
		class JetSetBitmapInverted : public JetSingleSetConfigBase
		{
			public:
				JetSetBitmapInverted(Printers::JetPrinter& printer, bool inverted);
				JetSetBitmapInverted(Printers::JetPrinter& printer);
				virtual bool parseRequest(const tinyxml2::XMLElement* xml);

			private:
				bool _inverted;
				virtual void buildRequest();
		};

		/**
		 * @brief The SetPrintSpeed command class
		 */
		class JetSetPrintSpeed : public JetSingleSetConfigBase
		{
			public:
				JetSetPrintSpeed(Printers::JetPrinter& printer, unsigned int speed);
				JetSetPrintSpeed(Printers::JetPrinter& printer);
				virtual bool parseRequest(const tinyxml2::XMLElement* xml);

			private:
				unsigned int _speed;
				virtual void buildRequest();
		};

		/**
		 * @brief The SetPrintDelay command class
		 */
		class JetSetPrintDelay : public JetSingleSetConfigBase
		{
			public:
				JetSetPrintDelay(Printers::JetPrinter& printer, unsigned int delay);
				JetSetPrintDelay(Printers::JetPrinter& printer);
				virtual bool parseRequest(const tinyxml2::XMLElement* xml);

			private:
				unsigned int _delay;
				virtual void buildRequest();
		};

		/**
		 * @brief The SetPrintDelay command class
		 */
		class JetSetHorizontalResolution : public JetSingleSetConfigBase
		{
			public:
				JetSetHorizontalResolution(Printers::JetPrinter& printer, unsigned int hres);
				JetSetHorizontalResolution(Printers::JetPrinter& printer);
				virtual bool parseRequest(const tinyxml2::XMLElement* xml);

			private:
				unsigned int _hres;
				virtual void buildRequest();
		};

		/**
		 * @brief The GetPrintSpeed command
		 */
		class JetGetPrintSpeed : public JetCommand
		{
			public:
				JetGetPrintSpeed(Printers::JetPrinter& printer);

				virtual bool parseRequest(const tinyxml2::XMLElement* xml);
				virtual bool parseResponse(const tinyxml2::XMLElement*xml);

			private:
				virtual void buildRequest();
				virtual void buildResponse();
		};

		/**
		 * @brief The GetPrintDelay command
		 */
		class JetGetPrintDelay : public JetCommand
		{
			public:
				JetGetPrintDelay(Printers::JetPrinter& printer);

				virtual bool parseRequest(const tinyxml2::XMLElement* xml);
				virtual bool parseResponse(const tinyxml2::XMLElement*xml);

			private:
				virtual void buildRequest();
				virtual void buildResponse();
		};

		/**
		 * @brief The GetHorizontalResolution command
		 */
		class JetGetHorizontalResolution : public JetCommand
		{
			public:
				JetGetHorizontalResolution(Printers::JetPrinter& printer);

				virtual bool parseRequest(const tinyxml2::XMLElement* xml);
				virtual bool parseResponse(const tinyxml2::XMLElement*xml);

			private:
				virtual void buildRequest();
				virtual void buildResponse();
		};

		/**
		 * @brief The GetHorizontalResolution command
		 */
		class JetResetInkAlarm : public JetCommand
		{
			public:
				JetResetInkAlarm(Printers::JetPrinter& printer);

				virtual bool parseRequest(const tinyxml2::XMLElement* xml);
				virtual bool parseResponse(const tinyxml2::XMLElement*xml);

			private:
				virtual void buildRequest();
				virtual void buildResponse();
		};
	}
}

#endif // MCONFIGCOMMANDS_H
