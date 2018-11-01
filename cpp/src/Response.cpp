#include "Response.h"
using namespace TSN;
void Response::initPublisher(std::string uuid, int  post_id, long date, std::string post)
{
    char partition_name[] = "response Ownership";
    mgr.createParticipant(partition_name);

    responseTypeSupport_var st = new responseTypeSupport();
    mgr.registerType(st.in());


    char topic_name[] = "response";
    mgr.createTopic(topic_name);

    mgr.createPublisher();

    bool auto_dispose_unregistered_instances = false;
    mgr.createWriter(auto_dispose_unregistered_instances);

    dWriter = mgr.getWriter();
    responseDataWriter = responseDataWriter::_narrow(dWriter.in());


    m_instance = new response();
    m_instance->post_id = post_id;
    m_instance->date_of_creation = date;
    m_instance->post_body = DDS::string_dup(post.c_str());
    strncpy(m_instance->uuid, uuid.c_str(), 37);

    userHandle = responseDataWriter->register_instance(*m_instance);

}
Response::Response(std::string uuid, int post_id, long date, std::string post)
{
    initPublisher(uuid, post_id, date, post);
}
void Response::publishEvent(std::string uuid, int post_id, long date, std::string post)
{
    m_instance->post_body = DDS::string_dup(post.c_str());
    m_instance->post_id = post_id;
    m_instance->date_of_creation = date;
    strncpy(m_instance->uuid, uuid.c_str(), 37);
    responseDataWriter->write(*m_instance, userHandle);
}

void Response::dispose()
{
    /* Remove the DataWriters */
    mgr.deleteWriter();

    /* Remove the Publisher. */
    mgr.deletePublisher();

    /* Remove the Topics. */
    mgr.deleteTopic();

    /* Remove Participant. */
    mgr.deleteParticipant();
}
/*
int OSPL_MAIN (int argc, char * argv[])
{
    os_time delay_200ms = { 0, 200000000 };
    std::cout << "Starting Publisher.." << std::endl;
    Response * pub;
    std::string post = "This is a test post";
    std::string uuid = "asasasasasasssssssssss-sss-s-s-ssss";
    int id = 1;
    long date = 1000;
    pub = new Response(uuid, id, date, post);
    pub->publishEvent(uuid, id, date, post);
    os_nanoSleep(delay_200ms);

    std::cout << "Starting subscriber..." << std::endl;
    os_time delay_2ms = { 0, 2000000 };
    responseSeq msgList;
    SampleInfoSeq infoSeq;

    DDSEntityManager mgr;

    char partition_name[] = "response Ownership";
    mgr.createParticipant(partition_name);

    responseTypeSupport_var st = new responseTypeSupport();
    mgr.registerType(st.in());

    char topic_name[] = "response";
    mgr.createTopic(topic_name);

    mgr.createSubscriber();
    mgr.createReader();


    DataReader_var dreader = mgr.getReader();
    responseDataReader_var responseDataReader = responseDataReader::_narrow(dreader.in());
    checkHandle(responseDataReader.in(), "responseDataReader::_narrow");

    bool closed = false;
    ReturnCode_t status = -1;
    int count = 0;
    while(!closed && count < 1500)
    {
        status = responseDataReader->take(msgList, infoSeq, LENGTH_UNLIMITED,
                                          ANY_SAMPLE_STATE, ANY_VIEW_STATE, ANY_INSTANCE_STATE);
        checkStatus(status, "responseDataReader::take");
        for(DDS::ULong j = 0; j < msgList.length(); j++)
        {
            std::cout << "Recieved Response: " << std::endl;
            std::cout << "Found post id: " << msgList[j].post_id << std::endl;
            std::cout << "Found post body: " << msgList[j].post_body << std::endl;
            std::cout << "Found date of creation: " << msgList[j].date_of_creation << std::endl;
            closed = true;
        }

        status = responseDataReader->return_loan(msgList, infoSeq);
        checkStatus(status, "responseDataReader::return_loan");
        os_nanoSleep(delay_2ms);
        count++;
        os_nanoSleep(delay_200ms);
    }

    mgr.deleteReader();
    mgr.deleteSubscriber();
    mgr.deleteTopic();
    mgr.deleteParticipant();
    pub->dispose();
    delete pub;
    return 0;
}
*/