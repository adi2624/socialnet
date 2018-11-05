#ifndef SOCIALNET_RESPONSE_H
#define SOCIALNET_RESPONSE_H
#include <iostream>
#include <string>
#include "DDSEntityManager.h"
#include "ccpp_tsn.h"
#include "os.h"
#include "example_main.h"
class Response
{
private:
    DDSEntityManager mgr;
    DataWriter_var dWriter;
    TSN::responseDataWriter_var _responseDataWriter;
    InstanceHandle_t userHandle;
    TSN::response * m_instance;
    ReturnCode_t status;
    void initPublisher(std::string uuid, TSN::response& res_instance);
public:
    Response();
    void publishEvent(TSN::response response_instance);
    TSN::response draft_response(char* uuid,unsigned long post_no,std::string post_body, long doc);
    std::string load_post(int post_no);
    void dispose();
};
#endif //SOCIALNET_RESPONSE_H
