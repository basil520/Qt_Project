// Don't modify this file as it will be overwritten.
//
#include "CDR/CDR.h"
#include "ReturnCode.h"
#include "BasicTypes.h"

#ifndef IDL_StringMessage_hh
#define IDL_StringMessage_hh

#ifndef StringMessageType_defined
#define StringMessageType_defined

struct StringMessageType {
  StringMessageType()
	{
		message = new char[255];
		message[0]= '\0';
	}

  StringMessageType(const StringMessageType  &IDL_s);

  ~StringMessageType(){
		delete message;
		message = NULL;
	}

  	int StructSize()
	{
		int strSize = 0;
		strSize += sizeof(StringMessageType);
		strSize += strlen(message);
		return strSize;
	}
  StringMessageType& operator= (const StringMessageType &IDL_s);

  void Marshal(CDR *cdr) const;
  void UnMarshal(CDR *cdr);

  char* message;
  
};

typedef sequence<StringMessageType> StringMessageTypeSeq;

#endif




#endif /*IDL_StringMessage_hh */
