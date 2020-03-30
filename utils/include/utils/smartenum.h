#ifndef MACSA_UTILS_SMART_ENUM_H
#define MACSA_UTILS_SMART_ENUM_H

#include <cinttypes>
#include <ostream>
#include <string>
#include <vector>
#include <stdint.h>

namespace Macsa {
	namespace Utils {

		/**
		* @brief The SmartEnum class is an abstract class to avoid boilerplate code.
		* Only equal operator and toString must be overrided.
		* 
		* 
		* This class converts a basic enum into a more complex class and can be used like 
		* and enum or as a string.
		* Implementation:
		* - Define the enum:
		* @verbatim
    	* enum nMyEnum {
		*     ENUM_ITEM0 = 0,
		*     ENUM_ITEM1,
		* };	
    	* @endverbatim
    	* With this enum, define your smart enum like this:
		* @verbatim
		* class MySmartEnum : public SmartEnum<nMyEnum>
		* {
		*     public:
		* 	    virtual void operator = (const enum nMyEnum& v){_val = v;}
		* 	    virtual void operator = (const std::string& val){
		* 		    if (val.compare("ENUM_ITEM0") == 0)
		* 			    _val = ENUM_ITEM0;
		* 			else if (val.compare("ENUM_ITEM1") == 0)
		* 				_val = ENUM_ITEM1;
		*		}
		*
		*		virtual std::string toString() const {
		*			switch (_val) {
		*				case ENUM_ITEM0: return "ENUM_ITEM0";
		*				case ENUM_ITEM1: return "ENUM_ITEM1";
		*			}
		*			return "";
		*		}
		*
		*		virtual std::vector<std::string> stringList() const
		*		{
		*			std::vector<std::string> list;
		*			list.push_back("ENUM_ITEM0");
		*			list.push_back("ENUM_ITEM1");
		*			return list;
		*		}
		* };
		* @endverbatim
		* **/
		template <typename N>
		class SmartEnum
		{
			public:
				SmartEnum(){}
				SmartEnum(const std::string& val) {*this = val;}
				SmartEnum(const N&  val) {*this = val;}
				virtual ~SmartEnum(){}
				inline N operator()() const {return _val;}
				inline bool operator == (const N& val) const {return _val == val;}
				inline bool operator != (const N& val) const {return _val != val;}
				inline bool operator == (const SmartEnum& other) const {return _val == other._val;}
				inline bool operator != (const SmartEnum& other) const {return _val != other._val;}
				inline void operator =  (const SmartEnum& other){_val = other._val;}

				virtual void operator =  (const N& v) = 0;
				virtual void operator = (const std::string& val) = 0;
				virtual std::string toString() const = 0;
				virtual std::vector<std::string> stringList() const = 0;

			protected:
					N _val;
		};
		template <typename N>
		inline std::ostream& operator << (std::ostream& os, const SmartEnum<N>& value) {return os << value.toString();}
		template <typename N>
		inline std::string& operator << (std::string&, const SmartEnum<N>& value) {return value.toString();}
		template <typename N>
		inline const SmartEnum<N>& operator << (SmartEnum<N>& se, const std::string& str) {se = str; return se;}
	}
}


#endif
