#include "mprotocol/mmessagevalues.h"
#include "mprotocol/mprotocol.h"

#include <sstream>

using namespace Macsa;
using namespace Macsa::MProtocol;
using namespace tinyxml2;

//================		BASE CLASS		================//
MMessageValues::MMessageValues(const std::string &command, Printers::TijPrinter& printer, const std::string &filename) :
	MCommand(command, printer)
{
	_filename = filename;
	_userFieldsMap.clear();
	_countersMap.clear();
	_datesMap.clear();
}

MMessageValues::~MMessageValues()
{}

std::string MMessageValues::filename() const
{
	return _filename;
}

userFieldsMap MMessageValues::userFieldsMap() const
{
	return _userFieldsMap;
}

countersMap MMessageValues::countersMap() const
{
	return _countersMap;
}

datesMap MMessageValues::datesMap() const
{
	return _datesMap;
}

XMLElement *MMessageValues::userFieldsToXml(XMLElement **parent)
{
	if (parent) {
		for (userFieldsMap::const_iterator it = _userFieldsMap.begin(); it != _userFieldsMap.end(); it++)
		{
			XMLElement* uiField = createChildNode(MMESSAGE_USER_FIELD_ELEMENT, parent);
			if (uiField) {
				uiField->SetAttribute(ATTRIBUTE_NAME, it->first.c_str());
				uiField->SetAttribute(ATTRIBUTE_VALUE, it->second.c_str());
			}
		}
	}

	return  *parent;
}

XMLElement *MMessageValues::datesToXml(XMLElement **parent)
{
	if (parent) {
		for (datesMap::const_iterator it = _datesMap.begin(); it != _datesMap.end(); it++)
		{
			XMLElement* dtField = createChildNode(MMESSAGE_DATETIME_FIELD_ELEMENT, parent);
			if (dtField != nullptr) {
				dtField->SetAttribute(ATTRIBUTE_NAME, it->first.c_str());
				Macsa::Nisx::DateTime dt = it->second;
				dtField->SetAttribute(MMESSAGE_DATETIME_FORMAT_ATTR, dt.format().c_str());
				dtField->SetAttribute(MMESSAGE_DATETIME_DOFFSET_ATTR, dt.dayOffset());
				dtField->SetAttribute(MMESSAGE_DATETIME_MOFFSET_ATTR, dt.monthOffset());
				dtField->SetAttribute(MMESSAGE_DATETIME_YOFFSET_ATTR, dt.yearOffset());
				dtField->SetAttribute(MMESSAGE_DATETIME_SOD_ATTR, dt.startOfDay());
			}
		}
	}

	return  *parent;
}

XMLElement *MMessageValues::countersToXml(XMLElement **parent)
{
	if (parent) {
		for (countersMap::const_iterator it = _countersMap.begin(); it != _countersMap.end(); it++)
		{
			XMLElement* counterField = createChildNode(MMESSAGE_COUNTER_FIELD_ELEMENT, parent);
			if (counterField != nullptr) {
				counterField->SetAttribute(ATTRIBUTE_NAME, it->first.c_str());
				Macsa::Nisx::Counter counter = it->second;
				counterField->SetAttribute(MMESSAGE_COUNTER_ZERO_ATTR, counter.leadingZeros());
				counterField->SetAttribute(MMESSAGE_COUNTER_MIN_ATTR, counter.min());
				counterField->SetAttribute(MMESSAGE_COUNTER_MAX_ATTR, counter.max());
				counterField->SetAttribute(MMESSAGE_COUNTER_STEP_ATTR, counter.step());
				counterField->SetAttribute(MMESSAGE_COUNTER_REPEAT_ATTR, counter.repeat());
			}
		}
	}

	return  *parent;
}

void MMessageValues::userFieldsFromXml(const XMLElement *parent, Macsa::MProtocol::userFieldsMap &map) const
{
	const XMLElement* uifield = parent->FirstChildElement(MMESSAGE_USER_FIELD_ELEMENT);
	while (uifield != nullptr) {
		std::string key   = getTextAttribute(uifield, ATTRIBUTE_NAME);
		std::string value = getTextAttribute(uifield, ATTRIBUTE_VALUE);
		if (key.length() > 0) {
			if (map.find(key) == map.end()) {
					map.insert(std::pair<std::string, std::string>(key, value));
			}
			else {
				map[key] = value;
			}
		}
		uifield->NextSiblingElement(MMESSAGE_USER_FIELD_ELEMENT);
	}
}

void MMessageValues::datesFromXml(const XMLElement *parent, Macsa::MProtocol::datesMap& map) const
{
	const XMLElement* dtfield = parent->FirstChildElement(MMESSAGE_DATETIME_FIELD_ELEMENT);
	while (dtfield != nullptr) {
		std::string key = getTextAttribute(dtfield, ATTRIBUTE_NAME);
		Macsa::Nisx::DateTime dt;
		if  (map.find(key) != map.end()) {
			dt = map.at(key);
		}
		dt.setFormat(getTextAttribute(dtfield, MMESSAGE_DATETIME_FORMAT_ATTR, dt.format()));
		dt.setDayOffset(dtfield->IntAttribute(MMESSAGE_DATETIME_DOFFSET_ATTR, dt.dayOffset()));
		dt.setMonthOffset(dtfield->IntAttribute(MMESSAGE_DATETIME_MOFFSET_ATTR, dt.monthOffset()));
		dt.setYearOffset(dtfield->IntAttribute(MMESSAGE_DATETIME_YOFFSET_ATTR, dt.yearOffset()));
		dt.setStartOfDay(static_cast<uint8_t>(dtfield->UnsignedAttribute(MMESSAGE_DATETIME_SOD_ATTR, dt.startOfDay())));

		if  (map.find(key) != map.end()) {
			map[key] = dt;
		}
		else {
			map.insert(std::pair<std::string, Macsa::Nisx::DateTime>(key, dt));
		}

		dtfield->NextSiblingElement(MMESSAGE_DATETIME_FIELD_ELEMENT);
	}
}

void MMessageValues::countersFromXml(const XMLElement *parent, Macsa::MProtocol::countersMap &map) const
{
	const XMLElement* counterfield = parent->FirstChildElement(MMESSAGE_COUNTER_FIELD_ELEMENT);
	while (counterfield != nullptr) {
		std::string key = getTextAttribute(counterfield, ATTRIBUTE_NAME);
		Macsa::Nisx::Counter counter;
		if  (map.find(key) != map.end()) {
			counter = map.at(key);
		}
		counter.setLeadingZeros(counterfield->IntAttribute(MMESSAGE_COUNTER_ZERO_ATTR, counter.leadingZeros()));
		counter.setMin(counterfield->IntAttribute(MMESSAGE_COUNTER_MIN_ATTR, counter.min()));
		counter.setMax(counterfield->IntAttribute(MMESSAGE_COUNTER_MAX_ATTR, counter.max()));
		counter.setStep(counterfield->IntAttribute(MMESSAGE_COUNTER_STEP_ATTR, counter.step()));
		counter.setRepeat(getBoolAttribute(counterfield, MMESSAGE_COUNTER_REPEAT_ATTR, counter.repeat()));

		if  (map.find(key) != map.end()) {
			map[key] = counter;
		}
		else {
			map.insert(std::pair<std::string, Macsa::Nisx::Counter>(key, counter));
		}

		counterfield->NextSiblingElement(MMESSAGE_COUNTER_FIELD_ELEMENT);
	}
}

//================		GET USER FIELDS		================//
MGetMessageValues::MGetMessageValues(Printers::TijPrinter &printer, const std::string &filename, const Macsa::MProtocol::userFieldsMap &userFields) :
	MMessageValues(MMESSAGE_USER_FIELD_GET, printer, filename)
{
	_userFieldsMap = userFields;
}

MGetMessageValues::~MGetMessageValues()
{}

void MGetMessageValues::buildRequest()
{
	XMLElement* cmd = newCommandNode();
	if (cmd != nullptr) {
		cmd->SetAttribute(ATTRIBUTE_FILEPATH, _filename.c_str());
	}
}

bool MGetMessageValues::parseRequest(const XMLElement *xml)
{
	const XMLElement* cmd = getCommand(xml, _id);
	bool valid = (cmd != nullptr);
	if  (valid) {
		_filename = getTextAttribute(cmd, ATTRIBUTE_FILEPATH);
	}
	return valid;
}

void MGetMessageValues::buildResponse()
{
	XMLElement* cmd = newCommandNode();
	if (cmd) {
		cmd->SetAttribute(ATTRIBUTE_FILEPATH, _filename.c_str());
		userFieldsToXml(&cmd);
	}
	addWindError(_error);
}

bool MGetMessageValues::parseResponse(const XMLElement *xml)
{
	const XMLElement* cmd = getCommand(xml, _id);
	bool valid = (cmd != nullptr);
	if  (valid) {
		_error = getCommandError(xml);
		_filename = getTextAttribute(cmd, ATTRIBUTE_FILEPATH);
		if (_error == Printers::nErrorCode::SUCCESS) {
			_userFieldsMap.clear();
			userFieldsFromXml(cmd, _userFieldsMap);
		}
	}
	return valid;
}

//================		SET USER FIELDS		================//
MSetMessageValues::MSetMessageValues(Printers::TijPrinter &printer, const std::string &filename, const Macsa::MProtocol::userFieldsMap &userFields) :
	MMessageValues(MMESSAGE_USER_FIELD_SET, printer, filename)
{
	_userFieldsMap = userFields;
}

MSetMessageValues::~MSetMessageValues()
{}

void MSetMessageValues::buildRequest()
{
	XMLElement* cmd = newCommandNode();
	if (cmd != nullptr) {
		cmd->SetAttribute(ATTRIBUTE_FILEPATH, _filename.c_str());
		userFieldsToXml(&cmd);
	}
}

bool MSetMessageValues::parseRequest(const XMLElement *xml)
{
	const XMLElement* cmd = getCommand(xml, _id);
	bool valid = (cmd != nullptr);
	if  (valid) {
		_filename = getTextAttribute(cmd, ATTRIBUTE_FILEPATH);
		userFieldsFromXml(cmd, _userFieldsMap);
	}
	return valid;
}

void MSetMessageValues::buildResponse()
{
	XMLElement* cmd = newCommandNode();
	if (cmd) {
		cmd->SetAttribute(ATTRIBUTE_FILEPATH, _filename.c_str());
	}
	addWindError(_error);
}

bool MSetMessageValues::parseResponse(const XMLElement *xml)
{
	const XMLElement* cmd = getCommand(xml, _id);
	bool valid = (cmd != nullptr);
	if  (valid) {
		_filename = getTextAttribute(cmd, ATTRIBUTE_FILEPATH);
	}
	return valid;
}

//================		GET VARIABLE FIELDS		================//
MGetMessageDataSource::MGetMessageDataSource(Printers::TijPrinter &printer,
											 const std::string& filename,
											 const std::string& fieldType,
											 const MProtocol::userFieldsMap& userFields,
											 const MProtocol::datesMap& dates,
											 const MProtocol::countersMap& counters) :
	MMessageValues(MMESSAGE_DATA_SOURCE_GET, printer, filename)
{
	_fieldType = fieldType;
	_userFieldsMap = userFields;
	_datesMap = dates;
	_countersMap = counters;
}

MGetMessageDataSource::~MGetMessageDataSource()
{}

void MGetMessageDataSource::buildRequest()
{
	XMLElement* cmd = newCommandNode();
	if (cmd != nullptr) {
		cmd->SetAttribute(ATTRIBUTE_FILEPATH, _filename.c_str());
		cmd->SetAttribute(MMESSAGE_DATA_SOURCE_FIELD_TYPE_ATTR, _fieldType.c_str());
	}
}
bool MGetMessageDataSource::parseRequest(const XMLElement *xml)
{
	const XMLElement* cmd = getCommand(xml, _id);
	bool valid = (cmd != nullptr);
	if  (valid) {
		_filename  = getTextAttribute(cmd, ATTRIBUTE_FILEPATH);
		_fieldType = getTextAttribute(cmd, MMESSAGE_DATA_SOURCE_FIELD_TYPE_ATTR, DATA_SOURCE_ALL_FIELDS);
	}
	return valid;

}

void MGetMessageDataSource::buildResponse()
{
	XMLElement* cmd = newCommandNode();
	if (cmd) {
		cmd->SetAttribute(ATTRIBUTE_FILEPATH, _filename.c_str());
		cmd->SetAttribute(MMESSAGE_DATA_SOURCE_FIELD_TYPE_ATTR, _fieldType.c_str());
		if (_fieldType.empty() || _fieldType.compare(DATA_SOURCE_USER_FIELDS) == 0) {
			userFieldsToXml(&cmd);
		}
		if (_fieldType.empty() || _fieldType.compare(DATA_SOURCE_DATETIME_FIELDS) == 0) {
			datesToXml(&cmd);
		}
		if (_fieldType.empty() || _fieldType.compare(DATA_SOURCE_COUNTER_FIELDS) == 0) {
			countersToXml(&cmd);
		}
	}
	addWindError(_error);
}

bool MGetMessageDataSource::parseResponse(const XMLElement *xml)
{
	const XMLElement* cmd = getCommand(xml, _id);
	bool valid = (cmd != nullptr);
	if  (valid) {
		_error = getCommandError(xml);
		_filename  = getTextAttribute(cmd, ATTRIBUTE_FILEPATH);
		_fieldType = getTextAttribute(cmd, MMESSAGE_DATA_SOURCE_FIELD_TYPE_ATTR, DATA_SOURCE_ALL_FIELDS);
		if (_error == Printers::nErrorCode::SUCCESS) {
			_userFieldsMap.clear();
			if (_fieldType.empty() || _fieldType.compare(DATA_SOURCE_USER_FIELDS) == 0) {
				userFieldsFromXml(cmd, _userFieldsMap);
			}
			if (_fieldType.empty() || _fieldType.compare(DATA_SOURCE_DATETIME_FIELDS) == 0) {
				datesFromXml(cmd, _datesMap);
			}
			if (_fieldType.empty() || _fieldType.compare(DATA_SOURCE_COUNTER_FIELDS) == 0) {
				countersFromXml(cmd, _countersMap);
			}
		}
	}
	return valid;

}

std::string MGetMessageDataSource::fieldType() const
{
	return _fieldType;
}

//================		SET VARIABLE FIELDS		================//
MSetMessageDataSource::MSetMessageDataSource(Printers::TijPrinter &printer,
											 const std::string &filename,
											 const std::string &fieldType,
											 const MProtocol::userFieldsMap &userFields,
											 const MProtocol::datesMap &dates,
											 const MProtocol::countersMap &counters) :
	MMessageValues(MMESSAGE_DATA_SOURCE_SET, printer, filename)
{
	_fieldType = fieldType;
	_userFieldsMap = userFields;
	_datesMap = dates;
	_countersMap = counters;
}

MSetMessageDataSource::~MSetMessageDataSource()
{}

void MSetMessageDataSource::buildRequest()
{
	XMLElement* cmd = newCommandNode();
	if (cmd) {
		cmd->SetAttribute(ATTRIBUTE_FILEPATH, _filename.c_str());
		if (!_userFieldsMap.empty()) {
			userFieldsToXml(&cmd);
		}
		if (!_datesMap.empty()) {
			datesToXml(&cmd);
		}
		if (!_countersMap.empty()) {
			countersToXml(&cmd);
		}
	}
}

bool MSetMessageDataSource::parseRequest(const XMLElement *xml)
{
	const XMLElement* cmd = getCommand(xml, _id);
	bool valid = (cmd != nullptr);
	if  (valid) {
		_filename = getTextAttribute(cmd, ATTRIBUTE_FILEPATH);
		userFieldsFromXml(cmd, _userFieldsMap);
		datesFromXml(cmd, _datesMap);
		countersFromXml(cmd, _countersMap);
	}
	return valid;
}

void MSetMessageDataSource::buildResponse()
{
	XMLElement* cmd = newCommandNode();
	if (cmd) {
		cmd->SetAttribute(ATTRIBUTE_FILEPATH, _filename.c_str());
	}
	addWindError(_error);

}

bool MSetMessageDataSource::parseResponse(const XMLElement *xml)
{
	const XMLElement* cmd = getCommand(xml, _id);
	bool valid = (cmd != nullptr);
	if  (valid) {
		_filename = getTextAttribute(cmd, ATTRIBUTE_FILEPATH);
	}
	return valid;
}

std::string MSetMessageDataSource::fieldType() const
{
	return _fieldType;
}
