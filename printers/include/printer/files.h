#ifndef PRINTER_FILES_H
#define PRINTER_FILES_H

#include <string>
#include <vector>
#include <map>

#include "ifilesmanager.h"

#define MESSAGES_DIRECTORY	"messages"
#define MESSAGES_FILTER	".nisx"

#define FONTS_DIRECTORY	"fonts"
#define FONTS_FILTER	".ttf"

#define IMAGES_DIRECTORY		"images"
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
		class Directory;
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
				std::vector<std::string> getDirectories(const std::string& drive) const;
				std::vector<std::string> getFiles(const std::string& drive, const std::string& directory) const;
				std::vector<std::string> getAllFiles(const std::string& filter) const;

				const Drive* getDrive(const std::string& drive) const;
				Drive* getDrive(const std::string& drive);
				const Directory* getDirectory(const std::string& drive, const std::string& directory) const;
				const File* getFile(const std::string& drive, const std::string& directory, const std::string& filename) const;
				const File* getFile(const std::string& filepath) const;

				virtual bool driveExist(const std::string& drive) const;
				virtual bool directoryExist(const std::string& drive, const std::string& directory) const;
				virtual bool fileExist(const std::string& drive, const std::string& directory, const std::string& filename) const;

				virtual bool clear();
				virtual bool addNewDrive(const std::string& drive);
				virtual bool addNewDirectory(const std::string& drive, const std::string& directory);
				virtual bool addNewFile(const std::string& drive, const std::string& directory, const std::string& filename);
				virtual bool addFile(const std::string& drive, const std::string& directory, const std::string& filename, const std::vector<uint8_t>& data);
				virtual bool setFile(const std::string& drive, const std::string& directory, const std::string& filename, const std::vector<uint8_t>& data);
				virtual bool setFile(const std::string& filepath, const std::vector<uint8_t>& data);
				virtual bool clearDrive(const std::string& drive);
				virtual bool clearDirectory(const std::string& drive, const std::string& directory);
				virtual bool deleteDrive(const std::string& drive);
				virtual bool deleteDirectory(const std::string& drive, const std::string& directory);
				virtual bool deleteFile(const std::string& drive, const std::string& directory, const std::string& filename);
				virtual bool renameDirectory(const std::string& drive, const std::string& olddirectory, const std::string& newDirectory);
				virtual bool renameFile(const std::string& drive, const std::string& directory, const std::string& oldName, const std::string& newName);
				virtual bool moveFile(const std::string &oldDrive, const std::string& oldDirectory, const std::string& oldName,
									 const std::string &newDrive, const std::string& newDirectory, const std::string& newName);

				virtual void updateDrives(const std::vector<std::string> drives);
				virtual void clearFilesOfType(const std::string& drive, const std::string& extension);
				virtual void clearFilesOfType(const std::string& drive, const std::vector<std::string>& extensions);

				 /* Full transfer methods*/
				virtual Drive*	removeDrive(const std::string& drive);
				virtual Directory* removeDirectory(const std::string &drive, const std::string &directory);/*Full transfer*/
				virtual File*	removeFile(const std::string &drive, const std::string& directory, const std::string& filename);/*Full transfer*/


				void splitFilepath(const std::string &pwd, std::string &drive, std::vector<std::string> &directories, std::string &file) const;
				void splitFilepath(const std::string &pwd, std::string &drive, std::string &directory, std::string &file) const;

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

				std::string description() const;
				void setDescription(const std::string &description);

				std::vector<std::string> getDirectoriesList() const;
				std::vector<std::string> getFilesList(const std::string& directory) const;
				std::vector<const File*> getFiles() const;

				const Directory* getDirectory(const std::string& directory) const;
				Directory* getDirectory(const std::string& directory);
				const File* getFile(const std::string& directory, const std::string& file) const;
				const File* getFile(const std::string& pwd) const;

				bool clear();
				bool clearDirectory(const std::string& directory);
				bool addEmptyDirectory(const std::string& directory);
				bool addNewFile(const std::string& directory, const std::string& filename);
				bool addFile(const std::string& directory, const std::string& filename, const std::vector<uint8_t>& data);
				bool addFile(const std::string& directory, File* file);
				bool setFileData(const std::string& directory, const std::string& filename, const std::vector<uint8_t>& data);
				bool renameDirectory(const std::string& olddirectory, const std::string& newDirectory);
				bool renameFile(const std::string& directory, const std::string& oldName, const std::string& newName);
				bool moveFile(const std::string& oldDirectory, const std::string& oldName, const std::string& newDirectory, const std::string& newName);
				bool moveFile(const std::string& oldDirectory, const std::string& newDirectory, const std::string& filename);
				bool deleteDirectory(const std::string& directory);
				bool deleteFile(const std::string& directory, const std::string& file);

				Directory* removeDirectory(const std::string& directory);
				File* removeFile(const std::string& directory, const std::string& filename);


				virtual void operator = (const Drive& other){return copy(other);}


			private:
				const std::string _name;
				std::string _description;
				const PrinterFiles* _parent;
				std::map<std::string, Directory*> _directories;

				virtual bool equal (const FileSystemAbstract& other) const override;
				virtual void copy (const Drive& other);

		};

		class Directory : public FileSystemAbstract
		{
			public:
				Directory(const std::string& name, const Drive* parent);
				Directory(const std::string& name, const Directory* parent);
				virtual ~Directory() override;

				std::string pwd() const;
				std::string name() const;
				std::vector<std::string> getFilesList() const;
				std::vector<std::string> getSubdirectoriesList() const;


				const Directory* getSubdirectory(const std::string& name) const;
				Directory* getSubdirectory(const std::string& name);
				bool addSubdirectory(const std::string &name);

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

				virtual void operator = (const Directory& other){return copy(other);}

			private:
				const Drive* _parent;
				const Directory* _parentDirectory;
				std::string _name;
				std::map<std::string, Directory*> _subdirectories;
				std::map<std::string, File*> _files;

				virtual bool equal (const FileSystemAbstract& other) const override;
				virtual void copy (const Directory& other);
		};

		class File {
			public:
				File(const std::string& filename, const Directory* parent);
				virtual ~File();

				std::string pwd() const;
				std::string directory() const;
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
				const Directory* _parent;
				std::string _name;
				std::vector<uint8_t>* _data;

				bool equal (const File& other) const;
				void copy (const File& other);
		};
	}
}


#endif //PRINTER_FILES_H
