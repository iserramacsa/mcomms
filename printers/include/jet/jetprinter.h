#ifndef MACSA_PRINTER_JET_PRINTER_H
#define MACSA_PRINTER_JET_PRINTER_H

#include "printer/printer.h"
#include "jet/datatypes.h"
#include "jet/printhead.h"
#include "jet/messagemanager.h"
#include "jet/jetcomms.h"
#include "jet/jetio.h"
#include "jet/jetboard.h"
#include "jet/jetlog.h"
#include <mutex>
#include <map>
#include <list>

namespace Macsa {
	namespace Printers {

		class JetPrinter : public Printer {

			public:
				static int jetLibraryVersionMajor();
				static int jetLibraryVersionMinor();
				static int jetLibraryVersionRevision();
				static std::string jetLibraryVersion();

			public:
				using logsList = std::list<Printers::LogItem>;
				using tanksMap = std::map<unsigned int, unsigned int>;

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

				std::string getLibraryVersion(const std::string& library) const;
				std::map<std::string,std::string> getLibrariesVersions() const;
				void clearLibrariesVersions();
				void setLibrariesVersions(const std::map<std::string, std::string> &librariesVersions);
				void setLibraryVersion(const std::string& library, const std::string& version);

				std::vector<unsigned int> printheads() const;
				JetPrinthead printhead(unsigned int id) const;
				void setPrinthead(const JetPrinthead ph);

				unsigned int printheadTemperature(unsigned int id);
				void setPrintheadTemperature(unsigned int id, unsigned int temperature);

				tanksMap inkTanks() const;
				unsigned int tankLevel(unsigned int id) const;
				void setTankLevel(unsigned int id, unsigned int level);

				bool paused() const;
				void setPause(bool paused);

				bool printStatus() const;
				void setPrintStatus(bool printStatus);

				JetMessagesManager &messageManager();
				const JetMessagesManager &messageManager() const;
				void setMessageManager(const JetMessagesManager& manager);

				bool inputEnabled(const std::string &boardType, unsigned int boardNum, const std::string &inputId) const;
				void setInputs(const std::string& boardType, unsigned int boardNum, const std::map<std::string, bool>& inputs);

				JetBoard board(const std::string& boardType, unsigned int boardNum) const;
				JetBoard board(JetBoardType boardType, unsigned int boardNum) const;
				void setBoard(const JetBoard& board);

				std::vector<JetIO> outputs() const;
				bool outputEnabled(const std::string& outputId) const;
				void setOutputs(const std::vector<JetIO>& outputs);

				PrintDirection printDir() const;
				void setPrintDir(const PrintDirection &printDir);

				uint64_t sscc() const;
				void setSscc(uint64_t sscc);

				bool bitmapInverted() const;
				void setBitmapInverted(bool bmpInverted);

				bool isInError() const;
				void setIsInError(bool isInError);

				void updateLogs(std::list<LogItem> logs);
				logsList logs(time_t from, time_t to) const;
				logsList logs() const ;

				virtual void operator = (const JetPrinter& other){return copy(other);}
				virtual bool operator == (const JetPrinter& other) const {return  equal(other);}
				virtual bool operator != (const JetPrinter& other) const {return !equal(other);}

			protected:
				std::mutex* _mutex;
				PrinterFiles _files;
				JetComms	_comms;
				std::map<std::string, std::string> _librariesVersions;
				std::map<unsigned int, JetPrinthead> _printheads;
				std::map<unsigned int, unsigned int> _inkTanks;
				std::vector<JetBoard> _boards;
				std::vector<JetIO> _outputs;
				std::list<LogItem> _logs;
				JetMessagesManager _messageManager;
				PrintDirection _printDir;
				bool _bmpInverted;
				bool _paused;
				bool _printStatus;
				bool _isInError;
				uint64_t _sscc;

				std::vector<JetBoard>::iterator getBoard(JetBoardType boardType, unsigned int boardNum);
				std::vector<JetBoard>::const_iterator getBoard(JetBoardType boardType, unsigned int boardNum) const;
				virtual bool equal(const Printer &other) const override;
				virtual void copy (const JetPrinter& other);

		};
	}
}

#endif
