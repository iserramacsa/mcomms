#include "printer/files.h"
#include <algorithm> // Update methods
#include <typeinfo>
#include <iostream>
#include <string.h> // strlen

#include <exception>

using namespace Macsa;
using namespace Macsa::Printers;
using namespace std;

#define DRIVE_STRING_DELIMITER	"//"
#define SLASH_CHAR	'/'


//#define TRACE	std::cout << __FILE__ <<  ":" << __LINE__ << "::" << __FUNCTION__ << std::endl;
#if __cplusplus >= 201103L
	using citDrive  = std::map<std::string, Drive*>::const_iterator;
	using citDirectory = std::map<std::string, Directory*>::const_iterator;
	using citFile	= std::map<std::string, File*>::const_iterator;
#else
	typedef std::map<std::string, Drive*>::const_iterator citDrive;
	typedef std::map<std::string, Directory*>::const_iterator citDirectory;
	typedef std::map<std::string, File*>::const_iterator citFile;
#endif


//====== FileSystemAbstract definitions ======//
FileSystemAbstract::FileSystemAbstract()
{}

FileSystemAbstract::FileSystemAbstract(const FileSystemAbstract &other)
{
	*this = other;
}

FileSystemAbstract::~FileSystemAbstract()
{}

template<class T>
T *FileSystemAbstract::getItem(const string &name, const std::map<string, T*> &map) const
{
	try {
		if (map.size() && map.find(name) != map.end()){
			return map.at(name);
		}
	} catch (std::exception e) {
		std::cerr << "EXCEPTION!! " << __FILE__ <<  ":" << __LINE__ << "::" << __FUNCTION__ << "  reason:" << e.what();
	}

	return nullptr;
}

template<class T>
std::vector<string> FileSystemAbstract::getItemsList(const std::map<string, T *> &map) const
{
	std::vector<string> list;
	list.clear();
#if __cplusplus >= 201103L
	for (auto& item : map) {
		list.push_back(item.first);
	}
#else
	for (typename std::map<string, T *>::const_iterator it = map.begin(); it != map.end(); it++) {
		list.push_back((*it).first);
	}
#endif
	return list;
}

template<class P, class T>
T *FileSystemAbstract::insertNewItem(const string &name, std::map<string, T*> &map, P *parent)
{
	T* item = nullptr;
	if (getItem(name, map) == nullptr) {
		item = new T(name, parent);
		map.insert(pair<string, T*>(name, item));
	}
	return item;
}

template<class T>
T* FileSystemAbstract::removeItem(const std::string& name, std::map<string, T*>& map)
{
	T* item = getItem(name, map);
	if (item != nullptr) {
		map.erase(name);
	}
	return item;
}

template<class T>
bool FileSystemAbstract::deleteItem(const std::string& name, std::map<string, T*>& map)
{
	bool success = false;
	T* item =  removeItem(name, map);
	if(item != nullptr) {
		delete item;
		success = true;
	}
	return success;
}

template<class T>
bool FileSystemAbstract::clear(std::map<string, T*> &map)
{

	while (map.size()){
		deleteItem(map.begin()->first, map);
	}
	return (map.size() == 0);
}

template<class T>
bool FileSystemAbstract::compare(const std::map<string, T *> &map1, const std::map<string, T*> &map2) const
{
	bool equal = false;

	if (map1.size() == map2.size()) {
#if __cplusplus >= 201103L
		for (auto& item : map1) {
#else
		for (typename std::map<string, T *>::const_iterator it = map1.begin(); it != map1.end(); it++) {
			typename std::map<string, T *>::const_reference item = *it;
#endif
			equal = (*(map2.at(item.first)) == *(item.second));
			if(!equal) {
				break;
			}
		}
	}

	return equal;
}


//====== PrinterFiles definitions ======//
PrinterFiles::PrinterFiles()
{
	clear();
	_filesManager = nullptr;
}

PrinterFiles::PrinterFiles(const PrinterFiles &other)
{
	clear();
	_filesManager = nullptr;
	copy(other);
}

PrinterFiles::~PrinterFiles()
{
	clear();
}

std::vector<string> PrinterFiles::getDrives() const
{
	return getItemsList(_drives);
}

std::vector<string> PrinterFiles::getDirectories(const string &drive) const
{
	Drive* d = getItem(drive, _drives);
	if (d != nullptr){
		return d->getDirectoriesList();
	}
	return std::vector<string>();
}

std::vector<string> PrinterFiles::getFiles(const string &drive, const string &directory) const
{
	const Directory* f = getDirectory(drive, directory);
	if (f != nullptr){
		return f->getFilesList();
	}
	return std::vector<string>();
}

std::vector<string> PrinterFiles::getAllFiles(const string &filter) const
{
	vector<string> exts;

	size_t comma = 0;
	while (comma != filter.npos) {
		const size_t lastComma = comma;
		comma = filter.find_first_of(EXTENSIONS_SEPARATOR, comma);
		exts.push_back(filter.substr(lastComma, (comma - lastComma)));
		if (comma != filter.npos) {
			comma++;
		}
	}

	std::vector<string> files;
#if __cplusplus >= 201103L
	for (auto& drive : _drives) {
		for (auto& file : drive.second->getFiles()) {
#else
	for (std::map<std::string, Drive*>::const_iterator d = _drives.begin(); d != _drives.end(); d++) {
		std::vector<const File*> driveFiles = d->second->getFiles();
		for (std::vector<const File*>::const_iterator f = driveFiles.begin(); f != driveFiles.end(); f++) {
			const File* file = *f;
#endif
			if (filter.empty() || filter.compare(ALL_FILES_FILTER) == 0) {
				files.push_back(file->pwd());
			}
			else {
				string extension = file->extension();
				extension = "*" + extension;
				if (std::find(exts.begin(), exts.end(), extension) != exts.end()) {
					files.push_back(file->pwd());
				}
			}
		}
	}
	return files;
}

const Drive *PrinterFiles::getDrive(const string &drive) const
{
	return getItem(drive, _drives);
}

Drive *PrinterFiles::getDrive(const string &drive)
{
	return getItem(drive, _drives);
}

const Directory *PrinterFiles::getDirectory(const string &drive, const string &directory) const
{
	const Drive * d = getItem(drive, _drives);
	if (d != nullptr){
		return d->getDirectory(directory);
	}
	return nullptr;
}

const File *PrinterFiles::getFile(const string &drive, const string &directory, const string &filename) const
{
	const Directory * f = getDirectory(drive, directory);
	if (f != nullptr){
		return f->getFile(filename);
	}
	return nullptr;
}

const File *PrinterFiles::getFile(const string &filepath) const
{
	string drive = "//";
	string directory = "";
	string filename = "";
	splitFilepath(filepath, drive, directory, filename);
	return getFile(drive, directory, filename);
}

bool PrinterFiles::driveExist(const string &drive) const
{
	return (getItem(drive, _drives) != nullptr);
}

bool PrinterFiles::directoryExist(const string &drive, const string &directory) const
{
	return ((getDirectory(drive, directory)) != nullptr);
}

bool PrinterFiles::fileExist(const string &drive, const string &directory, const string &filename) const
{
	return (getFile(drive, directory, filename) != nullptr);
}

bool PrinterFiles::clear()
{
	return FileSystemAbstract::clear(_drives);
}

bool PrinterFiles::addNewDrive(const string &drive)
{
	return (insertNewItem(drive, _drives, this) != nullptr);
}

bool PrinterFiles::addNewDirectory(const string &drive, const string &directory)
{
	bool added = false;
	Drive* d = getItem(drive, _drives);
	if (d != nullptr) {
		added = d->addEmptyDirectory(directory);
	}
	return added;
}

bool PrinterFiles::addNewFile(const std::string& drive, const std::string& directory, const std::string& filename)
{
	bool added = false;
	Drive * d = getItem(drive, _drives);
	if (d != nullptr){
		added = d->addNewFile(directory, filename);
	}
	return added;
}

bool PrinterFiles::addFile(const string &drive, const string &directory, const string &filename, const std::vector<uint8_t> &data)
{
	bool added = false;
	Drive * d = getItem(drive, _drives);
	if (d != nullptr){
		added = d->addFile(directory, filename, data);
	}
	return added;
}

bool PrinterFiles::setFile(const string &drive, const string &directory, const string &filename, const std::vector<uint8_t> &data)
{
	bool success = false;
	Drive * d = getItem(drive, _drives);
	if (d != nullptr){
		success = d->setFileData(directory, filename, data);
	}
	return success;
}

bool PrinterFiles::setFile(const string &filepath, const std::vector<uint8_t> &data)
{
	string drive = "", directory = "", filename = "";
	splitFilepath(filepath, drive, directory, filename);
	return setFile(drive, directory, filename, data);
}

bool PrinterFiles::clearDrive(const string &drive)
{
	bool success = false;
	Drive * d = getItem(drive, _drives);
	if (d != nullptr){
		success = d->clear();
	}

	return success;
}

bool PrinterFiles::clearDirectory(const string &drive, const string &directory)
{
	bool success = false;
	Drive * d = getItem(drive, _drives);
	if (d != nullptr){
		success = d->clearDirectory(directory);
	}

	return success;
}

bool PrinterFiles::deleteDrive(const string &drive)
{
	return deleteItem(drive, _drives);
}

bool PrinterFiles::deleteDirectory(const string &drive, const string &directory)
{
	bool success = false;
	Drive * d = getItem(drive, _drives);
	if (d != nullptr){
		success =  d->deleteDirectory(directory);
	}
	return success;
}

bool PrinterFiles::deleteFile(const string &drive, const string &directory, const string &filename)
{
	bool success = false;
	Drive * d = getItem(drive, _drives);
	if (d != nullptr){
		success =  d->deleteFile(directory, filename);
	}
	return success;
}

Drive *PrinterFiles::removeDrive(const string &drive)
{
	return removeItem(drive, _drives);
}

Directory* PrinterFiles::removeDirectory(const string &drive, const string &directory)
{
	Drive * d = getItem(drive, _drives);
	Directory* f = nullptr;
	if (d != nullptr){
		f = d->removeDirectory(directory);
	}
	return f;
}

File *PrinterFiles::removeFile(const string &drive, const string &directory, const string &filename)
{
	Drive * d = getItem(drive, _drives);
	File* f = nullptr;
	if (d != nullptr){
		f = d->removeFile(directory, filename);
	}
	return f;
}

void PrinterFiles::splitFilepath(const string &pwd, string &drive, vector<string> &directories, string &file) const
{
	drive.clear();
	directories.clear();
	file.clear();
	string path;

	size_t slash = pwd.find(DRIVE_STRING_DELIMITER);
	path = pwd;
	if(slash != pwd.npos) {
		drive = pwd.substr(0, slash + strlen(DRIVE_STRING_DELIMITER));
		path = pwd.substr(slash + strlen(DRIVE_STRING_DELIMITER));
	}

	while ((slash = path.find_last_of(SLASH_CHAR)) != file.npos) {
		directories.push_back(path.substr(0, slash));
		path = path.substr(slash + 1);
	}
	file = path;
}

void PrinterFiles::splitFilepath(const string &pwd, string &drive, string &directory, string &file) const
{
	vector<string> directories;
	splitFilepath(pwd, drive, directories, file);
	directory = "";
	for (uint i = 0; i < directories.size(); i++) {
		if (i) {
			directory += "/";
		}
		directory += directories.at(i);
	}

}

bool PrinterFiles::equal(const FileSystemAbstract &other) const
{
	bool equal = false;
	try {
		const PrinterFiles& fs = dynamic_cast<const PrinterFiles&>(other);
		equal = compare(_drives, fs._drives);
	}
	catch(std::bad_cast exp) {
		std::cout << __func__ <<"Caught bad cast" << std::endl;
	}

	return equal;
}

void PrinterFiles::copy(const PrinterFiles &other)
{
	clear();
	for (std::map<std::string, Drive*>::const_iterator drive = other._drives.begin(); drive != other._drives.end(); drive++)
	{
		if (drive->second){
			Drive* d = new Drive(drive->first, this);
			(*d) = (*(drive->second));
			_drives.insert(pair<string, Drive*>(drive->first, d));
		}
	}
}

IFilesManager *PrinterFiles::filesManager() const
{
	return _filesManager;
}

void PrinterFiles::setFilesManager(IFilesManager *filesManager)
{
	_filesManager = filesManager;
}

bool PrinterFiles::renameDirectory(const string &drive, const string &olddirectory, const string &newDirectory)
{
	bool success = false;
	Drive * d = getItem(drive, _drives);
	if (d != nullptr){
		success = d->renameDirectory(olddirectory, newDirectory);
	}
	return success;
}

bool PrinterFiles::renameFile(const string &drive, const string &directory, const string &oldName, const string &newName)
{
	bool success = false;
	Drive * d = getItem(drive, _drives);
	if (d != nullptr){
		success = d->renameFile(directory, oldName, newName);
	}
	return success;
}

bool PrinterFiles::moveFile(const string &oldDrive, const string &oldDirectory, const string &oldName, const string &newDrive, const string &newDirectory, const string &newName)
{
	bool success = false;
	Drive * dOld = getItem(oldDrive, _drives);
	Drive * dNew = getItem(newDrive, _drives);

	bool validParams = (dOld != nullptr && dOld->getFile(oldDirectory, oldName) != nullptr &&
						dNew != nullptr && dNew->getDirectory(newDirectory) != nullptr &&
						dNew->getFile(newDirectory, newName) == nullptr);

	if (validParams)
	{
		File* file = dOld->removeFile(oldDirectory, oldName);
		if (oldName.compare(newName) != 0) {
			file->setName(newName);
		}
		if (dNew->addFile(newDirectory, file)){
			success = true;
		}
		else {
			file->setName(oldName);
			dOld->addFile(oldDirectory, file);
		}
	}
	return success;
}

void PrinterFiles::updateDrives(const std::vector<std::string> drives)
{
	try {
		for (map<string, Drive*>::iterator d = _drives.begin(); d != _drives.end(); d++)
		{
			bool found = false;
#if __cplusplus >= 201103L
			for (auto& drive : drives) {
#else
			for (std::vector<std::string>::const_iterator it = drives.begin(); it != drives.end(); it++) {
				std::string drive = *it;
#endif
				if (drive.compare(d->second->name()) == 0) {
					found = true;
					break;
				}
			}
			if (!found) {
				d = _drives.erase(d);
			}
		}
	} catch (std::exception e) {
		std::cerr << "exception catched:" << e.what() << std::endl;
	}
}

void PrinterFiles::clearFilesOfType(const string &drive, const string &extension)
{
	Drive* d = getItem(drive, _drives);
	if (d) {
#if __cplusplus >= 201103L
		for (auto& file : d->getFiles()) {
#else
		std::vector<const File *>files = d->getFiles();
		for (std::vector<const File *>::const_iterator it = files.begin(); it != files.end(); it++) {
			const File * file = *it;
#endif
			if (extension.compare(file->extension()) == 0) {
				d->deleteFile(file->directory(), file->name());
			}
		}
	}
}

void PrinterFiles::clearFilesOfType(const string &drive, const std::vector<string> &extensions)
{
	Drive* d = getItem(drive, _drives);
	if (d) {
		for (auto& file : d->getFiles()) {
			if (std::find(extensions.begin(), extensions.end(), file->extension()) != extensions.end()) {
				d->deleteFile(file->directory(), file->name());
			}
		}
	}
}

//====== Drive definitions ======//
Drive::Drive(const string &name, const PrinterFiles *parent) :
	_name(name)
{
	_parent = parent;
	_directories.clear();
}

Drive::~Drive()
{
	clear();
}

std::string Drive::name() const
{
	return _name;
}

std::string Drive::description() const
{
	return _description;
}

void Drive::setDescription(const std::string &description)
{
	_description = description;
}

std::vector<string> Drive::getDirectoriesList() const
{
	return getItemsList(_directories);
}

std::vector<string> Drive::getFilesList(const string &directory) const
{
	Directory* f = getItem(directory, _directories);
	if (f != nullptr){
		return f->getFilesList();
	}

	return std::vector<string>();
}

std::vector<const File *> Drive::getFiles() const
{
	//TODO: add C++98 compatibility
	std::vector<const File *>files;
	for (auto& directory : _directories) {
		std::vector<const File *> currentDirectory = directory.second->getFiles();
		files.insert(files.end(),
					 std::make_move_iterator(currentDirectory.begin()),
					 std::make_move_iterator(currentDirectory.end()));
	}
	return files;
}

const Directory *Drive::getDirectory(const string &directory) const
{
	return getItem(directory, _directories);
}

Directory *Drive::getDirectory(const string &directory)
{
	return getItem(directory, _directories);
}

const File *Drive::getFile(const string &directory, const string &file) const
{
	const File * f = nullptr;
	Directory * pDirectory = getItem(directory, _directories);
	if (pDirectory != nullptr){
		f = pDirectory->getFile(file);
	}

	return f;
}

const File *Drive::getFile(const string &pwd) const
{
	const File * f = nullptr;
	if (_parent) {
		std::string drive, file;
		std::vector<std::string> directories;
		_parent->splitFilepath(pwd, drive, directories, file);
		if(directories.size()){
			Directory * pDirectory = getItem(directories.at(0), _directories);
			for (unsigned int d = 1; d < directories.size(); d++) {
				pDirectory = pDirectory->getSubdirectory(directories.at(d));
				if (pDirectory == nullptr) {
					break;
				}
			}
			if (pDirectory != nullptr) {
				f = pDirectory->getFile(file);
			}
		}
	}
	return f;
}

bool Drive::clear()
{
	return FileSystemAbstract::clear(_directories);
}

bool Drive::clearDirectory(const string &directory)
{
	bool success = false;
	Directory * f = getItem(directory, _directories);
	if (f != nullptr){
		success = f->clear();
	}

	return success;
}

bool Drive::addEmptyDirectory(const string &directory)
{
	return (insertNewItem(directory, _directories, this) != nullptr);
}

bool Drive::addNewFile(const string &directory, const string &filename)
{
	Directory* f = getItem(directory, _directories);
	if (f != nullptr) {
		return f->addEmptyFile(filename);
	}
	return false;
}

bool Drive::addFile(const string &directory, const string &filename, const std::vector<uint8_t> &data)
{
	Directory* f = getItem(directory, _directories);
	if (f != nullptr) {
		return f->addFile(filename, data);
	}
	return false;
}

bool Drive::addFile(const string &directory, File *file)
{
	Directory* f = getItem(directory, _directories);
	if (f != nullptr) {
		return f->addFile(file);
	}
	return false;
}

bool Drive::setFileData(const string &directory, const string &filename, const std::vector<uint8_t> &data)
{
	Directory* f = getItem(directory, _directories);
	if (f != nullptr) {
		return f->setFileData(filename, data);
	}
	return false;
}

bool Drive::renameDirectory(const string &olddirectory, const string &newDirectory)
{
	bool success = false;
	Directory* f = removeItem(olddirectory, _directories);
	if (f != nullptr) {
		f->setName(newDirectory);
		_directories.insert(pair<string, Directory*>(newDirectory, f));
		success = true;
	}
	return success;
}

Directory *Drive::removeDirectory(const string &directory)
{
	return removeItem(directory, _directories);
}

File *Drive::removeFile(const string &directory, const string &filename)
{
	Directory* f = getItem(directory, _directories);
	if (f != nullptr) {
		return f->removeFile(filename);
	}
	return nullptr;
}

bool Drive::equal(const FileSystemAbstract &other) const
{
    bool equal = false;
    try {
        const Drive& drive = dynamic_cast<const Drive&>(other);
        
        equal = (_name == drive._name);
		equal &= compare(_directories, drive._directories);
	}
	catch(std::bad_cast exp) {
		std::cout << __func__ <<"Caught bad cast" << std::endl;
	}

	return equal;
}

void Drive::copy(const Drive &other)
{
	clear();
	for (std::map<std::string, Directory*>::const_iterator directory = other._directories.begin(); directory != other._directories.end(); directory++)
	{
		if (directory->second){
			Directory* f = new Directory(directory->first, this);
			(*f) = (*(directory->second));
			_directories.insert(pair<string, Directory*>(directory->first, f));
		}
	}
}

bool Drive::renameFile(const string &directory, const string &oldName, const string &newName)
{
	Directory* f = getItem(directory, _directories);
	if (f != nullptr) {
		return f->renameFile(oldName, newName);
	}
	return false;
}

bool Drive::moveFile(const string &oldDirectory, const string &oldName, const string & newDirectory, const string &newName)
{
	bool success = false;
	Directory* fOld = getItem(oldDirectory, _directories);
	Directory* fNew = getItem(newDirectory, _directories);
	if (fOld != nullptr && fNew != nullptr && fNew->getFile(newName) == nullptr)
	{
		File* file = fOld->removeFile(oldName);
		if (oldName.compare(newName) != 0) {
			file->setName(newName);
		}

		if (fNew->addFile(file)) {
			success = true;
		}
		else {
			file->setName(oldName);
			fOld->addFile(file);
		}
	}
	return success;
}

bool Drive::moveFile(const string &oldDirectory, const string &newDirectory, const string &filename)
{
	return moveFile(oldDirectory, filename, newDirectory, filename);
}

bool Drive::deleteDirectory(const string &directory)
{
	return deleteItem(directory, _directories);
}

bool Drive::deleteFile(const string &directory, const string &file)
{
	bool success = false;
	Directory* f = getItem(directory, _directories);
	if (f != nullptr) {
		success = f->deleteFile(file);
	}
	return success;
}

//====== Directory definitions ======//
Directory::Directory(const string &name, const Drive *parent) :
	_parent(parent),
	_parentDirectory(nullptr),
	_name(name)
{
	_subdirectories.clear();
	_files.clear();
}

Directory::Directory(const string &name, const Directory *parent) :
	_parent(nullptr),
	_parentDirectory(parent),
	_name(name)
{
	_files.clear();
}

Directory::~Directory()
{
	clear();
}

string Directory::pwd() const
{
	string pwd = _name;
	if (_parent) {
		pwd = _parent->name() + "/" + pwd;
	}
	else if (_parentDirectory)  {
		pwd = _parentDirectory->name() + "/" + pwd;
	}
	return pwd;
}

string Directory::name() const
{
	return _name;
}

std::vector<string> Directory::getFilesList() const
{
	return getItemsList(_files);
}

const Directory *Directory::getSubdirectory(const string &name) const
{
	return getItem(name, _subdirectories);
}

Directory *Directory::getSubdirectory(const string &name)
{
	return getItem(name, _subdirectories);
}

bool Directory::addSubdirectory(const string &name)
{
	return (insertNewItem(name, _subdirectories, this) != nullptr);
}

void Directory::setName(const std::string &name)
{
	_name = name;
}

const File *Directory::getFile(const string &filename) const
{
	return getItem(filename, _files);
}

std::vector<const File *> Directory::getFiles() const
{
	std::vector<const File *> files;
	files.clear();
	for (auto& file : _files) {
		files.push_back(file.second);
	}
	return files;
}

std::vector<uint8_t> Directory::getFileContent(const string &filename) const
{
	const File * f = getFile(filename);
	if (f != nullptr) {
		return f->data();
	}
	return std::vector<uint8_t>();
}

bool Directory::clear()
{
	if (FileSystemAbstract::clear(_subdirectories)) {
		return FileSystemAbstract::clear(_files);
	}
	else {
		return false;
	}
}

bool Directory::addEmptyFile(const string &file)
{
	return (insertNewItem(file, _files, this) != nullptr);
}

bool Directory::addFile(const string &file, const std::vector<uint8_t> &data)
{
	bool success = false;
	File* f = insertNewItem(file, _files, this);
	if (f != nullptr) {
		success = f->setContent(data);
	}

	return success;
}

bool Directory::addFile(File *file)
{
	bool success = false;
	if (getItem(file->name(), _files) == nullptr) {
		_files.insert(pair<string, File*>(file->name(), file));
		success = true;
	}
	return success;
}

bool Directory::setFileData(const string &file, const std::vector<uint8_t> &data)
{
	bool success = false;
	File* f = getItem(file, _files);
	if (f != nullptr) {
		success = f->setContent(data);
	}
	return success;
}

File *Directory::removeFile(const string &file)
{
	return removeItem(file, _files);
}

bool Directory::deleteFile(const string &file)
{
	return deleteItem(file, _files);
}

bool Directory::renameFile(const string &oldName, const string &newName)
{
	bool success = false;
	if  (oldName.compare(newName) != 0) {
		File* f = getItem(oldName, _files);
		if (f != nullptr && getItem(newName, _files) == nullptr) {
			_files.insert(pair<string, File*>(newName, f));
			_files.erase(oldName);
			success = true;
		}
	}

	return success;
}

bool Directory::equal(const FileSystemAbstract &other) const
{
	bool equal = false;

	try
	{
		const Directory& directory = dynamic_cast<const Directory&>(other);
		if (_parent != nullptr && directory._parent != nullptr){
			equal =  (_parent->name()  == directory._parent->name());
		}
		else if (_parentDirectory != nullptr && directory._parentDirectory != nullptr) {
			equal =  (_parentDirectory->name()  == directory._parentDirectory->name());
		}
		if(equal){
			equal &= (_name == directory._name);
			equal &= compare(_files, directory._files);
		}

	}
	catch(std::bad_cast exp)
	{
		std::cout << __func__ <<"Caught bad cast" << std::endl;
	}

	return equal;

}

void Directory::copy(const Directory &other)
{
	clear();
	_name = other._name;
	for (std::map<std::string, File*>::const_iterator file = other._files.begin(); file != other._files.end(); file++)
	{
		File* f = new File(file->first, this);
		if (file->second){
			(*f) = (*(file->second));
		}
		if (!addFile(f)) {
			delete f;
		}
	}
}

//====== Files definitions ======//
File::File(const string &filename, const Directory *parent) :
	_parent(parent),
	_name(filename)
{
	_data = nullptr;
}

File::~File()
{
	if(_data != nullptr) {
		_data->clear();
		delete _data;
	}
}

string File::pwd() const
{
	string pwd = _name;

	if (_parent) {
		pwd = _parent->pwd() + "/" + pwd;
	}

	return pwd;
}

string File::directory() const
{
	if (_parent) {
		return  _parent->name();
	}
	return "";
}

std::string File::name() const
{
	return _name;
}

void File::setName(const std::string &name)
{
	_name = name;
}

bool File::empty() const
{
	return (size() == 0);
}

unsigned int File::size() const
{
	unsigned int size = 0;
	if(_data != nullptr) {
		size = static_cast<unsigned int>(_data->size());
	}
	return size;
}

std::string File::extension() const
{
	string ext = "";
	if (_name.length()){
		size_t dot = _name.find_last_of(".");
		if (dot != _name.npos){
			ext = _name.substr(dot);
		}
	}
	return ext;
}

std::vector<uint8_t> File::data() const
{
	std::vector<uint8_t> data;
	if (_data != nullptr) {
		data = *_data;
	}
	return data;
}

bool File::setContent(const std::vector<uint8_t> &data)
{
	bool success = false;
	if (_data == nullptr) {
		_data = new vector<uint8_t>(data);
		success = (_data != nullptr && (_data->size() == data.size()));
	}
	else {
		_data->clear();
		*_data = data;
		success = (_data->size() == data.size());
	}

	return success;
}

bool File::checkContent(const std::vector<uint8_t> *data) const
{
	bool equal = false;
	if (_data != nullptr && data != nullptr) {
		if (_data->size() == data->size()) {
			equal = ((*_data) == (*data));
		}
	}
	else {
		equal = (_data == nullptr && data == nullptr);
	}

	return equal;
}

bool File::equal(const File &other) const
{
	bool equal = (_parent != nullptr && other._parent != nullptr);

	if(!equal) {
		equal = (_parent == nullptr && other._parent == nullptr);
	}
	else {
		equal = _parent->name().compare(other._parent->name());
	}

	if (equal){
		equal = (_name.compare(other._name) == 0);
		equal &= checkContent(other._data);
	}

	return equal;
}

void File::copy(const File &other)
{
	_name = other.name();
	if (other._data != nullptr){
		setContent(*(other._data));
	}
}

