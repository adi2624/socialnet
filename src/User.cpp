#include "User.h"
#include <sstream>
#include<fstream>
#include <ostream>
#include<iostream>

void User::set_interests(std::vector<std::string> input_interests) 
{ 
    interests = input_interests; 
}

std::vector<std::string> User::get_interests() 
{ 
    return interests; 
}

void User::set_first_name(std::string fname) 
{ 
    first_name = fname;
} 

std::string User::get_first_name() 
{ 
    return first_name; 
}

void User::set_last_name(std::string lname) 
{ 
    last_name = lname; 
}

std::string User::get_last_name() 
{ 
    return last_name; 
}
 void User::set_post(std::vector<Post> post) 
{ 
    user_posts = post; 
    for(size_t i = 0; i < post.size(); i++)
    {
    	post_map.insert({post[i].get_serial_number(), post[i].get_post_data()});
    }
}


char* User::return_uuid()
{
    return  uuidCharArray;
}

void User::set_user_uuid(std::string uuid_string)
{
    for(int i = 0; i <37;i++)
    {
        
        if(i == 36)
        {
            this->uuidCharArray[i] = '\0';
        }
        else {
            this->uuidCharArray[i] = uuid_string[i];
        }
    }
}

void User::set_user_information()
{
    // This method is self explanatory 
    //boost::uuids::string_generator gen;
    boost::uuids::uuid uuid = boost::uuids::random_generator()();
    std::string uuid_string = to_string(uuid);
    for(int i = 0; i <37;i++)
    {
        this->uuidCharArray[i] = uuid_string[i];
        if(i == 36)
        {
            this->uuidCharArray[i] = '\0';
        }
    }

}

void User::write_to_file()
{
    std::ofstream userFile;
    userFile.open("users.tsn",std::ios_base::app);

    if(userFile.is_open())
    {
       /*
        ~FNAME:AdityaLNAME:RajguruInterests:Swimming Hockey NetflixUUID:dfefbf46-6dd2-4a7
        ~FNAME:DeviLNAME:TripathyInterests:TableTennis Coding AstronomyUUID:123456789abcdefg
       */

        userFile << "~FNAME" <<" " << first_name <<" "<<"LNAME"<<" "<<last_name<<" "<<"Interests: ";
        for(auto const& interest: interests)
        {
            userFile << interest << " "; 
        }

        userFile << "UUID: ";
        return_uuid();

        for(int i = 0; i < static_cast<int>(strlen(uuidCharArray)); i++)
        {
            userFile << uuidCharArray[i];
        }
        userFile << " DATE: " << date_of_birth << " POST_NUM: " << number_of_highest_post;
        userFile << "\n";
        userFile.close();
    }
    else
    {
        throw std::runtime_error("Could not open file");
    } 
}

void User::publishEvent(TSN::user_information msgInstance)
{
     auto UserInfo = 
                   dds_io<user_information,
                          user_informationSeq,
                          user_informationTypeSupport_var,
                          user_informationTypeSupport,
                          user_informationDataWriter_var,
                          user_informationDataWriter,
                          user_informationDataReader_var,
                          user_informationDataReader>

                          ( (char*) "user_information", true     , true );
     UserInfo.publish(msgInstance);

//        topic name,         publish, subscribe
}
TSN::user_information User::make_instance_user_information(User new_user)
{
    TSN::user_information temp;
    strncpy(temp.uuid, new_user.return_uuid(), 37);
    temp.first_name = new_user.get_first_name().c_str();
    temp.last_name = new_user.get_last_name().c_str();
    temp.number_of_highest_post = new_user.get_number_of_highest_post();
    temp.date_of_birth = new_user.get_date_of_birth();
    temp.interests.length(new_user.get_interests().size());
    for(size_t i = 0; i < new_user.get_interests().size(); i++)
    {
        temp.interests[i] = new_user.get_interests().at(i).c_str();
    }
    return temp;
}
void User::set_date_of_birth(std::string date)
{
    int month = stoi(date.substr(0,2));
    int day = stoi(date.substr(3,5));
    int year = stoi(date.substr(6,10));
    struct tm t = {0};
    t.tm_year = year-1900;
    t.tm_mon = month;
    t.tm_mday = day;
    time_t time = mktime(&t);
    date_of_birth = static_cast<long>(time);
}
void User::set_post_singular(std::string data, int sno)
{
    Post temp;
    temp.enter_post_data(data);
    temp.set_serial_number(sno);
    user_posts.push_back(temp);
    post_map.insert({sno, data});
}
void User::update_user_information_file()
{
     std::ifstream in("users.tsn");
     if(in)
     {
         system("cp users.tsn users.tmp");
         system("sed '$ d' users.tmp > users.tsn");
         system("rm -f users.tmp");
         this->write_to_file();
     }
     else
     {
         std::cerr<<"File not found";
     }

}
User User::populate_my_user()
{
    std::vector <std::string> my_interests;
    std::vector <Post> posts;
    User my_user;
    std::ifstream file;
    file.open("users.tsn");
    std::ifstream post_file;
    post_file.open("my_user.tsn");
    std::string test;
    std::string serial_number, post_data, garbage, fname, lname, uuid, interest, birthdate, post_num;
    while(std::getline(file, test))
    {
        std::stringstream iss(test);
        getline(iss, garbage ,' ');
        getline(iss,fname,' ');
        getline(iss, garbage,  ' ');
        getline(iss, lname, ' ');
        getline(iss, garbage, ' ');
        getline(iss, interest, ' ');
        if(interest != "UUID:") my_interests.push_back(interest);
        while(!(interest == "UUID:"))
        {
            getline(iss, interest, ' ');
            if(interest != "UUID:") my_interests.push_back(interest);
        }
        getline(iss, uuid, ' ');
        getline(iss, garbage, ' ');
        getline(iss, birthdate, ' ');
        getline(iss, garbage , ' ');
        getline(iss, post_num, ' ');
        break;
    }
    // use count variable to avoid the first line which we dont need
    int count = 0;
    while(std::getline(post_file, test))
    {
        if(count != 0)
        {
            Post my_post;
            int sno;
            std::stringstream iss(test);
            std::getline(iss, serial_number , ' ');
            std::getline(iss, post_data, '\n');
            sno = stoi(serial_number.substr(4));
            post_data = post_data.substr(5);
            my_post.set_serial_number(sno);
            my_post.enter_post_data(post_data);
            posts.push_back(my_post);
        }
        count++;
    }
    my_user.set_first_name(fname);
    my_user.set_last_name(lname);
    my_user.set_user_uuid(uuid);
    int highest = stoi(post_num);
    my_user.set_number_of_highest_post(static_cast<unsigned long long>(highest));
    my_user.set_interests(my_interests);
    my_user.set_post(posts);
    my_user.set_date_of_birth(stol(birthdate));
    file.close();
    post_file.close();
    return my_user;
}
std::string User::get_post_from_map(int sno)
{
	auto locate = post_map.find(sno);
	if(locate != post_map.end())
	{
		return locate->second;
	}
	else
	{
		return "Fail";
	}
}
