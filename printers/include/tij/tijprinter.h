#ifndef MACSA_PRINTER_TIJ_PRINTER_H
#define MACSA_PRINTER_TIJ_PRINTER_H

#include "printer/printer.h"
#include "printer/board.h"
#include "tijcomms.h"
#include <map>

namespace Macsa {
	namespace Printers {
		class TIJPrinter : public Printer{
			public:
				TIJPrinter();
				virtual ~TIJPrinter() override;

				virtual PrinterFiles* files() override;
				virtual const PrinterFiles* files() const override;

				virtual PrinterComms* comms() override;
				virtual const PrinterComms* comms() const override;

				virtual std::string formatedDateTime() const;

				virtual std::string controllerVersion() const;
				virtual std::string apiVersion() const;
				virtual std::string fpgaVersion() const;
				virtual void setVersions(const std::string &controllerVersion, const std::string &apiVersion, const std::string &fpgaVersion);

				virtual DateCodes dateCodes() const;
				virtual void setDateCodes(const DateCodes &dateCodes);


				virtual std::vector<Board> boards() const;
				virtual const Board* board(int id) const;
				virtual Board* board(int id);
				virtual void setBoard(const Board& board);
				virtual void setBoards(const std::vector<Board>& boards);

			private:
				PrinterFiles _files;
				TIJComms	_comms;
				std::string _controllerVersion;
				std::string _apiVersion;
				std::string _fpgaVersion;
				DateCodes	_dateCodes;

				std::map<int, Board> _boards;
				LoggerLevel _logLevel;
				bool _traceLogs;
				bool _traceComms;

				virtual bool equal(const Printer &other) const override;

		};
	}
}

#endif
