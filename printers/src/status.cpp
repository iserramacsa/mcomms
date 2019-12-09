//#include "printer/status.h"

//using namespace Macsa;
//using namespace Macsa::Printers;

//Status::Status(const Configuration &config):
//	_config(config)
//{
//	_dateTime = 0;
//	_lastUpdate = 0;
//	_controllerVersion = "";
//	_apiVersion = "";
//	_fpgaVersion = "";
//}

//Status::~Status()
//{}

//time_t Status::dateTime() const
//{
//	double diff = difftime(_lastUpdate, time(nullptr));
//	return (_dateTime + static_cast<long>(diff));
//}

//void Status::setDateTime(time_t dateTime)
//{
//	_dateTime = dateTime;
//	_lastUpdate = time(nullptr);
//}

//std::string Status::controllerVersion() const
//{
//    return _controllerVersion;
//}

//std::string Status::apiVersion() const
//{
//    return _apiVersion;
//}

//std::string Status::fpgaVersion() const
//{
//	return _fpgaVersion;
//}

//void Status::setVersions(const std::string &controllerVersion, const std::string &apiVersion, const std::string &fpgaVersion)
//{
//	_controllerVersion = controllerVersion;
//	_apiVersion = apiVersion;
//	_fpgaVersion = fpgaVersion;
//}
