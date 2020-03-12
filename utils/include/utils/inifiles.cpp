#include "inifiles.h"
#include <iostream>
#include <fstream>
using namespace Macsa::Utils;

INIFile::INIFile(const std::string filename) :
	_filename(filename)
{

}

bool INIFile::parse()
{
	std::ifstream file;
	file.open (_filename);
	return false;
}

bool INIFile::save()
{
	return false;
}

std::vector<std::string> INIFile::sections()
{
	std::vector<std::string> sections;
	for (auto s : _sections){
		sections.push_back(s.first);
	}

	return sections;
}

Section &INIFile::operator [](const std::string &section)
{
	if (_sections.find(section) == _sections.end()) {
		Section s(section);
		_sections.insert(std::pair<std::string, Section>(section, s));
	}

	return _sections[section];
}

const Section &INIFile::operator [](const std::string &section) const
{
	return _sections.at(section);
}

Section::Section(const std::string &section) :
	_section(section){}

Section::~Section()
{
	clear();
}

void Section::clear()
{
	while (size()) {
		std::map<std::string, IKey*>::iterator k = _keys.begin();
		delete  k->second;
		_keys.erase(k);
	}
}

template<typename V>
Key<V> &Section::operator[](const std::string &name)
{
	return _keys[name];
}

Macsa::Utils::IKey::IKey(const std::__cxx11::string &name) :
	_name(name){}

IKey::~IKey(){}


