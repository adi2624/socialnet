#include "Response.h"
#include "dds_io.h"
#include "Post.h"
#include<fstream>
#include <sstream>
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
Response::Response()
{
    
}
void Response::publishEvent(TSN::response response_instance)
{
    std::cout << "We are here!" <<std::endl;
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
    res.publish(response_instance);
}
TSN::response Response::draft_response(char* uuid,unsigned long post_no,std::string post_body, long doc){
    TSN::response resp_instance;
    for(int i=0;i<37;i++)
    {
        resp_instance.uuid[i]=uuid[i];
    }
    std::cout<<"RESP UUID: "<<resp_instance.uuid<<std::endl;
    resp_instance.post_id=post_no;
    
  
        resp_instance.post_body=post_body.c_str();

    
    resp_instance.date_of_creation=doc;
    return resp_instance;

}
std::string Response::load_post(int post_no) 
{
    std::ifstream post_file;
    post_file.open("my_user.tsn");
    int count = 0;
    std::string test;
    std::string serial_number;
    std::string post_data;
    while(std::getline(post_file, test))
     {
         if(count != 0 && count == post_no)
         {
             Post my_post;
             int sno;
             std::stringstream iss(test);
             std::getline(iss, serial_number , ' ');
             std::getline(iss, post_data, '\n');
             sno = stoi(serial_number.substr(4));
             post_data = post_data.substr(5);
             my_post.set_serial_number(sno);
             my_post.enter_post_data(post_data);
             return post_data;
         }
         count++;
     }
     post_file.close();

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

