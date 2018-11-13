#include "Message.h"
#include "dds_io.h"
#include <string>

using namespace TSN;
Message::Message(TSN::private_message msg)
{
    initPublisher(msg);
}
Message::Message()
{
}
void Message::publishEvent(TSN::private_message& msg)
{
     dds_io<private_message,
             private_messageSeq,
             private_messageTypeSupport_var,
             private_messageTypeSupport,
             private_messageDataWriter_var,
             private_messageDataWriter,
             private_messageDataReader_var,
             private_messageDataReader> res =
             dds_io<private_message,
             private_messageSeq,
             private_messageTypeSupport_var,
             private_messageTypeSupport,
             private_messageDataWriter_var,
             private_messageDataWriter,
             private_messageDataReader_var,
             private_messageDataReader>
             ( (char*) "private_message", true , true );
     res.publish(msg);

}
void Message::dispose()
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
void Message::initPublisher(TSN::private_message& msg)
{
     char partition_name[] = "private_message";
     mgr.createParticipant(partition_name);
 
     private_messageTypeSupport_var st = new private_messageTypeSupport();
     mgr.registerType(st.in());
 
 
     char topic_name[] = "private_Msg";
     mgr.createTopic(topic_name);
 
     mgr.createPublisher();
 
     bool auto_dispose_unregistered_instances = false;
     mgr.createWriter(auto_dispose_unregistered_instances);
 
     dWriter = mgr.getWriter();
     _private_messageDataWriter = private_messageDataWriter::_narrow(dWriter.in());
 
 
     m_instance = new private_message();
     *m_instance = msg; 
     userHandle = _private_messageDataWriter->register_instance(*m_instance);

}
TSN::private_message Message::construct_message(char * reciever_uuid, char * sender_uuid,
                                                std::string message_body, long date_of_creation)
{
    TSN::private_message temp;
    strncpy(temp.receiver_uuid, reciever_uuid,37);
    strncpy(temp.sender_uuid, sender_uuid, 37);
    temp.message_body = message_body.c_str();
    temp.date_of_creation = date_of_creation;
    return temp;
}
