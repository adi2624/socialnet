#include <iostream>
#include <string>
#include <sstream>
#include "Response.h"
#include "User.h"

using namespace DDS;
using namespace TSN;

std::string load_post(int post_no)
{
int number=0,i=0;
  bool found_post = false;
  std::string line,post;
  std::ifstream get_post("hello.tsn");
  if (!get_post.is_open())
    perror("error while opening file");
  //get_post.open("hello.tsn",ios::in);
  if (get_post.bad())
    perror("error while reading file");
  while(std::getline(get_post,line))
  {
    std::istringstream iss(line);
    std::string c;                          //GET LINE AND PUSH INTO STRINGSTREAM.
    c=iss.str();                              
   // std::cout<<"String received "<<c<<endl;  //Debugging string
    std::size_t pos = c.find("SNO:");
    std::size_t pos2=c.find("POST:");           //FIND DATA after POST:
    if(i!=0)      //IGNORE UUID AT TOP OF FILE
    { 
    std::string number_string = c.substr(pos+4,pos2-4);       
   // std::cout<<"Number String "<<number_string<<std::endl;   //please.ignore(#debug) FIND NUMBER BETWEEN SNO: and POST:
    number = std::stoi(number_string);
    }
    i++;
    if(number==post_no)
    {
      std::string final_post_text = c.substr(pos2+4);
    std::cout<<"Final text:"<<final_post_text<<std::endl;   //RETURN FOUND POST DATA
    return final_post_text;
    }
    
  }
  if(found_post==false)
  {
    return "Fail";    //If nothing is returned upon search, a segmentation fault will occur.
  }
}

int Response::responsePublisher(int argc, char* argv[])
{
	DDSEntityManager mgr;
	mgr.createParticipant("Response example");
	responseTypeSupport_var mt = new responseTypeSupport();
	mgr.registerType(mt.in());
	char topic_name[] = "response_Msg";
	mgr.createTopic(topic_name);
	mgr.createPublisher();
	bool autodispose_unregistered_instances = false;
  	mgr.createWriter(autodispose_unregistered_instances);
  	DataWriter_var writer = mgr.getWriter();
  	responseDataWriter_var responseWriter = responseDataWriter::_narrow(writer.in());

  	// send the post data here 
  	response user_response;
  	std::ifstream input_file;
    input_file.open("hello.tsn",ios::in);
    char uuidCharArray[17];      
    input_file.getline(uuidCharArray,25);
    strncpy(user_response.uuid,uuidCharArray + 5, 22);

    if(is_done)
    {
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

    mgr.deleteWriter();

	  /* Remove the Publisher. */
	  mgr.deletePublisher();
	  /* Remove the Topics. */
	  mgr.deleteTopic();

	  /* Remove Participant. */
	mgr.deleteParticipant();

	return 0;
}
int Response::responseSubsriber(int argc, char* argv[])
{
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

	  //os_nanoSleep(delay_2ms);

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

  Response temp;
  std::cout << "Starting listener.." << std::endl;
  std::string answer;
  std::cout << "Do you want to start sub?(y/n)";
  std::cin >> answer;
  if(answer == "y")
  {
    temp.responseSubsriber(argc, argv);
  }
  else
  {
    while(1)temp.responsePublisher(argc,argv);
  }
	return 0;
}
