#include "User.h"
#include<fstream>
#include<iostream>
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
    userFile.open("users.tsn",std::ios::app);
    if(userFile.is_open())
    {
       // std::string uuuid(UUUID);
        // each user will be delimited by a ~ character 
        userFile << "~";
        userFile <<first_name<<" "<<last_name <<" ";
        // here we start writing all the individual post that we have for the user
        //write all user interests to the file
        for(auto const& interest: interests)
        {
            userFile << interest << " "; 
        }
        userFile << "\n";
        //write user posts to the file 
        /*
        for(auto const& post: user_posts)
        {
            userFile << post.get_serial_number() << " " << post.get_post_data() << " " << post.get_creation_date()<< "\n";
        }
        */
        /*                      example file
         * ~UUID1
         * September 20, 1997
         * Hockey Football Computers
         * 01 Today I went for a walk. DATE
         * 02 I dont feel so goo today DATE
         * ~UUID2 
         * September 18, 1989
         * Running Painting 
         * 03
         *  Today I painted a house DATE
         * 04 I dont want to work today DATE 
         */

        userFile.close();
    }
    else
    {
        throw std::runtime_error("Could not open file");
    }
}
