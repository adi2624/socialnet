#include "User.h"
#include <sstream>
#include<fstream>
#include <ostream>
#include<iostream>

void User::set_interests(std::vector<std::string> input_interests) 
{ 
    interests = input_interests; 
    std::cout << "SETTING INTEREST: " << std::endl;
    for(size_t i = 0; i < input_interests.size(); i++)
    {
        std::cout << input_interests[i] << std::endl;
    }
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
}


char* User::return_uuid()
{
    return  uuidCharArray;
}

void User::set_user_uuid(std::string uuid_string)
{
    for(int i = 0; i <=37;i++)
    {
        
        if(i == 37)
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
    for(int i = 0; i <=37;i++)
    {
        this->uuidCharArray[i] = uuid_string[i];
        if(i == 37)
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
                          cout << "=== [Publisher] writing a message containing :" << endl;
    cout << "    userID  : " << msgInstance.uuid << endl;
    cout << "    Name : \"" << msgInstance.first_name << " " << msgInstance.last_name << "\"" << endl;
    

     UserInfo.publish(msgInstance);

//        topic name,         publish, subscribe
}
TSN::user_information User::make_instance_user_information(User new_user)
{
    TSN::user_information temp;
    strncpy(temp.uuid, new_user.return_uuid(), 37);
    temp.first_name = new_user.get_first_name().c_str();
    temp.last_name = new_user.get_last_name().c_str();
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
    std::cout << "SETTING BIRTHDATE: " << date_of_birth << std::endl;
}
void User::set_post_singular(std::string data)
{
    Post temp;
    temp.enter_post_data(data);
    user_posts.push_back(temp);
    std::cout << "SETTING POST: " << temp.get_post_data() << std::endl;  
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
