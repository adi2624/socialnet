#include "Request.h"
#include "Response.h"

using namespace TSN;


std::vector<User> Request::list_pub_users() 
{
    std::vector<User> users;
    std::vector <std::string> my_interests;
    std::ifstream file;
    file.open("users.tsn");
    std::ifstream post_file;
    std::string test;
    std::string serial_number, post_data, garbage, fname, lname, uuid, interest, birthdate, post_num;
    while(std::getline(file, test))
    {
        User my_user;
        std::stringstream iss(test);
        getline(iss, garbage ,' ');
        getline(iss,fname,' ');
        getline(iss, garbage,  ' ');
        getline(iss, lname, ' ');
        getline(iss, garbage, ' ');
        getline(iss, interest, ' ');
        if(interest != "UUID:") my_interests.push_back(interest);
        while(!(interest == "UUID:"))
        {
            getline(iss, interest, ' ');
            if(interest != "UUID:") my_interests.push_back(interest);
        }
        getline(iss, uuid, ' ');
        getline(iss, garbage, ' ');
        getline(iss, birthdate, ' ');
        getline(iss, garbage , ' ');
        getline(iss, post_num, ' ');
        my_user.set_first_name(fname);
        my_user.set_last_name(lname);
        my_user.set_user_uuid(uuid);
        int highest = stoi(post_num);
        my_user.set_number_of_highest_post(static_cast<unsigned long long>(highest));
        my_user.set_interests(my_interests);
        my_user.set_date_of_birth(stol(birthdate));
        users.push_back(my_user);
    }
    file.close();
    return users;
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
               // cout<<"Debug"<<std::endl;
		req.publish(reqsend_instance);
        std::cout<<"Publishing successful"<<std::endl;
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
    std::vector<int> serial_number;
    std::vector<User> name_user = list_pub_users();
    std::cout << "Please select user from below to send a request to :" << std::endl;
    std::string temp;
    int input;
    for (int i = 0; i < static_cast<int>(name_user.size()); i++) 
    {
        std::cout << "USER " << i + 1 << std::endl;
        std::cout << "FNAME: " << name_user.at(i).get_first_name() << std::endl;
        std::cout << "LNAME: " << name_user.at(i).get_last_name() << std::endl;
        std::cout << "UUID: " << name_user.at(i).return_uuid() << std::endl;
        std::cout << std::endl;
    }
    std::cout << "Enter the user number" << std::endl;    //ENTER THE USER NUMBER.
    std::cin.sync();
    std::getline(std::cin, temp);
    input = stoi(temp);
    node_request user_request;
    strcpy(user_request.fulfiller_uuid, name_user.at(input - 1).return_uuid());
    std::cout << "The received request was for UUID:" << user_request.fulfiller_uuid
              << std::endl; //OUTPUT THE UUID of the Intended Receiver.
    std::cout << "Enter the posts id you wish to request, type end to enter:" << std::endl;
    std::cin.sync();
    std::getline(std::cin, temp);
    int length = 0 ;
    while(!(temp == "end"))
    {
        std::cout << "*" << temp << "*" << std::endl;
        input = stoi(temp);
        serial_number.push_back(input);
        length++;
        std::cin.sync();
        std::getline(std::cin, temp);
    }
    user_request.requested_posts.length(length);
    for(int i = 0; i < length; i++) 
    {
        user_request.requested_posts[i] = serial_number[i];
    }
    std::ifstream input_file;
    input_file.open("my_user.tsn", ios::in);
    char uuidCharArray2[42];                //user.request.uuid is the UUID of the user we want the post from. user_request2.uuid is our UUID.
    input_file.getline(uuidCharArray2,42);
    request this_user_request2;
    strncpy(this_user_request2.uuid, uuidCharArray2+5, 37);
    this_user_request2.user_requests.length(3);
    this_user_request2.user_requests[0] = user_request;   
    input_file.close();
    return this_user_request2;     
}
