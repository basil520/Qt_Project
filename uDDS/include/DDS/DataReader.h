/************************************************************
** �ļ�����DomainParticipant.h
** Copyright (c) 2011-2021 �Ͼ�������Ϣ�Ƽ����޹�˾
** �����ˣ�Nephalem<250610346@qq.com>
** ��  �ڣ�2011-01-15
** �޸��ˣ�Nephalem<250610346@qq.com>
** ��  �ڣ�2011-03-05
** ��  ����DomainParticipantͷ�ļ�
** ��  ����Version 0.1
**----------------------------------------------------------
************************************************************/

#ifndef _DDS_DATAREADER_H_
#define _DDS_DATAREADER_H_

/* Nephalem �û�ͷ�ļ� */
#include "ReturnCode.h"
#include "BasicTypes.h"
#include "QoSPolicy.h"
/* Nephalem ϵͳͷ�ļ� */

/* Nephalem ǰ������ */
class DomainParticipantListener;
class Publisher;
class PublisherListener;
class Subscriber;
class SubscriberListener;
class TopicListener;
class MultiTopic;
class DomainParticipantImpl;
class TopicDescription;
class DataReaderListener;
class DataReaderImpl;



struct SampleInfo 
{
	//SampleStateKind 		sample_state;
	//ViewStateKind 			view_state;
	//InstanceStateKind 		instance_state;
	//Time_t					source_timestamp;
	//InstanceHandle_t 		instance_handle;
	//InstanceHandle_t 		publication_handle;
	//long 					disposed_generation_count;
	//long 					no_writers_generation_count;
	//long 					sample_rank;
	//long 					generation_rank;
	//long					absolute_generation_rank;
	bool 				valid_data;
};

typedef sequence<SampleInfo> SampleInfoSeq;

//JDXCZ  ������������ �淶������Ƕ��岻һ�� 

struct Condition
{
	//boolean get_trigger_value();
};

struct ReadCondition : Condition
{
	//SampleStateMask  	get_sample_state_mask();
	//ViewStateMask  		get_view_state_mask();
	////InstanceStateMask  	get_instance_state_mask();
	//DataReader  			get_datareader();
};

struct QueryCondition : ReadCondition
{
	//string			get_query_expression();
	//ReturnCode_t		get_query_parameters(inout StringSeq	query_parameters);
	//ReturnCode_t		set_query_parameters(in StringSeq query_parameters);
};



class DDS_DLL DataReader 
{
public:
	//���캯��
	DataReader(DataReaderImpl* pDataReaderImpl);
	//��������
	virtual ~DataReader(void);
public:
	/* JDXCZ �˴�Ϊ�淶�ж���Ľӿ� */

	/* JDXCZ ����DataReader��ֵ��������������ʧ�� */
	//ReturnCode_t set_qos(const DataReaderQos& QoS);

	/* JDXCZ ��ȡDataReader��ֵ */
	ReturnCode_t get_qos(DataReaderQos& QoS);

	///* JDXCZ ����DataReaderListener��ֵ */
	//ReturnCode_t set_listener(DataReaderListener* pListener, StatusMask mask);

	/* JDXCZ ����DataReaderListener��ֵ */
	DataReaderListener* get_listener();

	///* JDXCZ    ����һ��ReadCondition���󶨵�������DataReader*/
	//ReaderCondition* create_readcondition(SampleStateKind smaple_states[], ViewStateKind  view_states[], InstanceStateKind  instance_states[]);

	///* JDXCZ    ����һ��QueryCondition,�󶨵�������DataReader��*/
	//QueryCondition create_querycondition(SampleStateKind smaple_states[], ViewStateKind  view_states[], InstanceStateKind  instance_states[], const string& query_expression, string query_parameters);

	///* JDXCZ    ɾ�����ӵ�DataReader��ReadCondition*/
	//ReturnCode_t delete_readcondition(ReaderCondition* condition);

	/* JDXCZ    ͨ��DataReader����Dataֵ�ĺϼ�*/
	//ReturnCode_t read(Data data_values[], SampleInfo sample_infos[], long max_samples, SampleStateKind sample_states[], ViewStateKind view_states[], InstanceStateKind instance_states);
	ReturnCode_t read(UserDataVector& data_values, SampleInfoSeq sample_infos, int max_samples, SampleStateKind sample_states, ViewStateKind view_states, InstanceStateKind instance_states);

	/* JDXCZ    ����DataReader�е����������ϼ��Լ���Ӧ��SampleInfo�ṹ�ϼ�*/
	/* Nephalem data_values max_len = 0 ʹ���㿽�� ʹ�������ͨ��return_loan�黹 */
	/* Nephalem data_values max_len > 0 ʹ����� */
	/* Nephalem data_values sample_infos����������������ͬ */
	/* Nephalem take������ȡ�����ݲ����ٱ�take */
	//ReturnCode_t take(Data data_values[], SampleInfo sample_infos[], int max_samples, SampleStateKind sample_states, ViewStateKind view_states, InstanceStateKind instance_states);
	ReturnCode_t take(UserDataVector& data_values, SampleInfoSeq sample_infos, int max_samples, SampleStateKind sample_states, ViewStateKind view_states, InstanceStateKind instance_states);

	///* JDXCZ    ������ReadCondition��ָ��������ƥ�������*/
	//ReturnCode_t read_w_condition(Data data_values[], SampleInfo sample_infos[], long max_samples, const ReaderCondition& readcondition);

	///* JDXCZ    ������ReadCondition��ָ��������ƥ�������*/
	//ReturnCode_t take_w_condition(Data data_values[], SampleInfo sample_infos[], long max_samples, const ReaderCondition& readcondition);

	/* JDXCZ    ��DataReader������һ��֮ǰδ���ʹ���Dataֵ*/
	//ReturnCode_t read_next_sample(Data data_values[], SampleInfo sample_infos[]);
	//ReturnCode_t read_next_sample(UserDataVector data_values, SampleInfoSeq sample_infos);

	/* JDXCZ    ��DataReader������һ��֮ǰδ���ʹ���Dataֵ������DataReader�С�ɾ��������ʹ�䲻�ٿɷ���*/
	//ReturnCode_t take_next_sample(Data& data_values, SampleInfo& sample_info);
	ReturnCode_t take_next_sample(UserData& data_value, SampleInfo& sample_info);

	///* JDXCZ    ��DataReader����Dataֵ�ĺϼ� */
	//ReturnCode_t read_instance(Data data_values[], SampleInfo sample_info[], long max_samples, InstanceHandle_t handle, SampleStateKind sample_states, ViewStateKind samole_states[], InstanceStateKind instance_states);

	///* JDXCZ    ��DataReader����Dataֵ�ĺϼ�*/
	//ReturnCode_t take_instance(Data data_values[], SampleInfo sample_info[], long max_samples, InstanceHandle_t handle, SampleStateKind sample_states, ViewStateKind samole_states[], InstanceStateKind instance_states);

	///* JDXCZ    ��DataReader������һ��֮ǰδ���ʹ���Dataֵ */
	//ReturnCode_t reaad_next_instance(Data data_values[], SampleInfo sample_info[], long max_samples, InstanceHandle_t previous_handle, SampleStateKind sample_states, ViewStateKind samole_states[], InstanceStateKind instance_states);

	///* JDXCZ    ��DataReader������һ��֮ǰδ���ʹ���Dataֵ������DataReader�С�ɾ��������ʹ�䲻�ٿɷ���*/
	//ReturnCode_t take_next_instance(Data data_values[], SampleInfo sample_info[], long max_samples, InstanceHandle_t previous_handle, SampleStateKind sample_states, ViewStateKind samole_states[], InstanceStateKind instance_states);

	///* JDXCZ    ��DataReader����Dataֵ�ļ��ϣ���Ϊ��read_next_instance��ͬ��ֻ�Ƿ��ص�������������������ָ��������*/
	//ReturnCode_t read_next_instance_w_condition(Data data_values[], SampleInfo sample_infos[], long max_samples, InstanceHandle_t previous_handle, ReadCondition* pReadCondition);

	///* JDXCZ    DataReader����Dataֵ�ϼ�������DataReader�С�ɾ�������� */
	//ReturnCode_t take_next_instance_w_condition(Data data_values[], SampleInfo sample_infos[], long max_samples, InstanceHandle_t previous_handle, ReadCondition* pReadCondition);

	///* JDXCZ    ��DataReader֪ͨӦ�ó�������ɷ���data_values��sample_infos�ĺϼ�����Щ�ϼ��ǽ���ǰͨ��DataReader��read��take������õ� */
	//ReturnCode_t return_loan(Data data_values[], SampleInfo sample_infos[]);

	///* JDXCZ    ��������LIVELINESS_CHANGEDͨ��״̬ */
	//ReturnCode_t get_liveliness_changed_status(LivelinessChangedStatus& status);

	///* JDXCZ    ��������REQUESTED_DEADLINE_MISSEDͨ��״̬ */
	//ReturnCode_t get_requested_deadline_missed_status(_REQUESTED_DEADLINE_MISSED_STATUS& status);

	///* JDXCZ    ��������REQUESTED_INCOMPATIBLE_QOSͨ��״̬ */
	//ReturnCode_t get_requested_incompatible_qos_status(RequestedIncompatibleQosStatus& status);

	///* JDXCZ    ��������SAMPLE_LOSTͨ��״̬ */
	//ReturnCode_t get_sample_lost_status(SampleLostStatus& status);

	///* JDXCZ    ��������SAMPLE_REJECTEDͨ��״̬ */
	//ReturnCode_t get_sample_rejected_statu(SampleRejectedStatus& status);

	///* JDXCZ    ��������SUBSCRIPTION_MATCHEDͨ��״̬ */
	//ReturnCode_t get_subscription_matched_status(SubscriptionMatchedStatus& status);

	/* JDXCZ    ������DataReader������TopicDescription */
	TopicDescription* get_topicdescription();

	/* JDXCZ    ������DataReader������Subscriber */
	Subscriber* get_subscriber();

	///* JDXCZ    ��ȡ��instance_handle��Ӧ��ʵ���ؼ���ke�������key_holderʵ������ɹؼ���key���ֶ� */
	//ReturnCode_t get_key_value(Data key_holder, InstanceHandle_t handle);

	///* JDXCZ    ʵ��instance��Ϊ������������һ����� */
	//InstanceHandle_t lookup_instance(Data instance);

	///* JDXCZ    ɾ��ͨ��DataReader����ġ���������������������ʵ��,ɾ��QueryCondition ��ReadCondition���� */
	//ReturnCode_t delete_contained_entities();

	///* JDXCZ    ���������̣߳�ֱ�����յ����С���ʷ�����ݣ�����max_wait����ָ����ʱ���ѵ��� */
	//ReturnCode_t wait_for_historical_data(const Duration_t max_wait);

	///* JDXCZ    ��ȡ��ǰ��DataReader ���������ķ�����Ϣ */
	//ReturnCode_t get_matched_publication_data(PublicationBuiltinTopicData& publication_data, const InstanceHandle_t publication_handle);

	///* JDXCZ    ��ȡ��ǰ��DataReader ���������ķ����б� */
	//InstanceHandle_t get_matched_publications(InstanceHandle_t publication_handles[]);

public:
	/* Nephalem �Զ���ӿ� */
	/* Nephalem ��Cache�ж�ȡ���� */
	//ReturnCode_t ReadFromCache(char*& pMyDataValue, unsigned int& uiLeng, InstanceHandle_t& Handle, _CHANGE_KIND_T& Kind);

	///* Nephalem ��Cache�ж�ȡ���� */
	//ReturnCode_t TakeFromCache(char*& pMyDataValue, unsigned int& uiLeng, InstanceHandle_t& Handle, _CHANGE_KIND_T& Kind);

public:
	DataReaderImpl* getImpl();

	/* Nephalem ��ȡ������Guid */
	GUID_t getGuid();

protected:
	DataReaderImpl* m_pDataReaderImpl;
};

#endif

