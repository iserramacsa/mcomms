#ifndef MACSA_PRINTER_JET_MESSAGE_MANAGER_H
#define MACSA_PRINTER_JET_MESSAGE_MANAGER_H

#include <vector>
#include <string>
namespace Macsa {
	namespace Printers {

		class JetMessage {
			public:
				JetMessage(const std::string name, unsigned int number = 0);
				JetMessage(const JetMessage& other);
				~JetMessage();

				std::string name() const;

				unsigned int counter();
				void setCounter(unsigned int counter);

				unsigned int number();
				void setNumber(unsigned int number);

				inline bool operator == (const JetMessage& other) const {return equal(other);}
				inline bool operator != (const JetMessage& other) const {return !equal(other);}
				inline void operator = (const JetMessage& other) {copy(other);}


			private:
				unsigned int _counter;
				unsigned int _number;
				const std::string _name;

				virtual bool equal(const JetMessage& other) const;
				virtual void copy (const JetMessage& other);
		};

		class JetMessagesGroup {
			public:
				JetMessagesGroup(const std::string name);
				JetMessagesGroup(const JetMessagesGroup& other);
				~JetMessagesGroup();

				std::string name() const;

				std::string currentMessageName() const;
				unsigned int currentMessageNumber() const;
				void setCurrentMessage(const std::string& name, unsigned int number);

				std::vector<std::string> messages();
				void setMessages(const std::vector<std::string>& messages);

				JetMessage message(const std::string& name);

				inline bool operator == (const JetMessagesGroup& other) const {return equal(other);}
				inline bool operator != (const JetMessagesGroup& other) const {return !equal(other);}
				inline void operator = (const JetMessagesGroup& other) {copy(other);}

			private:
				const std::string _name;
				std::vector<JetMessage> _messages;
				JetMessage* _currentMessage;

				virtual bool equal(const JetMessagesGroup &other) const;
				virtual void copy (const JetMessagesGroup& other);
		};

		class JetMessagesManager {

			public:
				JetMessagesManager();
				JetMessagesManager(const JetMessagesManager&);
				virtual ~JetMessagesManager();

				std::string currentGroup() const;
				void setCurrentGroup(const std::string &currentGroup);

				int currentMessageNumber() const;
				std::string currentMessage() const;
				void setCurrentMessage(const std::string& name, unsigned int currentMessageNumber);

				inline bool operator == (const JetMessagesManager& other) const {return equal(other);}
				inline bool operator != (const JetMessagesManager& other) const {return !equal(other);}
				inline void operator = (const JetMessagesManager& other) {copy(other);}

			private:
				JetMessagesGroup* _currentGroup;
				std::vector<JetMessagesGroup> _messageGroups;

				virtual bool equal(const JetMessagesManager &other) const;
				virtual void copy (const JetMessagesManager& other);

		};
	}
}

#endif //MACSA_PRINTER_JET_MESSAGE_MANAGER_H
