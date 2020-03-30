#ifndef MACSA_PRINTER_JET_BOARD_H
#define MACSA_PRINTER_JET_BOARD_H

#include "jet/jetio.h"
#include "jet/datatypes.h"
#include <string>
#include <vector>
#include <map>

namespace Macsa {
	namespace Printers {

		class JetBoard {
			public:
				JetBoard(const std::string& type, unsigned int id);
				JetBoard(const JetBoard& other);
				~JetBoard();

				JetBoardType type() const;
				unsigned int number() const;

				std::string id() const;
				void setId(const std::string &id);

				std::string version() const;
				void setVersion(const std::string &version);

				bool input(const std::string& id) const;
				void setInputs(const std::map<std::string, bool>& inputs);

				inline void operator = (const JetBoard& other) {return copy(other);}
				inline bool operator == (const JetBoard& other) const {return equal(other);}
				inline bool operator != (const JetBoard& other) const {return !equal(other);}


			private:
				const JetBoardType _type;
				unsigned int _number;
				std::string _version;
				std::string _id;
				std::vector<JetIO> _inputs;

				std::vector<JetIO>::const_iterator getInput(const std::string& id) const;

				virtual bool equal(const JetBoard& other) const;
				virtual void copy (const JetBoard& other);
		};
	}
}

#endif //MACSA_PRINTER_JET_BOARD_H
