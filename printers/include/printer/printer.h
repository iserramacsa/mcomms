#ifndef PRINTER_DEFINITIONS_H
#define PRINTER_DEFINITIONS_H

#include <string>
#include "files.h"
#include "configuration.h"
#include "status.h"

namespace Macsa {
	namespace Printers {

		class Printer {
			public:
				Printer();
				virtual ~Printer();

				virtual std::string type() const;

				virtual int id() const;
				virtual void setId(int id);

				virtual bool statusChanged() const;
				virtual void setStatusChanged(bool changed);

				virtual bool configChanged() const;
				virtual void setConfigChanged(bool changed);

				virtual bool filesChanged() const;
				virtual void setFilesChanged(bool changed);

				virtual bool fontsChanged() const;
				virtual void setFontsChanged(bool changed);

				virtual bool errorsChanged() const;
				virtual void setErrorsChanged(bool changed);


				virtual std::string currentMessage() const;
				virtual void setCurrentMessage(std::string currentMessage);

                std::string dateTime() const;
                void setDateTime(const std::string &dateTime);

				Configuration *configuration();
				const Configuration *configuration() const;

				Status *status();
				const Status *status() const;

				PrinterFiles *files();
				const PrinterFiles *files() const;


        protected:
				Configuration _configuration;
				Status _status;
				PrinterFiles _files;

                int _id;

                bool _statusChanged;
                bool _configChanged;
                bool _filesChanged;
				bool _fontsChanged;
				bool _errorsChanged;

				std::string _type;
				std::string _currentMessage;
                std::string _dateTime;
		};
	}
}

#endif
