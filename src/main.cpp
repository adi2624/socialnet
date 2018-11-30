#include <future>
#include <string>
#include <queue>
#include <sstream>
#include <stdlib.h>
#include <iostream>
#include <time.h>
#include <vector>
#include <map>
#include <thread>
#include <regex>
#include <fstream>
#include <unistd.h>
#include <ncurses.h>
#include <cassert>
#include <form.h>
#include <menu.h>
#include "DDSEntityManager.h"
#include "ccpp_tsn.h"
#include "User.h"
#include "example_main.h"
#include <boost/lexical_cast.hpp>
#include <boost/regex.hpp>
#include "Request.h"
#include "Response.h"
#include "Post.h"
#include "Message.h"
#define ARRAY_SIZE(a) (sizeof(a) / sizeof(a[0]))
using namespace DDS;
using namespace TSN;



//NOTE: A NON CLEAN EXIT WILL BREAK THE FUNCTIONALITY OF THE PROGRAM.



/*===============================
 *
 *      GLOBALS :(
 *
 *===============================
 */
std::queue<std::string> print_queue;
std::map<std::string, User > user_hash_map;
bool user_is_initiated = false;
bool is_first_run=true;
int receive_counter=0;
int sno = 0;    
long post_count = 0;
long known_nodes = 0;
unsigned long long all_posts = 0;
Request req_to_send; //Initial Request object to iniotialize.
TSN::request reqsend_instance; //TSN::request to send request over the network.
std::map<int, std::string> userPostMap;
Post my_post;
User my_user;
std::vector<TSN::request> V; //Vector to store received requests
std::vector<TSN::user_information> userinfo_vector; //Vector to store received user information
std::vector<TSN::response> response_vec; //Vector to store received responses.
std::vector<TSN::private_message> message_vec; //Vector to store received messages.
bool runFlag=true;  //determines whether to run or end program.

/*//////////////////////////////////////////////////
/ DDS_IO STRUCTURES TO SEND DATA OVER NETWORK      /
/                                                  /
///////////////////////////////////////////////////*/
WINDOW *display_menu(int height, int width, int starty, int startx);
void destroy_win(WINDOW *local_win);
int kbhit();
void entry_point(void);
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
auto message_ =               
        dds_io<private_message,
              private_messageSeq,
              private_messageTypeSupport_var,
              private_messageTypeSupport,
              private_messageDataWriter_var,
              private_messageDataWriter,
              private_messageDataReader_var,
              private_messageDataReader>
              ( (char*) "private_message", false , true );



/*==============================
 *
 *      Function Prototypes
 *
 *==============================
 */
TSN::request test_data_request();

TSN::response test_data_response();

TSN::user_information initialize_user(bool *);

std::vector<Post> get_posts(unsigned long long number_of_posts, User to_request);

void list_all_users();

void receive_request();

void print(TSN::response D);

void print(TSN::request D);

void receive_userinfo();

void receive_response();

void print(TSN::user_information D);

void edit_user_data();

void make_post(char string[37], int sno);

void resync();

void init_params();

void set_params();

void calculate_stats();

void show_user();

void send_message();

void receive_message();

/*//////////////////////////////////////////////////
/ FUNCTION THAT IS LAUNCHED BYA THREAD AND RUNS    /
/ SUBSCRIBERS CONTINUOSLY.                         /
///////////////////////////////////////////////////*/

void get_content()
{
    while(runFlag)
    {
        receive_userinfo();
        receive_message();
        receive_request();
        receive_response();
        TSN::user_information temp = User::make_instance_user_information(my_user);
        if(my_user.get_number_of_highest_post() != 0)  my_user.publishEvent(temp);
        receive_counter++;
        sleep(60);  
    }
}

bool is_request_to_send(TSN::request req);

void grab_posts(User user_to_request);

void participate_thread();

void print_all(); 
/*////////////////////////////////////
/
/       MAIN
/
/
////////////////////////////////// */
int OSPL_MAIN(int argc, char *argv[]) {
    initscr();
    cbreak();
    noecho();
    keypad(stdscr, TRUE);
    entry_point();
    init_params();                       // Loads up parameters necessary to check whether there is user information present from a previous run.
    int user_action_num;                // STORES USER INPUT
    std::ifstream file;
    file.open("my_user.tsn");
    file.seekg(0, std::ios::end);
    std::string user_action;
    std::string answer = "Y";
    user_information userinfo_instance;    
    if(!file.good() && file.tellg() == -1)
    {
        userinfo_instance = initialize_user(&user_is_initiated);        //Initialize user if first run.
        my_user.publishEvent(userinfo_instance);
    }
    else 
    {
        my_user = User::populate_my_user();                              //Load info if not the first run.
        std::cout << my_user << std::endl;
    }
    std::thread update_content(get_content);                             //Launch thread of subscribers.
    user_action_num = -1;
    while (user_action_num != 9) {
        print_all();
        std::string user_action;
        std::cout << "What would you like to do?" << std::endl;
        std::cout << "1. List users" << std::endl;
        std::cout << "2. Show 'user'" << std::endl;
        std::cout << "3. Edit" << std::endl;
        std::cout << "4. Resync" << std::endl;                          //USER MENU
        std::cout << "5. Post" << std::endl;
        std::cout << "6. Show statistics" << std::endl;
        std::cout << "7. Request Post" << std::endl;
        std::cout << "8. Send message" << std::endl;
        std::cout << "9. Quit" << std::endl;
        std::cout << "Enter your choice: ";
        cin.clear();
        std::cin.sync();
        getline(std::cin, user_action);        
        user_action_num = stoi(user_action);
        //Update User Values every loop 
        my_user.update_user_information_file(); 
        switch (user_action_num) {
            case 1:
                list_all_users();                                   //list info about the user of this program.
                break; 
            case 2:
		        show_user();
                break; //action for show user
            case 3:
                edit_user_data();
                break; //action for edit
            case 4:
                resync();
                break; //action for resync
            case 5:
                make_post(userinfo_instance.uuid, sno++);          //MAKE A POST
                break;
            case 6:
                calculate_stats();
                break; //action for statistics
            case 7:
                {                                                   //MAKE A REQUEST FOR A POST
                    reqsend_instance=req_to_send.draft_request();
                    bool to_send = is_request_to_send(reqsend_instance);
                    if(to_send)
                    {
                        req_to_send.publishEvent(reqsend_instance);
                    }
                    else
                    {
                        for(int i = 0; i < (int)reqsend_instance.user_requests.length(); i++)
                        {
                            std::string locate(reqsend_instance.user_requests[i].fulfiller_uuid);
                            auto iter = user_hash_map.find(locate);
                            User found;
                            if(iter != user_hash_map.end())
                            {
                                found = iter->second;
                            }
                            else
                            {
                                break;
                            }
                            for(int j = 0; j < static_cast<int>(reqsend_instance.user_requests[i].requested_posts.length()); j++)
                            {
                                std::cout << "Post:" << std::endl;
                                std::cout << found.get_post_from_map(reqsend_instance.user_requests[i].requested_posts[j]) << std::endl;
                            }
                        }

                    }

                }
                break;
            case 8:
                send_message();             //SEND MESSAGE
                break;
        }
        if (user_action_num == 9)
        {
            runFlag=false;
            break;
        } 

    }
    update_content.join();                   //JOIN THE THREADS.
    set_params();
    file.close();
    return 0;
}


/*//////////////////////////////////////////////////
/ Function to print out info on receiving request. /
/                                                  /
///////////////////////////////////////////////////*/

void print(TSN::request D) 
{
    std::stringstream ss;
    ss << "Received : request" << std::endl;
    ss << "               " << D.uuid << std::endl;
    for (unsigned int i = 0; i < D.user_requests.length(); i++) {
        ss << "                 uuid    " << D.user_requests[i].fulfiller_uuid << std::endl;
        for (unsigned int j = 0; j < D.user_requests[i].requested_posts.length(); j++) {
            ss << "                 posts   " << D.user_requests[i].requested_posts[j] << std::endl;
        }
    }
    ss << std::endl;
    print_queue.push(ss.str());
}

/*//////////////////////////////////////////////////
/ Test request function                            /
/                                                  /
///////////////////////////////////////////////////*/

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

/*//////////////////////////////////////////////////
/ RECEIVE RESPONSES                                /
/                                                  /
///////////////////////////////////////////////////*/

void receive_response() {
    response_vec = res.recv();
    for (size_t i = 0; i < response_vec.size(); i++) 
    {
        print(response_vec[i]);
        std::string locate(response_vec[i].uuid);
        auto located = user_hash_map.find(locate);
        if(located != user_hash_map.end())
        {
            std::string data(response_vec[i].post_body);
            int id= (int)response_vec[i].post_id;
            if(!(located->second.is_in_map(id)))
            {
                User temp_t = located->second;
                temp_t.set_post_singular(data,id);
                located->second = temp_t;
            }
        }
    }
}

/*//////////////////////////////////////////////////
/ RECEIVE REQUESTS                                 /
/                                                  /
///////////////////////////////////////////////////*/

void receive_request() {
    int i = 0;
    V = req.recv();
    for (unsigned int i = 0; i < V.size(); i++) 
    {
        print(V[i]);
        for(size_t j=0;j<V[i].user_requests.length();j++)
        {
            char *uuidArray;
            uuidArray=my_user.return_uuid();
            if(strncmp(V[i].user_requests[j].fulfiller_uuid,uuidArray,36)==0)
            {
                Response my_response;
                Post my_post;
                TSN::response response_instance;
                for(size_t k = 0; k < V[i].user_requests[j].requested_posts.length(); k++)
                {
                    std::string post = my_response.load_post(V[i].user_requests[j].requested_posts[k]);
                    response_instance = my_response.draft_response(uuidArray,V[i].user_requests[j].requested_posts[k],post,20); //Change date of creation later
                    my_response.publishEvent(response_instance);
                }
            }
              
        }
    }
    i++;
}

/*//////////////////////////////////////////////////
/ LIST USERS                                       /
/                                                  /
///////////////////////////////////////////////////*/

void list_all_users()
{
    std::cout << my_user << std::endl;
}

/*//////////////////////////////////////////////////
/ RECEIVE MESSAGES                                 /
/                                                  /
///////////////////////////////////////////////////*/


void receive_message()
{
    std::stringstream ss;
    message_vec = message_.recv();
    for(size_t i = 0; i < message_vec.size(); i++)
    {
        ss << message_vec[i].message_body << std::endl;
    }
    print_queue.push(ss.str());
}

/*//////////////////////////////////////////////////
/ RECEIVE USERINFO                                 /
/                                                  /
///////////////////////////////////////////////////*/

void receive_userinfo() {
    userinfo_vector = UserInfo.recv();
    for (size_t i = 0; i < userinfo_vector.size(); i++) 
    {
        print(userinfo_vector[i]);
        User static_user;
        std::vector<std::string> user_interests;
        known_nodes++;
        all_posts += userinfo_vector[i].number_of_highest_post;
        static_user.set_number_of_highest_post(userinfo_vector[i].number_of_highest_post);
        static_user.set_date_of_birth(userinfo_vector[i].date_of_birth);
        static_user.set_first_name(std::string(userinfo_vector[i].first_name));
        static_user.set_last_name(std::string(userinfo_vector[i].last_name));
        static_user.set_user_uuid(userinfo_vector[i].uuid);
        for (size_t j = 0; j < userinfo_vector[i].interests.length(); j++) {
            user_interests.push_back(std::string(userinfo_vector[i].interests[j]));
        }
        static_user.set_interests(user_interests);
        if((strcmp(static_user.return_uuid(),my_user.return_uuid())!=0))
        {
            static_user.write_to_file();
        }
         else if(strcmp(static_user.return_uuid(),my_user.return_uuid())==0 && is_first_run==true && receive_counter==0)
        {
            static_user.write_to_file();
        }
        if(static_user.get_number_of_highest_post() != 0) grab_posts(static_user);
    }
}

/*//////////////////////////////////////////////////
/ INITIALIZE USER                                  /
/                                                  /
///////////////////////////////////////////////////*/

TSN::user_information initialize_user(bool * is_initialized) {

    std::ifstream myfile;
    myfile.open("my_user.tsn", ios::in);
    myfile.seekg(0, std::ios::end);
    if(myfile.good())
    {
        // temporary fix while i change my_user data
        user_information msgInstance;
        // get user information somehow
        User temp = Request::list_pub_users()[0]; //gets first user which is us.
        return User::make_instance_user_information(temp);
        
    }

    
    if (myfile.tellg() != 0 || !myfile.good()) 
    {
        *is_initialized = true;
        std::string temp_user;
        cout << "Enter your first name: " << std::endl;
        std::cin.sync();
        getline(std::cin, temp_user);
        my_user.set_first_name(temp_user);
        std::cout << "Enter your last name: " << std::endl;
        std::cin.sync();
        getline(std::cin, temp_user);
        my_user.set_last_name(temp_user);
        std::vector<std::string> user_interests;
        std::string user_answer_interest;
        std::cout << "What are you interested in?" << std::endl << "Type end to finish" << std::endl;
        std::cin.sync();
        getline(std::cin, user_answer_interest);
        while (!(user_answer_interest == "end")) {
            user_interests.push_back(user_answer_interest);
            std::cin.sync();
            getline(std::cin, user_answer_interest);
        }
        my_user.set_interests(user_interests);
        std::string date;
        std::cout << std::endl << "When is your birthday?(mm/dd/yyyy)" << std::endl;
        std::cin.sync();
        getline(std::cin, date);
        my_user.set_date_of_birth(date);
        user_information msgInstance;
        std::cout << "The following is your complete USERID generated by BOOST :\n";
        char uuidCharArray[42];
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
        strncpy(msgInstance.uuid, uuidCharArray, 42 - 5);
        std::vector<Post> temp_post_vec;
        //my_user.write_to_file();
        msgInstance.first_name = my_user.get_first_name().c_str();    //SET FNAME AND LNAME IS MSGINSTANCE
        msgInstance.last_name = my_user.get_last_name().c_str();
        msgInstance.date_of_birth = my_user.get_date_of_birth();
        my_user.set_number_of_highest_post(0);
        msgInstance.number_of_highest_post = my_user.get_number_of_highest_post();
        msgInstance.interests.length(
        my_user.get_interests().size());       //SET UP VALUES IN user_information STRUCT FOR DDS.
        for (auto i = 0; i < static_cast<int>(my_user.get_interests().size()); i++) {
            msgInstance.interests[i] = my_user.get_interests().at(i).c_str();
        }

        return msgInstance;
    }
  TSN::user_information blank_instance;
  strcpy(blank_instance.first_name,"fail");
  return blank_instance;
}

/*//////////////////////////////////////////////////
/ PRINT USER INFORMATION                           /
/                                                  /
///////////////////////////////////////////////////*/

void print(TSN::user_information D) 
{
    std::stringstream ss;
    auto locate = user_hash_map.find(D.uuid);
    if(locate == user_hash_map.end())
    {
        ss << "USER ONLINE: " << std::endl;
    }
    ss << "Received : user_information" << std::endl;
    ss << "               " << D.uuid << " "
              << D.first_name << " "
              << D.last_name << std::endl;
    ss << std::endl;
    print_queue.push(ss.str());
}

/*//////////////////////////////////////////////////
/ TEST DATA RESPONSE                               /
/                                                  /
///////////////////////////////////////////////////*/

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

/*//////////////////////////////////////////////////
/ PRINT RESPONSE                                   /
/                                                  /
///////////////////////////////////////////////////*/

void print(TSN::response D) 
{
    std::stringstream ss;
    ss << "Received : response" << std::endl;
    ss << "               " << D.uuid << " "
              << D.post_id << " "
              << D.post_body << " "
              << D.date_of_creation << std::endl;
    ss << std::endl;
    print_queue.push(ss.str());
}

/*//////////////////////////////////////////////////
/ EDIT USER DATA                                   /
/                                                  /
///////////////////////////////////////////////////*/

void edit_user_data() {

    std::string temp_fname;
    cout << "Enter your first name: " << std::endl;
    std::cin.sync();
    getline(std::cin, temp_fname);
    my_user.set_first_name(temp_fname);
    
    std::string temp_lname;
    std::cout << "Enter your last name: " << std::endl;
    std::cin.sync();
    getline(std::cin, temp_lname);
    my_user.set_last_name(temp_lname);

    std::vector<std::string> user_interests;
    std::string user_answer_interest;
    std::cout << "What are you interested in?" << std::endl << "Type end to finish" << std::endl;
    std::cin.sync();
    getline(std::cin, user_answer_interest);
    while (!(user_answer_interest == "end")) {
        user_interests.push_back(user_answer_interest);
        std::cin.sync();
        getline(std::cin, user_answer_interest);
    }
    my_user.set_interests(user_interests);

    std::string date;  std::cout << std::endl << "When is your birthday?(mm/dd/yyyy)" << std::endl;
    std::cin.sync();
    getline(std::cin, date);
    my_user.set_date_of_birth(date);
    my_user.set_number_of_highest_post(post_count);
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

/*//////////////////////////////////////////////////
/ MAKE POST                                        /
/                                                  /
///////////////////////////////////////////////////*/

void make_post(char string[37], int sno) {
    std::ofstream myfile;
    myfile.open("my_user.tsn", ios::app);
    std::string post_text;
    std::cout << "Enter the post text" << std::endl;
    std::cin.sync();
    getline(std::cin, post_text);
    my_user.set_post_singular(post_text, sno);
    myfile << "SNO:" << sno << " POST:" << post_text << endl;
    post_count++;
    my_user.set_number_of_highest_post(post_count);
    myfile.close();
}

/*//////////////////////////////////////////////////
/ RESYNC                                           /
/                                                  /
///////////////////////////////////////////////////*/

void resync() {

    if (remove("users.tsn") != 0)
        perror("Error Deleting File. Resync unsuccessfull");
    else
        cout << "File successfully deleted\n" << std::endl;

}

/*//////////////////////////////////////////////////
/ INITIALIZE PARAMETERS                            /
/                                                  /
///////////////////////////////////////////////////*/

void init_params()
{
    std::ifstream inputFile("params.tsn");
    string line;

    while(getline(inputFile,line))
    {
        istringstream ss(line);

        ss >> sno >> user_is_initiated >> post_count >> known_nodes;
    }

    inputFile.close();
}

/*//////////////////////////////////////////////////
/ SET PARAMETERS                                   /
/                                                  /
///////////////////////////////////////////////////*/

void set_params()
{
    std::ofstream file;
    file.open("params.tsn", std::ios::app);
    file << sno << " " << user_is_initiated << " " << post_count << " " << known_nodes;  
    file.close();
}

/*//////////////////////////////////////////////////
/ CALCULATE STATS- NOT FUNCTIONAL                  /
/                                                  /
///////////////////////////////////////////////////*/

void calculate_stats()
{
    int count = static_cast<int>(my_user.get_number_of_highest_post());
    int total = count;
    int nodes = 0;
    for(auto iter = user_hash_map.begin(); iter != user_hash_map.end(); iter++)
    {
        User get_post_user = iter->second;
        total += static_cast<int>(get_post_user.get_number_of_highest_post());
        nodes++;
    }
    std::cout << "TOTAL NODES: " << nodes << std::endl;
    std::cout << "Pecentage in this node: " <<( (double)count / (double)total ) * 100 << std::endl;
}

 
/*//////////////////////////////////////////////////
/ VIEW INFORMATION ABOUT A PARTICULAR USER         /
/                                                  /
///////////////////////////////////////////////////*/

void show_user()
{
    std::string user;
    std::cout << "Choose which user:" << std::endl;
    std::vector<User> temp = Request::list_pub_users();
    for(size_t i = 0; i < temp.size(); i++)
    {
        std::cout << "USER " << i << std::endl;
        std::cout << temp[i] << std::endl;
    }
    std::cout << "Choice: ";
    cin.sync();
    std::getline(std::cin, user);
    int user_idx = stoi(user);
    auto locate = user_hash_map.find(temp[user_idx].return_uuid());
    if(locate != user_hash_map.end())
    {
        User temp_user_t = locate->second;
        std::cout << "POSTS" << std::endl;
        std::vector<Post> bleh=temp_user_t.get_post();
        for(size_t i =0; i < bleh.size();i++)
        {
            std::cout << bleh[i].get_post_data() << bleh[i].get_serial_number() << std::endl;
        }
    }
}

/*//////////////////////////////////////////////////
/ GET POSTS                                        /
/                                                  /
///////////////////////////////////////////////////*/

std::vector<Post> get_posts(unsigned long long number_of_posts, User to_request)
{
    std::vector<TSN::response> responses;
    std::vector<Post> temp_posts;
    Request new_req;
    request user_request;
    node_request request_posts;
    strcpy(request_posts.fulfiller_uuid, to_request.return_uuid());
    request_posts.requested_posts.length(number_of_posts);
    int post = 1;
    for(int i = 0; i < static_cast<int>(number_of_posts); i++) 
    {
        request_posts.requested_posts[i] = post++;
    }
    strcpy(user_request.uuid, my_user.return_uuid());
    user_request.user_requests.length(1);
    user_request.user_requests[0] = request_posts;
    new_req.publishEvent(user_request);
    responses = res.recv();
    for(size_t i = 0; i < responses.size(); i++)
    {
        std::string post_body(responses[i].post_body);
        Post new_post;
        new_post.set_serial_number(responses[i].post_id);
        new_post.enter_post_data(post_body);
        new_post.set_date_of_creation(responses[i].date_of_creation);
        temp_posts.push_back(new_post);
    }
    return temp_posts;
}

/*//////////////////////////////////////////////////
/ SEND MESSAGE                                     /
/                                                  /
///////////////////////////////////////////////////*/

void send_message()
{
    TSN::private_message msg;
    std::string answer;
    std::string message_data;
    std::cout << "Who would you like to send a message to: " << std::endl;
    std::vector<User> users = Request::list_pub_users();
    for(size_t i = 0; i < users.size(); i++)
    {
        std::cout << "User: " << i << std::endl;
        std::cout << users[i] << std::endl;
    }
    std::cout << "Enter user number: ";
    std::cin.sync();
    getline(std::cin, answer);
    // check if answer is a number 
    char * p;
    strtol(answer.c_str(),&p,10);

    while(p == 0)
    {
        std::cout<< "Enter a valid number" << std::endl;
        std::cin.sync();
        std::cin >> answer;
        strtol(answer.c_str(), &p, 10);
    }
    std::cout << std::endl << "What would you like to say to user " << answer << "?" << std::endl;
    std::cin.sync();
    std::getline(std::cin, message_data);
    long result = static_cast<long>(std::time(nullptr));
    msg.date_of_creation = result;
    int index = std::stoi(answer);
    msg = Message::construct_message(users[index].return_uuid(), my_user.return_uuid(),
                                    message_data, result);
    Message m(msg);
    m.publishEvent(msg);
}
bool is_request_to_send(TSN::request req)
{
    for(int i = 0; i < static_cast<int>(req.user_requests.length()); i++)
    {
        std::string locate(req.user_requests[i].fulfiller_uuid);
        if(user_hash_map.find(locate) != user_hash_map.end())
        {
            return false;
        }
    }
    return true;
}
void grab_posts(User user_to_request)
{
    char * user_uuid = user_to_request.return_uuid();
    std::string locate(user_uuid);
    if(user_hash_map.find(locate) == user_hash_map.end() && user_to_request.get_number_of_highest_post() != 0)
    {
        node_request temp_request_t;
        strcpy(temp_request_t.fulfiller_uuid, user_uuid);
        request temp_request;
        strcpy(temp_request.uuid, my_user.return_uuid());
        int idx = 0;
        unsigned long size = user_to_request.get_number_of_highest_post();
        temp_request_t.requested_posts.length(static_cast<int>(size));
        for(int i = 1; i <= static_cast<int>(size); i++)
        {
            temp_request_t.requested_posts[idx] = i;
            idx++;
        }
        temp_request.user_requests.length(1);
        temp_request.user_requests[0] = temp_request_t;
        req_to_send.publishEvent(temp_request);
        user_hash_map.insert({locate, user_to_request});
    }
    else if(user_to_request.get_number_of_highest_post() != 0)
    {
        std::map<std::string, User>::iterator it = user_hash_map.find(locate);
        User found_user = it->second;
        if(found_user.get_number_of_highest_post() < user_to_request.get_number_of_highest_post())
        {
            node_request temp_request_t;
            strcpy(temp_request_t.fulfiller_uuid, user_uuid);
            request temp_request;
            strcpy(temp_request.uuid, my_user.return_uuid());
            int idx = 0;
            unsigned long size = user_to_request.get_number_of_highest_post();
            temp_request_t.requested_posts.length(size);
            for(int i = 1; i <= static_cast<int>(size); i++)
            {
                temp_request_t.requested_posts[idx] = i;
            }
            temp_request.user_requests.length(1);
            temp_request.user_requests[0] = temp_request_t;
            req_to_send.publishEvent(temp_request);
            std::string s(user_uuid);
            auto it = user_hash_map.find(locate);
            if(it != user_hash_map.end())
                it->second = user_to_request;
        }
    }
}

void print_all()
{
    while(!print_queue.empty())
    {
        std::cout << print_queue.front() << std::endl;
        print_queue.pop();
    }
}
void entry_point()
{
    std::string logo[16];
    logo[0] =  "TTTTTTTTTTTTTTTTTTTTTTT   SSSSSSSSSSSSSSS NNNNNNNN        NNNNNNNN";
    logo[1] =  "T:::::::::::::::::::::T SS:::::::::::::::SN:::::::N       N::::::N";
    logo[2] =  "T:::::::::::::::::::::TS:::::SSSSSS::::::SN::::::::N      N::::::N";
    logo[3] =  "T:::::TT:::::::TT:::::TS:::::S     SSSSSSSN:::::::::N     N::::::N";
    logo[4] =  "TTTTTT  T:::::T  TTTTTTS:::::S            N::::::::::N    N::::::N";
    logo[5] =  "        T:::::T        S:::::S            N:::::::::::N   N::::::N";
    logo[6] =  "        T:::::T         S::::SSSS         N:::::::N::::N  N::::::N";
    logo[7] =  "        T:::::T          SS::::::SSSSS    N::::::N N::::N N::::::N";
    logo[8] =  "        T:::::T            SSS::::::::SS  N::::::N  N::::N:::::::N";
    logo[9] =  "        T:::::T               SSSSSS::::S N::::::N   N:::::::::::N";
    logo[10] = "        T:::::T                    S:::::SN::::::N    N::::::::::N";
    logo[11] = "        T:::::T                    S:::::SN::::::N     N:::::::::N";
    logo[12] = "      TT:::::::TT      SSSSSSS     S:::::SN::::::N      N::::::::N";
    logo[13] = "      T:::::::::T      S::::::SSSSSS:::::SN::::::N       N:::::::N";
    logo[14] = "      T:::::::::T      S:::::::::::::::SS N::::::N        N::::::N";
    logo[15] = "      TTTTTTTTTTT       SSSSSSSSSSSSSSS   NNNNNNNN         NNNNNNN";
    WINDOW * login = newwin(LINES, COLS,0,0);
    box(login, '|', '~');
    wborder(login, '|', '|', '~', '~', '+', '+', '+', '+');
    wrefresh(login);
    int j = 3;
    start_color();
    init_pair(1, COLOR_BLUE, COLOR_BLACK);
    init_pair(2, COLOR_WHITE, COLOR_BLACK);
    wbkgd(stdscr,COLOR_PAIR(1));
    wbkgd(login, COLOR_PAIR(1));
    refresh();
    wrefresh(login);
    wattron(login,COLOR_PAIR(2));
    mvwprintw(login,3, COLS/2 - 35, "Made by: EDGAR, ADI, ATAFO, TUFAN");
    wattroff(login,COLOR_PAIR(2));
    mvwprintw(login,LINES-2, 2, "PRESS ANY KEY TO CONTINUE");
    for(int i = 0; i < 16; i++)
    {
        mvwprintw(login,++j, COLS/2 - 35, logo[i].c_str());
        wrefresh(login);
    }
    refresh();
    getchar();
    endwin();
}
int kbhit()
{
    int ch = getch();

    if (ch != ERR) {
        ungetch(ch);  std::string choices[] = {"List Users", "Show User", "Edit", "Resync", "Post", "Show Statistics","Request Post", "Message", "Exit"};
    int choice;
    int highlight = 0;
    WINDOW * menu_screen_lhs;
    WINDOW * menu_screen_rhs;
    menu_screen_lhs = newwin(LINES - 8,COLS / 2 - 20, 7,15);
    menu_screen_rhs = newwin(LINES - 8,COLS / 2 - 20, 7,COLS / 2 + 1);
    keypad(menu_screen_lhs, TRUE);
    box(menu_screen_lhs, 0, 0);
    box(menu_screen_rhs, 0, 0);
    wattron(menu_screen_lhs, COLOR_PAIR(1));
    wattron(menu_screen_rhs, COLOR_PAIR(1));
    wborder(menu_screen_lhs, '|', '|', '=', '=', '+', '+', '+', '+');
    wborder(menu_screen_rhs, '|', '|', '=', '=', '+', '+', '+', '+');
    while(1)
    {
        wrefresh(menu_screen_rhs);
        wrefresh(menu_screen_lhs);
        int y;
        int x;
        getmaxyx(menu_screen_lhs,y,x);
        y++;
        for(size_t i = 0; i < 9; i++)
        {
            if((int)i == highlight)
                wattron(menu_screen_lhs,A_REVERSE);

            mvwprintw(menu_screen_lhs,i+1,x/2 - 7, choices[i].c_str());
            wattroff(menu_screen_lhs, A_REVERSE);
        }
        choice = wgetch(menu_screen_lhs);

        switch(choice)
        {
            case KEY_UP:
                highlight--;
                if(highlight == -1)
                    highlight = 0;
                break;
            case KEY_DOWN:
                highlight++;
                if(highlight == 9)
                    highlight = 8;
                break;
            default:
                break;
        }
        if(highlight == 8 && choice == 10) break;
    }
    wrefresh(menu_screen_lhs);
    wrefresh(menu_screen_rhs);
    refresh();
    getchar();
        return 1;
    } else {
        return 0;
    }
}
void destroy_win(WINDOW *local_win)
{   
    wborder(local_win, ' ', ' ', ' ',' ',' ',' ',' ',' ');
    wrefresh(local_win);
    delwin(local_win);
}

