/*
 *                         OpenSplice DDS
 *
 *   This software and documentation are Copyright 2006 to 2013 PrismTech
 *   Limited and its licensees. All rights reserved. See file:
 *
 *                     $OSPL_HOME/LICENSE
 *
 *   for full copyright notice and license terms.
 *
 */

/************************************************************************
 * LOGICAL_NAME:    HelloWorldDataPublisher.cpp
 * FUNCTION:        OpenSplice Tutorial example code.
 * MODULE:          Tutorial for the C++ programming language.
 * DATE             September 2010.
 ************************************************************************
 *
 * This file contains the implementation for the 'HelloWorldDataPublisher' executable.
 *
 ***/
#include <string>
#include <sstream>
#include <iostream>
#include "DDSEntityManager.h"
#include "ccpp_tsn.h"
#include "os.h"
#include "Post.cpp"
#include "example_main.h"
#include <boost/uuid/uuid.hpp>            // uuid class
#include <boost/uuid/uuid_generators.hpp> // generators
#include <boost/uuid/uuid_io.hpp>  
#include <boost/lexical_cast.hpp>
using namespace DDS;
using namespace TSN;

/* entry point exported and demangled so symbol can be found in shared library */
extern "C"
{
  OS_API_EXPORT
  int UserInformationSubscriber(int argc, char *argv[]);
}

int UserInformationSubscriber(int argc, char *argv[])
{
  os_time delay_1s = { 1, 0 };
  DDSEntityManager mgr;

  // create domain participant
  mgr.createParticipant("HelloWorld example");

  //create type
 UserInformationTypeSupport_var mt = new UserInformationTypeSupport();
  mgr.registerType(mt.in());

  //create Topic
  char topic_name[] = "HelloWorldData_Msg";
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
UserInformationDataWriter_var HelloWorldWriter = UserInformationDataWriter::_narrow(dwriter.in());

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
std::cout<<"SIZE OF INTERESTS is "<<Interests.size()<<endl;
my_post.set_interest(Interests);
UserInformation msgInstance; /* Example on Stack */
/* Begin of Initialization of Booost UUID */
std::cout<<"IAm";
boost::uuids::uuid uuid = boost::uuids::random_generator()();
std::stringstream ss;
ss << uuid;//Code to generate boost string using stringstream
const std::string tmp = ss.str(); 
const char * value = tmp.c_str();
std::cout<<"ORIGINAL: "<<value<<endl;                           
std::string temp = value;
std::cout<<"TEMP SIZE : "<<temp.size()<<endl;
for(int i=0;i<16;i++)
{
  msgInstance.uuid[i] = temp.at(i);       //Truncation of BOOST UUID to 16 byte C Char Array and addition of null character
}

msgInstance.uuid[17]='\0';
/*  End of Boost UUID  */
  msgInstance.first_name = my_post.get_first_name().c_str();
  msgInstance.last_name = my_post.get_last_name().c_str();
  std::cout<<msgInstance.uuid<<endl;
  std::cout<<my_post.get_interests().size()<<endl;
  for(int i=0;i<my_post.get_interests().size();i++)
  {
      //std::cout<<my_post.get_interests().at(i).c_str()<<endl;
       //msgInstance.interests[i] = my_post.get_interests().at(i).c_str();
  }
 
  cout << "=== [Publisher] writ)ing a message containing :" << endl;
  cout << "    userID  : " << msgInstance.uuid << endl;
  cout << "    Name : \"" << msgInstance.first_name  <<" "<< msgInstance.last_name << "\"" << endl;
  

  ReturnCode_t status = HelloWorldWriter->write(msgInstance, DDS::HANDLE_NIL);
  checkStatus(status, "MsgDataWriter::write");
  os_nanoSleep(delay_1s);

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

int OSPL_MAIN (int argc, char *argv[])
{
  return UserInformationSubscriber (argc, argv);
}
