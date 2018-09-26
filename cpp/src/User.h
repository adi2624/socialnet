#ifndef __USER_H
#define __USER_H
#include <boost/uuid/uuid.hpp>
#include <boost/uuid/uuid_generators.hpp>
#include <boost/uuid/uuid_io.hpp>
#include "Post.h"
#include <map>
class User
{
public:
	// proposed changes 
	void set_interests(std::vector<std::string> input_interests) { interests = input_interests; }
	std::vector<std::string> get_interests() { return interests; }
    void set_first_name(std::string fname) { first_name = fname;} 
    std::string get_first_name() { return first_name; }
    void set_last_name(std::string lname) { last_name = lname; }
    std::string get_last_name() { return last_name; }
    void set_date(long birth) { birth_date = birth; }
    long get_birth_date() { return birth_date; }
	//
    void set_post(std::vector<Post> post) { user_posts = post; }
	void set_map(std::map<int, std::string>& user_post_map) { userPostMap = user_post_map; }
    std::map<int, std::string> get_map() { return userPostMap; }
    void set_user_information();
    void write_to_file();
    void set_user_uuid(std::string uuid_string);
    char * return_uuid();
private:
    std::map<int, std::string> userPostMap;
	std::vector<std::string> interests;
    std::string first_name;
    std::string last_name;
    long birth_date;
    char uuidCharArray[17];
    std::vector<Post> user_posts;
};
#endif

