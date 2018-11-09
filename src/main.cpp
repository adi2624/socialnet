#include <string>
#include <sstream>
#include <stdlib.h>
#include <iostream>
#include <time.h>
#include <vector>
#include <map>
#include <thread>
#include <regex>
#include <future>
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

/*===============================
 *
 *      GLOBALS :(
 *
 *===============================
 */
int sno = 0;    
Request *pub;         // *****************************************
Response *res_pub;    // <--- DONT FORGET TO FREE 
Request req_to_send;
TSN::request reqsend_instance; 
std::map<int, std::string> userPostMap;
Post my_post;
User my_user;
std::vector<TSN::request> V;
std::vector<TSN::user_information> userinfo_vector;
std::vector<TSN::response> response_vec;
bool runFlag=true;
auto req =
        dds_io<request,
                requestSeq,
                requestTypeSupport_var,
                requestTypeSupport,
                requestDataWriter_var,
                requestDataWriter,
                requestDataReader_var,
                requestDataReader>

                ((char *) "request", false, true);

auto UserInfo =
        dds_io<user_information,
                user_informationSeq,
                user_informationTypeSupport_var,
                user_informationTypeSupport,
                user_informationDataWriter_var,
                user_informationDataWriter,
                user_informationDataReader_var,
                user_informationDataReader>

                ((char *) "user_information", false, true);
auto res =
        dds_io<response,
                responseSeq,
                responseTypeSupport_var,
                responseTypeSupport,
                responseDataWriter_var,
                responseDataWriter,
                responseDataReader_var,
                responseDataReader>

                ((char *) "response", false, true);



/*==============================
 *
 *      Function Prototypes
 *
 *==============================
 */
TSN::request test_data_request();

TSN::response test_data_response();

TSN::user_information initialize_user();

long convert_to_epoch(int, int, int);

std::vector<std::string> list_all_users();

void receive_request();

void print(TSN::response D);

void print(TSN::request D);

void receive_userinfo();

void receive_response();

void print(TSN::user_information D);

void edit_user_data();

void make_post(char string[37], int sno);

void resync();
/*////////////////////////////////////
/
/       MAIN
/
/
////////////////////////////////// */

int OSPL_MAIN(int argc, char *argv[]) {


    int user_action_num;
    std::string user_action;
    std::string answer = "Y";
    // we only need to initialize user once
    user_information userinfo_instance;
    userinfo_instance = initialize_user();
    my_user.publishEvent(userinfo_instance);
    std::thread req_thread(receive_request);
    std::thread userinfo_thread(receive_userinfo);
    std::thread res_thread(receive_response);
    user_action_num = -1;
    while (user_action_num != 7) {
        
        std::string user_action;
        std::cout << "What would you like to do?" << std::endl;
        std::cout << "1. List users" << std::endl;
        std::cout << "2. Show 'user'" << std::endl;
        std::cout << "3. Edit" << std::endl;
        std::cout << "4. Resync" << std::endl;
        std::cout << "5. Post" << std::endl;
        std::cout << "6. Show statistics" << std::endl;
        std::cout << "7. Exit" << std::endl;
        std::cout << "Enter your choice: ";
        std::cin >> user_action;
        user_action_num = stoi(user_action);
        switch (user_action_num) {
            case 1:
                list_all_users();
                break; 
            case 2:
                reqsend_instance=req_to_send.draft_request();
                req_to_send.publishEvent(reqsend_instance);
                break; //action for show user
            case 3:
                edit_user_data();
                break; //action for edit
            case 4:
                resync();
                break; //action for resync
            case 5:
                make_post(userinfo_instance.uuid, sno++);
                break;
            case 6:
                break; //action for statistics
        }
        if (user_action_num == 7)
        {
            runFlag=false;
            break;
        } 

    }
    std::cout << "Test Thread Join" << std::endl;
    req_thread.join();
    std::cout << "Did Thread 1 Join" << std::endl;
    userinfo_thread.join();
    std::cout << "Did Thread 2 Join" << std::endl;
    res_thread.join();
    std::cout << "Did Thread 3 Join" << std::endl;
    //pub->dispose();
    //delete pub;
    //delete res_pub;
    return 0;
}

void print(TSN::request D) {
    //print_time ();
    std::cout << "Received : request" << std::endl;
    std::cout << "               " << D.uuid << std::endl;
    for (unsigned int i = 0; i < D.user_requests.length(); i++) {
        std::cout << "                 uuid    " << D.user_requests[i].fulfiller_uuid << std::endl;
        for (unsigned int j = 0; j < D.user_requests[i].requested_posts.length(); j++) {
            std::cout << "                 posts   " << D.user_requests[i].requested_posts[j] << std::endl;
        }
    }
    std::cout << std::endl;
}

TSN::request test_data_request() {
    TSN::request D;
    std::string uuid = "d21633d5-12fb-4c93-a4a4-a56f06b7ba24";
    strncpy(D.uuid, uuid.c_str(), sizeof(D.uuid));
    D.uuid[sizeof(D.uuid) - 1] = '\0';

    D.user_requests.length(1);

    std::string uuid2 = "924741ba-5eee-4db9-90fc-ea0175fd5686";
    strncpy(D.user_requests[0].fulfiller_uuid, uuid2.c_str(), sizeof(D.user_requests[0].fulfiller_uuid));
    D.user_requests[0].fulfiller_uuid[sizeof(D.user_requests[0].fulfiller_uuid) - 1] = '\0';

    D.user_requests[0].requested_posts.length(2);
    D.user_requests[0].requested_posts[0] = 600;
    D.user_requests[0].requested_posts[1] = 700;

    return D;
}

void receive_response() {
    while (runFlag) {
        response_vec = res.recv();
        for (size_t i = 0; i < response_vec.size(); i++) {
            print(response_vec[i]);
        }
    }
}

void receive_request() {
    int i = 0;
    while (runFlag) {
        V = req.recv();
        // std::cout<<"SIZE: "<<V.size()<<std::endl;
        for (unsigned int i = 0; i < V.size(); i++) {
            print(V[i]);
           for(size_t j=0;j<V[i].user_requests.length();j++)
           {
               std::cout<<"entered loop"<<std::endl;
               char *uuidArray;
               uuidArray=my_user.return_uuid();
               if(strcmp(V[i].user_requests[j].fulfiller_uuid,uuidArray)==0)
               {
                   std::cout<<"I've been asked to respond to a request"<<std::endl;
                   Response my_response;
                   TSN::response response_instance;
                   std::string post = my_response.load_post(V[i].user_requests[j].requested_posts[0]);
                   response_instance = my_response.draft_response(uuidArray,V[i].user_requests[j].requested_posts[0],post,20); //Change date of creation later
                   my_response.publishEvent(response_instance);
                   
               }
              
           }
        }
        i++;
    }
}

void receive_userinfo() {
    while (runFlag) {
        userinfo_vector = UserInfo.recv();
        // std::cout<<"SIZE: "<<V.size()<<std::endl;
        for (size_t i = 0; i < userinfo_vector.size(); i++) {
            //:w
            //print(userinfo_vector[i]);
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

            for (size_t j = 0; j < userinfo_vector[i].interests.length(); j++) {

                user_interests.push_back(std::string(userinfo_vector[i].interests[j]));

            }

            static_user.set_interests(user_interests);
            static_user.write_to_file();
        }

    }
}

TSN::user_information initialize_user() {
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
    std::string date;
    std::cout << std::endl << "When is your birthday?(mm/dd/yyyy)" << std::endl;
    std::cin >> date;
    int month = stoi(date.substr(0,2));
    int day = stoi(date.substr(3,5));
    int year = stoi(date.substr(6,10));
    long seconds = convert_to_epoch(day, month, year);
    std::cout << "BIRTHDATE: " << seconds << std::endl;
    my_user.set_date(seconds);
    user_information msgInstance;
    std::cout << "The following is your complete USERID generated by BOOST :\n";
    std::ifstream myfile;
    myfile.open("my_user.tsn", ios::in);
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
        output.open("my_user.tsn", ios::out);
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
        if (user_found) {
            std::cout << "UUID FOUND. Loading from file" << std::endl;
            std::ifstream input;
            input.open("my_user.tsn", ios::in);
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
            my_user.set_user_uuid(msgInstance.uuid);
        }
    }

/*  End of Boost UUID  */
    msgInstance.first_name = my_user.get_first_name().c_str();    //SET FNAME AND LNAME IS MSGINSTANCE
    msgInstance.last_name = my_user.get_last_name().c_str();
    msgInstance.date_of_birth = seconds;
    //std::cout<<msgInstance.uuid<<endl;
    msgInstance.interests.length(
            my_user.get_interests().size());       //SET UP VALUES IN user_information STRUCT FOR DDS.
    for (auto i = 0; i < static_cast<int>(my_user.get_interests().size()); i++) {
        msgInstance.interests[i] = my_user.get_interests().at(i).c_str();
    }

    std::cout << my_user.get_interests().size() << endl;


    return msgInstance;
}

void print(TSN::user_information D) {
    std::cout << "Received : user_information" << std::endl;
    std::cout << "               " << D.uuid << " "
              << D.first_name << " "
              << D.last_name << std::endl;
    for (unsigned int i = 0; i < D.interests.length(); i++) {
        std::cout << "(" << D.interests[i] << ") ";
    }
    std::cout << std::endl;
    std::cout << std::endl;
}

TSN::response test_data_response() {
    TSN::response D;
    static int count = 0;
    count++;
    std::string uuid = "d21633d5-12fb-4c93-a4a4-a56f06b7ba24";
    strncpy(D.uuid, uuid.c_str(), sizeof(D.uuid));
    D.uuid[sizeof(D.uuid) - 1] = '\0';
    D.post_id = count;
    D.post_body = DDS::string_dup("this is a sample post.....");
    D.date_of_creation = 1000;
    return D;
}

void print(TSN::response D) {

    std::cout << "Received : response" << std::endl;
    std::cout << "               " << D.uuid << " "
              << D.post_id << " "
              << D.post_body << " "
              << D.date_of_creation << std::endl;
    std::cout << std::endl;
}
long convert_to_epoch(int day, int month, int year)
{
    struct tm t = {0};
    t.tm_year = year-1900;
    t.tm_mon = month;
    t.tm_mday = day;
    time_t time = mktime(&t);
    return static_cast<long>(time);
}

void edit_user_data() {

    std::string temp_fname;
    cout << "Enter your first name: " << std::endl;
    std::cin >> temp_fname;
    my_post.set_first_name(temp_fname);
    my_user.set_first_name(temp_fname);
    
    std::string temp_lname;
    std::cout << "Enter your last name: " << std::endl;
    std::cin >> temp_lname;
    my_post.set_last_name(temp_lname);
    my_user.set_last_name(temp_lname);

    std::vector<std::string> user_interests;
    std::string user_answer_interest;
    std::cout << "What are you interested in?" << std::endl << "Type end to finish" << std::endl;
    std::cin >> user_answer_interest;
    while (!(user_answer_interest == "end")) {
        user_interests.push_back(user_answer_interest);
        std::cin >> user_answer_interest;
    }
    my_user.set_interests(user_interests);
    my_post.set_interest(user_interests);

    std::string date;  std::cout << std::endl << "When is your birthday?(mm/dd/yyyy)" << std::endl;
    std::cin >> date;
    int month = stoi(date.substr(0,2));
    int day = stoi(date.substr(3,5));
    int year = stoi(date.substr(6,10));
    long seconds_birthday = convert_to_epoch(month,day,year);
    my_user.set_date(seconds_birthday);
    
    std::ifstream in("users.tsn");
    if(in)
    {
        system("cp users.tsn users.tmp");
        system("sed '$ d' users.tmp > users.tsn");
        system("rm -f users.tmp");
        my_user.write_to_file();
    }
    else
    {
        std::cerr<<"File not found";
    }

}

std::vector<std::string> list_all_users() {
    std::ifstream users_file("users.tsn");
    std::string input, fname, lname;
    std::vector<std::string> users_vector;
    while (!users_file.eof()) {
        std::getline(users_file, input);
        std::stringstream ss;
        ss << input;
        ss >> fname >> lname;
        fname = fname.substr(1);
        users_vector.push_back(fname + " " + lname);
    }

    return users_vector;
}
void make_post(char string[37], int sno) {
    std::ofstream myfile;
    myfile.open("my_user.tsn", ios::app);
    std::string post_text;
    std::cout << "Enter the post text" << std::endl;
    cin.ignore();
    getline(std::cin, post_text);
    userPostMap[sno] = post_text;
    myfile << "SNO:" << sno << " POST:" << post_text << endl;
    myfile.close();
}
void resync() {

    if (remove("users.tsn") != 0)
        perror("Error Deleting File. Resync unsuccessfull");
    else
        cout << "File successfully deleted\n" << std::endl;

}
