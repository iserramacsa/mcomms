#include "jet/printhead.h"

using namespace Macsa::Printers;

JetPrinthead::JetPrinthead(unsigned int id) :
	_id(id)
{}

JetPrinthead::JetPrinthead(const JetPrinthead &other) :
	_id(other._id)
{
	copy(other);
}

unsigned int JetPrinthead::id() const
{
	return _id;
}

std::string JetPrinthead::ipAddress() const
{
	return _ipAddress;
}

void JetPrinthead::setIpAddress(const std::string &ipAddress)
{
	_ipAddress = ipAddress;
}

std::string JetPrinthead::lineId() const
{
	return _lineId;
}

void JetPrinthead::setLineId(const std::string &lineId)
{
	_lineId = lineId;
}

std::string JetPrinthead::machineId() const
{
	return _machineId;
}

void JetPrinthead::setMachineId(const std::string &machineId)
{
	_machineId = machineId;
}

std::string JetPrinthead::defaultFont() const
{
	return _defaultFont;
}

void JetPrinthead::setDefaultFont(const std::string &defaultFont)
{
	_defaultFont = defaultFont;
}

double JetPrinthead::printDelay() const
{
	return _printDelay;
}

void JetPrinthead::setPrintDelay(double printDelay)
{
	_printDelay = printDelay;
}

unsigned int JetPrinthead::horizontalResolution() const
{
	return _hres;
}

void JetPrinthead::sethorizontalResolution(unsigned int hRes)
{
	_hres = hRes;
}

unsigned int JetPrinthead::temperature() const
{
	return _temperature;
}

void JetPrinthead::setTemperature(unsigned int temperature)
{
	_temperature = temperature;
}

const Encoder &JetPrinthead::encoder() const
{
    return _encoder;
}

Encoder &JetPrinthead::encoder()
{
	return _encoder;
}
void JetPrinthead::setEncoder(const Encoder &encoder)
{
    _encoder = encoder;
}

bool JetPrinthead::printingList() const
{
	return _printingList;
}

void JetPrinthead::setPrintingList(bool printingList)
{
	_printingList = printingList;
}

bool JetPrinthead::fifo() const
{
	return _fifo;
}

void JetPrinthead::setFifo(bool fifo)
{
	_fifo = fifo;
}

bool JetPrinthead::delayInPoints() const
{
	return _delayInPoints;
}

void JetPrinthead::setDelayInPoints(bool delayInPoints)
{
	_delayInPoints = delayInPoints;
}

bool JetPrinthead::sendImageAfterPrint() const
{
	return _sendImageAfterPrint;
}

void JetPrinthead::setSendImageAfterPrint(bool sendImageAfterPrint)
{
	_sendImageAfterPrint = sendImageAfterPrint;
}

bool JetPrinthead::stbIncrementsSSCC() const
{
	return _stbIncrementsSSCC;
}

void JetPrinthead::setStbIncrementsSSCC(bool stbIncrementsSSCC)
{
	_stbIncrementsSSCC = stbIncrementsSSCC;
}

bool JetPrinthead::stbResetPrintingList() const
{
	return _stbResetPrintingList;
}

void JetPrinthead::setStbResetPrintingList(bool stbResetPrintingList)
{
	_stbResetPrintingList = stbResetPrintingList;
}

bool JetPrinthead::optimizeBarcode() const
{
	return _optimizeBarcode;
}

void JetPrinthead::setOptimizeBarcode(bool optimizeBarcode)
{
	_optimizeBarcode = optimizeBarcode;
}

int JetPrinthead::maxPrintTime() const
{
	return _maxPrintTime;
}

void JetPrinthead::setMaxPrintTime(int maxPrintTime)
{
	_maxPrintTime = maxPrintTime;
}

int JetPrinthead::uvLampTime() const
{
	return _uvLampTime;
}

void JetPrinthead::setUvLampTime(int uvLampTime)
{
	_uvLampTime = uvLampTime;
}

bool JetPrinthead::uvLampControl() const
{
	return _uvLampControl;
}

void JetPrinthead::setUvLampControl(bool uvLampControl)
{
	_uvLampControl = uvLampControl;
}

int JetPrinthead::xrOffset() const
{
	return _xrOffset;
}

void JetPrinthead::setXrOffset(int xrOffset)
{
	_xrOffset = xrOffset;
}

int JetPrinthead::cellFilter() const
{
	return _cellFilter;
}

void JetPrinthead::setCellFilter(int cellFilter)
{
	_cellFilter = cellFilter;
}

OverlappingMode JetPrinthead::overlappingMode() const
{
	return _overlappingMode;
}

void JetPrinthead::setOverlappingMode(const OverlappingMode &overlappingMode)
{
	_overlappingMode = overlappingMode;
}

void JetPrinthead::setOverlappingMode(const nOverlappingMode &overlappingMode)
{
	_overlappingMode = overlappingMode;
}

void JetPrinthead::setOverlappingMode(const std::string &overlappingMode)
{
	_overlappingMode = overlappingMode;
}

TriggerMode JetPrinthead::printMode() const
{
	return _printMode;
}

void JetPrinthead::setPrintMode(const TriggerMode &printMode)
{
	_printMode = printMode;
}

void JetPrinthead::setPrintMode(const nTriggerMode &printMode)
{
	_printMode = printMode;
}

void JetPrinthead::setPrintMode(const std::string &printMode)
{
	_printMode = printMode;
}

bool JetPrinthead::equal(const JetPrinthead &other) const
{
	bool equal = false;

	if (_id == other._id) {
		equal &= (_ipAddress == other._ipAddress);
		equal &= (_lineId == other._lineId);
		equal &= (_machineId == other._machineId);
		equal &= (_defaultFont == other._defaultFont);
		equal &= (static_cast<int>(_printDelay * 1000) == static_cast<int>(other._printDelay * 1000));
		equal &= (_temperature == other._temperature);
		equal &= (_hres == other._hres);
		equal &= (_printingList == other._printingList);
		equal &= (_fifo == other._fifo);
		equal &= (_delayInPoints == other._delayInPoints);
		equal &= (_sendImageAfterPrint == other._sendImageAfterPrint);
		equal &= (_stbIncrementsSSCC == other._stbIncrementsSSCC);
		equal &= (_stbResetPrintingList == other._stbResetPrintingList);
		equal &= (_optimizeBarcode == other._optimizeBarcode);
		equal &= (_maxPrintTime == other._maxPrintTime);
		equal &= (_encoder == other._encoder);
		equal &= (_uvLampTime == other._uvLampTime);
		equal &= (_uvLampControl == other._uvLampControl);
		equal &= (_xrOffset == other._xrOffset);
		equal &= (_cellFilter == other._cellFilter);
		equal &= (_overlappingMode == other._overlappingMode);
		equal &= (_printMode == other._printMode);
	}

	return equal;
}

void JetPrinthead::copy(const JetPrinthead &other)
{
	_ipAddress = other._ipAddress;
	_lineId = other._lineId;
	_machineId = other._machineId;
	_defaultFont = other._defaultFont;
	_printDelay = other._printDelay;
	_temperature = other._temperature;
	_hres = other._hres;
	_printingList = other._printingList;
	_fifo = other._fifo;
	_delayInPoints = other._delayInPoints;
	_sendImageAfterPrint = other._sendImageAfterPrint;
	_stbIncrementsSSCC = other._stbIncrementsSSCC;
	_stbResetPrintingList = other._stbResetPrintingList;
	_optimizeBarcode = other._optimizeBarcode;
	_maxPrintTime = other._maxPrintTime;
	_encoder = other._encoder;
	_uvLampTime = other._uvLampTime;
	_uvLampControl = other._uvLampControl;
	_xrOffset = other._xrOffset;
	_cellFilter = other._cellFilter;
	_overlappingMode = other._overlappingMode;
	_printMode = other._printMode;
}
