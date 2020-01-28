#ifndef MACSA_MPROTOCOL_COMMANDS_CONFIG_H
#define MACSA_MPROTOCOL_COMMANDS_CONFIG_H
#include "mconfigbase.h"

namespace Macsa {
	namespace MProtocol {
		/**
		 * @brief The GETCONFIG command class
		 */
		class MGetConfig : public MConfigCommand
		{
			public:
				MGetConfig(Printers::TIJPrinter& printer);

				virtual bool parseRequest(const tinyxml2::XMLElement* xml);
				virtual bool parseResponse(const tinyxml2::XMLElement*xml);

			private:
				virtual void buildRequest();
				virtual void buildResponse();

		};

		/**
		 * @brief The SETCONFIG command class
		 */
		class MSetConfig : public MConfigCommand
		{
			public:
				MSetConfig(Printers::TIJPrinter& printer);

				virtual bool parseRequest(const tinyxml2::XMLElement* xml);
				virtual bool parseResponse(const tinyxml2::XMLElement*xml);

			protected:
				virtual void buildRequest();
				virtual void buildResponse();
		};

		/**
		 * @brief The SETCONFIG command class
		 */
		class MSetDateTime : public MSetConfig
		{
			public:
				MSetDateTime(Printers::TIJPrinter& printer);
			private:
				virtual void buildRequest();
		};
	}
}

#endif // MCONFIGCOMMANDS_H
