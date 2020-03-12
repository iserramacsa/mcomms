#ifndef MACSA_UTILS_INI_FILE_H
#define MACSA_UTILS_INI_FILE_H

#include <string>
#include <vector>
#include <map>

namespace Macsa {
	namespace Utils {

		class IKey
		{
			public:
				IKey(const std::string& name);
				virtual ~IKey();
				inline const std::string name() {return _name;}
			private:
				const std::string _name;
		};

		template <typename V>
		class Key : public IKey
		{
			public:
				Key(const std::string& name) :
					IKey(name){}
				virtual ~Key(){}

				inline void set(const V& val){_value = val;}
				inline V operator()(){ return _value;}

			private:
				V _value;

		};

		class Section
		{
			public:
				Section(const std::string& section);
				~Section();

				template<typename V>
				V value(const std::string name);

				template<typename V>
				void setKey(const std::string& name, const V& value);

				template<typename V>
				Key<V>& operator[](const std::string& name);

				inline unsigned long size(){return _keys.size();}

			private:
				const std::string _section;
				std::map<std::string, IKey*> _keys;

				void clear();
		};

		class INIFile
		{
			public:
				INIFile(const std::string filename);

				bool parse();
				bool save();

				std::vector<std::string> sections();
				Section& operator [](const std::string& section);
				const Section& operator [](const std::string& section) const;

			private:
				const std::string _filename;
				std::map<std::string, Section> _sections;
		};
	}
}

#endif //MACSA_UTILS_INI_FILE_H
