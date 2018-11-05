#ifndef __USER_H
#define __USER_H
#include <boost/uuid/uuid.hpp>
#include <boost/uuid/uuid_generators.hpp>
#include <boost/uuid/uuid_io.hpp>
#include "Post.h"
#include <map>
#include "DDSEntityManager.h"
#include "ccpp_tsn.h"
#include "dds_io.h"
class User
{
public:
	void set_interests(std::vector<std::string> input_interests);
	std::vector<std::string> get_interests();
    void set_first_name(std::string fname);
    std::string get_first_name();
    void set_last_name(std::string lname);
    std::string get_last_name();
    void set_date(long birth);
    long get_birth_date();
    void set_post(std::vector<Post> post);
	void set_map(std::map<int, std::string>& user_post_map);
    std::map<int, std::string> get_map();
    void set_user_information();
    void write_to_file();
    void set_user_uuid(std::string uuid_string);
    char * return_uuid();
    TSN::user_information initialize();
    void publishEvent(TSN::user_information msgInstance);
private:
    std::map<int, std::string> userPostMap;
	std::vector<std::string> interests;
    std::string first_name;
    std::string last_name;
    long birth_date;
    char uuidCharArray[37];
    std::vector<Post> user_posts;
};
#endif

