#ifndef MACSA_PRINTER_JET_PRINTHEAD_H
#define MACSA_PRINTER_JET_PRINTHEAD_H

#include "printer/encoder.h"
#include "jet/datatypes.h"

namespace Macsa {
	namespace Printers {
		class JetPrinthead {
			public:
				JetPrinthead(unsigned int id);
				JetPrinthead(const JetPrinthead&);

				inline bool operator == (const JetPrinthead& other) const {return equal(other);}
				inline bool operator != (const JetPrinthead& other) const {return !equal(other);}

				unsigned int id() const;

				std::string ipAddress() const;
				void setIpAddress(const std::string &ipAddress);

				std::string lineId() const;
				void setLineId(const std::string &lineId);

				std::string machineId() const;
				void setMachineId(const std::string &machineId);

				std::string defaultFont() const;
				void setDefaultFont(const std::string &defaultFont);

				double printDelay() const;
				void setPrintDelay(double printDelay);

				unsigned int horizontalResolution() const;
				void sethorizontalResolution(unsigned int hRes);

				bool invertedBitmap() const;
				void setInvertedBitmap(bool inverted);

				unsigned int temperature() const;
				void setTemperature(unsigned int temperature);

			protected:
				//std::mutex* _mutex;
				const unsigned int _id; //JetPrinterType ¿?
				std::string _ipAddress;
				std::string _lineId;
				std::string _machineId;
				std::string _defaultFont;
				double _printDelay;
				unsigned int _temperature;
				unsigned int _hres;
				bool _inverted;
				bool _printingList;
				bool _fifo;
				bool _delayInPoints;
				bool _sendImageAfterPrint;
				bool _stbIncrementsSSCC;
				bool _stbResetPrintingList;
				bool _optimizeBarcode;
				int _maxPrintTime;
				Encoder _encoder;
				int _uvLampTime;
				bool _uvLampControl;
				int _xrOffset;
				int _cellFilter;
				OverlappingMode _overlappingMode;

				bool equal(const JetPrinthead &other) const;
				void copy (const JetPrinthead& other);

		};
	}
}

#endif //MACSA_PRINTER_JET_PRINTHEAD_H
