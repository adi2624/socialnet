#include "Response.h"
#include "dds_io.h"
#include<fstream>
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

    
    std::cout<<"HELLO"<<resp_instance.post_body<<std::endl;
    resp_instance.date_of_creation=doc;
    return resp_instance;

}
std::string Response::load_post(int post_no) {
    int number = 0, i = 0;
    std::string line, post;
    std::ifstream get_post("my_user.tsn");
    if (!get_post.is_open())
        perror("error while opening file");
    //get_post.open("hello.tsn",ios::in);
    if (get_post.bad())
        perror("error while reading file");
    while (std::getline(get_post, line)) {
        std::istringstream iss(line);
        std::string c;                          //GET LINE AND PUSH INTO STRINGSTREAM.
        c = iss.str();
        //std::cout<<"String received "<<c<<endl;  //Debugging string
        std::size_t pos = c.find("SNO:");
        std::size_t pos2 = c.find("POST:");           //FIND DATA after POST:
        if (i != 0)      //IGNORE UUID AT TOP OF FILE
        {
            std::string number_string = c.substr(pos + 4, pos2 - 4);
           // std::cout<<"Number String "<<number_string<<std::endl;   //please.ignore(#debug) FIND NUMBER BETWEEN SNO: and POST:
            number = std::stoi(number_string);
        }
        i++;
        if (number == post_no-1 && i!=1) {
            std::string final_post_text = c.substr(pos2 + 4);
           // std::cout << "Final text:" << final_post_text << std::endl;   //RETURN FOUND POST DATA
            return final_post_text;
        }

    }
    return "Fail";
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

