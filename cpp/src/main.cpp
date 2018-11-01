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

using namespace DDS;
using namespace TSN;

int sno = 0;        //KEEPS TRACK OF SERIAL NO: DO NOT REMOVE IT'S A GLOBAL VARIABLE
void make_post(char string[37], int sno);

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
std::string load_post(int post_no) {
    std::map<int, std::string>::iterator postIter = userPostMap.find(post_no);
    if (postIter == userPostMap.end()) return "Fail";
    return postIter->second;
}

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
    int post_no = 0;
    std::vector<string> interests = my_post.get_interests();
    cout << "    userID  : " << my_user.return_uuid() << std::endl;
    cout << "    Name : \"" << my_post.get_first_name() << " " << my_post.get_last_name() << "\"" << std::endl;
    cout << "The following are the User's interests " << std::endl;

    for (int i = 0; i < static_cast<int>(my_post.get_interests().size()); i++) {
        cout << interests[i] << endl;
    }

    if (load_post(post_no++) == "Fail")
        return;

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
    std::string input = "N";
    std::cout << "Lets setup your profile! " << std::endl;
    int is_user_found = user_informationPublisher(argc, argv);
    //std::thread second(run_subscriber,argc,argv);
    char uuidCharArray[17];
    if (is_user_found) {
        std::cout << "UUID FOUND. Loading from file" << std::endl;
        std::ifstream input;
        input.open("hello.tsn", ios::in);
        //LOAD GENERATED UUID AND COUNT THE NO OF POSTS IN THE DISK.
        input.getline(uuidCharArray, 25);
        std::cout << "Loaded: " << uuidCharArray << std::endl;
        while (!input.eof()) {
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

   