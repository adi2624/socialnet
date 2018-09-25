#include<iostream>
#include<string>
#include "Response.h"
using namespace DDS;
using namespace TSN;
int responsePublisher(int argc, char* argv[])
{
	DDSEntityManager mgr;
	mgr.createParticipant("Response example");
	responseTypeSupport_var mt = new responseTypeSupport();
	mgr.registerType(mt.in());
	char topic_name[] = "response";
	mgr.createTopic(topic_name);
	mgr.createPublisher();
	bool autodispose_unregistered_instances = false;
  	mgr.createWriter(autodispose_unregistered_instances);
  	DataWriter_var writer = mgr.getWriter();
  	responseDataWriter_var responseWriter = responseDataWriter::_narrow(writer.in());

  	// send the post data here 

}
int responseSubsriber(int argc, char* argv[])
{
	// How i think this function works
	DDSEntityManager mgr;
	mgr.createParticipant("Response sub example");
	responseSeq resList;
	SampleInfoSeq infoSeq;

	responseTypeSupport_var mt = new responseTypeSupport();
	mgr.registerType(mt.in());
	char topic_name[] = "response_Msg";
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
	    checkStatus(status, "requestDataReader::take");
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
	    checkStatus(status, "requestDataReader::return_loan");
	    //os_nanoSleep(delay_200ms);
	    ++count;
	}

	  //os_nanoSleep(delay_2ms);

	  //cleanup
	  mgr.deleteReader();
	  mgr.deleteSubscriber();
	  mgr.deleteTopic();
	  mgr.deleteParticipant();
	  std::cout<<"The subscriber is ending"<<std::endl;
	  return 0;

}
int main()
{
	return 0;
}
