#include "User.h"
#include<fstream>
#include<iostream>

char* User::return_uuid()
{
    return  uuidCharArray;
}
void User::set_user_uuid(std::string uuid_string)
{
    for(int i = 0; i <=17;i++)
    {
        this->uuidCharArray[i] = uuid_string[i];
        if(i == 17)
        {
            this->uuidCharArray[i] = '\0';
        }
    }
}
void User::set_user_information()
{
    // This method is self explanatory 
    boost::uuids::string_generator gen;
    boost::uuids::uuid uuid = boost::uuids::random_generator()();
    std::string uuid_string = to_string(uuid);
    for(int i = 0; i <=17;i++)
    {
        this->uuidCharArray[i] = uuid_string[i];
        if(i == 17)
        {
            this->uuidCharArray[i] = '\0';
        }
    }

}

/*
 * Writes user information to file on local disk
 */
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

        for(int i = 0; i < strlen(uuidCharArray); i++)
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