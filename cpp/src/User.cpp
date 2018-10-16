#include "User.h"
#include<fstream>
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

void User::set_date(long birth) 
{ 
    birth_date = birth; 
}

long User::get_birth_date() 
{ 
    return birth_date; 
}

 void User::set_post(std::vector<Post> post) 
{ 
    user_posts = post; 
}

void User::set_map(std::map<int, std::string>& user_post_map) 
{ 
    userPostMap = user_post_map; 
}

std::map<int, std::string> User::get_map() 
{ 
    return userPostMap;
}

char* User::return_uuid()
{
    return  uuidCharArray;
}

void User::set_user_uuid(std::string uuid_string)
{
    for(int i = 0; i <=37;i++)
    {
        this->uuidCharArray[i] = uuid_string[i];
        if(i == 37)
        {
            this->uuidCharArray[i] = '\0';
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

        userFile << "\n";
        userFile.close();
    }
    else
    {
        throw std::runtime_error("Could not open file");
    } 
}