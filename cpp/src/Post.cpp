#include"Post.h"
#include<string.h>
void Post::set_interest(std::vector<std::string> input_interests)
{
    for(int i=0;i<input_interests.size();i++)
    {
        interests.push_back(input_interests.at(i));
    }
}

std::vector<std::string> Post::get_interests()
{
    return interests;
}

void Post::set_first_name(std::string fname)
{
    first_name=fname;
}

std::string Post::get_first_name()
{
    return first_name;
}

std::string Post::get_last_name()
{
    return last_name;
}

void Post::set_last_name(std::string lname)
{
    last_name=lname;
}
void  Post::enter_post_data(std::string data)
{
    my_post_data = data;
}
std::string Post::get_post_data()
{
    return my_post_data;
}