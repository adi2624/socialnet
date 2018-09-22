//******************************************************************
// 
//  Generated by IDL to C++ Translator
//  
//  File name: tsnDcps.h
//  Source: tsnDcps.idl
//  Generated: Sat Sep 22 17:14:23 2018
//  OpenSplice V6.4.140320OSS
//  
//******************************************************************
#ifndef _TSNDCPS_H_
#define _TSNDCPS_H_

#include "sacpp_mapping.h"
#include "sacpp_DDS_DCPS.h"
#include "tsn.h"
#include "dds_dcps.h"


namespace TSN
{

   class user_informationTypeSupportInterface;

   typedef user_informationTypeSupportInterface * user_informationTypeSupportInterface_ptr;
   typedef DDS_DCPSInterface_var < user_informationTypeSupportInterface> user_informationTypeSupportInterface_var;
   typedef DDS_DCPSInterface_out < user_informationTypeSupportInterface> user_informationTypeSupportInterface_out;


   class user_informationDataWriter;

   typedef user_informationDataWriter * user_informationDataWriter_ptr;
   typedef DDS_DCPSInterface_var < user_informationDataWriter> user_informationDataWriter_var;
   typedef DDS_DCPSInterface_out < user_informationDataWriter> user_informationDataWriter_out;


   class user_informationDataReader;

   typedef user_informationDataReader * user_informationDataReader_ptr;
   typedef DDS_DCPSInterface_var < user_informationDataReader> user_informationDataReader_var;
   typedef DDS_DCPSInterface_out < user_informationDataReader> user_informationDataReader_out;


   class user_informationDataReaderView;

   typedef user_informationDataReaderView * user_informationDataReaderView_ptr;
   typedef DDS_DCPSInterface_var < user_informationDataReaderView> user_informationDataReaderView_var;
   typedef DDS_DCPSInterface_out < user_informationDataReaderView> user_informationDataReaderView_out;


   class requestTypeSupportInterface;

   typedef requestTypeSupportInterface * requestTypeSupportInterface_ptr;
   typedef DDS_DCPSInterface_var < requestTypeSupportInterface> requestTypeSupportInterface_var;
   typedef DDS_DCPSInterface_out < requestTypeSupportInterface> requestTypeSupportInterface_out;


   class requestDataWriter;

   typedef requestDataWriter * requestDataWriter_ptr;
   typedef DDS_DCPSInterface_var < requestDataWriter> requestDataWriter_var;
   typedef DDS_DCPSInterface_out < requestDataWriter> requestDataWriter_out;


   class requestDataReader;

   typedef requestDataReader * requestDataReader_ptr;
   typedef DDS_DCPSInterface_var < requestDataReader> requestDataReader_var;
   typedef DDS_DCPSInterface_out < requestDataReader> requestDataReader_out;


   class requestDataReaderView;

   typedef requestDataReaderView * requestDataReaderView_ptr;
   typedef DDS_DCPSInterface_var < requestDataReaderView> requestDataReaderView_var;
   typedef DDS_DCPSInterface_out < requestDataReaderView> requestDataReaderView_out;


   class responseTypeSupportInterface;

   typedef responseTypeSupportInterface * responseTypeSupportInterface_ptr;
   typedef DDS_DCPSInterface_var < responseTypeSupportInterface> responseTypeSupportInterface_var;
   typedef DDS_DCPSInterface_out < responseTypeSupportInterface> responseTypeSupportInterface_out;


   class responseDataWriter;

   typedef responseDataWriter * responseDataWriter_ptr;
   typedef DDS_DCPSInterface_var < responseDataWriter> responseDataWriter_var;
   typedef DDS_DCPSInterface_out < responseDataWriter> responseDataWriter_out;


   class responseDataReader;

   typedef responseDataReader * responseDataReader_ptr;
   typedef DDS_DCPSInterface_var < responseDataReader> responseDataReader_var;
   typedef DDS_DCPSInterface_out < responseDataReader> responseDataReader_out;


   class responseDataReaderView;

   typedef responseDataReaderView * responseDataReaderView_ptr;
   typedef DDS_DCPSInterface_var < responseDataReaderView> responseDataReaderView_var;
   typedef DDS_DCPSInterface_out < responseDataReaderView> responseDataReaderView_out;

   struct user_informationSeq_uniq_ {};
   typedef DDS_DCPSUVLSeq < user_information, struct user_informationSeq_uniq_> user_informationSeq;
   typedef DDS_DCPSSequence_var < user_informationSeq> user_informationSeq_var;
   typedef DDS_DCPSSequence_out < user_informationSeq> user_informationSeq_out;
   class user_informationTypeSupportInterface
   :
      virtual public DDS::TypeSupport
   { 
   public:
      typedef user_informationTypeSupportInterface_ptr _ptr_type;
      typedef user_informationTypeSupportInterface_var _var_type;

      static user_informationTypeSupportInterface_ptr _duplicate (user_informationTypeSupportInterface_ptr obj);
      DDS::Boolean _local_is_a (const char * id);

      static user_informationTypeSupportInterface_ptr _narrow (DDS::Object_ptr obj);
      static user_informationTypeSupportInterface_ptr _unchecked_narrow (DDS::Object_ptr obj);
      static user_informationTypeSupportInterface_ptr _nil () { return 0; }
      static const char * _local_id;
      user_informationTypeSupportInterface_ptr _this () { return this; }


   protected:
      user_informationTypeSupportInterface () {};
      ~user_informationTypeSupportInterface () {};
   private:
      user_informationTypeSupportInterface (const user_informationTypeSupportInterface &);
      user_informationTypeSupportInterface & operator = (const user_informationTypeSupportInterface &);
   };

   class user_informationDataWriter
   :
      virtual public DDS::DataWriter
   { 
   public:
      typedef user_informationDataWriter_ptr _ptr_type;
      typedef user_informationDataWriter_var _var_type;

      static user_informationDataWriter_ptr _duplicate (user_informationDataWriter_ptr obj);
      DDS::Boolean _local_is_a (const char * id);

      static user_informationDataWriter_ptr _narrow (DDS::Object_ptr obj);
      static user_informationDataWriter_ptr _unchecked_narrow (DDS::Object_ptr obj);
      static user_informationDataWriter_ptr _nil () { return 0; }
      static const char * _local_id;
      user_informationDataWriter_ptr _this () { return this; }

      virtual DDS::LongLong register_instance (const user_information& instance_data) = 0;
      virtual DDS::LongLong register_instance_w_timestamp (const user_information& instance_data, const DDS::Time_t& source_timestamp) = 0;
      virtual DDS::Long unregister_instance (const user_information& instance_data, DDS::LongLong handle) = 0;
      virtual DDS::Long unregister_instance_w_timestamp (const user_information& instance_data, DDS::LongLong handle, const DDS::Time_t& source_timestamp) = 0;
      virtual DDS::Long write (const user_information& instance_data, DDS::LongLong handle) = 0;
      virtual DDS::Long write_w_timestamp (const user_information& instance_data, DDS::LongLong handle, const DDS::Time_t& source_timestamp) = 0;
      virtual DDS::Long dispose (const user_information& instance_data, DDS::LongLong handle) = 0;
      virtual DDS::Long dispose_w_timestamp (const user_information& instance_data, DDS::LongLong handle, const DDS::Time_t& source_timestamp) = 0;
      virtual DDS::Long writedispose (const user_information& instance_data, DDS::LongLong handle) = 0;
      virtual DDS::Long writedispose_w_timestamp (const user_information& instance_data, DDS::LongLong handle, const DDS::Time_t& source_timestamp) = 0;
      virtual DDS::Long get_key_value (user_information& key_holder, DDS::LongLong handle) = 0;
      virtual DDS::LongLong lookup_instance (const user_information& instance_data) = 0;

   protected:
      user_informationDataWriter () {};
      ~user_informationDataWriter () {};
   private:
      user_informationDataWriter (const user_informationDataWriter &);
      user_informationDataWriter & operator = (const user_informationDataWriter &);
   };

   class user_informationDataReader
   :
      virtual public DDS::DataReader
   { 
   public:
      typedef user_informationDataReader_ptr _ptr_type;
      typedef user_informationDataReader_var _var_type;

      static user_informationDataReader_ptr _duplicate (user_informationDataReader_ptr obj);
      DDS::Boolean _local_is_a (const char * id);

      static user_informationDataReader_ptr _narrow (DDS::Object_ptr obj);
      static user_informationDataReader_ptr _unchecked_narrow (DDS::Object_ptr obj);
      static user_informationDataReader_ptr _nil () { return 0; }
      static const char * _local_id;
      user_informationDataReader_ptr _this () { return this; }

      virtual DDS::Long read (user_informationSeq& received_data, DDS::SampleInfoSeq& info_seq, DDS::Long max_samples, DDS::ULong sample_states, DDS::ULong view_states, DDS::ULong instance_states) = 0;
      virtual DDS::Long take (user_informationSeq& received_data, DDS::SampleInfoSeq& info_seq, DDS::Long max_samples, DDS::ULong sample_states, DDS::ULong view_states, DDS::ULong instance_states) = 0;
      virtual DDS::Long read_w_condition (user_informationSeq& received_data, DDS::SampleInfoSeq& info_seq, DDS::Long max_samples, DDS::ReadCondition_ptr a_condition) = 0;
      virtual DDS::Long take_w_condition (user_informationSeq& received_data, DDS::SampleInfoSeq& info_seq, DDS::Long max_samples, DDS::ReadCondition_ptr a_condition) = 0;
      virtual DDS::Long read_next_sample (user_information& received_data, DDS::SampleInfo& sample_info) = 0;
      virtual DDS::Long take_next_sample (user_information& received_data, DDS::SampleInfo& sample_info) = 0;
      virtual DDS::Long read_instance (user_informationSeq& received_data, DDS::SampleInfoSeq& info_seq, DDS::Long max_samples, DDS::LongLong a_handle, DDS::ULong sample_states, DDS::ULong view_states, DDS::ULong instance_states) = 0;
      virtual DDS::Long take_instance (user_informationSeq& received_data, DDS::SampleInfoSeq& info_seq, DDS::Long max_samples, DDS::LongLong a_handle, DDS::ULong sample_states, DDS::ULong view_states, DDS::ULong instance_states) = 0;
      virtual DDS::Long read_next_instance (user_informationSeq& received_data, DDS::SampleInfoSeq& info_seq, DDS::Long max_samples, DDS::LongLong a_handle, DDS::ULong sample_states, DDS::ULong view_states, DDS::ULong instance_states) = 0;
      virtual DDS::Long take_next_instance (user_informationSeq& received_data, DDS::SampleInfoSeq& info_seq, DDS::Long max_samples, DDS::LongLong a_handle, DDS::ULong sample_states, DDS::ULong view_states, DDS::ULong instance_states) = 0;
      virtual DDS::Long read_next_instance_w_condition (user_informationSeq& received_data, DDS::SampleInfoSeq& info_seq, DDS::Long max_samples, DDS::LongLong a_handle, DDS::ReadCondition_ptr a_condition) = 0;
      virtual DDS::Long take_next_instance_w_condition (user_informationSeq& received_data, DDS::SampleInfoSeq& info_seq, DDS::Long max_samples, DDS::LongLong a_handle, DDS::ReadCondition_ptr a_condition) = 0;
      virtual DDS::Long return_loan (user_informationSeq& received_data, DDS::SampleInfoSeq& info_seq) = 0;
      virtual DDS::Long get_key_value (user_information& key_holder, DDS::LongLong handle) = 0;
      virtual DDS::LongLong lookup_instance (const user_information& instance) = 0;

   protected:
      user_informationDataReader () {};
      ~user_informationDataReader () {};
   private:
      user_informationDataReader (const user_informationDataReader &);
      user_informationDataReader & operator = (const user_informationDataReader &);
   };

   class user_informationDataReaderView
   :
      virtual public DDS::DataReaderView
   { 
   public:
      typedef user_informationDataReaderView_ptr _ptr_type;
      typedef user_informationDataReaderView_var _var_type;

      static user_informationDataReaderView_ptr _duplicate (user_informationDataReaderView_ptr obj);
      DDS::Boolean _local_is_a (const char * id);

      static user_informationDataReaderView_ptr _narrow (DDS::Object_ptr obj);
      static user_informationDataReaderView_ptr _unchecked_narrow (DDS::Object_ptr obj);
      static user_informationDataReaderView_ptr _nil () { return 0; }
      static const char * _local_id;
      user_informationDataReaderView_ptr _this () { return this; }

      virtual DDS::Long read (user_informationSeq& received_data, DDS::SampleInfoSeq& info_seq, DDS::Long max_samples, DDS::ULong sample_states, DDS::ULong view_states, DDS::ULong instance_states) = 0;
      virtual DDS::Long take (user_informationSeq& received_data, DDS::SampleInfoSeq& info_seq, DDS::Long max_samples, DDS::ULong sample_states, DDS::ULong view_states, DDS::ULong instance_states) = 0;
      virtual DDS::Long read_w_condition (user_informationSeq& received_data, DDS::SampleInfoSeq& info_seq, DDS::Long max_samples, DDS::ReadCondition_ptr a_condition) = 0;
      virtual DDS::Long take_w_condition (user_informationSeq& received_data, DDS::SampleInfoSeq& info_seq, DDS::Long max_samples, DDS::ReadCondition_ptr a_condition) = 0;
      virtual DDS::Long read_next_sample (user_information& received_data, DDS::SampleInfo& sample_info) = 0;
      virtual DDS::Long take_next_sample (user_information& received_data, DDS::SampleInfo& sample_info) = 0;
      virtual DDS::Long read_instance (user_informationSeq& received_data, DDS::SampleInfoSeq& info_seq, DDS::Long max_samples, DDS::LongLong a_handle, DDS::ULong sample_states, DDS::ULong view_states, DDS::ULong instance_states) = 0;
      virtual DDS::Long take_instance (user_informationSeq& received_data, DDS::SampleInfoSeq& info_seq, DDS::Long max_samples, DDS::LongLong a_handle, DDS::ULong sample_states, DDS::ULong view_states, DDS::ULong instance_states) = 0;
      virtual DDS::Long read_next_instance (user_informationSeq& received_data, DDS::SampleInfoSeq& info_seq, DDS::Long max_samples, DDS::LongLong a_handle, DDS::ULong sample_states, DDS::ULong view_states, DDS::ULong instance_states) = 0;
      virtual DDS::Long take_next_instance (user_informationSeq& received_data, DDS::SampleInfoSeq& info_seq, DDS::Long max_samples, DDS::LongLong a_handle, DDS::ULong sample_states, DDS::ULong view_states, DDS::ULong instance_states) = 0;
      virtual DDS::Long read_next_instance_w_condition (user_informationSeq& received_data, DDS::SampleInfoSeq& info_seq, DDS::Long max_samples, DDS::LongLong a_handle, DDS::ReadCondition_ptr a_condition) = 0;
      virtual DDS::Long take_next_instance_w_condition (user_informationSeq& received_data, DDS::SampleInfoSeq& info_seq, DDS::Long max_samples, DDS::LongLong a_handle, DDS::ReadCondition_ptr a_condition) = 0;
      virtual DDS::Long return_loan (user_informationSeq& received_data, DDS::SampleInfoSeq& info_seq) = 0;
      virtual DDS::Long get_key_value (user_information& key_holder, DDS::LongLong handle) = 0;
      virtual DDS::LongLong lookup_instance (const user_information& instance) = 0;

   protected:
      user_informationDataReaderView () {};
      ~user_informationDataReaderView () {};
   private:
      user_informationDataReaderView (const user_informationDataReaderView &);
      user_informationDataReaderView & operator = (const user_informationDataReaderView &);
   };

   struct requestSeq_uniq_ {};
   typedef DDS_DCPSUVLSeq < request, struct requestSeq_uniq_> requestSeq;
   typedef DDS_DCPSSequence_var < requestSeq> requestSeq_var;
   typedef DDS_DCPSSequence_out < requestSeq> requestSeq_out;
   class requestTypeSupportInterface
   :
      virtual public DDS::TypeSupport
   { 
   public:
      typedef requestTypeSupportInterface_ptr _ptr_type;
      typedef requestTypeSupportInterface_var _var_type;

      static requestTypeSupportInterface_ptr _duplicate (requestTypeSupportInterface_ptr obj);
      DDS::Boolean _local_is_a (const char * id);

      static requestTypeSupportInterface_ptr _narrow (DDS::Object_ptr obj);
      static requestTypeSupportInterface_ptr _unchecked_narrow (DDS::Object_ptr obj);
      static requestTypeSupportInterface_ptr _nil () { return 0; }
      static const char * _local_id;
      requestTypeSupportInterface_ptr _this () { return this; }


   protected:
      requestTypeSupportInterface () {};
      ~requestTypeSupportInterface () {};
   private:
      requestTypeSupportInterface (const requestTypeSupportInterface &);
      requestTypeSupportInterface & operator = (const requestTypeSupportInterface &);
   };

   class requestDataWriter
   :
      virtual public DDS::DataWriter
   { 
   public:
      typedef requestDataWriter_ptr _ptr_type;
      typedef requestDataWriter_var _var_type;

      static requestDataWriter_ptr _duplicate (requestDataWriter_ptr obj);
      DDS::Boolean _local_is_a (const char * id);

      static requestDataWriter_ptr _narrow (DDS::Object_ptr obj);
      static requestDataWriter_ptr _unchecked_narrow (DDS::Object_ptr obj);
      static requestDataWriter_ptr _nil () { return 0; }
      static const char * _local_id;
      requestDataWriter_ptr _this () { return this; }

      virtual DDS::LongLong register_instance (const request& instance_data) = 0;
      virtual DDS::LongLong register_instance_w_timestamp (const request& instance_data, const DDS::Time_t& source_timestamp) = 0;
      virtual DDS::Long unregister_instance (const request& instance_data, DDS::LongLong handle) = 0;
      virtual DDS::Long unregister_instance_w_timestamp (const request& instance_data, DDS::LongLong handle, const DDS::Time_t& source_timestamp) = 0;
      virtual DDS::Long write (const request& instance_data, DDS::LongLong handle) = 0;
      virtual DDS::Long write_w_timestamp (const request& instance_data, DDS::LongLong handle, const DDS::Time_t& source_timestamp) = 0;
      virtual DDS::Long dispose (const request& instance_data, DDS::LongLong handle) = 0;
      virtual DDS::Long dispose_w_timestamp (const request& instance_data, DDS::LongLong handle, const DDS::Time_t& source_timestamp) = 0;
      virtual DDS::Long writedispose (const request& instance_data, DDS::LongLong handle) = 0;
      virtual DDS::Long writedispose_w_timestamp (const request& instance_data, DDS::LongLong handle, const DDS::Time_t& source_timestamp) = 0;
      virtual DDS::Long get_key_value (request& key_holder, DDS::LongLong handle) = 0;
      virtual DDS::LongLong lookup_instance (const request& instance_data) = 0;

   protected:
      requestDataWriter () {};
      ~requestDataWriter () {};
   private:
      requestDataWriter (const requestDataWriter &);
      requestDataWriter & operator = (const requestDataWriter &);
   };

   class requestDataReader
   :
      virtual public DDS::DataReader
   { 
   public:
      typedef requestDataReader_ptr _ptr_type;
      typedef requestDataReader_var _var_type;

      static requestDataReader_ptr _duplicate (requestDataReader_ptr obj);
      DDS::Boolean _local_is_a (const char * id);

      static requestDataReader_ptr _narrow (DDS::Object_ptr obj);
      static requestDataReader_ptr _unchecked_narrow (DDS::Object_ptr obj);
      static requestDataReader_ptr _nil () { return 0; }
      static const char * _local_id;
      requestDataReader_ptr _this () { return this; }

      virtual DDS::Long read (requestSeq& received_data, DDS::SampleInfoSeq& info_seq, DDS::Long max_samples, DDS::ULong sample_states, DDS::ULong view_states, DDS::ULong instance_states) = 0;
      virtual DDS::Long take (requestSeq& received_data, DDS::SampleInfoSeq& info_seq, DDS::Long max_samples, DDS::ULong sample_states, DDS::ULong view_states, DDS::ULong instance_states) = 0;
      virtual DDS::Long read_w_condition (requestSeq& received_data, DDS::SampleInfoSeq& info_seq, DDS::Long max_samples, DDS::ReadCondition_ptr a_condition) = 0;
      virtual DDS::Long take_w_condition (requestSeq& received_data, DDS::SampleInfoSeq& info_seq, DDS::Long max_samples, DDS::ReadCondition_ptr a_condition) = 0;
      virtual DDS::Long read_next_sample (request& received_data, DDS::SampleInfo& sample_info) = 0;
      virtual DDS::Long take_next_sample (request& received_data, DDS::SampleInfo& sample_info) = 0;
      virtual DDS::Long read_instance (requestSeq& received_data, DDS::SampleInfoSeq& info_seq, DDS::Long max_samples, DDS::LongLong a_handle, DDS::ULong sample_states, DDS::ULong view_states, DDS::ULong instance_states) = 0;
      virtual DDS::Long take_instance (requestSeq& received_data, DDS::SampleInfoSeq& info_seq, DDS::Long max_samples, DDS::LongLong a_handle, DDS::ULong sample_states, DDS::ULong view_states, DDS::ULong instance_states) = 0;
      virtual DDS::Long read_next_instance (requestSeq& received_data, DDS::SampleInfoSeq& info_seq, DDS::Long max_samples, DDS::LongLong a_handle, DDS::ULong sample_states, DDS::ULong view_states, DDS::ULong instance_states) = 0;
      virtual DDS::Long take_next_instance (requestSeq& received_data, DDS::SampleInfoSeq& info_seq, DDS::Long max_samples, DDS::LongLong a_handle, DDS::ULong sample_states, DDS::ULong view_states, DDS::ULong instance_states) = 0;
      virtual DDS::Long read_next_instance_w_condition (requestSeq& received_data, DDS::SampleInfoSeq& info_seq, DDS::Long max_samples, DDS::LongLong a_handle, DDS::ReadCondition_ptr a_condition) = 0;
      virtual DDS::Long take_next_instance_w_condition (requestSeq& received_data, DDS::SampleInfoSeq& info_seq, DDS::Long max_samples, DDS::LongLong a_handle, DDS::ReadCondition_ptr a_condition) = 0;
      virtual DDS::Long return_loan (requestSeq& received_data, DDS::SampleInfoSeq& info_seq) = 0;
      virtual DDS::Long get_key_value (request& key_holder, DDS::LongLong handle) = 0;
      virtual DDS::LongLong lookup_instance (const request& instance) = 0;

   protected:
      requestDataReader () {};
      ~requestDataReader () {};
   private:
      requestDataReader (const requestDataReader &);
      requestDataReader & operator = (const requestDataReader &);
   };

   class requestDataReaderView
   :
      virtual public DDS::DataReaderView
   { 
   public:
      typedef requestDataReaderView_ptr _ptr_type;
      typedef requestDataReaderView_var _var_type;

      static requestDataReaderView_ptr _duplicate (requestDataReaderView_ptr obj);
      DDS::Boolean _local_is_a (const char * id);

      static requestDataReaderView_ptr _narrow (DDS::Object_ptr obj);
      static requestDataReaderView_ptr _unchecked_narrow (DDS::Object_ptr obj);
      static requestDataReaderView_ptr _nil () { return 0; }
      static const char * _local_id;
      requestDataReaderView_ptr _this () { return this; }

      virtual DDS::Long read (requestSeq& received_data, DDS::SampleInfoSeq& info_seq, DDS::Long max_samples, DDS::ULong sample_states, DDS::ULong view_states, DDS::ULong instance_states) = 0;
      virtual DDS::Long take (requestSeq& received_data, DDS::SampleInfoSeq& info_seq, DDS::Long max_samples, DDS::ULong sample_states, DDS::ULong view_states, DDS::ULong instance_states) = 0;
      virtual DDS::Long read_w_condition (requestSeq& received_data, DDS::SampleInfoSeq& info_seq, DDS::Long max_samples, DDS::ReadCondition_ptr a_condition) = 0;
      virtual DDS::Long take_w_condition (requestSeq& received_data, DDS::SampleInfoSeq& info_seq, DDS::Long max_samples, DDS::ReadCondition_ptr a_condition) = 0;
      virtual DDS::Long read_next_sample (request& received_data, DDS::SampleInfo& sample_info) = 0;
      virtual DDS::Long take_next_sample (request& received_data, DDS::SampleInfo& sample_info) = 0;
      virtual DDS::Long read_instance (requestSeq& received_data, DDS::SampleInfoSeq& info_seq, DDS::Long max_samples, DDS::LongLong a_handle, DDS::ULong sample_states, DDS::ULong view_states, DDS::ULong instance_states) = 0;
      virtual DDS::Long take_instance (requestSeq& received_data, DDS::SampleInfoSeq& info_seq, DDS::Long max_samples, DDS::LongLong a_handle, DDS::ULong sample_states, DDS::ULong view_states, DDS::ULong instance_states) = 0;
      virtual DDS::Long read_next_instance (requestSeq& received_data, DDS::SampleInfoSeq& info_seq, DDS::Long max_samples, DDS::LongLong a_handle, DDS::ULong sample_states, DDS::ULong view_states, DDS::ULong instance_states) = 0;
      virtual DDS::Long take_next_instance (requestSeq& received_data, DDS::SampleInfoSeq& info_seq, DDS::Long max_samples, DDS::LongLong a_handle, DDS::ULong sample_states, DDS::ULong view_states, DDS::ULong instance_states) = 0;
      virtual DDS::Long read_next_instance_w_condition (requestSeq& received_data, DDS::SampleInfoSeq& info_seq, DDS::Long max_samples, DDS::LongLong a_handle, DDS::ReadCondition_ptr a_condition) = 0;
      virtual DDS::Long take_next_instance_w_condition (requestSeq& received_data, DDS::SampleInfoSeq& info_seq, DDS::Long max_samples, DDS::LongLong a_handle, DDS::ReadCondition_ptr a_condition) = 0;
      virtual DDS::Long return_loan (requestSeq& received_data, DDS::SampleInfoSeq& info_seq) = 0;
      virtual DDS::Long get_key_value (request& key_holder, DDS::LongLong handle) = 0;
      virtual DDS::LongLong lookup_instance (const request& instance) = 0;

   protected:
      requestDataReaderView () {};
      ~requestDataReaderView () {};
   private:
      requestDataReaderView (const requestDataReaderView &);
      requestDataReaderView & operator = (const requestDataReaderView &);
   };

   struct responseSeq_uniq_ {};
   typedef DDS_DCPSUVLSeq < response, struct responseSeq_uniq_> responseSeq;
   typedef DDS_DCPSSequence_var < responseSeq> responseSeq_var;
   typedef DDS_DCPSSequence_out < responseSeq> responseSeq_out;
   class responseTypeSupportInterface
   :
      virtual public DDS::TypeSupport
   { 
   public:
      typedef responseTypeSupportInterface_ptr _ptr_type;
      typedef responseTypeSupportInterface_var _var_type;

      static responseTypeSupportInterface_ptr _duplicate (responseTypeSupportInterface_ptr obj);
      DDS::Boolean _local_is_a (const char * id);

      static responseTypeSupportInterface_ptr _narrow (DDS::Object_ptr obj);
      static responseTypeSupportInterface_ptr _unchecked_narrow (DDS::Object_ptr obj);
      static responseTypeSupportInterface_ptr _nil () { return 0; }
      static const char * _local_id;
      responseTypeSupportInterface_ptr _this () { return this; }


   protected:
      responseTypeSupportInterface () {};
      ~responseTypeSupportInterface () {};
   private:
      responseTypeSupportInterface (const responseTypeSupportInterface &);
      responseTypeSupportInterface & operator = (const responseTypeSupportInterface &);
   };

   class responseDataWriter
   :
      virtual public DDS::DataWriter
   { 
   public:
      typedef responseDataWriter_ptr _ptr_type;
      typedef responseDataWriter_var _var_type;

      static responseDataWriter_ptr _duplicate (responseDataWriter_ptr obj);
      DDS::Boolean _local_is_a (const char * id);

      static responseDataWriter_ptr _narrow (DDS::Object_ptr obj);
      static responseDataWriter_ptr _unchecked_narrow (DDS::Object_ptr obj);
      static responseDataWriter_ptr _nil () { return 0; }
      static const char * _local_id;
      responseDataWriter_ptr _this () { return this; }

      virtual DDS::LongLong register_instance (const response& instance_data) = 0;
      virtual DDS::LongLong register_instance_w_timestamp (const response& instance_data, const DDS::Time_t& source_timestamp) = 0;
      virtual DDS::Long unregister_instance (const response& instance_data, DDS::LongLong handle) = 0;
      virtual DDS::Long unregister_instance_w_timestamp (const response& instance_data, DDS::LongLong handle, const DDS::Time_t& source_timestamp) = 0;
      virtual DDS::Long write (const response& instance_data, DDS::LongLong handle) = 0;
      virtual DDS::Long write_w_timestamp (const response& instance_data, DDS::LongLong handle, const DDS::Time_t& source_timestamp) = 0;
      virtual DDS::Long dispose (const response& instance_data, DDS::LongLong handle) = 0;
      virtual DDS::Long dispose_w_timestamp (const response& instance_data, DDS::LongLong handle, const DDS::Time_t& source_timestamp) = 0;
      virtual DDS::Long writedispose (const response& instance_data, DDS::LongLong handle) = 0;
      virtual DDS::Long writedispose_w_timestamp (const response& instance_data, DDS::LongLong handle, const DDS::Time_t& source_timestamp) = 0;
      virtual DDS::Long get_key_value (response& key_holder, DDS::LongLong handle) = 0;
      virtual DDS::LongLong lookup_instance (const response& instance_data) = 0;

   protected:
      responseDataWriter () {};
      ~responseDataWriter () {};
   private:
      responseDataWriter (const responseDataWriter &);
      responseDataWriter & operator = (const responseDataWriter &);
   };

   class responseDataReader
   :
      virtual public DDS::DataReader
   { 
   public:
      typedef responseDataReader_ptr _ptr_type;
      typedef responseDataReader_var _var_type;

      static responseDataReader_ptr _duplicate (responseDataReader_ptr obj);
      DDS::Boolean _local_is_a (const char * id);

      static responseDataReader_ptr _narrow (DDS::Object_ptr obj);
      static responseDataReader_ptr _unchecked_narrow (DDS::Object_ptr obj);
      static responseDataReader_ptr _nil () { return 0; }
      static const char * _local_id;
      responseDataReader_ptr _this () { return this; }

      virtual DDS::Long read (responseSeq& received_data, DDS::SampleInfoSeq& info_seq, DDS::Long max_samples, DDS::ULong sample_states, DDS::ULong view_states, DDS::ULong instance_states) = 0;
      virtual DDS::Long take (responseSeq& received_data, DDS::SampleInfoSeq& info_seq, DDS::Long max_samples, DDS::ULong sample_states, DDS::ULong view_states, DDS::ULong instance_states) = 0;
      virtual DDS::Long read_w_condition (responseSeq& received_data, DDS::SampleInfoSeq& info_seq, DDS::Long max_samples, DDS::ReadCondition_ptr a_condition) = 0;
      virtual DDS::Long take_w_condition (responseSeq& received_data, DDS::SampleInfoSeq& info_seq, DDS::Long max_samples, DDS::ReadCondition_ptr a_condition) = 0;
      virtual DDS::Long read_next_sample (response& received_data, DDS::SampleInfo& sample_info) = 0;
      virtual DDS::Long take_next_sample (response& received_data, DDS::SampleInfo& sample_info) = 0;
      virtual DDS::Long read_instance (responseSeq& received_data, DDS::SampleInfoSeq& info_seq, DDS::Long max_samples, DDS::LongLong a_handle, DDS::ULong sample_states, DDS::ULong view_states, DDS::ULong instance_states) = 0;
      virtual DDS::Long take_instance (responseSeq& received_data, DDS::SampleInfoSeq& info_seq, DDS::Long max_samples, DDS::LongLong a_handle, DDS::ULong sample_states, DDS::ULong view_states, DDS::ULong instance_states) = 0;
      virtual DDS::Long read_next_instance (responseSeq& received_data, DDS::SampleInfoSeq& info_seq, DDS::Long max_samples, DDS::LongLong a_handle, DDS::ULong sample_states, DDS::ULong view_states, DDS::ULong instance_states) = 0;
      virtual DDS::Long take_next_instance (responseSeq& received_data, DDS::SampleInfoSeq& info_seq, DDS::Long max_samples, DDS::LongLong a_handle, DDS::ULong sample_states, DDS::ULong view_states, DDS::ULong instance_states) = 0;
      virtual DDS::Long read_next_instance_w_condition (responseSeq& received_data, DDS::SampleInfoSeq& info_seq, DDS::Long max_samples, DDS::LongLong a_handle, DDS::ReadCondition_ptr a_condition) = 0;
      virtual DDS::Long take_next_instance_w_condition (responseSeq& received_data, DDS::SampleInfoSeq& info_seq, DDS::Long max_samples, DDS::LongLong a_handle, DDS::ReadCondition_ptr a_condition) = 0;
      virtual DDS::Long return_loan (responseSeq& received_data, DDS::SampleInfoSeq& info_seq) = 0;
      virtual DDS::Long get_key_value (response& key_holder, DDS::LongLong handle) = 0;
      virtual DDS::LongLong lookup_instance (const response& instance) = 0;

   protected:
      responseDataReader () {};
      ~responseDataReader () {};
   private:
      responseDataReader (const responseDataReader &);
      responseDataReader & operator = (const responseDataReader &);
   };

   class responseDataReaderView
   :
      virtual public DDS::DataReaderView
   { 
   public:
      typedef responseDataReaderView_ptr _ptr_type;
      typedef responseDataReaderView_var _var_type;

      static responseDataReaderView_ptr _duplicate (responseDataReaderView_ptr obj);
      DDS::Boolean _local_is_a (const char * id);

      static responseDataReaderView_ptr _narrow (DDS::Object_ptr obj);
      static responseDataReaderView_ptr _unchecked_narrow (DDS::Object_ptr obj);
      static responseDataReaderView_ptr _nil () { return 0; }
      static const char * _local_id;
      responseDataReaderView_ptr _this () { return this; }

      virtual DDS::Long read (responseSeq& received_data, DDS::SampleInfoSeq& info_seq, DDS::Long max_samples, DDS::ULong sample_states, DDS::ULong view_states, DDS::ULong instance_states) = 0;
      virtual DDS::Long take (responseSeq& received_data, DDS::SampleInfoSeq& info_seq, DDS::Long max_samples, DDS::ULong sample_states, DDS::ULong view_states, DDS::ULong instance_states) = 0;
      virtual DDS::Long read_w_condition (responseSeq& received_data, DDS::SampleInfoSeq& info_seq, DDS::Long max_samples, DDS::ReadCondition_ptr a_condition) = 0;
      virtual DDS::Long take_w_condition (responseSeq& received_data, DDS::SampleInfoSeq& info_seq, DDS::Long max_samples, DDS::ReadCondition_ptr a_condition) = 0;
      virtual DDS::Long read_next_sample (response& received_data, DDS::SampleInfo& sample_info) = 0;
      virtual DDS::Long take_next_sample (response& received_data, DDS::SampleInfo& sample_info) = 0;
      virtual DDS::Long read_instance (responseSeq& received_data, DDS::SampleInfoSeq& info_seq, DDS::Long max_samples, DDS::LongLong a_handle, DDS::ULong sample_states, DDS::ULong view_states, DDS::ULong instance_states) = 0;
      virtual DDS::Long take_instance (responseSeq& received_data, DDS::SampleInfoSeq& info_seq, DDS::Long max_samples, DDS::LongLong a_handle, DDS::ULong sample_states, DDS::ULong view_states, DDS::ULong instance_states) = 0;
      virtual DDS::Long read_next_instance (responseSeq& received_data, DDS::SampleInfoSeq& info_seq, DDS::Long max_samples, DDS::LongLong a_handle, DDS::ULong sample_states, DDS::ULong view_states, DDS::ULong instance_states) = 0;
      virtual DDS::Long take_next_instance (responseSeq& received_data, DDS::SampleInfoSeq& info_seq, DDS::Long max_samples, DDS::LongLong a_handle, DDS::ULong sample_states, DDS::ULong view_states, DDS::ULong instance_states) = 0;
      virtual DDS::Long read_next_instance_w_condition (responseSeq& received_data, DDS::SampleInfoSeq& info_seq, DDS::Long max_samples, DDS::LongLong a_handle, DDS::ReadCondition_ptr a_condition) = 0;
      virtual DDS::Long take_next_instance_w_condition (responseSeq& received_data, DDS::SampleInfoSeq& info_seq, DDS::Long max_samples, DDS::LongLong a_handle, DDS::ReadCondition_ptr a_condition) = 0;
      virtual DDS::Long return_loan (responseSeq& received_data, DDS::SampleInfoSeq& info_seq) = 0;
      virtual DDS::Long get_key_value (response& key_holder, DDS::LongLong handle) = 0;
      virtual DDS::LongLong lookup_instance (const response& instance) = 0;

   protected:
      responseDataReaderView () {};
      ~responseDataReaderView () {};
   private:
      responseDataReaderView (const responseDataReaderView &);
      responseDataReaderView & operator = (const responseDataReaderView &);
   };

}




#endif 
