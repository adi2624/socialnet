#ifndef __USER_H
#define __USER_H
#include <boost/uuid/uuid.hpp>
#include <boost/uuid/uuid_generators.hpp>
#include <boost/uuid/uuid_io.hpp>
#include "Post.h"
#include "DDSEntityManager.h"
#include "ccpp_tsn.h"
#include "dds_io.h"


class User
{
public:
    static User populate_my_user();
    void update_user_information_file();
    static TSN::user_information make_instance_user_information(User new_user);
    void set_interests(std::vector<std::string> input_interests);
    std::vector<std::string> get_interests();
    void set_first_name(std::string fname);
    std::string get_first_name();
    void set_last_name(std::string lname);
    std::string get_last_name();
    void set_date_of_birth(std::string date);
    void set_date_of_birth(long seconds) { date_of_birth = seconds; } 
    long get_date_of_birth() { return date_of_birth; }
    void set_number_of_highest_post(unsigned long long posts) { number_of_highest_post = posts; }
    unsigned long long get_number_of_highest_post() { return number_of_highest_post; }
    void set_post(std::vector<Post> post);
    void set_post_singular(std::string data, int sno);
    std::vector<Post> get_post() { return user_posts; }
    void set_user_information();
    void write_to_file();
    void set_user_uuid(std::string uuid_string);
    char * return_uuid();
    TSN::user_information initialize();
    void publishEvent(TSN::user_information msgInstance);
    friend ostream& operator << (ostream& out, User t)
    {
        std::string str(t.return_uuid());
        out << str << std::endl;
        out << t.get_first_name() << " " << t.get_last_name() << " " << t.get_date_of_birth() << std::endl;
        out << "Interests: " << std::endl;
        for(size_t i = 0; i < t.get_interests().size(); i++)
        {
            out << t.get_interests().at(i) << std::endl;
        }
        out << "Posts: " << std::endl;
        for(size_t i = 0; i < t.get_post().size(); i++)
        {
            out << t.get_post().at(i).get_post_data() << std::endl;
        }
        return out;
    }
private:
    unsigned long long number_of_highest_post;
    long date_of_birth;
	std::vector<std::string> interests;
    std::string first_name;
    std::string last_name;
    long birth_date;
    char uuidCharArray[37];
    std::vector<Post> user_posts;
};
#endif

