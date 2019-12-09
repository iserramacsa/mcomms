#ifndef MFILESCOMMANDS_H
#define MFILESCOMMANDS_H

#include "mcommands.h"

namespace Macsa {
	namespace MProtocol {
		/**
		 * @brief The GETCONFIG command class
		 */
		class MGetFilesList : public MCommand
		{
			public:
				MGetFilesList(Printers::TIJPrinter& printer, const std::string& filter = "");
				virtual bool parseResponse(const tinyxml2::XMLElement*xml);
				virtual bool parseRequest(const tinyxml2::XMLElement* xml);

				std::string filter() const;

			private:
				std::string _filter;

				virtual void buildRequest();
				virtual void buildResponse();

				void splitFilePwd(const std::string& pwd, std::string& drive, std::string& folder, std::string& file);
				void insertFileToPrinterData(const std::string& pwd);
		};

		class MCopyFile : public MCommand
		{
			public:
				MCopyFile(Printers::TIJPrinter& printer, const std::string& sourceFilename = "", const std::string& targetFilename = "");
				virtual bool parseRequest(const tinyxml2::XMLElement* xml);
				virtual bool parseResponse(const tinyxml2::XMLElement*xml);

				std::string sourceFilename() const;
				std::string targetFilename() const;

			private:
				std::string _sourceFilename;
				std::string _targetFilename;

				virtual void buildRequest();
				virtual void buildResponse();
		};

		class MMoveFile : public MCommand
		{
			public:
				MMoveFile(Printers::TIJPrinter& printer, const std::string& sourceFilename = "", const std::string& targetFilename = "");
				virtual bool parseRequest(const tinyxml2::XMLElement* xml);
				virtual bool parseResponse(const tinyxml2::XMLElement*xml);

				std::string sourceFilename() const;
				std::string targetFilename() const;

			private:
				std::string _sourceFilename;
				std::string _targetFilename;

				virtual void buildRequest();
				virtual void buildResponse();
		};

		class MDeleteFile : public MCommand
		{
			public:
				MDeleteFile(Printers::TIJPrinter& printer, const std::string& filename = "");
				virtual bool parseRequest(const tinyxml2::XMLElement* xml);
				virtual bool parseResponse(const tinyxml2::XMLElement*xml);

				std::string filename() const;

			private:
				std::string _filename;

				virtual void buildRequest();
				virtual void buildResponse();
		};

		class MGetFile : public MCommand
		{
			public:
				MGetFile(Macsa::Printers::TIJPrinter &printer, const std::string &filename = "", bool raw = false);
				virtual bool parseRequest(const tinyxml2::XMLElement* xml);
				virtual bool parseResponse(const tinyxml2::XMLElement*xml);

				std::string filename() const;
				bool raw() const;

				std::vector<uint8_t> content() const;

			private:
				std::string _filename;
				std::vector<uint8_t> _content;
				bool _raw;

				virtual void buildRequest();
				virtual void buildResponse();
				std::string contentToString(const std::vector<uint8_t> content, bool raw) const;
				std::vector<uint8_t> contentFromString(const char* data, bool raw) const;
		};

		class MSetFile : public MCommand
		{
			public:
				MSetFile(Macsa::Printers::TIJPrinter &printer, const std::string &filename = "", const std::vector<uint8_t>& content = std::vector<uint8_t>(), bool raw = false);
				virtual bool parseRequest(const tinyxml2::XMLElement* xml);
				virtual bool parseResponse(const tinyxml2::XMLElement*xml);

				std::string filename() const;
				bool raw() const;

				std::vector<uint8_t> content() const;

			private:
				std::string _filename;
				std::vector<uint8_t> _content;
				bool _raw;

				virtual void buildRequest();
				virtual void buildResponse();
				std::string contentToString(const std::vector<uint8_t> content, bool raw) const;
				std::vector<uint8_t> contentFromString(const char* data, bool raw) const;
		};
	}
}
#endif // MFILESCOMMANDS_H
