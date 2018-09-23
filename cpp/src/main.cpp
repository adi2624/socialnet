#include <string>
#include <sstream>
#include <iostream>
#include<vector>
#include<cstdlib>
#include<string>
#include<thread>
#include<fstream>
#include "DDSEntityManager.h"
#include "ccpp_tsn.h"
#include "os.h"
#include "User.h"
#include "example_main.h"
#include <boost/uuid/uuid.hpp>            // uuid class
#include <boost/uuid/uuid_generators.hpp> // generators
#include <boost/uuid/uuid_io.hpp>  
#include <boost/lexical_cast.hpp>
using namespace DDS;
using namespace TSN;
 int sno=0;        //KEEPS TRACK OF SERIAL NO: DO NOT REMOVE IT'S A GLOBAL VARIABLE
void make_post(char string[17],int sno);
int user_informationPublisher(int argc, char *argv[])
{
  os_time delay_1s = { 1, 0 };
  DDSEntityManager mgr;

  // create domain participant
  mgr.createParticipant("TSN example");

  //create type
 user_informationTypeSupport_var mt = new user_informationTypeSupport();
  mgr.registerType(mt.in());

  //create Topic
  char topic_name[] = "tsn_Msg";
  mgr.createTopic(topic_name);

  //create Publisher
  mgr.createPublisher();

  // create DataWriter :
  // If autodispose_unregistered_instances is set to true (default value),
  // you will have to start the subscriber before the publisher
  bool autodispose_unregistered_instances = false;
  mgr.createWriter(autodispose_unregistered_instances);

  // Publish Events
  DataWriter_var dwriter = mgr.getWriter();
user_informationDataWriter_var TSNWriter = user_informationDataWriter::_narrow(dwriter.in());

Post my_post;
std::string temp_user;
cout<<"Enter the first name of the User"<<endl;
cin>>temp_user;
my_post.set_first_name(temp_user);

cout<<"Enter the last name of the user"<<endl;
cin>>temp_user;
my_post.set_last_name(temp_user);

std::vector<std::string> Interests;
Interests.push_back("Swimming");
Interests.push_back("Hockey");
Interests.push_back("Netflix");
my_post.set_interest(Interests);
user_information msgInstance; /* Example on Stack */
/* Begin of Initialization of Booost UUID */
std::cout<<"The following is your complete USERID generated by BOOST :\n";
std::ifstream myfile;
myfile.open("hello.tsn",ios::in);
char uuidCharArray[17];
bool is_empty=true;
while(!myfile.eof())
{ 
  std::string data;
  myfile>>data;
  if(data=="")            //CODE TO CHECK IF FILE IS EMPTY
  {
    break;
  }
  is_empty = false; 
}
myfile.close();
//std::cout<<"mai yaha hu "<<is_empty<<std::endl;

if (is_empty)
{
    // do your error handling

   // Empty File
  std::ofstream output;                                       //Generate a new UUID if file is empty.
  output.open("hello.tsn",ios::out);
  std::cout<<"The file is empty. Generating new UUID.....\n";
    boost::uuids::uuid uuid = boost::uuids::random_generator()();
    std::string uuid_string = to_string(uuid);
    for(int i = 0; i <=17;i++)
    {
        uuidCharArray[i] = uuid_string[i];
        if(i == 17)
        {
            uuidCharArray[i] = '\0';
        }
    }

  output<<"UUID:"<<uuidCharArray<<std::endl;
  output.close();
  sno++;    //INCREMENT SERIAL NO TO POST 1.
}
else
{
  std::cout<<"UUID FOUND. Loading from file"<<std::endl;
  std::ifstream input;
  input.open("hello.tsn",ios::in);
  char uuidCharArray[17];                                   //LOAD GENERATED UUID AND COUNT THE NO OF POSTS IN THE DISK.
  input.getline(uuidCharArray,25);
  std::cout<<"Loaded: "<<uuidCharArray<<std::endl;
  while(!input.eof())
  {
    std::string garbage_value;
    std::getline(input,garbage_value);
    sno++;
  }
  input.close();
}

strncpy(msgInstance.uuid,uuidCharArray + 5, 22);


/*  End of Boost UUID  */
  msgInstance.first_name = my_post.get_first_name().c_str();
  msgInstance.last_name = my_post.get_last_name().c_str();
  
  //std::cout<<msgInstance.uuid<<endl;
  msgInstance.interests.length(my_post.get_interests().size());       //SET UP VALUES IN user_information STRUCT FOR DDS.
  for(int i=0;i<my_post.get_interests().size();i++)
  {
      msgInstance.interests[i] = my_post.get_interests().at(i).c_str();
  }
  
  std::cout<<my_post.get_interests().size()<<endl;
 
  
  cout << "=== [Publisher] writing a message containing :" << endl;
  cout << "    userID  : " << msgInstance.uuid << endl;
  cout << "    Name : \"" << msgInstance.first_name  <<" "<< msgInstance.last_name << "\"" << endl;
  cout<<"The following are the User's interests "<<endl;
  for(int i=0;i<my_post.get_interests().size();i++)
  {
  cout << msgInstance.interests[i]<<endl;
  }
  
  ReturnCode_t status = TSNWriter->write(msgInstance, DDS::HANDLE_NIL);
  checkStatus(status, "MsgDataWriter::write");
  os_nanoSleep(delay_1s);
  std::cout<<"Would you like to make a post (Y/N)?"<<endl;  //Ask a user to make a post.
  std::string temp_post;
  cin>>temp_post;
 
  if(temp_post=="Y")
  {
    make_post(msgInstance.uuid, sno);
  }

  /* Remove the DataWriters */
  mgr.deleteWriter();

  /* Remove the Publisher. */
  mgr.deletePublisher();
  /* Remove the Topics. */
  mgr.deleteTopic();

  /* Remove Participant. */
  mgr.deleteParticipant();

  return 0;
}
int user_informationSubscriber(int argc, char *argv[])
{
  os_time delay_2ms = { 0, 2000000 };
  os_time delay_200ms = { 0, 200000000 };
  user_informationSeq msgList;
  SampleInfoSeq infoSeq;

  DDSEntityManager mgr;

  // create domain participant
  mgr.createParticipant("TSN example");

  //create type
 user_informationTypeSupport_var mt = new user_informationTypeSupport();
  mgr.registerType(mt.in());

  //create Topic
  char topic_name[] = "tsn_Msg";
  mgr.createTopic(topic_name);

  //create Subscriber
  mgr.createSubscriber();

  // create DataReader
  mgr.createReader();

  DataReader_var dreader = mgr.getReader();
  user_informationDataReader_var HelloWorldReader = user_informationDataReader::_narrow(dreader.in());
  checkHandle(HelloWorldReader.in(), "user_informationDataReader::_narrow");

  cout << "=== [Subscriber] Ready ..." << endl;

  bool closed = false;
  ReturnCode_t status =  - 1;
  int count = 0;
  User static_user;
  std::vector<std::string> user_interests;
  while (!closed && count < 1500) // We dont want the example to run indefinitely
  {
    status = HelloWorldReader->take(msgList, infoSeq, LENGTH_UNLIMITED,
      ANY_SAMPLE_STATE, ANY_VIEW_STATE, ANY_INSTANCE_STATE);
    checkStatus(status, "user_informationDataReader::take");
    for (DDS::ULong j = 0; j < msgList.length(); j++)
    {
      cout << "=== [Subscriber] message received :" << endl;
      cout << "    userID  : " << msgList[j].uuid << endl;
      cout << "    Name : \"" << msgList[j].first_name <<" "<< msgList[j].last_name<< "\"" << endl;
      std::string fname(msgList[j].first_name);
      static_user.set_first_name(fname);
      std::string lname(msgList[j].last_name);
      static_user.set_last_name(lname);

      cout << " The following are the user's "<< msgList[j].interests.length()<<" interests " << endl;
      for (DDS::ULong k = 0; k < msgList[j].interests.length(); k++)
      {
         cout << "   " << k+1 << "  " << msgList[j].interests[k] << endl;
         std::string interest(msgList[j].interests[k]);
         user_interests.push_back(interest);
      }
      closed = true;
    }
    static_user.set_interests(user_interests);
    static_user.write_to_file();
    status = HelloWorldReader->return_loan(msgList, infoSeq);
    checkStatus(status, "user_informationDataReader::return_loan");
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
void make_post(char string[17], int sno)
{
  std::ofstream myfile;
  myfile.open("hello.tsn",ios::app);
  std::string post_text;
  std::cout<<"Enter the post text"<<std::endl;
  cin.ignore();
  getline(std::cin,post_text);
  myfile<<"SNO:"<<sno<<" POST:"<<post_text<<endl;
  myfile.close();
}
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
std::vector<std::string> list_all_users()
{
  std::ifstream users_file("users.tsn");
  std::string input,fname,lname;
  std::vector<std::string> users_vector;
  while(!users_file.eof()) 
  {
  std::getline(users_file,input);
  std::stringstream ss;
  ss<<input;
  ss>>fname>>lname;
  fname =fname.substr(1);
  users_vector.push_back(fname+" "+lname);
  }
  
  return users_vector;
  

}
void run_subscriber(int argc, char *argv[])
{
  while(1)
  {
  user_informationSubscriber(argc,argv);
  sleep(10);
  }
}
int OSPL_MAIN (int argc, char *argv[])
{
    std::vector<std::string> topic_names;
    std::string user_info("\"user_information\"");
     std::cout<<"Welcome to the Social Network!"<<std::endl;
    std::cout<<"The program is listening for UserInformation published on the "<<user_info<<" topic"<<std::endl;
    std::cout<<"Starting Subscriber ........ "<<std::endl;
     std::string input="N";
        user_informationPublisher(argc,argv); 
           //std::thread second(run_subscriber,argc,argv);

           do
           {
                    //TESTING: RUN PUBLISHER INFINITE LOOP.
           std::cout<<"Publishing has finished, would you like to run the publisher again?(Y/N)"<<std::endl;
           std::cin>>input;
           std::cout<<"Remember that it takes 30 seconds before a subscribed message is received and only shows up after the (y/n) to run publisher or not"<<std::endl;
           }while(input=="Y");
         
      
        
        //first.join();   IMPORTANT! THIS NEEDS TO BE JOINED LATER.
        

        //std::cout<<"Joining has finished"<<std::endl;
          
         
      /*

      TESTING FOR LIST ALL USERS. WRITE_TO_FILE() HAS BEEN DEACTIVATED HERE.

     std::string temp;
     temp=load_post(1); //Make sure to change the number of the post that you want to find.
     std::cout<<"Found :"<<temp<<std::endl;
     std::vector<std::string> users_list = list_all_users();
     for(int i=0;i<users_list.size();i++)
     {
       std::cout<<users_list.at(i)<<std::endl;
     }
     */
     // second.join();
     return 0;

}

   