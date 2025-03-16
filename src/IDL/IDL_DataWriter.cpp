#include "IDL_DataWriter.h"

StringMessageTypeDataWriter::StringMessageTypeDataWriter(DataWriterImpl * pDataWriterImpl)
	: DataWriter(pDataWriterImpl)
{
}

StringMessageTypeDataWriter::~StringMessageTypeDataWriter()
{
}

StringMessageTypeDataWriter* StringMessageTypeDataWriter::narrow(DataWriter* pDataWriter) 
{
	if (!pDataWriter)
		return NULL;
	StringMessageTypeDataWriter *aStringMessageTypeDataWriter = (StringMessageTypeDataWriter*)pDataWriter;
    return aStringMessageTypeDataWriter;
}

ReturnCode_t StringMessageTypeDataWriter::write(StringMessageType& data, const InstanceHandle_t & handle){
	char *buf = new char[DEFAULT_CDRSIZE];
	CDR* CDRData = NULL;
	ReturnCode_t ret = RETCODE_OK;
	CDRData = new CDR((unsigned char *)buf, DEFAULT_CDRSIZE, MY_BYTE_SEX, 1);
	data.Marshal(CDRData);
	char* myData = CDRData->GetBufferPtr();
	int typeSize = CDRData->GetContentLen();
	char* pDataVale = new char[typeSize + 4]();
	pDataVale[1] = 0x01;
	memcpy(pDataVale + 4, myData, typeSize);
	//InstanceHandle_t handle = HANDLE_NIL;
	ret = DataWriter::write(pDataVale, typeSize + 4, handle);
	buf = (char*)CDRData->pReal_buffer;
	if (buf)
		delete buf;
	if (CDRData)
		delete CDRData;
	if (pDataVale)
		delete pDataVale;
	return ret;
}

