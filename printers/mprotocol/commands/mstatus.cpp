#include "mprotocol/mstatus.h"

using namespace Macsa::MProtocol;
using namespace tinyxml2;

MGetStatus::MGetStatus(Printers::Printer &printer):
	MCommandBase(printer)
{
}

std::string MGetStatus::commandName() const
{
	return MSTATUS;
}

void MGetStatus::build()
{
	XMLElement * cmd = _doc.NewElement(MSTATUS);
	XMLElement * dt = textElement(MSTATUS_DT, dateTime());
	cmd->InsertEndChild(dt);

	setWind(&cmd);
}


bool MGetStatus::parse(const XMLElement *root)
{
	return isNoChildrenSingleNode(root, MSTATUS);
}

