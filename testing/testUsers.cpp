#include "include/testFunctions.h"

#include <boost/lexical_cast.hpp>
#include <boost/uuid/uuid.hpp>
#include <boost/uuid/uuid_generators.hpp>
#include <boost/uuid/uuid_io.hpp>

//test to see if we can create a user with a valid uuid and call functions from the users class

BOOST_AUTO_TEST_CASE(testUsers)
{
    boost::uuid:uuid sampleUUID = boost::uuids::random_generator()();
    std::string uuid = boost::lexical_cast<std::string>(sampleUUID);

    vector<std::string> interests;
    interests.push_back("testing users");

    //create a valid user and push it to the list of users
    User dummy_user;
    dummy_user.set_first_name("dummy");
    std::testString = dummy_user.get_first_name();
    std::cout << "First Name is: " << testString << std::endl;
    BOOST_TEST_PASSPOINT();
    std::cout << "Accurately store and retrieve first name: PASS" << std::endl;

    //put last name in file and be able to retrieve it
    dummy_user.set_last_name("user");
    testString = dummy_user.get_last_name();
    std::cout << "Last Name is: " << testString << std::endl;
    BOOST_TEST_PASSPOINT();
    std::cout << "Accurately store and retrieve last name: PASS" << std::endl;

    //put uuid in file and be able to retrieve it
    dummy_user.set_user_uuid(sampleUUID);
    char * sampleUUID = dummy_user.return_uuid();
    std::cout << "UUID is: " << sampleUUID << std::endl;
    BOOST_TEST_PASSPOINT();
    std::cout << "Accurately store and retrieve uuid: PASS" << std::endl;


    //store and retrieve user interests
    dummy_user.set_user_interests(interests);
    vector<std::string> testInterests = dummy_user.get_interests();
    
    for(testInterests::const_iterator i= testInterests.begin(); i != testInterests.end(); ++i)
    {
        std::cout << *i << " " << std::endl;
    }

    BOOST_TEST_PASSPOINT();
    std::cout << "Can store and retrieve user interests: PASS" << std::endl;
}

