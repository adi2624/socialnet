#include "include/testFunctions.h"

#include <boost/lexical_cast.hpp>
#include <boost/uuid/uuid.hpp>
#include <boost/uuid/uuid_generators.hpp>
#include <boost/uuid/uuid_io.hpp>



//make a test post and send it out 
//send to post class 
//add post to user's saved post in my_user.tsn
//save post to file
// Delete test user's info (resync)
BOOST_AUTO_TEST_CASE(testMakePosts)
{
    boost::uuid:uuid sampleUUID = boost::uuids::random_generator()();
    std::string uuid = boost::lexical_cast<std::string>(sampleUUID);

    vector<std::string> interests;
    interests.push_back("hello world");

    User dummy_user(sampleUUID, "test", "test", "test", interests);

}

