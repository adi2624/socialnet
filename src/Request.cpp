
#include "Request.h"


using namespace TSN;
/*
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
            std::cout << "Final text:" << final_post_text << std::endl;   //RETURN FOUND POST DATA
            return final_post_text;
        }

    }
    return "Fail";
}
*/
std::vector<User> Request::list_pub_users() 
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

void Request::initPublisher(char uuid[], TSN::node_request &temp) {
    
    char partition_name[] = "Request Publisher";
    mgr.createParticipant(partition_name);

    requestTypeSupport_var st = new requestTypeSupport();
    mgr.registerType(st.in());


    char topic_name[] = "request";
    mgr.createTopic(topic_name);

    mgr.createPublisher();
    bool auto_dispose_unregistered_instances = false;

    mgr.createWriter(auto_dispose_unregistered_instances);

    dWriter = mgr.getWriter();
    _requestDataWriter = requestDataWriter::_narrow(dWriter.in());

    m_instance = new request();
    strncpy(m_instance->uuid, uuid, 37);
    m_instance->user_requests.length(1);
    m_instance->user_requests[0] = temp;

    userHandle = _requestDataWriter->register_instance(*m_instance);


}

Request::Request() {
    
}

void Request::publishEvent(TSN::request reqsend_instance) {
      dds_io<request,
                          requestSeq,
                          requestTypeSupport_var,
                          requestTypeSupport,
                          requestDataWriter_var,
                          requestDataWriter,
                          requestDataReader_var,
                          requestDataReader> req =
                          dds_io<request,
                          requestSeq,
                          requestTypeSupport_var,
                          requestTypeSupport,
                          requestDataWriter_var,
                          requestDataWriter,
                          requestDataReader_var,
                          requestDataReader>

                          ( (char*) "request", true , true );
                //        topic name,         publish, subscribe
                cout<<"Debug"<<std::endl;
req.publish(reqsend_instance);
}

void Request::dispose() {
    /* Remove the DataWriters */
    mgr.deleteWriter();

    /* Remove the Publisher. */
    mgr.deletePublisher();

    /* Remove the Topics. */
    mgr.deleteTopic();

    /* Remove Participant. */
    mgr.deleteParticipant();
}

TSN::request Request::draft_request()
{
    std::vector<User> name_user = list_pub_users();
    std::cout << "Please select user from below to send a request to :" << std::endl;
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
    this_user_request2.user_requests[0] = user_request;   
    input_file.close();
    return this_user_request2;     

}
/*

int OSPL_MAIN(int argc, char *argv[]) {

    // Publisher code
    os_time delay_200ms = {0, 200000000};
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
    std::cout << user_request.requested_posts[0];
    //LOAD LOCAL USER'S UUID FROM HELLO.TSN
    std::ifstream input_file;
    input_file.open("hello.tsn", ios::in);
    char uuidCharArray2[42];
    input_file.getline(uuidCharArray2, 42);
    
    request this_user_request2;
    strncpy(this_user_request2.uuid, uuidCharArray2+5, 37);
  //  std::cout<<"UUIDend of aeeay: "<<this_user_request2.uuid<<std::endl;
    this_user_request2.user_requests.length(1);
    this_user_request2.user_requests[0] = user_request;        //COPY NODE REQUEST INTO THE FINAL REQUEST SEQUENCE.
    pub = new Request(this_user_request2.uuid, user_request);
    pub->publishEvent(this_user_request2.uuid, user_request);
    os_nanoSleep(delay_200ms);
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
    bool closed = false;
    ReturnCode_t status = -1;
    int count = 0;
    // same deal, we want this user uuid
    input_file.open("hello.tsn", ios::in);
    char uuidCharArray[17];
    input_file.getline(uuidCharArray, 25);
    request this_user_request;
    strncpy(this_user_request.uuid, uuidCharArray + 5, 22);
    while (!closed && count < 1500) // We dont want the example to run indefinitely
    {
        status = PublisherReader->take(reqList, infoSeq, LENGTH_UNLIMITED,
                                       ANY_SAMPLE_STATE, ANY_VIEW_STATE, ANY_INSTANCE_STATE);
        checkStatus(status, "requestDataReader::take");
        for (DDS::ULong j = 0; j < reqList.length(); j++) {
            //CODE TO CHECK THE CORRECT UUID's ARE BEING SENT AND RECEIVED.
            cout << "=== [Subscriber] message received :" << endl;
            cout << "    Sender userID  : " << reqList[j].uuid << endl;
            cout << "    IS THIS MY UUID? : \"" << reqList[j].user_requests[0].fulfiller_uuid << "and post_no"
                 << reqList[j].user_requests[0].requested_posts[0] << std::endl;
            closed = true;
        }

        status = PublisherReader->return_loan(reqList, infoSeq);
        checkStatus(status, "requestDataReader::return_loan");
        os_nanoSleep(delay_200ms);
        ++count;
    }

    //cleanup
    mgr.deleteReader();
    mgr.deleteSubscriber();
    mgr.deleteTopic();
    mgr.deleteParticipant();
    pub->dispose();
    delete pub;
    std::cout << "The subscriber is ending" << std::endl;

}
*/
