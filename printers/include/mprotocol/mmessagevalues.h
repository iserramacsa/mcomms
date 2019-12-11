#ifndef  MACSA_MPROTOCOL_COMMANDS_MESSAGE_VALUES_H
#define  MACSA_MPROTOCOL_COMMANDS_MESSAGE_VALUES_H

#include "mcommands.h"
#include <string>
#include <map>
#include "nisx/counter.h"
#include "nisx/datetime.h"

namespace Macsa {
	namespace MProtocol {

#if __cplusplus >= 201103L
		using userFieldsMap = std::map<std::string, std::string>;
		using datesMap      = std::map<std::string, Nisx::DateTime>;
		using countersMap   = std::map<std::string, Nisx::Counter>;
#else
		typedef std::map<std::string, std::string>           userFieldsMap;
		typedef std::map<std::string, Nisx::DateTime> datesMap;
		typedef std::map<std::string, Nisx::Counter>  countersMap;
#endif
		/**
		 * @brief The MMessageValues is an abstract class to group all methods related
		 * to get/modify variable fields of printer message files
		 */
		class MMessageValues : public MCommand
		{
			public:
				MMessageValues(const std::string& command, Printers::TIJPrinter& printer, const std::string& filename);
				virtual ~MMessageValues();

				std::string filename() const;
				MProtocol::userFieldsMap userFieldsMap() const;
				MProtocol::countersMap countersMap() const;
				MProtocol::datesMap datesMap() const;

			protected:
				std::string _filename;
				MProtocol::userFieldsMap _userFieldsMap;
				MProtocol::countersMap _countersMap;
				MProtocol::datesMap _datesMap;

				tinyxml2::XMLElement* userFieldsToXml(tinyxml2::XMLElement** parent);
				tinyxml2::XMLElement* datesToXml(tinyxml2::XMLElement** parent);
				tinyxml2::XMLElement* countersToXml(tinyxml2::XMLElement** parent);

				void userFieldsFromXml(const tinyxml2::XMLElement *parent, MProtocol::userFieldsMap& map) const;
				void datesFromXml(const tinyxml2::XMLElement* parent, MProtocol::datesMap& map) const;
				void countersFromXml(const tinyxml2::XMLElement* parent, MProtocol::countersMap& map) const;

		};

		/**
		 * @brief The GETMESSAGEVALUES command class, allow the client to get user filed of the specified Nisx file in filename
		 */
		class MGetMessageValues : public MMessageValues
		{
			public:
				MGetMessageValues(Printers::TIJPrinter& printer, const std::string& filename = "",
								  const MProtocol::userFieldsMap &userFields = MProtocol::userFieldsMap());
				virtual  ~MGetMessageValues();
				virtual bool parseRequest(const tinyxml2::XMLElement* xml);
				virtual bool parseResponse(const tinyxml2::XMLElement*xml);
			private:
				virtual void buildRequest();
				virtual void buildResponse();
		};

		/**
		 * @brief The SETMESSAGEVALUES command class, allow the client to change user filed of specified Nisx file in filename
		 */
		class MSetMessageValues : public MMessageValues
		{
			public:
				MSetMessageValues(Printers::TIJPrinter& printer, const std::string& filename = "",
								  const MProtocol::userFieldsMap& userFields = MProtocol::userFieldsMap());
				virtual  ~MSetMessageValues();
				virtual bool parseRequest(const tinyxml2::XMLElement* xml);
				virtual bool parseResponse(const tinyxml2::XMLElement*xml);

			private:
				virtual void buildRequest();
				virtual void buildResponse();
		};

		/**
		 * @brief The GETMESSAGEDATASOURCE command class, allow the client to get variable fields of the specified Nisx file in filename
		 */
		class MGetMessageDataSource : public MMessageValues
		{
			public:
				MGetMessageDataSource(Printers::TIJPrinter& printer, const std::string& filename = "", const std::string& fieldType = "",
									  const MProtocol::userFieldsMap &userFields = MProtocol::userFieldsMap(),
									  const MProtocol::datesMap &dates = MProtocol::datesMap(),
									  const MProtocol::countersMap &counters = MProtocol::countersMap());
				virtual ~MGetMessageDataSource();
				virtual bool parseRequest(const tinyxml2::XMLElement* xml);
				virtual bool parseResponse(const tinyxml2::XMLElement*xml);
				std::string fieldType() const;

			private:
				virtual void buildRequest();
				virtual void buildResponse();

				std::string _fieldType;
		};

		/**
		 * @brief The SETMESSAGEDATASOURCE command class, allow the client to change variable fields of the specified Nisx file in filename
		 */
		class MSetMessageDataSource : public MMessageValues
		{
			public:
				MSetMessageDataSource(Printers::TIJPrinter& printer, const std::string& filename = "", const std::string& fieldType = "",
									  const MProtocol::userFieldsMap &userFields = MProtocol::userFieldsMap(),
									  const MProtocol::datesMap &dates = MProtocol::datesMap(),
									  const MProtocol::countersMap &counters = MProtocol::countersMap());
				virtual ~MSetMessageDataSource();
				virtual bool parseRequest(const tinyxml2::XMLElement* xml);
				virtual bool parseResponse(const tinyxml2::XMLElement*xml);
				std::string fieldType() const;

			private:
				virtual void buildRequest();
				virtual void buildResponse();

				std::string _fieldType;
		};
	}
}

#endif // MACSA_MPROTOCOL_COMMANDS_MESSAGE_VALUES_H
