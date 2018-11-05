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
    Response(std::string uuid, TSN::response& res_instance);
    void publishEvent(std::string uuid,TSN::response& res_instance);
    void dispose();
};
#endif //SOCIALNET_RESPONSE_H
