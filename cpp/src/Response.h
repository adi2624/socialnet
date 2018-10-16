#ifndef _RESPONSE_H
#define _RESPONSE_H

#include <iostream>
#include <string>
#include <sstream>
#include <fstream>
#include "DDSEntityManager.h"
#include "ccpp_tsn.h"
#include "os.h"
#include "example_main.h"
#include "User.h"

using namespace TSN;

class Response 
{
private:
	DDSEntityManager mgr;
	DataWriter_var dWriter;
	responseDataWriter_var responseDataWriter;
	InstanceHandle_t userHandle;
	response * m_instance;
	ReturnCode_t status;
	void initPublisher(std::string uuid, int post_id, long date, std::string post);


public:
	Response(std::string uuid, int post_id, long date, std::string post);
	void publishEvent(std::string uuid, int post_id, long date, std::string post);
	void dispose();

};

#endif