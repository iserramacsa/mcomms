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

				virtual int dateTime() const;
				virtual void setDateTime(int dateTime);

			private:
				int _dateTime;
				const Configuration& _config;

		};
	}
}

#endif	//MACSA_PRINTERS_STATUS_H

