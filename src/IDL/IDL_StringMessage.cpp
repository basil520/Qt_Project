// Don't modify this file as it will be overwritten.
//
#include "IDL_StringMessage.h"

StringMessageType::StringMessageType(const StringMessageType &IDL_s){
  message = IDL_s.message;
}

StringMessageType& StringMessageType::operator= (const StringMessageType &IDL_s){
  if (this == &IDL_s) return *this;
  message = IDL_s.message;
  return *this;
}

void StringMessageType::Marshal(CDR *cdr) const {
  cdr->PutString(message);
}

void StringMessageType::UnMarshal(CDR *cdr){
  {
    char *IDL_str;
    cdr->GetString(IDL_str);
    if(message != NULL )
    {
        delete message;
        message = NULL;
    }
    message = IDL_str;
  }
}

