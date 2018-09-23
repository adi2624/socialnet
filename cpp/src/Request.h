#include<iostream>
#include<string>
#include "DDSEntityManager.h"
#include "ccpp_tsn.h"
#include "os.h"
#include "example_main.h"
#include<fstream>
#include "User.h"
std::vector<User> list_pub_users();
int requestPublisher(int argc, char* argv[]);
int requestSubscriber(int argc, char* argv[]);