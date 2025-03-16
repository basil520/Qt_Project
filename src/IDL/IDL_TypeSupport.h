#ifndef _IDL_TYPESUPPORT_H_INCLUDED_ 
#define _IDL_TYPESUPPORT_H_INCLUDED_

#include <string>
using std::string;
#include "IDL_DataWriter.h"
#include "IDL_DataReader.h"
#include "DDS/TypeSupport.h"

class StringMessageTypeTypeSupport : public TypeSupport {
public:
	static StringMessageType* create_data()
	{
		return new StringMessageType;
	}

	static ReturnCode_t delete_data(StringMessageType* pStringMessageType)
	{
		delete pStringMessageType;
		pStringMessageType = NULL;
		return ReturnCode_t();
	}

	static void print_data(StringMessageType* pStringMessageType,int layer = 0)
	{
		char *c = new char[layer];
		int i = 0;
		for (; i < layer; i++)
		{
			c[i] = '\t';
		}
		c[i] = '\0';
		std::cout<<c<<"StringMessageType:"<<std::endl;
		std::cout<<c<<"  message = "<< pStringMessageType->message <<std::endl;
	}

	static const char* get_type_name()
	{
		return "StringMessageType";
	}

	static int register_type(DomainParticipant* participant, string type_name)
	{
		if (type_name.empty())
			type_name = get_type_name();

		return participant->register_type(type_name);
	}
};

#endif
