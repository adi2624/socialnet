#include "Response.h"
#include "dds_io.h"

using namespace TSN;
void Response::initPublisher(std::string uuid, response& res_instance)
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
    _responseDataWriter = responseDataWriter::_narrow(dWriter.in());


    m_instance = new response();
    m_instance->post_id = res_instance.post_id;
    m_instance->date_of_creation = res_instance.date_of_creation;
    m_instance->post_body = res_instance.post_body;
    strncpy(m_instance->uuid, uuid.c_str(), 37); // <-------------- REVISIT num 37

    userHandle = _responseDataWriter->register_instance(*m_instance);

}
Response::Response(std::string uuid, response& res_instance)
{
    initPublisher(uuid, res_instance);
}
void Response::publishEvent(std::string uuid, response& res_instance)
{
    std::cout << "We are here!" <<std::endl;
    m_instance->post_body = res_instance.post_body;
    m_instance->post_id = res_instance.post_id;
    m_instance->date_of_creation = res_instance.date_of_creation;
    strncpy(m_instance->uuid, uuid.c_str(), 37); // <---------------- REVISIT 37
    _responseDataWriter->write(*m_instance, userHandle);
    dds_io<response,
            responseSeq,
            responseTypeSupport_var,
            responseTypeSupport,
            responseDataWriter_var,
            responseDataWriter,
            responseDataReader_var,
            responseDataReader> res =
            dds_io<response,
            responseSeq,
            responseTypeSupport_var,
            responseTypeSupport,
            responseDataWriter_var,
            responseDataWriter,
            responseDataReader_var,
            responseDataReader>
            ( (char*) "response", true , true );
    res.publish(*m_instance);
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

