#include"Request.h"
#include "Response.h"
using namespace DDS;
using namespace TSN;
/*////////////////////////////////////
/
/ LOAD USERS FROM THE USERS.TSN FILE INTO MEMORY
/   
/
////////////////////////////////////*/
std::vector<User> list_pub_users()
{
	
	std::vector<User> name_user;		//EXPORT A VECTOR OF USERS AFTER LOADING ALL USERS FROM USERS.TSN
	std::string temp_line;
	std::ifstream file("users.tsn");
	int i=0;
	while(!file.eof())
	{
		User my_user;
		std::getline(file,temp_line);
		if(temp_line!="")		//Don't run loop on empty newline.
		{
		std::size_t pos_lname = temp_line.find("LNAME:");
		std::size_t pos_fname = temp_line.find("FNAME:");
		//std::cout<<"Space found at "<<pos_fname<<std::endl;
		std::size_t pos_uuid = temp_line.find("UUID:");
		std::size_t pos_interests = temp_line.find("Interests:");
		my_user.set_first_name(temp_line.substr((pos_fname+6),pos_lname-(pos_fname+6)));
		my_user.set_last_name(temp_line.substr((pos_lname+6),(pos_interests-1)-(pos_lname+5)));
		my_user.set_user_uuid(temp_line.substr(pos_uuid+5));
		name_user.push_back(my_user);
		//std::cout<<"Name: "<<temp_line.substr(pos+1,pos_name-1)<<"UUID: "<<temp_line.substr(pos_uuid+5);
		//name_user.push_back(temp_line.substr(pos+1,pos_name-1)+temp_line.substr(pos_uuid+5));
		}
	}
	file.close();
	return name_user;
}
/*////////////////////////////////////
/
/       REQUEST PUBLISHER
/   
/
////////////////////////////////////*/
int requestPublisher(int argc, char* argv[])
{
	os_time delay_1s = { 1, 0 };
  	DDSEntityManager mgr;
	mgr.createParticipant("Publisher Example");			//POSSIBLE BUG HERE. COMMENTING OUT EVERYTHING WITH mgr in it MAKES THE PROGRAM RUN.
	requestTypeSupport_var mt = new requestTypeSupport();
	mgr.registerType(mt.in());
	
	std::cout<<"Was here"<<std::endl;
	char topic_name[] = "tsn_publisher";
	mgr.createTopic(topic_name);

	mgr.createPublisher();

	bool autodispose_unregistered_instances = false;
  	mgr.createWriter(autodispose_unregistered_instances);
  	DataWriter_var writer = mgr.getWriter();
  	requestDataWriter_var PublisherWriter = requestDataWriter::_narrow(writer.in());



	std::cout<<"Please select user from below to send a request to :"<<std::endl;
	std::vector<User> name_user;
	name_user = list_pub_users();		//LIST ALL THE USERS TO CHOOSE FROM.
	int input;
	for(int i=0;i<name_user.size();i++)
	{
		std::cout<<"USER "<<i+1<<std::endl;
		std::cout<<"FNAME: "<<name_user.at(i).get_first_name()<<std::endl;
		std::cout<<"LNAME: "<<name_user.at(i).get_last_name()<<std::endl;
		std::cout<<"UUID: "<<name_user.at(i).return_uuid()<<std::endl;
	}
	std::cout<<"Enter the user number"<<std::endl;	//ENTER THE USER NUMBER.
	std::cin>>input;
	node_request user_request;
	strcpy(user_request.fulfiller_uuid , name_user.at(input-1).return_uuid());
	std::cout<<"The received request was for UUID:"<<user_request.fulfiller_uuid<<std::endl; //OUTPUT THE UUID of the Intended Receiver.
	std::cout<<"Enter the serial no of the post that you want from this user"<<std::endl;
	std::cin>>input;
	user_request.requested_posts.length(1);
	user_request.requested_posts[0] = input;
	std::cout<<user_request.requested_posts[0];
	

	
	//LOAD LOCAL USER'S UUID FROM HELLO.TSN
	std::ifstream input_file;
    input_file.open("hello.tsn",ios::in);
    char uuidCharArray[17];      
    input_file.getline(uuidCharArray,25);
    request this_user_request;
    strncpy(this_user_request.uuid,uuidCharArray + 5, 22);
	this_user_request.user_requests.length(1);
	this_user_request.user_requests[0] = user_request;		//COPY NODE REQUEST INTO THE FINAL REQUEST SEQUENCE.

	//TESTING CODE
	std::cout<<"MY UUID :"<<this_user_request.uuid<<"REQUESTED POST FROM UUID : "<<this_user_request.user_requests[0].fulfiller_uuid<<std::endl;
	cout << "=== [Publisher] writing a message containing :" << endl;
 	 cout << "    userID  : " << this_user_request.uuid << std::endl;
  	cout << "    Fulfiller UUID:" << this_user_request.user_requests[0].fulfiller_uuid  <<"and has requested post_no: "<< this_user_request.user_requests[0].requested_posts[0] << "\"" << endl;
	ReturnCode_t status = PublisherWriter->write(this_user_request, DDS::HANDLE_NIL);
  checkStatus(status, "requestDataWriter::write");
  os_nanoSleep(delay_1s);
  mgr.deleteWriter();

  /* Remove the Publisher. */
  mgr.deletePublisher();
  /* Remove the Topics. */
  mgr.deleteTopic();

  /* Remove Participant. */
  mgr.deleteParticipant();
	return 0;
}
/*////////////////////////////////////
/
/       REQUEST SUBSCRIBER
/   
/
////////////////////////////////////*/
int requestSubscriber(int argc, char* argv[])
{
  os_time delay_2ms = { 0, 2000000 };
  os_time delay_200ms = { 0, 200000000 };
  requestSeq reqList;
  SampleInfoSeq infoSeq;
  DDSEntityManager mgr;
  mgr.createParticipant("Publisher Example");
  requestTypeSupport_var mt = new requestTypeSupport();
  mgr.registerType(mt.in());
  char topic_name[] = "tsn_publisher";
	mgr.createTopic(topic_name);
	mgr.createSubscriber();
	mgr.createReader();
	 DataReader_var dreader = mgr.getReader();
	 requestDataReader_var PublisherReader = requestDataReader::_narrow(dreader.in());
  checkHandle(PublisherReader.in(), "requestDataReader::_narrow");
  cout << "=== [Subscriber] Ready ..." << endl;
  bool closed = false;
  ReturnCode_t status =  - 1;
  int count = 0;
  	// same deal, we want this user uuid
  	Response new_response;
  	std::ifstream input_file;
    input_file.open("hello.tsn",ios::in);
    char uuidCharArray[17];      
    input_file.getline(uuidCharArray,25);
    request this_user_request;
    strncpy(this_user_request.uuid,uuidCharArray + 5, 22);
    new_response.set_this_uuid(this_user_request.uuid);
   while (!closed && count < 1500) // We dont want the example to run indefinitely
  {
    status = PublisherReader->take(reqList, infoSeq, LENGTH_UNLIMITED,
      ANY_SAMPLE_STATE, ANY_VIEW_STATE, ANY_INSTANCE_STATE);
    checkStatus(status, "requestDataReader::take");
    for (DDS::ULong j = 0; j < reqList.length(); j++)
    {
		//CODE TO CHECK THE CORRECT UUID's ARE BEING SENT AND RECEIVED.
      cout << "=== [Subscriber] message received :" << endl;
      cout << "    Sender userID  : " << reqList[j].uuid << endl;
      cout << "    IS THIS MY UUID? : \"" << reqList[j].user_requests[0].fulfiller_uuid <<"and post_no"<<reqList[j].user_requests[0].requested_posts[0]<<std::endl;
      if( strcmp(this_user_request.uuid,reqList[j].user_requests[0].fulfiller_uuid) )
      {
      	new_response.add_uuid_to_vec(reqList[j].user_requests[0].requested_posts[0]);
      }
      new_response.set_is_done(true);
      closed = true;
    }
   
    status = PublisherReader->return_loan(reqList, infoSeq);
    checkStatus(status, "requestDataReader::return_loan");
    os_nanoSleep(delay_200ms);
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
/*////////////////////////////////////
/
/       MAIN
/   
/
////////////////////////////////////*/
int main(int argc, char* argv[])
{
		
	int temp = requestPublisher(argc,argv); //START PUBLISHER ONCE.
	std::cout<<"Do you want to start the subscriber?(Y/N)"<<std::endl;
	std::string input;
	std::cin>>input;
	if(input=="Y")
	{
		int return_code = requestSubscriber(argc,argv);	//RUN SUBSCRIBER
	}

	/*
	TESTING NAMES IN USER DATA STRUCTURE
	for(int i=0;i<name_user.size();i++)
	{
		std::cout<<name_user.at(i).get_first_name()<<name_user.at(i).get_last_name()<<name_user.at(i).return_uuid()<<std::endl;
	}
	*/
	return 0;
}
