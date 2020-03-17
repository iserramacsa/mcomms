#ifndef MACSA_PRINTER_JET_PRINTER_H
#define MACSA_PRINTER_JET_PRINTER_H

#include "printer/printer.h"
#include "printhead.h"
#include "messagemanager.h"
#include "jetcomms.h"
#include <mutex>
#include <map>

namespace Macsa {
	namespace Printers {
		class JetPrinter : public Printer {

			public:
				static int libraryVersionMajor();
				static int libraryVersionMinor();
				static int libraryVersionRevision();
				static std::string libraryVersion();

			public:
				JetPrinter();
				JetPrinter(const JetPrinter&);

				virtual ~JetPrinter() override;

				virtual PrinterFiles* files() override;
				virtual const PrinterFiles* files() const override;

				virtual PrinterComms* comms() override;
				virtual const PrinterComms* comms() const override;

				virtual std::string formatedDateTime() const;
				virtual std::string formatedDateTime(time_t time) const;
				virtual std::time_t dateTimeFromString(const std::string &dt) const;

				virtual void setDateTime(const std::time_t& dateTime) override;
				virtual void setDateTime(const std::string& formatedDatetime);

				virtual void operator = (const JetPrinter& other){return copy(other);}

				unsigned int printheadTemperature(unsigned int id);
				void setPrintheadTemperature(unsigned int id, unsigned int temperature);

				unsigned int tankLevel(unsigned int id);
				void setTankLevel(unsigned int id, unsigned int level);

				bool paused() const;
				void setPause(bool paused);

				bool printStatus() const;
				void setPrintStatus(bool printStatus);

				JetMessagesManager& messageManager();
				void setMessageManager(const JetMessagesManager& manager);

			protected:
				std::mutex* _mutex;
				PrinterFiles _files;
				JetComms	_comms;
				std::map<unsigned int, JetPrinthead> _printheads;
				JetMessagesManager _messageManager;
				std::map<unsigned int, unsigned int> _inkTanks;

				bool _paused;
				bool _printStatus;

				virtual bool equal(const Printer &other) const override;
				virtual void copy (const JetPrinter& other);

		};
	}
}

#endif
