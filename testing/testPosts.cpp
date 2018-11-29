#include "include/testFunctions.h"

#include <boost/lexical_cast.hpp>
#include <boost/uuid/uuid.hpp>
#include <boost/uuid/uuid_generators.hpp>
#include <boost/uuid/uuid_io.hpp>


BOOST_AUTO_TEST_CASE(testMakePosts)
{
    boost::uuids::uuid sampleUUID = boost::uuids::random_generator()();
    std::string uuid = boost::lexical_cast<std::string>(sampleUUID);

    vector<std::string> interests;
    interests.push_back("hello world");

    //create sample user
    User dummy_user;
    dummy_user.set_first_name("dummy");
    dummy_user.set_last_name("user");
    dummy_user.set_user_uuid(uuid);
    dummy_user.set_interests(interests);

    BOOST_TEST_PASSPOINT();
    std::cout << "User can be created: PASS" << std::endl;

    //make post and send it to post class
    //write post to users saved post
    std::time_t startTime = std::time(0);
    boost::random::mt19937 num{static_cast<std::uint32_t>(startTime)};
    boost::random::uniform_int_distribution<> range{1, 150};
    int postContent = range(num);
    
    int i = 0;
    std::string samplePost = " ";
    for(i = 0; i < postContent; i++)
    {
        samplePost += "Hi";
    }

    std::cout << "Sample post is: " << samplePost << std::endl;
    dummy_user.set_post_singular(samplePost,1);

    BOOST_TEST_PASSPOINT();
    std::cout << "Post can be made: Pass" << std::endl;

    //write post to file
    dummy_user.write_to_file();

    BOOST_TEST_PASSPOINT();
    std::cout << "Posts can be saved on disk: Pass" << std::endl;

}

