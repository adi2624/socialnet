
#ifndef TEMP_REQUEST_H
#define TEMP_REQUEST_H
#include <iostream>
#include <string>
#include <sstream>
#include <fstream>
#include <vector>
#include "DDSEntityManager.h"
#include "ccpp_tsn.h"
#include "os.h"
#include "example_main.h"
#include "User.h"

//dds_io.h has been included from User.h

class Request
{
private:
    DDSEntityManager mgr;
    DataWriter_var dWriter;
    TSN::requestDataWriter_var _requestDataWriter;
    InstanceHandle_t userHandle;
    TSN::request * m_instance;
    ReturnCode_t status;
    void initPublisher(char uuid[], TSN::node_request& requests);

public:
    Request();
    void publishEvent(TSN::request reqsend_instance);
    static std::vector<User> list_pub_users() ;
    TSN::request draft_request();
    void dispose();
};




#endif //TEMP_REQUEST_H
