#include "mprotocol/mlive.h"

using namespace Macsa::MProtocol;
using namespace tinyxml2;

MLive::MLive(Printers::Printer &printer) :
	MCommandBase(printer)
{
}

std::string MLive::commandName() const
{
	return MLIVE;
}

#if defined (MSERVER)

void MLive::build()
{
	XMLElement* cmd = _doc.NewElement(MLIVE);
	cmd->SetAttribute(MLIVE_DT_ATTR,		dateTime().c_str());
	cmd->SetAttribute(MLIVE_STATUS_ATTR,	MTools::toString(_printer.statusChanged()).c_str());
	cmd->SetAttribute(MLIVE_CONFIG_ATTR,	MTools::toString(_printer.configChanged()).c_str());
	cmd->SetAttribute(MLIVE_FILES_ATTR,		MTools::toString(_printer.filesChanged()).c_str());
	cmd->SetAttribute(MLIVE_FONTS_ATTR,		MTools::toString(_printer.fontsChanged()).c_str());
	cmd->SetAttribute(MLIVE_ERRORS_ATTR,	MTools::toString(_printer.errorsChanged()).c_str());

	setWind(&cmd);
}

bool MLive::parse(const XMLElement *root)
{
	return isNoChildrenSingleNode(root, MLIVE);
}

#elif defined (MCLIENT)

void MLive::build()
{
	XMLElement* cmd = _doc.NewElement(MLIVE);
	setWind(&cmd);
}

bool MLive::parse(const XMLElement *wind)
{
    bool valid = false;
    const XMLElement * pwind = getWindNode(wind);
	if(pwind != nullptr){
		const XMLElement * cmd = pwind->FirstChildElement(MLIVE);
		if (cmd != nullptr)
        {
            const char* dt = cmd->Attribute(MLIVE_DT_ATTR);
            valid = (!cmd->NoChildren() && dt != nullptr);
            if (valid){
                _printer.setDateTime(dt);
                _printer.setStatusChanged(cmd->BoolAttribute(MLIVE_STATUS_ATTR));
                _printer.setConfigChanged(cmd->BoolAttribute(MLIVE_CONFIG_ATTR));
                _printer.setFilesChanged(cmd->BoolAttribute(MLIVE_FILES_ATTR));
                _printer.setFontsChanged(cmd->BoolAttribute(MLIVE_FONTS_ATTR));
                _printer.setErrorsChanged(cmd->BoolAttribute(MLIVE_ERRORS_ATTR));

                //TODO new protocol childs
            }

        }
    }
    return valid;
}

#endif
