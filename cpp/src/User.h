#ifndef __USER_H
#define __USER_H
#include <boost/uuid/uuid.hpp>
#include <boost/uuid/uuid_generators.hpp>
#include <boost/uuid/uuid_io.hpp>
#include "Post.h"
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
	//
	
    void set_user_information();
    void write_to_file();
    void set_user_uuid(std::string uuid_string);
    char * return_uuid();
private:
	std::vector<std::string> interests;
    std::string first_name;
    std::string last_name;
    /*
     * for this next line we will have to import a boost date library
     * we are already using boost so I figures this shouldnt be a big deal
     */

    //date birth_date;
    char uuidCharArray[17];
    std::vector<Post> user_posts;
};
#endif

