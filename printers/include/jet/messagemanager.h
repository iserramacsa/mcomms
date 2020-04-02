#ifndef MACSA_PRINTER_JET_MESSAGE_MANAGER_H
#define MACSA_PRINTER_JET_MESSAGE_MANAGER_H

#include <vector>
#include <string>
namespace Macsa {
	namespace Printers {

		class Message {
			public:
				Message(const std::string name, unsigned int number = 0);
				Message(const Message& other);
				~Message();

				std::string name() const;

				unsigned int counter() const;
				void setCounter(unsigned int counter);

				unsigned int number() const;
				void setNumber(unsigned int number);

				std::string content() const;
				void setContent(const std::string &content);

				inline bool operator == (const Message& other) const {return equal(other);}
				inline bool operator != (const Message& other) const {return !equal(other);}
				inline void operator = (const Message& other) {copy(other);}

			private:
				unsigned int _counter;
				unsigned int _number;
				const std::string _name;
				std::string _content;

				virtual bool equal(const Message& other) const;
				virtual void copy (const Message& other);
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
				void setCurrentMessage(unsigned int number);
				void setMessageCounter(unsigned int messageNumber, unsigned int counter);

				std::vector<Message> messages() const;
				void setMessages(const std::vector<std::string>& messages);

				Message message(const std::string& name) const;
				Message message(unsigned int msgNum) const;
				void setMessageContent(const Message& msg);

				void clear();
				void addMessage(const std::string& name, unsigned int num);

				inline bool operator == (const JetMessagesGroup& other) const {return equal(other);}
				inline bool operator != (const JetMessagesGroup& other) const {return !equal(other);}
				inline void operator = (const JetMessagesGroup& other) {copy(other);}

			private:
				const std::string _name;
				std::vector<Message> _messages;
				Message* _currentMessage;

				virtual bool equal(const JetMessagesGroup &other) const;
				virtual void copy (const JetMessagesGroup& other);
		};

		class JetMessagesManager {

			public:
				JetMessagesManager();
				JetMessagesManager(const JetMessagesManager&);
				virtual ~JetMessagesManager();

				std::vector<std::string> groups() const;
				std::vector<Message> messages(const std::string& group) const;
				Message message(unsigned int num) const;

				std::string currentGroup() const;
				void setCurrentGroup(const std::string &currentGroup);
				bool groupExist(const std::string& group) const;
				bool addNewGroup(const std::string& group);
				JetMessagesGroup* group(const std::string& group);

				int currentMessageNumber() const;
				std::string currentMessage() const;
				void setCurrentMessage(const std::string& name, unsigned int currentMessageNumber);
				void setCurrentMessage(unsigned int currentMessageNumber);
				void setMessageCounter(unsigned int messageNumber, unsigned int counter);
				void setMessageContent(const Message& msg);


				inline bool operator == (const JetMessagesManager& other) const {return equal(other);}
				inline bool operator != (const JetMessagesManager& other) const {return !equal(other);}
				inline void operator = (const JetMessagesManager& other) {copy(other);}

			private:
				JetMessagesGroup* _currentGroup;
				std::vector<JetMessagesGroup> _messageGroups;

				virtual bool equal(const JetMessagesManager &other) const;
				virtual void copy (const JetMessagesManager& other);

				std::vector<JetMessagesGroup>::iterator findGroup(const std::string& group);
				std::vector<JetMessagesGroup>::const_iterator findGroup(const std::string& group) const;

		};
	}
}

#endif //MACSA_PRINTER_JET_MESSAGE_MANAGER_H
