#ifndef MACSA_PRINTER_TIJ_PRINTER_H
#define MACSA_PRINTER_TIJ_PRINTER_H

#include "printer/printer.h"
#include "printer/board.h"
#include "tijcomms.h"
#include <map>

namespace Macsa {
	namespace Printers {
		class TijPrinter : public Printer {

			public:
				static int libraryVersionMajor();
				static int libraryVersionMinor();
				static int libraryVersionRevision();
				static std::string libraryVersion();

			public:
				TijPrinter();
				TijPrinter(const TijPrinter&);


				virtual ~TijPrinter() override;

				virtual PrinterFiles* files() override;
				virtual const PrinterFiles* files() const override;

				virtual PrinterComms* comms() override;
				virtual const PrinterComms* comms() const override;

				virtual std::string formatedDateTime() const;
				virtual std::string formatedDateTime(time_t time) const;
				virtual std::time_t dateTimeFromString(std::string dt) const;

				virtual void setDateTime(const std::time_t& dateTime) override;
				virtual void setDateTime(const std::string& formatedDatetime);

				virtual std::string controllerVersion() const;
				virtual std::string apiVersion() const;
				virtual std::string fpgaVersion() const;
				virtual void setVersions(const std::string &controllerVersion, const std::string &apiVersion, const std::string &fpgaVersion);

				virtual DateCodes dateCodes() const;
				virtual void setDateCodes(const DateCodes &dateCodes);

				virtual std::vector<Board> boards() const;
				virtual Board* board(int id);
				virtual const Board * board(int id) const;
				virtual void setBoard(const Board& board);
				virtual void setBoards(const std::vector<Board>& boards);

				virtual std::vector<Error> errorsLog() const;
				virtual void setErrorsLog(const std::vector<Error>& errorsLog);

				virtual bool logsEnabled() const;
				virtual void setlogsEnabled(bool enable);
				virtual bool logComsEnabled() const;
				virtual void setlogComsEnabled(bool enable);
				virtual LoggerLevel loggerLevel() const;
				virtual void setloggerLevel(const LoggerLevel& logLevel);
				virtual void setloggerLevel(const std::string& logLevel);

				virtual void operator = (const TijPrinter& other){return copy(other);}

            protected:
				PrinterFiles _files;
				TijComms	_comms;
				std::string _controllerVersion;
				std::string _apiVersion;
				std::string _fpgaVersion;
				DateCodes	_dateCodes;
				std::mutex* _mutex;

				std::vector<Board> _boards;
				std::vector<Error> _errorsLog;
				LoggerLevel _logLevel;
				bool _traceLogs;
				bool _traceComms;

				virtual bool equal(const Printer &other) const override;
				virtual void copy (const TijPrinter& other);

		};
	}
}

#endif
