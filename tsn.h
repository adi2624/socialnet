//******************************************************************
// 
//  Generated by IDL to C++ Translator
//  
//  File name: tsn.h
//  Source: src/idl/tsn.idl
//  Generated: Wed Nov 14 11:35:28 2018
//  OpenSplice 6.7.180404OSS
//  
//******************************************************************
#ifndef _TSN_H_
#define _TSN_H_

#include "sacpp_mapping.h"


namespace TSN
{
   struct user_information;
   struct node_request;
   struct request;
   struct post_data;
   struct response;
   struct private_message;
   typedef DDS::ULong serial_number;
   const DDS::ULong UUID_SIZE = (DDS::ULong) 37UL;

   struct user_information
   {
         typedef DDS::Char _uuid_slice;
         typedef DDS::Char _uuid[37];
         typedef _uuid _uuid_out;
         static _uuid_slice * _uuid_alloc ();
         static void _uuid_free (_uuid_slice *);
         static void _uuid_copy (_uuid_slice* to, const _uuid_slice* from);
         static _uuid_slice *_uuid_dup (const _uuid_slice* from);

         struct _uuid_uniq_ {};
         typedef DDS_DCPS_FArray_var< _uuid, _uuid_slice, struct _uuid_uniq_> _uuid_var;
         typedef DDS_DCPS_Array_forany< _uuid, _uuid_slice, struct _uuid_uniq_> _uuid_forany;
         struct _interests_seq_uniq_ {};
         typedef DDS_DCPSUStrSeqT <struct _interests_seq_uniq_> _interests_seq;
         typedef DDS_DCPSUStrSeq_var < _interests_seq> _interests_seq_var;
         typedef DDS_DCPSUStrSeq_out < _interests_seq> _interests_seq_out;
         _uuid uuid;
         DDS::String_mgr first_name;
         DDS::String_mgr last_name;
         DDS::Long date_of_birth;
         _interests_seq interests;
         DDS::ULongLong number_of_highest_post;
   };

   typedef DDS_DCPSStruct_var < user_information> user_information_var;
   typedef DDS_DCPSStruct_out < user_information> user_information_out;

   struct node_request
   {
         typedef DDS::Char _fulfiller_uuid_slice;
         typedef DDS::Char _fulfiller_uuid[37];
         typedef _fulfiller_uuid _fulfiller_uuid_out;
         static _fulfiller_uuid_slice * _fulfiller_uuid_alloc ();
         static void _fulfiller_uuid_free (_fulfiller_uuid_slice *);
         static void _fulfiller_uuid_copy (_fulfiller_uuid_slice* to, const _fulfiller_uuid_slice* from);
         static _fulfiller_uuid_slice *_fulfiller_uuid_dup (const _fulfiller_uuid_slice* from);

         struct _fulfiller_uuid_uniq_ {};
         typedef DDS_DCPS_FArray_var< _fulfiller_uuid, _fulfiller_uuid_slice, struct _fulfiller_uuid_uniq_> _fulfiller_uuid_var;
         typedef DDS_DCPS_Array_forany< _fulfiller_uuid, _fulfiller_uuid_slice, struct _fulfiller_uuid_uniq_> _fulfiller_uuid_forany;
         struct _requested_posts_seq_uniq_ {};
         typedef DDS_DCPSUFLSeq < DDS::ULong, struct _requested_posts_seq_uniq_> _requested_posts_seq;
         typedef DDS_DCPSSequence_var < _requested_posts_seq> _requested_posts_seq_var;
         typedef DDS_DCPSSequence_out < _requested_posts_seq> _requested_posts_seq_out;
         _fulfiller_uuid fulfiller_uuid;
         _requested_posts_seq requested_posts;
   };

   typedef DDS_DCPSStruct_var < node_request> node_request_var;
   typedef DDS_DCPSStruct_out < node_request> node_request_out;

   struct request
   {
         typedef DDS::Char _uuid_slice;
         typedef DDS::Char _uuid[37];
         typedef _uuid _uuid_out;
         static _uuid_slice * _uuid_alloc ();
         static void _uuid_free (_uuid_slice *);
         static void _uuid_copy (_uuid_slice* to, const _uuid_slice* from);
         static _uuid_slice *_uuid_dup (const _uuid_slice* from);

         struct _uuid_uniq_ {};
         typedef DDS_DCPS_FArray_var< _uuid, _uuid_slice, struct _uuid_uniq_> _uuid_var;
         typedef DDS_DCPS_Array_forany< _uuid, _uuid_slice, struct _uuid_uniq_> _uuid_forany;
         struct _user_requests_seq_uniq_ {};
         typedef DDS_DCPSUVLSeq < node_request, struct _user_requests_seq_uniq_> _user_requests_seq;
         typedef DDS_DCPSSequence_var < _user_requests_seq> _user_requests_seq_var;
         typedef DDS_DCPSSequence_out < _user_requests_seq> _user_requests_seq_out;
         _uuid uuid;
         _user_requests_seq user_requests;
   };

   typedef DDS_DCPSStruct_var < request> request_var;
   typedef DDS_DCPSStruct_out < request> request_out;

   struct post_data
   {
         typedef DDS::Char _owner_uuid_slice;
         typedef DDS::Char _owner_uuid[37];
         typedef _owner_uuid _owner_uuid_out;
         static _owner_uuid_slice * _owner_uuid_alloc ();
         static void _owner_uuid_free (_owner_uuid_slice *);
         static void _owner_uuid_copy (_owner_uuid_slice* to, const _owner_uuid_slice* from);
         static _owner_uuid_slice *_owner_uuid_dup (const _owner_uuid_slice* from);

         struct _owner_uuid_uniq_ {};
         typedef DDS_DCPS_FArray_var< _owner_uuid, _owner_uuid_slice, struct _owner_uuid_uniq_> _owner_uuid_var;
         typedef DDS_DCPS_Array_forany< _owner_uuid, _owner_uuid_slice, struct _owner_uuid_uniq_> _owner_uuid_forany;
         _owner_uuid owner_uuid;
         DDS::ULong post_id;
   };

   typedef DDS_DCPSStruct_var < post_data> post_data_var;
   typedef post_data&post_data_out;

   struct response
   {
         typedef DDS::Char _uuid_slice;
         typedef DDS::Char _uuid[37];
         typedef _uuid _uuid_out;
         static _uuid_slice * _uuid_alloc ();
         static void _uuid_free (_uuid_slice *);
         static void _uuid_copy (_uuid_slice* to, const _uuid_slice* from);
         static _uuid_slice *_uuid_dup (const _uuid_slice* from);

         struct _uuid_uniq_ {};
         typedef DDS_DCPS_FArray_var< _uuid, _uuid_slice, struct _uuid_uniq_> _uuid_var;
         typedef DDS_DCPS_Array_forany< _uuid, _uuid_slice, struct _uuid_uniq_> _uuid_forany;
         struct _child_posts_seq_uniq_ {};
         typedef DDS_DCPSUFLSeq < post_data, struct _child_posts_seq_uniq_> _child_posts_seq;
         typedef DDS_DCPSSequence_var < _child_posts_seq> _child_posts_seq_var;
         typedef DDS_DCPSSequence_out < _child_posts_seq> _child_posts_seq_out;
         _uuid uuid;
         DDS::ULong post_id;
         DDS::String_mgr post_body;
         DDS::Long date_of_creation;
         post_data parent_post;
         _child_posts_seq child_posts;
   };

   typedef DDS_DCPSStruct_var < response> response_var;
   typedef DDS_DCPSStruct_out < response> response_out;

   struct private_message
   {
         typedef DDS::Char _receiver_uuid_slice;
         typedef DDS::Char _receiver_uuid[37];
         typedef _receiver_uuid _receiver_uuid_out;
         static _receiver_uuid_slice * _receiver_uuid_alloc ();
         static void _receiver_uuid_free (_receiver_uuid_slice *);
         static void _receiver_uuid_copy (_receiver_uuid_slice* to, const _receiver_uuid_slice* from);
         static _receiver_uuid_slice *_receiver_uuid_dup (const _receiver_uuid_slice* from);

         struct _receiver_uuid_uniq_ {};
         typedef DDS_DCPS_FArray_var< _receiver_uuid, _receiver_uuid_slice, struct _receiver_uuid_uniq_> _receiver_uuid_var;
         typedef DDS_DCPS_Array_forany< _receiver_uuid, _receiver_uuid_slice, struct _receiver_uuid_uniq_> _receiver_uuid_forany;
         typedef DDS::Char _sender_uuid_slice;
         typedef DDS::Char _sender_uuid[37];
         typedef _sender_uuid _sender_uuid_out;
         static _sender_uuid_slice * _sender_uuid_alloc ();
         static void _sender_uuid_free (_sender_uuid_slice *);
         static void _sender_uuid_copy (_sender_uuid_slice* to, const _sender_uuid_slice* from);
         static _sender_uuid_slice *_sender_uuid_dup (const _sender_uuid_slice* from);

         struct _sender_uuid_uniq_ {};
         typedef DDS_DCPS_FArray_var< _sender_uuid, _sender_uuid_slice, struct _sender_uuid_uniq_> _sender_uuid_var;
         typedef DDS_DCPS_Array_forany< _sender_uuid, _sender_uuid_slice, struct _sender_uuid_uniq_> _sender_uuid_forany;
         _receiver_uuid receiver_uuid;
         _sender_uuid sender_uuid;
         DDS::String_mgr message_body;
         DDS::Long date_of_creation;
   };

   typedef DDS_DCPSStruct_var < private_message> private_message_var;
   typedef DDS_DCPSStruct_out < private_message> private_message_out;
}
template <>
TSN::user_information::_uuid_slice* DDS_DCPS_ArrayHelper < TSN::user_information::_uuid, TSN::user_information::_uuid_slice, TSN::user_information::_uuid_uniq_>::alloc ();
template <>
void DDS_DCPS_ArrayHelper < TSN::user_information::_uuid, TSN::user_information::_uuid_slice, TSN::user_information::_uuid_uniq_>::copy (TSN::user_information::_uuid_slice *to, const TSN::user_information::_uuid_slice* from);
template <>
void DDS_DCPS_ArrayHelper < TSN::user_information::_uuid, TSN::user_information::_uuid_slice, TSN::user_information::_uuid_uniq_>::free (TSN::user_information::_uuid_slice *ptr);
template <>
TSN::node_request::_fulfiller_uuid_slice* DDS_DCPS_ArrayHelper < TSN::node_request::_fulfiller_uuid, TSN::node_request::_fulfiller_uuid_slice, TSN::node_request::_fulfiller_uuid_uniq_>::alloc ();
template <>
void DDS_DCPS_ArrayHelper < TSN::node_request::_fulfiller_uuid, TSN::node_request::_fulfiller_uuid_slice, TSN::node_request::_fulfiller_uuid_uniq_>::copy (TSN::node_request::_fulfiller_uuid_slice *to, const TSN::node_request::_fulfiller_uuid_slice* from);
template <>
void DDS_DCPS_ArrayHelper < TSN::node_request::_fulfiller_uuid, TSN::node_request::_fulfiller_uuid_slice, TSN::node_request::_fulfiller_uuid_uniq_>::free (TSN::node_request::_fulfiller_uuid_slice *ptr);
template <>
TSN::request::_uuid_slice* DDS_DCPS_ArrayHelper < TSN::request::_uuid, TSN::request::_uuid_slice, TSN::request::_uuid_uniq_>::alloc ();
template <>
void DDS_DCPS_ArrayHelper < TSN::request::_uuid, TSN::request::_uuid_slice, TSN::request::_uuid_uniq_>::copy (TSN::request::_uuid_slice *to, const TSN::request::_uuid_slice* from);
template <>
void DDS_DCPS_ArrayHelper < TSN::request::_uuid, TSN::request::_uuid_slice, TSN::request::_uuid_uniq_>::free (TSN::request::_uuid_slice *ptr);
template <>
TSN::post_data::_owner_uuid_slice* DDS_DCPS_ArrayHelper < TSN::post_data::_owner_uuid, TSN::post_data::_owner_uuid_slice, TSN::post_data::_owner_uuid_uniq_>::alloc ();
template <>
void DDS_DCPS_ArrayHelper < TSN::post_data::_owner_uuid, TSN::post_data::_owner_uuid_slice, TSN::post_data::_owner_uuid_uniq_>::copy (TSN::post_data::_owner_uuid_slice *to, const TSN::post_data::_owner_uuid_slice* from);
template <>
void DDS_DCPS_ArrayHelper < TSN::post_data::_owner_uuid, TSN::post_data::_owner_uuid_slice, TSN::post_data::_owner_uuid_uniq_>::free (TSN::post_data::_owner_uuid_slice *ptr);
template <>
TSN::response::_uuid_slice* DDS_DCPS_ArrayHelper < TSN::response::_uuid, TSN::response::_uuid_slice, TSN::response::_uuid_uniq_>::alloc ();
template <>
void DDS_DCPS_ArrayHelper < TSN::response::_uuid, TSN::response::_uuid_slice, TSN::response::_uuid_uniq_>::copy (TSN::response::_uuid_slice *to, const TSN::response::_uuid_slice* from);
template <>
void DDS_DCPS_ArrayHelper < TSN::response::_uuid, TSN::response::_uuid_slice, TSN::response::_uuid_uniq_>::free (TSN::response::_uuid_slice *ptr);
template <>
TSN::private_message::_receiver_uuid_slice* DDS_DCPS_ArrayHelper < TSN::private_message::_receiver_uuid, TSN::private_message::_receiver_uuid_slice, TSN::private_message::_receiver_uuid_uniq_>::alloc ();
template <>
void DDS_DCPS_ArrayHelper < TSN::private_message::_receiver_uuid, TSN::private_message::_receiver_uuid_slice, TSN::private_message::_receiver_uuid_uniq_>::copy (TSN::private_message::_receiver_uuid_slice *to, const TSN::private_message::_receiver_uuid_slice* from);
template <>
void DDS_DCPS_ArrayHelper < TSN::private_message::_receiver_uuid, TSN::private_message::_receiver_uuid_slice, TSN::private_message::_receiver_uuid_uniq_>::free (TSN::private_message::_receiver_uuid_slice *ptr);
template <>
TSN::private_message::_sender_uuid_slice* DDS_DCPS_ArrayHelper < TSN::private_message::_sender_uuid, TSN::private_message::_sender_uuid_slice, TSN::private_message::_sender_uuid_uniq_>::alloc ();
template <>
void DDS_DCPS_ArrayHelper < TSN::private_message::_sender_uuid, TSN::private_message::_sender_uuid_slice, TSN::private_message::_sender_uuid_uniq_>::copy (TSN::private_message::_sender_uuid_slice *to, const TSN::private_message::_sender_uuid_slice* from);
template <>
void DDS_DCPS_ArrayHelper < TSN::private_message::_sender_uuid, TSN::private_message::_sender_uuid_slice, TSN::private_message::_sender_uuid_uniq_>::free (TSN::private_message::_sender_uuid_slice *ptr);




#endif
