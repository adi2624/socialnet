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
#include "os.h"
#include "User.h"
#include "example_main.h"
#include <boost/lexical_cast.hpp>
#include <boost/regex.hpp>
#include "Request.h"
#include "Response.h"

using namespace DDS;
using namespace TSN;

int sno = 0;        //KEEPS TRACK OF SERIAL NO: DO NOT REMOVE IT'S A GLOBAL VARIABLE
void make_post(char string[37], int sno);
std::vector<User> list_pub_users();
void start_response_publisher(int post_no);
void start_response_subscriber();
Request* start_request_publisher();
void start_request_subscriber();
std::string load_post(int post_no);
std::string load_uuid();

std::map<int, std::string> userPostMap;
Post my_post;
User my_user;

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
int user_informationPublisher(int argc, char *argv[]) {
    os_time delay_1s = {1, 0};
    DDSEntityManager mgr;

    std::cout << "Creating Participant" << std::endl;
    // create domain participant
    mgr.createParticipant("TSN example");
    std::cout << "Participant created" << std::endl;

    //create type
    user_informationTypeSupport_var mt = new user_informationTypeSupport();
    mgr.registerType(mt.in());

    //create Topic
    char topic_name[] = "tsn_Msg";
    mgr.createTopic(topic_name);

    //create Publisher
    mgr.createPublisher();

    // create DataWriter :
    // If autodispose_unregistered_instances is set to true (default value),
    // you will have to start the subscriber before the publisher
    bool autodispose_unregistered_instances = false;
    mgr.createWriter(autodispose_unregistered_instances);

    // Publish Events
    DataWriter_var dwriter = mgr.getWriter();
    user_informationDataWriter_var TSNWriter = user_informationDataWriter::_narrow(dwriter.in());

    int user_found = 0;
    std::string temp_user;
    cout << "Enter your first name: " << std::endl;
    std::cin >> temp_user;
    my_post.set_first_name(temp_user);
    my_user.set_first_name(temp_user);

    std::cout << "Enter your last name: " << std::endl;
    std::cin >> temp_user;
    my_post.set_last_name(temp_user);
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
    my_post.set_interest(user_interests);

//std::string date;
//std::cout << std::endl << "When is your birthday?(mm/dd/yyyy)" << std::endl;
//std::cin >> date;
//int month = stoi(date.substr(0,2));
//int day = stoi(date.substr(3,5));
//int year = stoi(date.substr(6,10));
//long seconds_birthday = calculate_seconds(month,day,year);
//my_user.set_date(seconds_birthday);



    user_information msgInstance; /* Example on Stack */
/* Begin of Initialization of Booost UUID */
    std::cout << "The following is your complete USERID generated by BOOST :\n";
    std::ifstream myfile;
    myfile.open("hello.tsn", ios::in);
    char uuidCharArray[37];
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
        std::vector<Post> temp_post_vec;
        my_post.enter_post_data("Test data.");
        temp_post_vec.push_back(my_post);
        my_user.set_post(temp_post_vec);
        my_user.write_to_file();
    } else {
        user_found = 1;
    }
    strncpy(msgInstance.uuid, uuidCharArray + 5, 42 - 5);  //COPY UUID INTO MSGINSTANCE OBJECT


/*  End of Boost UUID  */
    msgInstance.first_name = my_post.get_first_name().c_str();    //SET FNAME AND LNAME IS MSGINSTANCE
    msgInstance.last_name = my_post.get_last_name().c_str();

    //std::cout<<msgInstance.uuid<<endl;
    msgInstance.interests.length(
            my_post.get_interests().size());       //SET UP VALUES IN user_information STRUCT FOR DDS.
    for (auto i = 0; i < static_cast<int>(my_post.get_interests().size()); i++) {
        msgInstance.interests[i] = my_post.get_interests().at(i).c_str();
    }

    std::cout << my_post.get_interests().size() << endl;


    cout << "=== [Publisher] writing a message containing :" << endl;
    cout << "    userID  : " << msgInstance.uuid << endl;
    cout << "    Name : \"" << msgInstance.first_name << " " << msgInstance.last_name << "\"" << endl;
    cout << "The following are the User's interests " << endl;
    for (int i = 0; i < static_cast<int>(my_post.get_interests().size()); i++) {
        cout << msgInstance.interests[i] << endl;
    }

    //WRITE TO THE DDS NETWORK.
    ReturnCode_t status = TSNWriter->write(msgInstance, DDS::HANDLE_NIL);
    checkStatus(status, "MsgDataWriter::write");
    os_nanoSleep(delay_1s);

    /* Remove the DataWriters */
    mgr.deleteWriter();

    /* Remove the Publisher. */
    mgr.deletePublisher();
    /* Remove the Topics. */
    mgr.deleteTopic();

    /* Remove Participant. */
    mgr.deleteParticipant();

    return user_found;
}

/*////////////////////////////////////
/
/       USER INFORMATION SUBSCRIBER
/   
/
////////////////////////////////////*/
int user_informationSubscriber(int argc, char *argv[]) {
    os_time delay_2ms = {0, 2000000};
    os_time delay_200ms = {0, 200000000};
    user_informationSeq msgList;    //DATA STRUCTURE THAT RECEIVES MSGS.
    SampleInfoSeq infoSeq;

    DDSEntityManager mgr;

    // create domain participant
    mgr.createParticipant("TSN example");

    //create type
    user_informationTypeSupport_var mt = new user_informationTypeSupport();
    mgr.registerType(mt.in());

    //create Topic
    char topic_name[] = "tsn_Msg";
    mgr.createTopic(topic_name);

    //create Subscriber
    mgr.createSubscriber();

    // create DataReader
    mgr.createReader();

    DataReader_var dreader = mgr.getReader();
    user_informationDataReader_var HelloWorldReader = user_informationDataReader::_narrow(dreader.in());
    checkHandle(HelloWorldReader.in(), "user_informationDataReader::_narrow");

    cout << "=== [Subscriber] Ready ..." << endl;

    bool closed = false;
    bool flag = false;
    ReturnCode_t status = -1;
    int count = 0;
    User static_user; //USER OBJECT TO WRITE PARAMETERS TO USERS.TSN
    std::vector<std::string> user_interests;
    while (!closed && count < 1500) // We dont want the example to run indefinitely
    {
        status = HelloWorldReader->take(msgList, infoSeq, LENGTH_UNLIMITED,
                                        ANY_SAMPLE_STATE, ANY_VIEW_STATE, ANY_INSTANCE_STATE);
        checkStatus(status, "user_informationDataReader::take");
        for (DDS::ULong j = 0; j < msgList.length(); j++) {
            cout << "=== [Subscriber] message received :" << endl;
            cout << "    userID  : " << msgList[j].uuid << endl;
            cout << "    Name : \"" << msgList[j].first_name << " " << msgList[j].last_name << "\"" << endl;
            std::string fname(msgList[j].first_name);
            static_user.set_first_name(fname);
            std::string lname(msgList[j].last_name);    //SET PARAMETERS IN THE USER OBJECT AFTER READING.
            static_user.set_last_name(lname);
            static_user.set_user_uuid(msgList[j].uuid);


            cout << " The following are the user's " << msgList[j].interests.length() << " interests " << endl;
            for (DDS::ULong k = 0; k < msgList[j].interests.length(); k++) {
                cout << "   " << k + 1 << "  " << msgList[j].interests[k] << endl;
                std::string interest(msgList[j].interests[k]);
                user_interests.push_back(interest);
            }
            closed = true;
            flag = true;
        }
        static_user.set_interests(user_interests);  //PUSH INTERESTS TO USER OBJECT
        if (flag == true)
            static_user.write_to_file();  //WRITE USER TO FILE
        status = HelloWorldReader->return_loan(msgList, infoSeq);
        checkStatus(status, "user_informationDataReader::return_loan");
        os_nanoSleep(delay_200ms);
        ++count;
    }

    os_nanoSleep(delay_2ms);

    //cleanup
    mgr.deleteReader();
    mgr.deleteSubscriber();
    mgr.deleteTopic();
    mgr.deleteParticipant();
    std::cout << "The subscriber is ending" << std::endl;
    return 0;
}
//END OF SUBSCRIBER
/*////////////////////////////////////
/
/       MAKE POST
/   
/
////////////////////////////////////*/
void make_post(char string[37], int sno) {
    std::ofstream myfile;
    myfile.open("hello.tsn", ios::app);
    std::string post_text;
    std::cout << "Enter the post text" << std::endl;
    cin.ignore();
    getline(std::cin, post_text);
    userPostMap[sno] = post_text;
    myfile << "SNO:" << sno << " POST:" << post_text << endl;
    myfile.close();
}

/*////////////////////////////////////
/
/       LOAD POST
/   
/
////////////////////////////////////*/
/*std::string load_post(int post_no) {
    std::map<int, std::string>::iterator postIter = userPostMap.find(post_no);
    if (postIter == userPostMap.end()) return "Fail";
    return postIter->second;
}
*/
/*////////////////////////////////////
/
/       LIST USERS
/   
/
////////////////////////////////////*/
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

/*////////////////////////////////////
/
/       SHOW USERS DATA
/   
/
////////////////////////////////////*/
void show_user_data() {
    //THIS IS THE REQUEST PUBLISHER
   
   Request*pub = start_request_publisher();

//THIS IS THE REQUEST SUBSCRIBER PART OF THE CODE

    start_request_subscriber();
    pub->dispose();
    delete pub;
}
std::vector<User> list_pub_users() 
{

    std::vector<User> name_user;        //EXPORT A VECTOR OF USERS AFTER LOADING ALL USERS FROM USERS.TSN
    std::string temp_line;
    std::ifstream file("users.tsn");
    while (!file.eof()) 
    {
        User my_user;
        std::getline(file, temp_line);
        //std::cout << temp_line << std::endl;
        if (temp_line != "")        //Don't run loop on empty newline.
        {
           std::size_t pos_lname = temp_line.find("LNAME");
           std::size_t pos_fname = temp_line.find("FNAME");
           std::size_t pos_interests = temp_line.find("Inter");
           std::size_t pos_uuid = temp_line.find("UUID:");
           std::string temp_fname;
           std::string temp_lname;
           std::string temp_uuid;

           temp_fname = temp_line.substr(pos_fname + 6, pos_lname - 7);
           temp_lname = temp_line.substr(pos_lname + 6, pos_interests - 19);
           temp_uuid = temp_line.substr(pos_uuid + 6);
           
            //std::cout<<"Space found at "<<pos_fname<<std::endl;
         
            my_user.set_first_name(temp_fname);
            my_user.set_last_name(temp_lname);
            my_user.set_user_uuid(temp_uuid);
            name_user.push_back(my_user);
            //std::cout<<"Name: "<<temp_line.substr(pos+1,pos_name-1)<<"UUID: "<<temp_line.substr(pos_uuid+5);
            //name_user.push_back(temp_line.substr(pos+1,pos_name-1)+temp_line.substr(pos_uuid+5));
        }
    }
    file.close();
    return name_user;
}

/*////////////////////////////////////
/
/      RE SYNC
/   
/
////////////////////////////////////*/
void resync() {

    if (remove("users.tsn") != 0)
        perror("Error Deleting File. Resync unsuccessfull");
    else
        cout << "File successfully deleted\n" << std::endl;

}

/*////////////////////////////////////
/
/       EDIT USER DATA
/   
/
////////////////////////////////////*/
void edit_user_data() {

    std::string temp_user;
    cout << "Enter your first name: " << std::endl;
    std::cin >> temp_user;
    my_post.set_first_name(temp_user);
    my_user.set_first_name(temp_user);

    std::cout << "Enter your last name: " << std::endl;
    std::cin >> temp_user;
    my_post.set_last_name(temp_user);
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
    my_post.set_interest(user_interests);

//  std::string date;
//  std::cout << std::endl << "When is your birthday?(mm/dd/yyyy)" << std::endl;
//  std::cin >> date;
//  int month = stoi(date.substr(0,2));
//  int day = stoi(date.substr(3,5));
//  int year = stoi(date.substr(6,10));
//  long seconds_birthday = calculate_seconds(month,day,year);
//  my_user.set_date(seconds_birthday);

}

/*////////////////////////////////////
/
/   LOOP TO CONTINUOUSLY RUN SUBSCRIBER
/   
/
////////////////////////////////////*/
void run_subscriber(int argc, char *argv[]) {
    while (1) {
        user_informationSubscriber(argc, argv);
        sleep(10);
    }
}

/*////////////////////////////////////
/
/       MAIN
/   
/
////////////////////////////////////*/
int OSPL_MAIN(int argc, char *argv[]) {
    User externPost;
    std::vector<std::string> topic_names;
    std::string user_info("\"user_information\"");
    std::cout << "Welcome to the Social Network!" << std::endl;
    std::cout << "The program is listening for UserInformation published on the " << user_info << " topic" << std::endl;
    std::cout << "Starting Subscriber ........ " << std::endl;
    std::cout << "Lets setup your profile! " << std::endl;
    int is_user_found = user_informationPublisher(argc, argv);
    //std::thread second(run_subscriber,argc,argv);
    char uuidCharArray[17];
    if (is_user_found) {
        std::cout << "UUID FOUND. Loading from file" << std::endl;
        std::ifstream input;
        input.open("hello.tsn", ios::in);
        //LOAD GENERATED UUID AND COUNT THE NO OF POSTS IN THE DISK.
        input.getline(uuidCharArray, 42);
        std::cout << "Loaded: " << uuidCharArray << std::endl;
        while (input) {
            std::string garbage_value;
            std::getline(input, garbage_value);
            sno++;
        }
        input.close();
    }
    //user_informationPublisher(argc,argv);
    //std::thread second(run_subscriber,argc,argv);    //PROGRAM SEG FAULTS UPON LAUNCHING THREAD. RUN SUBSCRIBER SHOULD USE THREAD TO CHECK CONTINUOSLY BUT DISABLED FOR NOW.

    while (1) {
        int user_action_num;
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
                break; //action for list user
            case 2:
                show_user_data();
                break; //action for show user
            case 3:
                edit_user_data();
                break; //action for edit
            case 4:
                resync();
                break; //action for resync
            case 5:
                make_post(uuidCharArray, sno);
                break;
            case 6:
                break; //action for statistics
        }
        externPost.set_map(userPostMap);
        if (user_action_num == 7) break;

    }



    //first.join();   IMPORTANT! THIS NEEDS TO BE JOINED LATER.


    //std::cout<<"Joining has finished"<<std::endl;


    /*

    TESTING FOR LIST ALL USERS. WRITE_TO_FILE() HAS BEEN DEACTIVATED HERE.

   std::string temp;
   temp=load_post(1); //Make sure to change the number of the post that you want to find.
   std::cout<<"Found :"<<temp<<std::endl;
   std::vector<std::string> users_list = list_all_users();
   for(int i=0;i<users_list.size();i++)
   {
     std::cout<<users_list.at(i)<<std::endl;
   }
   */
    // second.join();
    return 0;

}

void start_response_publisher(int post_no)
{
    std::cout<< "[Starting Response Publisher]......"<<std::endl;
    Response *response_pub;
    std::string post = load_post(post_no);
    std::cout<<"Found post: "<<post<<std::endl;
    std::string uuid;
    uuid = load_uuid();
    int id = 1;
    long date = 1000;
    response_pub = new Response(uuid, id, date, post);
    response_pub->publishEvent(uuid, id, date, post);
    std::cout<<"[Publishing has finished]..."<<std::endl;
    response_pub->dispose();
    delete response_pub;

}
void start_response_subscriber()
{
    std::cout << "[Starting subscriber...]" << std::endl;
   // os_time delay_2ms = { 0, 2000000 };
    responseSeq msgList;
    SampleInfoSeq infoSeq;

    DDSEntityManager mgr;

    char partition_name[] = "response Ownership";
    mgr.createParticipant(partition_name);

    responseTypeSupport_var st = new responseTypeSupport();
    mgr.registerType(st.in());

    char topic_name[] = "response";
    mgr.createTopic(topic_name);

    mgr.createSubscriber();
    mgr.createReader();


    DataReader_var dreader = mgr.getReader();
    responseDataReader_var responseDataReader = responseDataReader::_narrow(dreader.in());
    checkHandle(responseDataReader.in(), "responseDataReader::_narrow");

    bool closed = false;
    ReturnCode_t status = -1;
    int count = 0;
    while(!closed && count < 1500)
    {
        status = responseDataReader->take(msgList, infoSeq, LENGTH_UNLIMITED,
                                          ANY_SAMPLE_STATE, ANY_VIEW_STATE, ANY_INSTANCE_STATE);
        checkStatus(status, "responseDataReader::take");
        for(DDS::ULong j = 0; j < msgList.length(); j++)
        {
            std::cout << "Recieved Response: " << std::endl;
            std::cout << "Found post id: " << msgList[j].post_id << std::endl;
            std::cout << "Found post body: " << msgList[j].post_body << std::endl;
            std::cout << "Found date of creation: " << msgList[j].date_of_creation << std::endl;
            closed = true;
        }

        status = responseDataReader->return_loan(msgList, infoSeq);
        checkStatus(status, "responseDataReader::return_loan");
        //os_nanoSleep(delay_2ms);
        count++;
        //os_nanoSleep(delay_200ms);
    }

    mgr.deleteReader();
    mgr.deleteSubscriber();
    mgr.deleteTopic();
    mgr.deleteParticipant();
   // pub->dispose();
   // delete pub;
    //return 0;

}
   std::string load_post(int post_no) {
    int number = 0, i = 0;
    std::string line, post;
    std::ifstream get_post("hello.tsn");
    if (!get_post.is_open())
        perror("error while opening file");
    //get_post.open("hello.tsn",ios::in);
    if (get_post.bad())
        perror("error while reading file");
    while (std::getline(get_post, line)) {
        std::istringstream iss(line);
        std::string c;                          //GET LINE AND PUSH INTO STRINGSTREAM.
        c = iss.str();
        // std::cout<<"String received "<<c<<endl;  //Debugging string
        std::size_t pos = c.find("SNO:");
        std::size_t pos2 = c.find("POST:");           //FIND DATA after POST:
        if (i != 0)      //IGNORE UUID AT TOP OF FILE
        {
            std::string number_string = c.substr(pos + 4, pos2 - 4);
            // std::cout<<"Number String "<<number_string<<std::endl;   //please.ignore(#debug) FIND NUMBER BETWEEN SNO: and POST:
            number = std::stoi(number_string);
        }
        i++;
        if (number == post_no) {
            std::string final_post_text = c.substr(pos2 + 4);
           // std::cout << "Final text:" << final_post_text << std::endl;   //RETURN FOUND POST DATA
            return final_post_text;
        }

    }
    return "Fail";
}

std::string load_uuid()
{
    std::ifstream input_uuid;
    input_uuid.open("hello.tsn", ios::in);
     
    if (input_uuid.bad())
        perror("error while reading file");
    char uuidCharArray2[42];
    input_uuid.getline(uuidCharArray2, 42);
    char uuid[37];
    strncpy(uuid, uuidCharArray2+5, 37);
    std::string final_uuid (uuid);
    return final_uuid;
}

Request* start_request_publisher()
{
    
    
     Request *pub;
    std::cout << "Please select user from below to send a request to :" << std::endl;
    std::vector<User> name_user;
    name_user = list_pub_users();        //LIST ALL THE USERS TO CHOOSE FROM.
    int input;
    for (int i = 0; i < static_cast<int>(name_user.size()); i++) {
        std::cout << "USER " << i + 1 << std::endl;
        std::cout << "FNAME: " << name_user.at(i).get_first_name() << std::endl;
        std::cout << "LNAME: " << name_user.at(i).get_last_name() << std::endl;
        std::cout << "UUID: " << name_user.at(i).return_uuid() << std::endl;
        std::cout << std::endl;
    }
    std::cout << "Enter the user number" << std::endl;    //ENTER THE USER NUMBER.
    std::cin >> input;
    node_request user_request;
    strcpy(user_request.fulfiller_uuid, name_user.at(input - 1).return_uuid());
    std::cout << "The received request was for UUID:" << user_request.fulfiller_uuid
              << std::endl; //OUTPUT THE UUID of the Intended Receiver.
    std::cout << "Enter the serial no of the post that you want from this user" << std::endl;
    std::cin >> input;
    user_request.requested_posts.length(1);
    user_request.requested_posts[0] = input;
   // std::cout << user_request.requested_posts[0];
    //LOAD LOCAL USER'S UUID FROM HELLO.TSN
    std::ifstream input_file;
    input_file.open("hello.tsn", ios::in);
    char uuidCharArray2[42];                //user.request.uuid is the UUID of the user we want the post from. user_request2.uuid is our UUID.
    input_file.getline(uuidCharArray2, 42);
    //std::cout<<uuidCharArray2<<std::endl;
    request this_user_request2;
    strncpy(this_user_request2.uuid, uuidCharArray2+5, 37);
    //std::cout<<"UUIDend of aeeay: "<<this_user_request2.uuid<<std::endl;
    this_user_request2.user_requests.length(1);
    this_user_request2.user_requests[0] = user_request;        //COPY NODE REQUEST INTO THE FINAL REQUEST SEQUENCE.
    pub = new Request(this_user_request2.uuid, user_request);       //Send our UUID and request instance to constructor.
    pub->publishEvent(this_user_request2.uuid, user_request);
    std::cout<<"Request has been published"<<std::endl;
   // os_nanoSleep(delay_200ms);
   
    input_file.close();
    return pub;
    
}

void start_request_subscriber()
{
    bool send_response=false;
    bool closed = false;
    int requested_post_no=0;
    requestSeq reqList;
    SampleInfoSeq infoSeq;

    //Subscriber code
    std::cout << "Starting Subscriber" << std::endl;
    DDSEntityManager mgr;
    mgr.createParticipant("Request Publisher");
    requestTypeSupport_var mt = new requestTypeSupport();
    mgr.registerType(mt.in());
    char topic_name[] = "Request_msg";
    mgr.createTopic(topic_name);
    mgr.createSubscriber();
    mgr.createReader();
    DataReader_var dreader = mgr.getReader();
    requestDataReader_var PublisherReader = requestDataReader::_narrow(dreader.in());
    checkHandle(PublisherReader.in(), "requestDataReader::_narrow");
    cout << "=== [Subscriber] Ready ..." << endl;
    ReturnCode_t status = -1;
    int count = 0;
    // same deal, we want this user uuid
    std::ifstream read_uuid;
    read_uuid.open("hello.tsn", ios::in);
    char uuidCharArray[42];
    read_uuid.getline(uuidCharArray, 42);
    //std::cout<<uuidCharArray<<std::endl;
    request this_user_request;
    strncpy(this_user_request.uuid, uuidCharArray + 5, 37);
    std::cout<<"MY UUID = "<<this_user_request.uuid<<std::endl;
    while (!closed && count < 1500) // We dont want the example to run indefinitely
    {
        status = PublisherReader->take(reqList, infoSeq, LENGTH_UNLIMITED,
                                       ANY_SAMPLE_STATE, ANY_VIEW_STATE, ANY_INSTANCE_STATE);
        checkStatus(status, "requestDataReader::take");
        for (DDS::ULong j = 0; j < reqList.length(); j++) {
            //CODE TO CHECK THE CORRECT UUID's ARE BEING SENT AND RECEIVED.
            cout << "=== [Subscriber] message received :" << endl;
            cout << "    Sender userID  : " << reqList[j].uuid << endl;
            cout << "    IS THIS MY UUID? : \"" << reqList[j].user_requests[0].fulfiller_uuid << " and post_no "
                 << reqList[j].user_requests[0].requested_posts[0] << std::endl;
            if(strcmp(reqList[j].user_requests[0].fulfiller_uuid,this_user_request.uuid)==0)
            {
                std::cout<< " Posts have been requested from me!"<<std::endl;
                send_response=true;
                requested_post_no=reqList[j].user_requests[0].requested_posts[0];
            }
            
            closed = true;
        }

        status = PublisherReader->return_loan(reqList, infoSeq);
        checkStatus(status, "requestDataReader::return_loan");
       // os_nanoSleep(delay_200ms);
        ++count;
    }

    //cleanup
    mgr.deleteReader();
    mgr.deleteSubscriber();
    mgr.deleteTopic();
    mgr.deleteParticipant();
    std::cout << "The subscriber is ending" << std::endl;

    if(send_response==true)
    {
        //SEND RESPONSE;

        start_response_publisher(requested_post_no);
        start_response_subscriber();
    }
    
    
}