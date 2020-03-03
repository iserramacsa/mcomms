#ifndef PRINTER_FILES_H
#define PRINTER_FILES_H

#include <string>
#include <vector>
#include <map>

#include "ifilesmanager.h"

#define MESSAGES_FOLDER	"messages"
#define MESSAGES_FILTER	".nisx"

#define FONTS_FOLDER	"fonts"
#define FONTS_FILTER	".ttf"

#define IMAGES_FOLDER		"images"
#define IMAGES_FILTER_PNG	".png"
#define IMAGES_FILTER_JPG	".jpg"
#define IMAGES_FILTER_JPEG	".jpeg"
#define IMAGES_FILTER_BMP	".bmp"
#define IMAGES_FILTER		".png,.jpg,.jpeg,s.bmp"

#define ALL_FILES_FILTER	"*.*"
#define EXTENSIONS_SEPARATOR ","


namespace Macsa {
	namespace Printers {
		class Drive;
		class Folder;
		class File;

		class FileSystemAbstract
		{
			public:
				FileSystemAbstract();
				FileSystemAbstract(const FileSystemAbstract& other);
				virtual ~FileSystemAbstract();

				virtual bool operator == (const FileSystemAbstract& other) const {return equal(other);}
				virtual bool operator != (const FileSystemAbstract& other) const {return !equal(other);}

			protected:

				template<class T>
				T* getItem(const std::string& name, const std::map<std::string, T*>& map) const;

				template<class T>
				std::vector<std::string> getItemsList(const std::map<std::string, T*>& map) const;

				template<class P, class T>
				T* insertNewItem(const std::string& name, std::map<std::string, T*>& map, P* parent);

				template<class T>
				T* removeItem(const std::string& name, std::map<std::string, T*>& map);

				template<class T>
				bool deleteItem(const std::string& name, std::map<std::string, T*>& map);

				template<class T>
				bool clear(std::map<std::string, T*>& map);

				template<class T>
				bool compare(const std::map<std::string, T*>& map1, const std::map<std::string, T*>& map2) const;

				virtual bool equal (const FileSystemAbstract& other) const = 0;
		};

		class PrinterFiles : public FileSystemAbstract
		{
			public:
				PrinterFiles();
				PrinterFiles(const PrinterFiles& other);
				virtual ~PrinterFiles() override;

				std::vector<std::string> getDrives() const;
				std::vector<std::string> getFolders(const std::string& drive) const;
				std::vector<std::string> getFiles(const std::string& drive, const std::string& folder) const;
				std::vector<std::string> getAllFiles(const std::string& filter) const;

				const Drive* getDrive(const std::string& drive) const;
//				const Folder* getFolder(const std::string& path) const;
				const Folder* getFolder(const std::string& drive, const std::string& folder) const;
				const File* getFile(const std::string& drive, const std::string& folder, const std::string& filename) const;
				const File* getFile(const std::string& filepath) const;

				bool driveExist(const std::string& drive) const;
				bool folderExist(const std::string& drive, const std::string& folder) const;
				bool fileExist(const std::string& drive, const std::string& folder, const std::string& filename) const;

				bool clear();
				bool addNewDrive(const std::string& drive);
				bool addNewFolder(const std::string& drive, const std::string& folder);
				bool addNewFile(const std::string& drive, const std::string& folder, const std::string& filename);
				bool addFile(const std::string& drive, const std::string& folder, const std::string& filename, const std::vector<uint8_t>& data);
				bool setFile(const std::string& drive, const std::string& folder, const std::string& filename, const std::vector<uint8_t>& data);
				bool setFile(const std::string& filepath, const std::vector<uint8_t>& data);
				bool clearDrive(const std::string& drive);
				bool clearFolder(const std::string& drive, const std::string& folder);
				bool deleteDrive(const std::string& drive);
				bool deleteFolder(const std::string& drive, const std::string& folder);
				bool deleteFile(const std::string& drive, const std::string& folder, const std::string& filename);
				bool renameFolder(const std::string& drive, const std::string& oldfolder, const std::string& newFolder);
				bool renameFile(const std::string& drive, const std::string& folder, const std::string& oldName, const std::string& newName);
				bool moveFile(const std::string &oldDrive, const std::string& oldFolder, const std::string& oldName,
							  const std::string &newDrive, const std::string& newFolder, const std::string& newName);

				void updateDrives(const std::vector<std::string> drives);
				void clearFilesOfType(const std::string& drive, const std::string& extension);
				void clearFilesOfType(const std::string& drive, const std::vector<std::string>& extensions);

				 /* Full transfer methods*/
				Drive*	removeDrive(const std::string& drive);
				Folder* removeFolder(const std::string &drive, const std::string &folder);/*Full transfer*/
				File*	removeFile(const std::string &drive, const std::string& folder, const std::string& filename);/*Full transfer*/


				void splitFilepath(const std::string &pwd, std::string &drive, std::vector<std::string> &folders, std::string &file) const;
				void splitFilepath(const std::string &pwd, std::string &drive, std::string &folder, std::string &file) const;

				IFilesManager *filesManager() const;
				void setFilesManager(IFilesManager *filesManager);

				virtual void operator = (const PrinterFiles& other){copy(other);}

			private:
				std::map<std::string, Drive*> _drives;
				IFilesManager*	_filesManager;

				virtual bool equal (const FileSystemAbstract& other) const override;
				virtual void copy (const PrinterFiles& other);
		};

		class Drive : public FileSystemAbstract
		{
			public:
				Drive(const std::string& name, const PrinterFiles* parent);
				virtual ~Drive() override;

				std::string name() const;

				std::vector<std::string> getFoldersList() const;
				std::vector<std::string> getFilesList(const std::string& folder) const;
				std::vector<const File*> getFiles() const;

				const Folder* getFolder(const std::string& folder) const;
				const File* getFile(const std::string& folder, const std::string& file) const;

				bool clear();
				bool clearFolder(const std::string& folder);
				bool addEmptyFolder(const std::string& folder);
				bool addNewFile(const std::string& folder, const std::string& filename);
				bool addFile(const std::string& folder, const std::string& filename, const std::vector<uint8_t>& data);
				bool addFile(const std::string& folder, File* file);
				bool setFileData(const std::string& folder, const std::string& filename, const std::vector<uint8_t>& data);
				bool renameFolder(const std::string& oldfolder, const std::string& newFolder);
				bool renameFile(const std::string& folder, const std::string& oldName, const std::string& newName);
				bool moveFile(const std::string& oldFolder, const std::string& oldName, const std::string& newFolder, const std::string& newName);
				bool moveFile(const std::string& oldFolder, const std::string& newFolder, const std::string& filename);
				bool deleteFolder(const std::string& folder);
				bool deleteFile(const std::string& folder, const std::string& file);

				Folder* removeFolder(const std::string& folder);
				File* removeFile(const std::string& folder, const std::string& filename);

				virtual void operator = (const Drive& other){return copy(other);}

			private:
				const std::string _name;
				const PrinterFiles* _parent;
				std::map<std::string, Folder*> _folders;

				virtual bool equal (const FileSystemAbstract& other) const override;
				virtual void copy (const Drive& other);

		};

		class Folder : public FileSystemAbstract
		{
			public:
				Folder(const std::string& name, const Drive* parent);
				virtual ~Folder() override;

				std::string pwd() const;
				std::string name() const;
				std::vector<std::string> getFilesList() const;

				const File* getFile(const std::string& filename) const;
				std::vector<const File*> getFiles() const;
				std::vector<uint8_t> getFileContent(const std::string& filename) const;


				void setName(const std::string &name);
				bool clear();
				bool addEmptyFile(const std::string& file);
				bool addFile(const std::string& file, const std::vector<uint8_t>& data);
				bool addFile(File *file);
				bool setFileData(const std::string& file, const std::vector<uint8_t>& data);
				File* removeFile(const std::string& file);
				bool deleteFile(const std::string& file);
				bool renameFile(const std::string& oldName, const std::string& newName);

				virtual void operator = (const Folder& other){return copy(other);}

			private:
				const Drive* _parent;
				std::string _name;
				std::map<std::string, File*> _files;

				virtual bool equal (const FileSystemAbstract& other) const override;
				virtual void copy (const Folder& other);
		};

		class File {
			public:
				File(const std::string& filename, const Folder* parent);
				virtual ~File();

				std::string pwd() const;
				std::string folder() const;
				std::string name() const;
				unsigned int size() const;
				std::string extension() const;
				std::vector<uint8_t> data() const;
				bool empty() const;

				void setName(const std::string &name);
				bool setContent(const std::vector<uint8_t>& data);
				bool checkContent(const std::vector<uint8_t>* data) const;

				virtual bool operator == (const File& other) const {return equal(other);}
				virtual bool operator != (const File& other) const {return !equal(other);}
				virtual void operator = (const File& other) {return copy(other);}

			private:
				const Folder* _parent;
				std::string _name;
				std::vector<uint8_t>* _data;

				bool equal (const File& other) const;
				void copy (const File& other);
		};
	}
}


#endif //PRINTER_FILES_H
