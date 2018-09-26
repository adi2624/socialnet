#include <iostream>
#include <string>
#include <sstream>
#include "Response.h"
#include "User.h"

using namespace DDS;
using namespace TSN;

/*
int responsePublisher(int argc, char* argv[])
{
	DDSEntityManager mgr2;
	mgr2.createParticipant("Response example");
	responseTypeSupport_var mt = new responseTypeSupport();
	mgr2.registerType(mt.in());
	char topic_name[] = "response_Msg";
	mgr2.createTopic(topic_name);
	mgr2.createPublisher();
	bool autodispose_unregistered_instances = false;
  mgr2.createWriter(autodispose_unregistered_instances);
  DataWriter_var writer = mgr2.getWriter();
  responseDataWriter_var responseWriter = responseDataWriter::_narrow(writer.in());

	// send the post data here 
	response user_response;
	std::ifstream input_file;
  input_file.open("hello.tsn",ios::in);
  char uuidCharArray[17];      
  input_file.getline(uuidCharArray,25);
  strncpy(user_response.uuid,uuidCharArray + 5, 22);
  if(is_done())
  {
    std::cout << "HERE";
  	for(const auto& val: post_id_vec)
  	{
  		// TODO: send one item per second
  		user_response.post_id = val;
  		user_response.post_body = load_post(val).c_str();
      std::cout << "Sending:" << uuidCharArray << user_response.post_id << user_response.post_body << std::endl;
  		ReturnCode_t status = responseWriter->write(user_response, DDS::HANDLE_NIL);
  		checkStatus(status, "responseDataWriter::write");
  	}
  }

  mgr2.deleteWriter();

	 
	mgr2.deletePublisher();
	
	mgr2.deleteTopic();

	  
	mgr2.deleteParticipant();

	return 0;
}
*/

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
