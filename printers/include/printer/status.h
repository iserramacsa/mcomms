#ifndef MACSA_PRINTERS_STATUS_H
#define MACSA_PRINTERS_STATUS_H

#include "configuration.h"

namespace Macsa {
	namespace Printers {
		class Status
		{
			public:
				Status(const Configuration& config);
				virtual ~Status();

				virtual time_t dateTime() const;
				virtual void setDateTime(time_t dateTime);

				virtual std::string controllerVersion() const;
				virtual std::string apiVersion() const;
				virtual std::string fpgaVersion() const;
				virtual void setVersions(const std::string &controllerVersion, const std::string &apiVersion, const std::string &fpgaVersion);

			private:
				std::time_t _dateTime;
				std::time_t _lastUpdate;

				std::string _controllerVersion;
				std::string _apiVersion;
				std::string _fpgaVersion;

				const Configuration& _config;

		};
	}
}

#endif	//MACSA_PRINTERS_STATUS_H

