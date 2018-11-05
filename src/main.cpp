#include <string>
#include <sstream>
#include <iostream>
#include <vector>
#include <map>
#include <thread>
#include <regex>
#include <fstream>
#include "DDSEntityManager.h"
#include "ccpp_tsn.h"
#include "User.h"
#include "example_main.h"
#include <boost/lexical_cast.hpp>
#include <boost/regex.hpp>
#include "Request.h"
#include "Response.h"
#include "Post.h"
using namespace DDS;
using namespace TSN;

int sno = 0;        //KEEPS TRACK OF SERIAL NO: DO NOT REMOVE IT'S A GLOBAL VARIABLE
void receive_request();
void print ( TSN::response D );

void print ( TSN::request D );
void receive_userinfo();
void receive_response();
Request* pub;         // *****************************************
Response * res_pub;   // <-------------- DONT FORGET TO FREE THESE
TSN::request test_data_request ();
TSN::response test_data_response ();
TSN::user_information initialize_user();
void print ( TSN::user_information D );

std::map<int, std::string> userPostMap;
Post my_post;
User my_user;
std::vector<TSN::request> V ;
std::vector<TSN::user_information> userinfo_vector;
std::vector<TSN::response> response_vec;
auto req = 
                            dds_io<request,
                                    requestSeq,
                                    requestTypeSupport_var,
                                    requestTypeSupport,
                                    requestDataWriter_var,
                                    requestDataWriter,
                                    requestDataReader_var,
                                    requestDataReader>


                                    ( (char*) "request", false     , true );

auto UserInfo = 
                   dds_io<user_information,
                          user_informationSeq,
                          user_informationTypeSupport_var,
                          user_informationTypeSupport,
                          user_informationDataWriter_var,
                          user_informationDataWriter,
                          user_informationDataReader_var,
                          user_informationDataReader>

                          ( (char*) "user_information", false     , true );
auto res =
            dds_io<response,
            responseSeq,
            responseTypeSupport_var,
            responseTypeSupport,
            responseDataWriter_var,
            responseDataWriter,
            responseDataReader_var,
            responseDataReader>
            ( (char*) "response", false , true );



//long calculate_seconds(int month, unsigned day, unsigned year)
//{
//  // TODO: FINISH THIS FUNCTION
//  long temp;
//  return temp;
//
//}
/*////////////////////////////////////
/
/       USER INFORMATION PUBLISHER
/   
/
////////////////////////////////////*/



/*////////////////////////////////////
/
/       MAIN
/   
/
////////////////////////////////////*/

int OSPL_MAIN(int argc, char *argv[]) {
   
  
    User externPost;
     int user_action_num;
        std::string user_action;
        std::string answer="Y";
        user_information userinfo_instance = initialize_user();
        my_user.publishEvent(userinfo_instance);
        std::thread req_thread(receive_request);
        std::thread userinfo_thread(receive_userinfo);
        std::thread res_thread(receive_response);
        while(answer=="Y")
       {
           TSN::response test_inst= test_data_response();
        TSN::request instance=test_data_request();
        pub = new Request(instance.uuid,instance.user_requests[0]);
        pub->publishEvent(instance.uuid,instance.user_requests[0]);
        string str(test_inst.uuid);
        res_pub = new Response(str,test_inst);
        res_pub->publishEvent(str, test_inst);
        std::cout<<"Do you want to continue?--------------------------------------------------------------------------------------------------------------------------"<<std::endl;
        std::cin>> answer;
        std::cout << "*" << answer << "*" << std::endl;
       }
       std::cout << "herer" << std::endl;
       req_thread.join();
       std::cout << "herer3" << std::endl; 
       userinfo_thread.join();
       std::cout<<"Program Terminated"<<std::endl;
       // externPost.set_map(userPostMap);
      
        //pub->dispose();
        //delete pub;

    



    return 0;

}
void print ( TSN::request D )
{
   //print_time ();
   std::cout << "Received : request" << std::endl;
   std::cout << "               " << D.uuid  << std::endl;
   for (unsigned int i=0;i<D.user_requests.length ();i++)
   {
      std::cout << "                 uuid    " << D.user_requests[i].fulfiller_uuid << std::endl;
      for (unsigned int j=0;j<D.user_requests[i].requested_posts.length ();j++)
      {
          std::cout << "                 posts   " << D.user_requests[i].requested_posts[j] << std::endl;
      }
   }
   std::cout << std::endl;
}
TSN::request test_data_request ()
{
   TSN::request D;
   std::string  uuid = "d21633d5-12fb-4c93-a4a4-a56f06b7ba24";
   strncpy (D.uuid,uuid.c_str(),sizeof(D.uuid));
   D.uuid[sizeof(D.uuid)-1] = '\0';

   D.user_requests.length(1);

   std::string uuid2 = "924741ba-5eee-4db9-90fc-ea0175fd5686";
   strncpy(D.user_requests[0].fulfiller_uuid,uuid2.c_str(),sizeof(D.user_requests[0].fulfiller_uuid));
   D.user_requests[0].fulfiller_uuid[sizeof(D.user_requests[0].fulfiller_uuid)-1] = '\0';

   D.user_requests[0].requested_posts.length(2);
   D.user_requests[0].requested_posts[0]=600;
   D.user_requests[0].requested_posts[1]=700;

   return D;
}
void receive_response()
{
    while(1)
    {
        response_vec = res.recv();
        for(size_t i = 0; i < response_vec.size(); i++)
        {
            print(response_vec[i]);
        }
    }
}
void receive_request()
{
    int i=0;
                        while(1)
                        {
                                                    V = req.recv ();
                                               // std::cout<<"SIZE: "<<V.size()<<std::endl;
                                                for (unsigned int i=0;i<V.size();i++)
                                                {
                                                    print ( V[i] );
                                                }
                                                i++;
                        }
}

void receive_userinfo()
{
    while(1)
                        {
                                                    userinfo_vector = UserInfo.recv ();
                                               // std::cout<<"SIZE: "<<V.size()<<std::endl;
                                                for (size_t i=0;i<userinfo_vector.size();i++)
                                                {
                                                    print ( userinfo_vector[i] );
                                                    User static_user;
                                                    std::vector<std::string> user_interests;
                                                    static_user.set_first_name(std::string(userinfo_vector[i].first_name));
                                                    static_user.set_last_name(std::string(userinfo_vector[i].last_name));
                                                    static_user.set_user_uuid(userinfo_vector[i].uuid);
                                                      // std::cout<<"The size of interest vector is"<<userinfo_vector[i].interests.length()<<std::endl;
                                                      /*----------------------------------------------------
                                                      |
                                                      |ISSUE: FOR LOOP DOES NOT RUN ACCORDING TO THE SIZE OF INTEREST VECTOR
                                                      |
                                                      |
                                                      ----------------------------------------------------==*/
        
                                                     for (size_t j=0;j<userinfo_vector[i].interests.length();j++)
                                                        {
                                                          
                                                            user_interests.push_back(std::string(userinfo_vector[i].interests[j]));
                                                            
                                                        }
                                                     
                                                    static_user.set_interests(user_interests);
                                                    static_user.write_to_file();
                                                }
                                                
                        }
}

TSN::user_information initialize_user()
{
     int user_found = 0;
    std::string temp_user;
    cout << "Enter your first name: " << std::endl;
    std::cin >> temp_user;
    my_user.set_first_name(temp_user);
    std::cout << "Enter your last name: " << std::endl;
    std::cin >> temp_user;
    my_user.set_last_name(temp_user);
    std::vector<std::string> user_interests;
    std::string user_answer_interest;
    std::cout << "What are you interested in?" << std::endl << "Type end to finish" << std::endl;
    std::cin >> user_answer_interest;
    while (!(user_answer_interest == "end")) {
        user_interests.push_back(user_answer_interest);
        std::cin >> user_answer_interest;
    }
    my_user.set_interests(user_interests);
     user_information msgInstance;
     std::cout << "The following is your complete USERID generated by BOOST :\n";
    std::ifstream myfile;
    myfile.open("hello.tsn", ios::in);
    char uuidCharArray[42];
    bool is_empty = true;
    while (!myfile.eof()) {
        std::string data;
        myfile >> data;
        if (data == "")            //CODE TO CHECK IF FILE IS EMPTY
        {
            break;
        }
        is_empty = false;
    }
    myfile.close();

    if (is_empty) {
        // do your error handling

        // Empty File
        std::ofstream output;                                       //Generate a new UUID if file is empty.
        output.open("hello.tsn", ios::out);
        std::cout << "The file is empty. Generatin a UUID.....\n";
        boost::uuids::uuid uuid = boost::uuids::random_generator()();
        std::string uuid_string = to_string(uuid);

        for (int i = 0; i <= 37; i++) {
            uuidCharArray[i] = uuid_string[i];
            if (i == 37) {                                       //COPY GENERATED UUID TO uuidCharArray
                uuidCharArray[i] = '\0';
            }
        }

        my_user.set_user_uuid(uuid_string);
        output << "UUID:" << uuidCharArray << std::endl;
        output.close();
        sno++;    //INCREMENT SERIAL NO TO POST 1.
        strncpy(msgInstance.uuid, uuidCharArray, 42 - 5);
        std::vector<Post> temp_post_vec;
        my_post.enter_post_data("Test data.");
        temp_post_vec.push_back(my_post);
        my_user.set_post(temp_post_vec);
        //my_user.write_to_file();
    } else {
        user_found = 1;
        if(user_found) {
        std::cout << "UUID FOUND. Loading from file" << std::endl;
        std::ifstream input;
        input.open("hello.tsn", ios::in);
        //LOAD GENERATED UUID AND COUNT THE NO OF POSTS IN THE DISK.
        input.getline(uuidCharArray, 42);
        std::cout << "Loaded: " << uuidCharArray << std::endl;
        while (input) {
            std::string garbage_value;
            std::getline(input, garbage_value);         //count the no of posts
            sno++;
        }
        input.close();
        strncpy(msgInstance.uuid, uuidCharArray + 5, 42 - 5);
    }
    }

/*  End of Boost UUID  */
    msgInstance.first_name = my_user.get_first_name().c_str();    //SET FNAME AND LNAME IS MSGINSTANCE
    msgInstance.last_name = my_user.get_last_name().c_str();

    //std::cout<<msgInstance.uuid<<endl;
    msgInstance.interests.length(
            my_user.get_interests().size());       //SET UP VALUES IN user_information STRUCT FOR DDS.
    for (auto i = 0; i < static_cast<int>(my_user.get_interests().size()); i++) {
        msgInstance.interests[i] = my_user.get_interests().at(i).c_str();
    }

    std::cout << my_user.get_interests().size() << endl;


    
    return msgInstance;
}

void print ( TSN::user_information D )
{
   std::cout << "Received : user_information" << std::endl;
   std::cout << "               " << D.uuid << " "
                                << D.first_name << " "
                                << D.last_name <<std::endl;
   for (unsigned int i=0;i<D.interests.length ();i++)
   {
       std::cout << "(" << D.interests[i] << ") "; 
   }
   std::cout << std::endl;
   std::cout << std::endl;
}
TSN::response test_data_response()
{
    TSN::response D;
    static int count=0;
    count++;
    std::string  uuid = "d21633d5-12fb-4c93-a4a4-a56f06b7ba24";
    strncpy (D.uuid,uuid.c_str(),sizeof(D.uuid));
    D.uuid[sizeof(D.uuid)-1] = '\0';
    D.post_id = count;
    D.post_body = DDS::string_dup("this is a sample post....."); 
    D.date_of_creation = 1000;
    return D;
}
void print ( TSN::response D )
{

    std::cout << "Received : response" << std::endl;
    std::cout << "               " << D.uuid  << " "
                                  << D.post_id  << " "
                                  << D.post_body << " "
                                  << D.date_of_creation << std::endl;
    std::cout << std::endl;
}
