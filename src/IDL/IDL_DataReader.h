#ifndef _IDL_DATAREADER_H_INCLUDED_
#define _IDL_DATAREADER_H_INCLUDED_

#include "ReturnCode.h"
#include "BasicTypes.h"
#include "IDL_StringMessage.h"
#include "DDS/DomainParticipantFactory.h"
#include "DDS/Topic.h"
#include "DDS/Subscriber.h"
#include "DDS/DataReader.h"
#include "DDS/Listener/DataReaderListener.h"

class DataReaderImpl;

class StringMessageTypeDataReader : public DataReader 
{
public:
	StringMessageTypeDataReader(DataReaderImpl* pDataReaderImpl);

	~StringMessageTypeDataReader();

	static StringMessageTypeDataReader* narrow(DataReader* pDataReader);

	ReturnCode_t take(StringMessageTypeSeq& data_values, SampleInfoSeq & sample_infos, int max_samples, SampleStateKind sample_states, ViewStateKind view_states, InstanceStateKind instance_states);

	ReturnCode_t read(StringMessageTypeSeq& data_values, SampleInfoSeq & sample_infos, int max_samples, SampleStateKind sample_states, ViewStateKind view_states, InstanceStateKind instance_states);

	ReturnCode_t take_next_sample(StringMessageType& receivedData, SampleInfo & sample_info);

	ReturnCode_t return_loan(StringMessageTypeSeq& data_values, SampleInfoSeq& sample_infos);


};

#endif
