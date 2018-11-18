#include <string>
#include <sstream>
#include <iostream>
//#include <functional>
#include <mutex>
#include <vector>


#include "DDSEntityManager.h"
#include "ccpp_tsn.h"

using namespace DDS;
using namespace TSN;

// Interfaces to the pub/sub network
// this code is derived (copied!) from the opensplice examples



template <typename DATA_READER_VAR,typename SEQ,typename MSG> 
class read_listener: public virtual DDS::DataReaderListener
{
  private:
     std::vector<MSG> incoming_list;
     std::mutex incoming_list_lock;
  public:
     DATA_READER_VAR m_Reader;
     read_listener ()
     {
     }
     std::vector<MSG>  recv ()
     {
         incoming_list_lock.lock();
         std::vector<MSG> retval;
         retval = incoming_list;
         incoming_list.clear ();
         incoming_list_lock.unlock();
         return retval;
     }
     /* Callback method implementation. */
      virtual void on_data_available(DDS::DataReader_ptr reader)
      {
         DDS::ReturnCode_t status;
         SEQ msgList;

         SampleInfoSeq infoSeq;
         status = m_Reader->take(msgList, infoSeq, LENGTH_UNLIMITED,
                  ANY_SAMPLE_STATE, ANY_VIEW_STATE, ANY_INSTANCE_STATE);
         checkStatus(status, "MsgDataReader::read");
         for (DDS::ULong i = 0; i < msgList.length(); i++)
         {
            if (msgList.length()>0) // you can get callback with no actual data payload
            {
               //_cb ( msgList[i] );
               incoming_list_lock.lock();
               incoming_list.push_back (msgList[i]);
               incoming_list_lock.unlock();
            }
         }
         status = m_Reader->return_loan(msgList, infoSeq);
         checkStatus(status, "MsgDataReader::return_loan");
      }

      virtual void on_requested_deadline_missed(DDS::DataReader_ptr reader,
        const DDS::RequestedDeadlineMissedStatus &status)
      {
      }

      virtual void on_requested_incompatible_qos(DDS::DataReader_ptr reader,
        const DDS::RequestedIncompatibleQosStatus &status)
      {
      }

      virtual void on_sample_rejected(DDS::DataReader_ptr reader, const DDS
        ::SampleRejectedStatus &status)
      {
      }

      virtual void on_liveliness_changed(DDS::DataReader_ptr reader, const DDS
        ::LivelinessChangedStatus &status)
      {
      }

      virtual void on_subscription_matched(DDS::DataReader_ptr reader, const
        DDS::SubscriptionMatchedStatus &status)
      {
      }

      virtual void on_sample_lost(DDS::DataReader_ptr reader, const DDS
        ::SampleLostStatus &status)
      {
      }

};


template <typename MSG, typename SEQ, typename TYPE_SUPPORT_VAR, class TYPE_SUPPORT,
          typename DATA_WRITER_VAR, class DATA_WRITER, typename DATA_READER_VAR, class DATA_READER>
class dds_io
{
  typedef void (*cb_func_type)( MSG );
   private:
      DDSEntityManager mgr;
      TYPE_SUPPORT_VAR mt;
      DataWriter_var dwriter;
      DATA_WRITER_VAR listenerWriter;
      DataReader_var dreader;
      read_listener<DATA_READER_VAR,SEQ,MSG> *myListener;
   public:
      dds_io ( char *topicName, bool pub = false, bool sub = false ) 
      {
         DDSEntityManager mgr;

         // create domain participant
         char partition_name[] = "";
         mgr.createParticipant(partition_name);

         //create type
         mt = new TYPE_SUPPORT();
         mgr.registerType(mt.in());

         //create Topic
         mgr.createTopic( topicName );

         if (pub) // meaning we intend to publish from this object
         {
            //create Publisher
            mgr.createPublisher();

            // create DataWriter
            mgr.createWriter();

           // Publish Events
           dwriter = mgr.getWriter();
           listenerWriter = DATA_WRITER::_narrow(dwriter.in());
         }

         if (sub) // meaning we intend to subscribe
         {
           // this is a subscription
           //create Subscriber
           mgr.createSubscriber();

           // create DataReader
           mgr.createReader();

           DataReader_var dreader = mgr.getReader();
       
           myListener = new read_listener<DATA_READER_VAR,SEQ,MSG> ();

           myListener->m_Reader = DATA_READER::_narrow(dreader.in());
           checkHandle(myListener->m_Reader.in(), "MsgDataReader::_narrow");

              DDS::StatusMask mask =
                    DDS::DATA_AVAILABLE_STATUS;
           myListener->m_Reader->set_listener(myListener, mask);
         }
      }

      std::vector<MSG> recv ()
      {
         return  myListener->recv ();
      }
      void publish ( MSG D )
      {
         ReturnCode_t status = listenerWriter->write(D, DDS::HANDLE_NIL );
         checkStatus(status, "MsgDataWriter::write");
      }
};

