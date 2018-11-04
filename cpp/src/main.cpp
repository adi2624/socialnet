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
#include "dds_io.h"


using namespace DDS;
using namespace TSN;

int sno = 0;        //KEEPS TRACK OF SERIAL NO: DO NOT REMOVE IT'S A GLOBAL VARIABLE
void receive_request();
void print ( TSN::request D );
Request* pub;
TSN::request test_data_request ();

std::map<int, std::string> userPostMap;
Post my_post;
User my_user;
std::vector<TSN::request> V ;
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
         std::thread req_thread(receive_request);
         while(answer=="Y")
       {
        TSN::request instance=test_data_request();
        pub = new Request(instance.uuid,instance.user_requests[0]);
        pub->publishEvent(instance.uuid,instance.user_requests[0]);
       
        std::cout<<"Do you want to continue?--------------------------------------------------------------------------------------------------------------------------"<<std::endl;
        std::cin>> answer;
        
       }
       req_thread.join();
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