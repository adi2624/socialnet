#ifndef __POST_H
#define __POST_H

#include<iostream>
#include<string>
#include<vector>

class Post
{
    public:
    std::string my_post_data;
    int serial_number;
    int get_serial_number() { return serial_number; };
    void set_serial_number(int sno) { serial_number = sno; }
    long date_of_creation;
    void set_date_of_creation(long time) { date_of_creation = time; }
    long get_date_of_creation() { return date_of_creation; }
    void  enter_post_data(std::string data) { my_post_data = data; }
    std::string get_post_data() { return my_post_data; }
    
};

#endif
