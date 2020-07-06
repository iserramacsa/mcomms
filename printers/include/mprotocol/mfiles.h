#ifndef MACSA_MPROTOCOL_COMMANDS_FILES_H
#define MACSA_MPROTOCOL_COMMANDS_FILES_H

#include "mcommands.h"

namespace Macsa {
	namespace MProtocol {
		/**
		 * @brief The GETCONFIG command class
		 */
		class MGetFilesList : public MCommand
		{
			public:
				MGetFilesList(Printers::TijPrinter& printer, const std::string& filter = "");
				virtual bool parseResponse(const tinyxml2::XMLElement*xml);
				virtual bool parseRequest(const tinyxml2::XMLElement* xml);

				std::string filter() const;

			private:
				std::string _filter;

				virtual void buildRequest();
				virtual void buildResponse();

				void splitFilePwd(const std::string& pwd, std::string& drive, std::string& directory, std::string& file);
				void insertFileToPrinterData(const std::string& pwd);
		};

		class MCopyFile : public MCommand
		{
			public:
				MCopyFile(Printers::TijPrinter& printer, const std::string& sourceFilename = "", const std::string& targetFilename = "");
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
				MMoveFile(Printers::TijPrinter& printer, const std::string& sourceFilename = "", const std::string& targetFilename = "");
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
				MDeleteFile(Printers::TijPrinter& printer, const std::string& filename = "");
				virtual bool parseRequest(const tinyxml2::XMLElement* xml);
				virtual bool parseResponse(const tinyxml2::XMLElement*xml);

				std::string filename() const;

			private:
				std::string _filename;

				virtual void buildRequest();
				virtual void buildResponse();
		};

		class MFileContentCommand : public MCommand
		{
			public:
				MFileContentCommand(const std::string& command, Printers::TijPrinter &printer, const std::string &filename = "", bool raw = false, const std::vector<uint8_t>& content = std::vector<uint8_t>());
				virtual ~MFileContentCommand();

				std::string filename() const;
				std::vector<uint8_t> content() const;
				void setContent(const std::vector<uint8_t>& content);
				void setContent(const std::string& content);

				bool raw() const;

			protected:
				std::string _filename;
				std::vector<uint8_t> _content;
				bool _raw;

				std::string contentToString(const std::vector<uint8_t> content, bool raw) const;
				std::vector<uint8_t> contentFromString(const char* data, bool raw) const;

		};

		class MGetFile : public MFileContentCommand
		{
			public:
				MGetFile(Macsa::Printers::TijPrinter &printer, const std::string &filename = "", bool raw = false);
				virtual bool parseRequest(const tinyxml2::XMLElement* xml);
				virtual bool parseResponse(const tinyxml2::XMLElement*xml);

			private:
				virtual void buildRequest();
				virtual void buildResponse();
		};

		class MSetFile : public MFileContentCommand
		{
			public:
				MSetFile(Macsa::Printers::TijPrinter &printer, const std::string &filename = "", const std::vector<uint8_t>& content = std::vector<uint8_t>(), bool raw = false);
				virtual bool parseRequest(const tinyxml2::XMLElement* xml);
				virtual bool parseResponse(const tinyxml2::XMLElement*xml);

			private:
				virtual void buildRequest();
				virtual void buildResponse();
		};
	}
}
#endif // MFILESCOMMANDS_H
