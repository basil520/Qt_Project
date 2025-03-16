#ifndef _IDL_DATAWRITER_H_INCLUDED_
#define _IDL_DATAWRITER_H_INCLUDED_
#include "ReturnCode.h"
#include "BasicTypes.h"
#include "DDS/DomainParticipantFactory.h"
#include "DDS/Topic.h"
#include "DDS/Publisher.h"
#include "DDS/DataWriter.h"
#include "IDL_StringMessage.h"
class DataWriterImpl;

class StringMessageTypeDataWriter : public DataWriter
{
public:
	StringMessageTypeDataWriter(DataWriterImpl* pDataWriterImpl);

	~StringMessageTypeDataWriter();

	static StringMessageTypeDataWriter* narrow(DataWriter* pDataWriter);

	ReturnCode_t write(StringMessageType& data,const InstanceHandle_t & handle);

};

#endif
