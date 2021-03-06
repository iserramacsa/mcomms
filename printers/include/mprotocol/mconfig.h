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
				MGetConfig(Printers::TijPrinter& printer);

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
				MSetConfig(Printers::TijPrinter& printer);

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
				MSetDateTime(Printers::TijPrinter& printer);
			private:
				virtual void buildRequest();
		};

		/**
		 * @brief The SETCONFIG command class
		 */
		class MUpdateConfig : public MSetConfig
		{
			public:
				MUpdateConfig(Printers::TijPrinter& baseConfig, Printers::TijPrinter& newConfig);
			private:
				virtual void buildRequest();
				Printers::TijPrinter _newConfig;
				void updateGeneralConfig(tinyxml2::XMLElement** parent);
				void updateCommsConfig(tinyxml2::XMLElement** parent);
				void updateBoards(tinyxml2::XMLElement** parent);
		};
	}
}

#endif // MCONFIGCOMMANDS_H
