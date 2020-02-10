#include "printer/files.h"
#include <algorithm> // Update methods
#include <typeinfo>
#include <iostream>
#include <string.h> // strlen

using namespace Macsa;
using namespace Macsa::Printers;
using namespace std;

#define DRIVE_STRING_DELIMITER	"//"
#define SLASH_CHAR	'/'


#define TRACE	std::cout << __FILE__ <<  ":" << __LINE__ << "::" << __FUNCTION__ << std::endl;
#if __cplusplus >= 201103L
	using citDrive  = std::map<std::string, Drive*>::const_iterator;
	using citFolder = std::map<std::string, Folder*>::const_iterator;
	using citFile	= std::map<std::string, File*>::const_iterator;
#else
	typedef std::map<std::string, Drive*>::const_iterator citDrive;
	typedef std::map<std::string, Folder*>::const_iterator citFolder;
	typedef std::map<std::string, File*>::const_iterator citFile;
#endif


//====== FileSystemAbstract definitions ======//
FileSystemAbstract::FileSystemAbstract()
{TRACE}

FileSystemAbstract::FileSystemAbstract(const FileSystemAbstract &other)
{
	TRACE
	*this = other;
}

FileSystemAbstract::~FileSystemAbstract()
{TRACE}
#include <exception>
template<class T>
T *FileSystemAbstract::getItem(const string &name, const std::map<string, T*> &map) const
{
	TRACE
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
	TRACE
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
	TRACE
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
	TRACE
	T* item = getItem(name, map);
	if (item != nullptr) {
		map.erase(name);
	}
	return item;
}

template<class T>
bool FileSystemAbstract::deleteItem(const std::string& name, std::map<string, T*>& map)
{
	TRACE
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
	TRACE
	while (map.size()){
		deleteItem(map.begin()->first, map);
	}
	return (map.size() == 0);
}

template<class T>
bool FileSystemAbstract::compare(const std::map<string, T *> &map1, const std::map<string, T*> &map2) const
{
	TRACE
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

PrinterFiles::~PrinterFiles()
{
	clear();
}

std::vector<string> PrinterFiles::getDrives() const
{
	return getItemsList(_drives);
}

std::vector<string> PrinterFiles::getFolders(const string &drive) const
{
	Drive* d = getItem(drive, _drives);
	if (d != nullptr){
		return d->getFoldersList();
	}
	return std::vector<string>();
}

std::vector<string> PrinterFiles::getFiles(const string &drive, const string &folder) const
{
	const Folder* f = getFolder(drive, folder);
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

//const Folder *PrinterFiles::getFolder(const string &path) const
//{
//	std::string drive = "//";

//}

const Folder *PrinterFiles::getFolder(const string &drive, const string &folder) const
{
	const Drive * d = getItem(drive, _drives);
	if (d != nullptr){
		return d->getFolder(folder);
	}
	return nullptr;
}

const File *PrinterFiles::getFile(const string &drive, const string &folder, const string &filename) const
{
	const Folder * f = getFolder(drive, folder);
	if (f != nullptr){
		return f->getFile(filename);
	}
	return nullptr;
}

bool PrinterFiles::driveExist(const string &drive) const
{
	return (getItem(drive, _drives) != nullptr);
}

bool PrinterFiles::folderExist(const string &drive, const string &folder) const
{
	return ((getFolder(drive, folder)) != nullptr);
}

bool PrinterFiles::fileExist(const string &drive, const string &folder, const string &filename) const
{
	return (getFile(drive, folder, filename) != nullptr);
}

bool PrinterFiles::clear()
{
	TRACE
	return FileSystemAbstract::clear(_drives);
}

bool PrinterFiles::addNewDrive(const string &drive)
{
	return (insertNewItem(drive, _drives, this) != nullptr);
}

bool PrinterFiles::addNewFolder(const string &drive, const string &folder)
{
	bool added = false;
	Drive* d = getItem(drive, _drives);
	if (d != nullptr) {
		added = d->addEmptyFolder(folder);
	}
	return added;
}

bool PrinterFiles::addNewFile(const std::string& drive, const std::string& folder, const std::string& filename)
{
	bool added = false;
	Drive * d = getItem(drive, _drives);
	if (d != nullptr){
		added = d->addNewFile(folder, filename);
	}
	return added;
}

bool PrinterFiles::addFile(const string &drive, const string &folder, const string &filename, const std::vector<uint8_t> &data)
{
	bool added = false;
	Drive * d = getItem(drive, _drives);
	if (d != nullptr){
		added = d->addFile(folder, filename, data);
	}
	return added;
}

bool PrinterFiles::setFile(const string &drive, const string &folder, const string &filename, const std::vector<uint8_t> &data)
{
	bool success = false;
	Drive * d = getItem(drive, _drives);
	if (d != nullptr){
		success = d->setFileData(folder, filename, data);
	}
	return success;
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

bool PrinterFiles::clearFolder(const string &drive, const string &folder)
{
	bool success = false;
	Drive * d = getItem(drive, _drives);
	if (d != nullptr){
		success = d->clearFolder(folder);
	}

	return success;
}

bool PrinterFiles::deleteDrive(const string &drive)
{
	return deleteItem(drive, _drives);
}

bool PrinterFiles::deleteFolder(const string &drive, const string &folder)
{
	bool success = false;
	Drive * d = getItem(drive, _drives);
	if (d != nullptr){
		success =  d->deleteFolder(folder);
	}
	return success;
}

bool PrinterFiles::deleteFile(const string &drive, const string &folder, const string &filename)
{
	bool success = false;
	Drive * d = getItem(drive, _drives);
	if (d != nullptr){
		success =  d->deleteFile(folder, filename);
	}
	return success;
}

Drive *PrinterFiles::removeDrive(const string &drive)
{
	return removeItem(drive, _drives);
}

Folder* PrinterFiles::removeFolder(const string &drive, const string &folder)
{
	Drive * d = getItem(drive, _drives);
	Folder* f = nullptr;
	if (d != nullptr){
		f = d->removeFolder(folder);
	}
	return f;
}

File *PrinterFiles::removeFile(const string &drive, const string &folder, const string &filename)
{
	Drive * d = getItem(drive, _drives);
	File* f = nullptr;
	if (d != nullptr){
		f = d->removeFile(folder, filename);
	}
	return f;
}

void PrinterFiles::splitFilepath(const string &pwd, string &drive, vector<string> &folders, string &file) const
{
	drive.clear();
	folders.clear();
	file.clear();
	string path;

	size_t slash = pwd.find(DRIVE_STRING_DELIMITER);
	path = pwd;
	if(slash != pwd.npos) {
		drive = pwd.substr(0, slash + strlen(DRIVE_STRING_DELIMITER));
		path = pwd.substr(slash + strlen(DRIVE_STRING_DELIMITER));
	}

	while ((slash = path.find_last_of(SLASH_CHAR)) != file.npos) {
		folders.push_back(path.substr(0, slash));
		path = path.substr(slash + 1);
	}
	file = path;
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
			*d = *(drive->second);
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

bool PrinterFiles::renameFolder(const string &drive, const string &oldfolder, const string &newFolder)
{
	bool success = false;
	Drive * d = getItem(drive, _drives);
	if (d != nullptr){
		success = d->renameFolder(oldfolder, newFolder);
	}
	return success;
}

bool PrinterFiles::renameFile(const string &drive, const string &folder, const string &oldName, const string &newName)
{
	bool success = false;
	Drive * d = getItem(drive, _drives);
	if (d != nullptr){
		success = d->renameFile(folder, oldName, newName);
	}
	return success;
}

bool PrinterFiles::moveFile(const string &oldDrive, const string &oldFolder, const string &oldName, const string &newDrive, const string &newFolder, const string &newName)
{
	bool success = false;
	Drive * dOld = getItem(oldDrive, _drives);
	Drive * dNew = getItem(newDrive, _drives);

	bool validParams = (dOld != nullptr && dOld->getFile(oldFolder, oldName) != nullptr &&
						dNew != nullptr && dNew->getFolder(newFolder) != nullptr &&
						dNew->getFile(newFolder, newName) == nullptr);

	if (validParams)
	{
		File* file = dOld->removeFile(oldFolder, oldName);
		if (oldName.compare(newName) != 0) {
			file->setName(newName);
		}
		if (dNew->addFile(newFolder, file)){
			success = true;
		}
		else {
			file->setName(oldName);
			dOld->addFile(oldFolder, file);
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
				d->deleteFile(file->folder(), file->name());
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
				d->deleteFile(file->folder(), file->name());
			}
		}
	}
}

//====== Drive definitions ======//
Drive::Drive(const string &name, const PrinterFiles *parent) :
	_name(name)
{
	_parent = parent;
	_folders.clear();
}

Drive::~Drive()
{

}

std::string Drive::name() const
{
	return _name;
}

std::vector<string> Drive::getFoldersList() const
{
	return getItemsList(_folders);
}

std::vector<string> Drive::getFilesList(const string &folder) const
{
	Folder* f = getItem(folder, _folders);
	if (f != nullptr){
		return f->getFilesList();
	}

	return std::vector<string>();
}

std::vector<const File *> Drive::getFiles() const
{
	//TODO: add C++98 compatibility
	std::vector<const File *>files;
	for (auto& folder : _folders) {
		std::vector<const File *> currentFolder = folder.second->getFiles();
		files.insert(files.end(),
					 std::make_move_iterator(currentFolder.begin()),
					 std::make_move_iterator(currentFolder.end()));
	}
	return files;
}

const Folder *Drive::getFolder(const string &folder) const
{
	return getItem(folder, _folders);
}

const File *Drive::getFile(const string &folder, const string &file) const
{
	const File * f = nullptr;
	Folder * pFolder = getItem(folder, _folders);
	if (pFolder != nullptr){
		f = pFolder->getFile(file);
	}

	return f;
}

bool Drive::clear()
{
	TRACE
	return FileSystemAbstract::clear(_folders);
}

bool Drive::clearFolder(const string &folder)
{
	bool success = false;
	Folder * f = getItem(folder, _folders);
	if (f != nullptr){
		success = f->clear();
	}

	return success;
}

bool Drive::addEmptyFolder(const string &folder)
{
	return (insertNewItem(folder, _folders, this) != nullptr);
}

bool Drive::addNewFile(const string &folder, const string &filename)
{
	Folder* f = getItem(folder, _folders);
	if (f != nullptr) {
		return f->addEmptyFile(filename);
	}
	return false;
}

bool Drive::addFile(const string &folder, const string &filename, const std::vector<uint8_t> &data)
{
	Folder* f = getItem(folder, _folders);
	if (f != nullptr) {
		return f->addFile(filename, data);
	}
	return false;
}

bool Drive::addFile(const string &folder, File *file)
{
	Folder* f = getItem(folder, _folders);
	if (f != nullptr) {
		return f->addFile(file);
	}
	return false;
}

bool Drive::setFileData(const string &folder, const string &filename, const std::vector<uint8_t> &data)
{
	Folder* f = getItem(folder, _folders);
	if (f != nullptr) {
		return f->setFileData(filename, data);
	}
	return false;
}

bool Drive::renameFolder(const string &oldfolder, const string &newFolder)
{
	bool success = false;
	Folder* f = removeItem(oldfolder, _folders);
	if (f != nullptr) {
		f->setName(newFolder);
		_folders.insert(pair<string, Folder*>(newFolder, f));
		success = true;
	}
	return success;
}

Folder *Drive::removeFolder(const string &folder)
{
	return removeItem(folder, _folders);
}

File *Drive::removeFile(const string &folder, const string &filename)
{
	Folder* f = getItem(folder, _folders);
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
		equal &= compare(_folders, drive._folders);
	}
	catch(std::bad_cast exp) {
		std::cout << __func__ <<"Caught bad cast" << std::endl;
	}

	return equal;
}

void Drive::copy(const Drive &other)
{
	clear();
	for (std::map<std::string, Folder*>::const_iterator folder = other._folders.begin(); folder != other._folders.end(); folder++)
	{
		if (folder->second){
			Folder* f = new Folder(folder->first, this);
			*f = *(folder->second);
			_folders.insert(pair<string, Folder*>(folder->first, f));
		}
	}
}

bool Drive::renameFile(const string &folder, const string &oldName, const string &newName)
{
	Folder* f = getItem(folder, _folders);
	if (f != nullptr) {
		return f->renameFile(oldName, newName);
	}
	return false;
}

bool Drive::moveFile(const string &oldFolder, const string &oldName, const string & newFolder, const string &newName)
{
	bool success = false;
	Folder* fOld = getItem(oldFolder, _folders);
	Folder* fNew = getItem(newFolder, _folders);
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

bool Drive::moveFile(const string &oldFolder, const string &newFolder, const string &filename)
{
	return moveFile(oldFolder, filename, newFolder, filename);
}

bool Drive::deleteFolder(const string &folder)
{
	return deleteItem(folder, _folders);
}

bool Drive::deleteFile(const string &folder, const string &file)
{
	bool success = false;
	Folder* f = getItem(folder, _folders);
	if (f != nullptr) {
		success = f->deleteFile(file);
	}
	return success;
}

//====== Folder definitions ======//
Folder::Folder(const string &name, const Drive *parent) :
	_parent(parent),
	_name(name)
{
	_files.clear();
}

Folder::~Folder()
{
	clear();
}

string Folder::pwd() const
{
	string pwd = _name;
	if (_parent) {
		pwd = _parent->name() + "/" + pwd;
	}
	return pwd;
}

string Folder::name() const
{
	return _name;
}

std::vector<string> Folder::getFilesList() const
{
	return getItemsList(_files);
}

void Folder::setName(const std::string &name)
{
	_name = name;
}

const File *Folder::getFile(const string &filename) const
{
	return getItem(filename, _files);
}

std::vector<const File *> Folder::getFiles() const
{
	std::vector<const File *> files;
	files.clear();
	for (auto& file : _files) {
		files.push_back(file.second);
	}
	return files;
}

std::vector<uint8_t> Folder::getFileContent(const string &filename) const
{
	const File * f = getFile(filename);
	if (f != nullptr) {
		return f->data();
	}
	return std::vector<uint8_t>();
}

bool Folder::clear()
{
	return FileSystemAbstract::clear(_files);
}

bool Folder::addEmptyFile(const string &file)
{
	return (insertNewItem(file, _files, this) != nullptr);
}

bool Folder::addFile(const string &file, const std::vector<uint8_t> &data)
{
	bool success = false;
	File* f = insertNewItem(file, _files, this);
	if (f != nullptr) {
		success = f->setContent(data);
	}

	return success;
}

bool Folder::addFile(File *file)
{
	bool success = false;
	if (getItem(file->name(), _files) == nullptr) {
		_files.insert(pair<string, File*>(file->name(), file));
		success = true;
	}
	return success;
}

bool Folder::setFileData(const string &file, const std::vector<uint8_t> &data)
{
	bool success = false;
	File* f = getItem(file, _files);
	if (f != nullptr) {
		success = f->setContent(data);
	}
	return success;
}

File *Folder::removeFile(const string &file)
{
	return removeItem(file, _files);
}

bool Folder::deleteFile(const string &file)
{
	return deleteItem(file, _files);
}

bool Folder::renameFile(const string &oldName, const string &newName)
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

bool Folder::equal(const FileSystemAbstract &other) const
{
	bool equal = false;

	try
	{
		const Folder& folder = dynamic_cast<const Folder&>(other);

		equal =  (_parent->name().compare(folder._parent->name()) == 0);
		if(equal){
			equal &= (_name == folder._name);
			equal &= compare(_files, folder._files);
		}

	}
	catch(std::bad_cast exp)
	{
		std::cout << __func__ <<"Caught bad cast" << std::endl;
	}

	return equal;

}

void Folder::copy(const Folder &other)
{
	clear();
	_name = other._name;
	for (std::map<std::string, File*>::const_iterator file = other._files.begin(); file != other._files.end(); file++)
	{
		File* f = new File(file->first, this);
		if (file->second){
			*f = *(file->second);
		}
		if (!addFile(f)) {
			delete f;
		}
	}
}

//====== Files definitions ======//
File::File(const string &filename, const Folder *parent) :
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

string File::folder() const
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

