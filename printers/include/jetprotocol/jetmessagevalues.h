#ifndef  MACSA_JetProtocol_COMMANDS_MESSAGE_VALUES_H
#define  MACSA_JetProtocol_COMMANDS_MESSAGE_VALUES_H

#include "jetcommand.h"
#include <string>
#include <map>
#include "nisx/counter.h"
#include "nisx/datetime.h"

namespace Macsa {
	namespace JetProtocol {

//#if __cplusplus >= 201103L
//		using userFieldsMap = std::map<std::string, std::string>;
//		using datesMap      = std::map<std::string, Nisx::DateTime>;
//		using countersMap   = std::map<std::string, Nisx::Counter>;
//#else
//		typedef std::map<std::string, std::string>           userFieldsMap;
//		typedef std::map<std::string, Nisx::DateTime> datesMap;
//		typedef std::map<std::string, Nisx::Counter>  countersMap;
//#endif
		/**
		 * @brief The JetMessageNumber
		 */
		class JetMessageNumber : public JetCommand
		{
			public:
				JetMessageNumber(Printers::JetPrinter& printer, const std::string& filename);
				virtual ~JetMessageNumber();

				virtual bool parseRequest(const tinyxml2::XMLElement* xml);
				virtual bool parseResponse(const tinyxml2::XMLElement*xml);

			protected:
				std::string _filename;

				virtual void buildRequest();
				virtual void buildResponse();

		};
	}
}

#endif // MACSA_JetProtocol_COMMANDS_MESSAGE_VALUES_H
