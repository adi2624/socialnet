#ifndef __POST_H
#define __POST_H

#include<iostream>
#include<string>
#include<vector>

class Post
{
    public:
    std::string first_name;
    std::string last_name;
    std::string my_post_data;
    std::vector<std::string> interests;
    void set_interest(std::vector<std::string> interests);
    std::vector<std::string> get_interests();
    void set_first_name(std::string fname);
    std::string get_first_name();
    void set_last_name(std::string lname);
    void  enter_post_data(std::string data);
    std::string get_post_data();
    std::string get_last_name();
    
};

#endif