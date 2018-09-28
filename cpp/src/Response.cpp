#include <iostream>
#include <string>
#include <sstream>
#include "Response.h"
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

int main(int argc, char* argv[])
{
  std::cout << "Starting response subscriber ..." << std::endl;
  responseSubsriber(argc,argv); 
	return 0;
}
