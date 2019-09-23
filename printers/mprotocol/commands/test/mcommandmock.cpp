#include "mcommandmock.h"
#include <gmock/gmock.h>

MCommandMock::MCommandMock(Macsa::Printers::Printer &printer) :
	MCommandBase(printer)
{}

MCommandMock::~MCommandMock()
{}

std::string MCommandMock::commandName() const
{
	return "MCommandMock";
}

bool MCommandMock::parse(const tinyxml2::XMLElement * /*element*/)
{
	return true;
}

tinyxml2::XMLElement *MCommandMock::getWind()
{
	return MCommandBase::getWind();
}

tinyxml2::XMLElement *MCommandMock::setWind(tinyxml2::XMLElement **cmd, MErrorCode error)
{
	return MCommandBase::setWind(cmd, error);
}

const tinyxml2::XMLElement *MCommandMock::getWindNode(const tinyxml2::XMLElement *element)
{
	return MCommandBase::getWindNode(element);
}

bool MCommandMock::isNoChildrenSingleNode(const tinyxml2::XMLElement *wind, const std::string &nodeName)
{
	return MCommandBase::isNoChildrenSingleNode(wind, nodeName);
}

std::string MCommandMock::dateTime() const
{
	return MCommandBase::dateTime();
}

tinyxml2::XMLElement *MCommandMock::textElement(const std::string &name, const std::string &content, tinyxml2::XMLElement **parentNode)
{
	return MCommandBase::textElement(name, content, parentNode);
}

void MCommandMock::build()
{
	return;
}

tinyxml2::XMLError MCommandMock::QueryStringAttribute(const tinyxml2::XMLElement *element, const std::string &attr, std::string &value)
{
	return MCommandBase::QueryStringAttribute(element, attr, value);
}

bool MCommandMock::isElement(const tinyxml2::XMLElement *element, const std::string &name)
{
	return MCommandBase::isElement(element, name);
}

tinyxml2::XMLElement *MCommandMock::newElement(const std::string &name, tinyxml2::XMLElement **parentNode)
{
	return MCommandBase::newElement(name, parentNode);
}

bool MCommandMock::valid(const tinyxml2::XMLElement *wind)
{
	return MCommandBase::valid(wind);
}

tinyxml2::XMLDocument *MCommandMock::doc()
{
	return &_doc;
}
