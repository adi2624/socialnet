#ifndef MESSAGE_H
#define MESSAGE_H
#include <iostream>
#include "DDSEntityManager.h"
#include "ccpp_tsn.h"
#include "example_main.h"

class Message 
{
    private:
        DDSEntityManager mgr;
        DataWriter_var dWriter;
        TSN::private_messageDataWriter_var _private_messageDataWriter;
        InstanceHandle_t userHandle;
        ReturnCode_t status;
        TSN::private_message * m_instance;
        void initPublisher(TSN::private_message& msg);
    public:
        Message(TSN::private_message);
        Message();
        void publishEvent(TSN::private_message& msg);
        void dispose();
        TSN::private_message construct_message(char * reciever_uuid, char * sender_uuid, std::string message_body, long date_of_creation);
};


#endif
