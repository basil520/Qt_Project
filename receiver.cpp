#include <stdio.h>
#include <stdlib.h>
#include <cstring>
#include <unistd.h>

#include "src/IDL/IDL_TypeSupport.h"

class StringMessageTypeListener : public DataReaderListener {
public:
	virtual void on_data_available(DataReader* reader);
};

void StringMessageTypeListener::on_data_available(DataReader* reader)
{
	StringMessageTypeDataReader *StringMessageType_reader = NULL;
	StringMessageTypeSeq data_seq;
	SampleInfoSeq info_seq;
	ReturnCode_t retcode;
	int i;

	StringMessageType_reader = StringMessageTypeDataReader::narrow(reader);
	if (StringMessageType_reader == NULL) {
		fprintf(stderr, "DataReader narrow error\n");
		return;
	}

	retcode = StringMessageType_reader->read(
		data_seq, info_seq, 10, 0, 0, 0);

	if (retcode == RETCODE_NO_DATA) {
		return;
	}
	else if (retcode != RETCODE_OK) {
		fprintf(stderr, "take error %d\n", retcode);
		return;
	}

	for (i = 0; i < data_seq.length(); ++i) {
			StringMessageTypeTypeSupport::print_data(&data_seq[i]);

	}
}

static int subscriber_shutdown(
	DomainParticipant *participant)
{
	ReturnCode_t retcode;
	int status = 0;

	if (participant != NULL) {
		retcode = participant->delete_contained_entities();
		if (retcode != RETCODE_OK) {
			fprintf(stderr, "delete_contained_entities error %d\n", retcode);
			status = -1;
		}

		retcode = DomainParticipantFactory::get_instance()->delete_participant(participant);
		if (retcode != RETCODE_OK) {
			fprintf(stderr, "delete_participant error %d\n", retcode);
			status = -1;
		}
	}
	return status;
}

extern "C" int subscriber_main(int domainId, int sample_count)
{
	DomainParticipant *participant = NULL;
	Subscriber *subscriber = NULL;
	Topic *topic = NULL;
	StringMessageTypeListener *reader_listener = NULL;
	DataReader *reader = NULL;
	ReturnCode_t retcode;
	const char *type_name = NULL;
	int count = 0;
	int status = 0;

	participant = DomainParticipantFactory::get_instance()->create_participant(
		domainId, PARTICIPANT_QOS_DEFAULT,
		NULL, STATUS_MASK_NONE);
	if (participant == NULL) {
		fprintf(stderr, "create_participant error\n");
		subscriber_shutdown(participant);
		return -1;
	}

	subscriber = participant->create_subscriber(
		SUBSCRIBER_QOS_DEFAULT,
		NULL, STATUS_MASK_NONE);
	if (subscriber == NULL) {
		fprintf(stderr, "create_subscriber error\n");
		subscriber_shutdown(participant);
		return -1;
	}

	type_name = StringMessageTypeTypeSupport::get_type_name();
	retcode = StringMessageTypeTypeSupport::register_type(
		participant, type_name);
	if (retcode != RETCODE_OK) {
		fprintf(stderr, "register_type error %d\n", retcode);
		subscriber_shutdown(participant);
		return -1;
	}

	topic = participant->create_topic(
		"Example StringMessageType",
		type_name, TOPIC_QOS_DEFAULT,
		NULL /* listener */, STATUS_MASK_NONE);
	if (topic == NULL) {
		fprintf(stderr, "create_topic error\n");
		subscriber_shutdown(participant);
		return -1;
	}

	reader_listener = new StringMessageTypeListener();

	reader = subscriber->create_datareader(
		topic, DATAREADER_QOS_DEFAULT,
		reader_listener, STATUS_MASK_ALL);
	if (reader == NULL) {
		fprintf(stderr, "create_datareader error\n");
		subscriber_shutdown(participant);
		delete reader_listener;
		return -1;
	}

	for (count = 0; (sample_count == 0) || (count < sample_count); ++count) {
	}


	status = subscriber_shutdown(participant);
	delete reader_listener;

	return status;
}

int main(int argc, char *argv[])
{
	int domain_id = 0;
	int sample_count = 0;

	if (argc >= 2) {
		domain_id = atoi(argv[1]);
	}
	if (argc >= 3) {
		sample_count = atoi(argv[2]);
	}
	return subscriber_main(domain_id, sample_count);
}


