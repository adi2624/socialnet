#include "Post.h"
#include <sstream>
#include <fstream>
#include <ostream>
#include <iostream>


int Post::get_serial_number()
{
   return serial_number;
}

void Post::set_serial_number(int sno)
{
   serial_number = sno;
}

void Post::set_date_of_creation(long time)
{
   date_of_creation = time;
}

long Post::get_date_of_creation()
{
   return date_of_creation;
}

void Post::enter_post_data(std::string data)
{
   my_post_data = data;
}

std::string Post::get_post_data()
{
   return my_post_data;
}
