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

				unsigned int temperature() const;
				void setTemperature(unsigned int temperature);

				inline void operator = (const JetPrinthead& other) {return copy(other);}
				inline bool operator == (const JetPrinthead& other) const {return equal(other);}
				inline bool operator != (const JetPrinthead& other) const {return !equal(other);}

				const Encoder& encoder() const;
				Encoder& encoder();
				void setEncoder(const Encoder &encoder);

				bool printingList() const;
				void setPrintingList(bool printingList);

				bool fifo() const;
				void setFifo(bool fifo);

				bool delayInPoints() const;
				void setDelayInPoints(bool delayInPoints);

				bool sendImageAfterPrint() const;
				void setSendImageAfterPrint(bool sendImageAfterPrint);

				bool stbIncrementsSSCC() const;
				void setStbIncrementsSSCC(bool stbIncrementsSSCC);

				bool stbResetPrintingList() const;
				void setStbResetPrintingList(bool stbResetPrintingList);

				bool optimizeBarcode() const;
				void setOptimizeBarcode(bool optimizeBarcode);

				int maxPrintTime() const;
				void setMaxPrintTime(int maxPrintTime);

				int uvLampTime() const;
				void setUvLampTime(int uvLampTime);

				bool uvLampControl() const;
				void setUvLampControl(bool uvLampControl);

				int xrOffset() const;
				void setXrOffset(int xrOffset);

				int cellFilter() const;
				void setCellFilter(int cellFilter);

				OverlappingMode overlappingMode() const;
				void setOverlappingMode(const OverlappingMode &overlappingMode);
				void setOverlappingMode(const nOverlappingMode &overlappingMode);
				void setOverlappingMode(const std::string &overlappingMode);

				TriggerMode printMode() const;
				void setPrintMode(const TriggerMode &printMode);
				void setPrintMode(const nTriggerMode &printMode);
				void setPrintMode(const std::string &printMode);

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
				bool _printingList;
				bool _fifo;
				bool _delayInPoints;
				bool _sendImageAfterPrint;
				bool _stbIncrementsSSCC;
				bool _stbResetPrintingList;
				bool _optimizeBarcode;
				bool _uvLampControl;
				int _maxPrintTime;
				int _uvLampTime;
				int _xrOffset;
				int _cellFilter;
				OverlappingMode _overlappingMode;
				TriggerMode _printMode;
				Encoder _encoder;

				bool equal(const JetPrinthead &other) const;
				void copy (const JetPrinthead& other);

		};
	}
}

#endif //MACSA_PRINTER_JET_PRINTHEAD_H
