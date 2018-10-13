#include <iostream>
#include <string>
#include <sstream>

#include "Response.h"
#include "os.h"
#include "User.h"

using namespace DDS;
using namespace TSN;

int responseSubsriber(int argc, char* argv[])
{
  	os_time delay_2ms = { 0, 2000000 };
    os_time delay_200ms = { 0, 200000000 };
	DDSEntityManager mgr;
	mgr.createParticipant("Response example");
	responseSeq resList;
	SampleInfoSeq infoSeq;

	responseTypeSupport_var mt = new responseTypeSupport();
	mgr.registerType(mt.in());
	char topic_name[] = "ResponseData_Msg";
	mgr.createTopic(topic_name);
	mgr.createSubscriber();
	mgr.createReader();
	DataReader_var dreader = mgr.getReader();
	responseDataReader_var PublisherReader = responseDataReader::_narrow(dreader.in());
	checkHandle(PublisherReader.in(), "responseDataReader::_narrow");
	cout << "=== [Subscriber] Ready ..." << endl;
  bool closed = false;
  ReturnCode_t status =  - 1;
  int count = 0;
  
	while (!closed && count < 1500) // We dont want the example to run indefinitely
  {
	    status = PublisherReader->take(resList, infoSeq, LENGTH_UNLIMITED,
	    ANY_SAMPLE_STATE, ANY_VIEW_STATE, ANY_INSTANCE_STATE);
	    checkStatus(status, "responseDataReader::take");
	    for (DDS::ULong j = 0; j < resList.length(); j++)
	    {
			//CODE TO CHECK THE CORRECT UUID's ARE BEING SENT AND RECEIVED.
	      std::cout << "=== [Subscriber] message received :" << std::endl;
	      std::cout << "    Sender userID  : " << resList[j].uuid << std::endl;
	      std::cout << "    Serial number  : " << resList[j].post_id << std::endl;
	      std::cout << "    Post body      : " << resList[j].post_body << std::endl;
	      closed = true;
	    }
	   
	    status = PublisherReader->return_loan(resList, infoSeq);
	    checkStatus(status, "responseDataReader::return_loan");
	    //os_nanoSleep(delay_200ms);
	    ++count;
	}

	  os_nanoSleep(delay_2ms);

	  //cleanup
	  mgr.deleteReader();
	  mgr.deleteSubscriber();
	  mgr.deleteTopic();
	  mgr.deleteParticipant();
	  std::cout<<"The subscriber is ending"<<std::endl;
	  return 0;

}

// This works now but we need to ge tthis information from the request
//In the code below uuidd has to be equal to fulfiller uuid in request

int responsePublisher(int argc, char* argv[])
{
	os_time delay_2s = {2, 0};
	DDSEntityManager mgr;

	char partition_name[] = "Response example";
	mgr.createParticipant(partition_name);

	responseTypeSupport_var mt = new responseTypeSupport();
	mgr.registerType(mt.in());


	char topic_name[] = "ResponseData_Msg";
	mgr.createTopic(topic_name);

	mgr.createPublisher();
    bool autodispose_unregistered_instances = false;
    mgr.createWriter(autodispose_unregistered_instances);


	DataWriter_var dwriter = mgr.getWriter();
	responseDataWriter_var responseWriter = responseDataWriter::_narrow(dwriter.in());

    response D;
    std::string  uuid = "d21633d5-12fb-4c93-a4a4-a56f06b7ba24";
    strncpy (D.uuid,uuid.c_str(),sizeof(D.uuid));
    D.uuid[sizeof(D.uuid)-1] = '\0';
    D.post_id = 1;
    D.post_body = DDS::string_dup("this is a sample post.....");
    D.date_of_creation = 1000;
	std::cout << "=========== Response Publisher writing response containing :" << std::endl;
	std::cout << "Message: " << D.post_body << std::endl;


	ReturnCode_t status = responseWriter->write(D,DDS::HANDLE_NIL);
	checkStatus(status, "responseDataWriter::write");
	os_nanoSleep(delay_2s);

	mgr.deleteWriter();
	mgr.deletePublisher();
	mgr.deleteTopic();
	mgr.deleteParticipant();
}

int main(int argc, char* argv[])
{
	responsePublisher(argc,argv);
	std::cout << "Starting response subscriber ..." << std::endl;


    responseSubsriber(argc,argv);
	return 0;
}
