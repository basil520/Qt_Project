#include "IDL_DataReader.h"

StringMessageTypeDataReader::StringMessageTypeDataReader(DataReaderImpl * pDataReaderImpl)
	:DataReader(pDataReaderImpl)
{
}

StringMessageTypeDataReader::~StringMessageTypeDataReader() 
{
}

StringMessageTypeDataReader* StringMessageTypeDataReader::narrow(DataReader* pDataReader) 
{
	if (!pDataReader)
		return NULL;

	StringMessageTypeDataReader *aStringMessageTypeDataReader = (StringMessageTypeDataReader*)pDataReader;
	return aStringMessageTypeDataReader;
}

ReturnCode_t StringMessageTypeDataReader::take(StringMessageTypeSeq & data_values, SampleInfoSeq & sample_infos, int max_samples, SampleStateKind sample_states, ViewStateKind view_states, InstanceStateKind instance_states)
{
	UserDataVector userDataVector;
	DataReader::take(userDataVector, sample_infos, max_samples, sample_states, view_states, instance_states);

	data_values.ensure_length(userDataVector.size(), userDataVector.size());
	for (int i = 0; i < userDataVector.size(); i++)
	{
		CDR* CDRData = new CDR((unsigned char *)userDataVector[i].pData + 4, userDataVector[i].ilength - 4, MY_BYTE_SEX, 1);
		data_values[i].UnMarshal(CDRData);
		if (CDRData)
			delete CDRData;
		delete userDataVector[i].pData;
	}
	return ReturnCode_t();
}

ReturnCode_t StringMessageTypeDataReader::read(StringMessageTypeSeq & data_values, SampleInfoSeq & sample_infos, int max_samples, SampleStateKind sample_states, ViewStateKind view_states, InstanceStateKind instance_states)
{
	UserDataVector userDataVector;
	DataReader::read(userDataVector, sample_infos, max_samples, sample_states, view_states, instance_states);

	data_values.ensure_length(userDataVector.size(), userDataVector.size());
	for (int i = 0; i < userDataVector.size(); i++)
	{
		CDR* CDRData = new CDR((unsigned char *)userDataVector[i].pData + 4, userDataVector[i].ilength - 4, MY_BYTE_SEX, 1);
		data_values[i].UnMarshal(CDRData);
		if (CDRData)
			delete CDRData;
		delete userDataVector[i].pData;
	}
	return ReturnCode_t();
}

ReturnCode_t StringMessageTypeDataReader::take_next_sample(StringMessageType& receivedData, SampleInfo& sample_info)
{
	UserData userData;
	DataReader::take_next_sample(userData, sample_info);
	CDR* CDRData = new CDR((unsigned char *)userData.pData + 4, userData.ilength - 4, MY_BYTE_SEX, 1);
	receivedData.UnMarshal(CDRData);
	if (CDRData)
	{
		delete CDRData;
	}
	return ReturnCode_t();
}

ReturnCode_t StringMessageTypeDataReader::return_loan(StringMessageTypeSeq& data_values, SampleInfoSeq& sample_infos)
{
	return ReturnCode_t();
}

