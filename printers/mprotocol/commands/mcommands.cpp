#include "mprotocol/mcommands.h"

#include <iostream>
#include <iomanip>
#include <sstream>

using namespace Macsa::MProtocol;
using namespace tinyxml2;

static int32_t seed = -1;

MCommandBase::MCommandBase(Printers::Printer& printer) :
	_printer(printer)
{
#if defined (MCLIENT)
		_id = nextId();
#endif
}

MCommandBase::~MCommandBase()
{
	_doc.Clear();
}

std::string MCommandBase::toString()
{
	build();
	XMLPrinter p;
	_doc.Print(&p);
	return p.CStr();
}

XMLElement * MCommandBase::getWind()
{
	if (_doc.RootElement() != nullptr){
		_doc.Clear();
	}
	XMLElement* wind = _doc.NewElement(MWIND);
	int id = static_cast<int>(_id);
	wind->SetAttribute(MWIND_ID_ATTR, id);
	_doc.InsertEndChild(wind);
	return _doc.RootElement();
}

XMLElement * MCommandBase::setWind(XMLElement ** cmd, MErrorCode error)
{
	if (cmd != nullptr && (*cmd) != nullptr){
		XMLElement *wind = getWind();
		XMLElement *xmlerror = _doc.NewElement(MERROR);
		xmlerror->SetAttribute(MERROR_CODE_ATTR,  error.toString().c_str());

		if(wind->InsertEndChild(xmlerror) == nullptr) {
			std::cerr << "[ERROR] (" << __PRETTY_FUNCTION__ << ") Error creating child (ERROR)" << std::endl;
		}

		if(wind->InsertEndChild(*cmd) == nullptr) {
			std::cerr << "[ERROR] (" << __PRETTY_FUNCTION__ << ") Error creating child ("<< (*cmd)->Name() <<")" << std::endl;
		}
		return wind;
	}
	return nullptr;
}

const XMLElement * MCommandBase::getWindNode(const XMLElement *root)
{
	if(isElement(root, MWIND)){
		unsigned int id = 0;
		if (root->QueryUnsignedAttribute(MWIND_ID_ATTR, &id) != XML_SUCCESS) {
			id = -1;
		}
#if defined (MSERVER)
		_id = static_cast<uint32_t>(id);
		return root;
#elif defined (MCLIENT)
		if (root->FirstChildElement(MERROR) != nullptr) {
			return root;
		}
#endif
	}

	return nullptr;
}

std::string MCommandBase::dateTime() const
{
	time_t t1 = ::time(nullptr);
	struct tm *t2 = localtime(&t1);

	std::stringstream dt;
	dt <<  std::setfill ('0') << std::setw(2) << t2->tm_mday;
	dt <<  std::setfill ('0') << std::setw(2) << (t2->tm_mon + 1);
	dt <<  std::setfill ('0') << std::setw(4) << (t2->tm_year + 1900);

	dt <<  std::setfill ('0') << std::setw(2) << t2->tm_hour;
	dt <<  std::setfill ('0') << std::setw(2) << t2->tm_min;
	dt <<  std::setfill ('0') << std::setw(2) << t2->tm_sec;

	return dt.str();
}

bool MCommandBase::isNoChildrenSingleNode(const XMLElement * wind, const std::string &nodeName)
{
	const XMLElement * pwind = getWindNode(wind);
	if(pwind != nullptr){
		const XMLElement * cmd = pwind->FirstChildElement(nodeName.c_str());
		if (cmd != nullptr){
			return  (std::string(cmd->Value()).compare(nodeName) == 0 &&
					 cmd->NoChildren());
		}
	}
	return false;
}

XMLElement *MCommandBase::textElement(const std::string &name, const std::string &content, XMLElement **parentNode)
{
	XMLElement* element = newElement(name, parentNode);
	if (element != nullptr){
		element->SetText(content.c_str());
	}
	return element;
}

XMLError MCommandBase::QueryStringAttribute(const XMLElement *element, const std::string &attr, std::string &value)
{
	const char* val = element->Attribute(attr.c_str());
	if(val != nullptr) {
		value = val;
		return XML_SUCCESS;
	}

	value.clear();
	return XML_NO_ATTRIBUTE;
}

bool MCommandBase::isElement(const XMLElement *element, const std::string &name)
{
	return (element != nullptr && element->ToElement() != nullptr && name.compare(element->Name()) == 0);
}

XMLElement *MCommandBase::newElement(const std::string &name, XMLElement **parentNode)
{
	 XMLElement * element = nullptr;
	 if (name.size()) {
		 element = _doc.NewElement(name.c_str());
		 if(element && parentNode != nullptr){
			 (*parentNode)->InsertEndChild(element);
		 }
	 }
	 return element;
}

bool MCommandBase::valid(const XMLElement *wind)
{
	bool valid = false;
	const XMLElement * err = wind->FirstChildElement(MERROR);
	if (err != nullptr){
		valid = (err->Attribute(MERROR_CODE_ATTR, MErrorCode(MErrorCode::Success).toString().c_str()) != nullptr);
	}
	return valid;
}

uint32_t MCommandBase::nextId() const
{
	if(++seed < 0){seed = 0;}
	return static_cast<uint32_t>(seed);
}
