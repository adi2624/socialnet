
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
    Request(char uuid[], TSN::node_request& requests);
    void publishEvent(char uuid[] , TSN::node_request& requests);
    void dispose();
};




#endif //TEMP_REQUEST_H
