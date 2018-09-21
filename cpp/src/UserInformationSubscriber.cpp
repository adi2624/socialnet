
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
 * LOGICAL_NAME:    HelloWorldDataSubscriber.cpp
 * FUNCTION:        OpenSplice HelloWorld example code.
 * MODULE:          HelloWorld for the C++ programming language.
 * DATE             September 2010.
 ************************************************************************
 *
 * This file contains the implementation for the 'HelloWorldDataSubscriber' executable.
 *
 ***/
#include <string>
#include <sstream>
#include <iostream>
#include "DDSEntityManager.h"
#include "ccpp_tsn.h"
#include "os.h"
#include "example_main.h"

using namespace DDS;
using namespace TSN;

/* entry point exported and demangled so symbol can be found in shared library */
extern "C"
{
  OS_API_EXPORT
  int user_informationSubscriber(int argc, char *argv[]);
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
      cout << " The following are the user's "<< msgList[j].interests.length()<<" interests " << endl;
      for (DDS::ULong k = 0; k < msgList[j].interests.length(); k++)
      {
         cout << "   " << k+1 << "  " << msgList[j].interests[k] << endl;
}
      closed = true;
    }
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

  return 0;
}

int OSPL_MAIN (int argc, char *argv[])
{
  return user_informationSubscriber (argc, argv);
}
