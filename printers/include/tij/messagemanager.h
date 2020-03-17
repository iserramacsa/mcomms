#ifndef MACSA_PRINTERS_MESSAGE_MANAGER_H
#define MACSA_PRINTERS_MESSAGE_MANAGER_H

#include "tij/datatypes.h"
#include <string>
#include <vector>
#include <array>
//BCD modes definition
#define MAX_BCD_CODES   16

namespace Macsa {
	namespace Printers {
#if __cplusplus >= 201103L
		using BCDTable = std::array<std::string, MAX_BCD_CODES>;
#else
		typedef std::array<std::string, MAX_BCD_CODES> BCDTable;
#endif

		class MessageManager {
			public:
				MessageManager();
				~MessageManager();

				BCDMode mode() const;
				void setMode(const BCDMode &mode);
				void setMode(const nBCDMode &mode);
				void setMode(const std::string &mode);

				std::string userMessage() const;
				void setUserMessage(const std::string &userMessage);

				const BCDTable& bcdTable() const;
				void setBcdTable(const std::vector<std::string>& bcdTable);
				void setBcdTable(const BCDTable& bcdTable);
				void setBcdMessage(uint8_t code, const std::string& message);
				const std::string& bcdMessage(uint8_t code);

				uint8_t currentBcdCode() const;
				void setCurrentBcdCode(const uint8_t &currentBcdCode);

				std::string currentMessage() const;

				void clear();

				//Operators
				void operator = (const MessageManager& other) {return copy(other);}
				bool operator == (const MessageManager& other)const {return equal(other);}
				bool operator != (const MessageManager& other)const {return !equal(other);}

			private:
				BCDMode		_mode;
				uint8_t		_currentBcdCode;
				std::string _userMessage;
				BCDTable _bcdTable;

				bool equal(const MessageManager& other) const;
				void copy(const MessageManager& other);

		};
	}
}

#endif //MACSA_PRINTERS_MESSAGE_MANAGER_H
