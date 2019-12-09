#ifndef MCONFIGCOMMANDS_H
#define MCONFIGCOMMANDS_H
#include "mcommands.h"

namespace Macsa {
	namespace MProtocol {
		/**
		 * @brief The GETCONFIG command class
		 */
		class MGetConfig : public MCommand
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
		class MSetConfig : public MCommand
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

				virtual bool parseRequest(const tinyxml2::XMLElement* xml);

			private:
				virtual void buildRequest();
		};
	}
}

#endif // MCONFIGCOMMANDS_H
