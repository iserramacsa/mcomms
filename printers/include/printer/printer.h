#ifndef PRINTER_DEFINITIONS_H
#define PRINTER_DEFINITIONS_H

#include <string>
#include "files.h"
#include "configuration.h"
#include "status.h"
#include "comms.h"

namespace Macsa {
	namespace Printers {
		class Printer {
			public:
				Printer();
				virtual ~Printer();

				virtual std::string type() const;

				virtual int id() const;
				virtual void setId(int id);

				//virtual bool statusChanged() const;
				//virtual void setStatusChanged(bool changed);
				//
				//virtual bool configChanged() const;
				//virtual void setConfigChanged(bool changed);
				//
				//virtual bool filesChanged() const;
				//virtual void setFilesChanged(bool changed);
				//
				//virtual bool fontsChanged() const;
				//virtual void setFontsChanged(bool changed);
				//
				//virtual bool errorsChanged() const;
				//virtual void setErrorsChanged(bool changed);

				std::time_t dateTime() const;
				void setDateTime(const std::time_t &dateTime);
				std::string formatedDateTime() const;

				virtual std::string controllerVersion() const;
				virtual std::string apiVersion() const;
				virtual std::string fpgaVersion() const;
				virtual void setVersions(const std::string &controllerVersion, const std::string &apiVersion, const std::string &fpgaVersion);

				Configuration& configuration();
				const Configuration& configuration() const;

				Status& status();
				const Status& status() const;

				PrinterFiles& files();
				const PrinterFiles& files() const;

				PrinterComms& comms();
				const PrinterComms& comms() const;
        protected:
				int _id;
				Configuration	_configuration;
				Status			_status;
				PrinterFiles	_files;
				PrinterComms	_comms;


//              bool _statusChanged;	//TODO Move to printer monitor
//              bool _configChanged;	//TODO Move to printer monitor
//              bool _filesChanged;		//TODO Move to printer monitor
//				bool _fontsChanged;		//TODO Move to printer monitor
//				bool _errorsChanged;	//TODO Move to printer monitor

				std::string _type;
		};
	}
}

#endif
