#ifndef PRINTER_FILES_MANAGER_H
#define PRINTER_FILES_MANAGER_H

#include <string>
#include <vector>
#include "tij/datatypes.h"

namespace Macsa {
	namespace Printers {
		class IFilesManager
		{
			public:
				virtual ErrorCode copyFile(const std::string& source, const std::string& destination) const = 0;
				virtual ErrorCode moveFile(const std::string& source, const std::string& destination) const = 0;
				virtual ErrorCode deleteFile(const std::string& filename) const = 0;
				virtual ErrorCode getFile(const std::string& filename, std::vector<uint8_t>& content) const = 0;
				virtual ErrorCode setFile(const std::string& filename, const std::vector<uint8_t>& content) const = 0;
		};
	}
}

#endif
