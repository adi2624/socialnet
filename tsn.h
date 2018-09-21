//******************************************************************
// 
//  Generated by IDL to C++ Translator
//  
//  File name: tsn.h
//  Source: idl/tsn.idl
//  Generated: Fri Sep 21 03:29:07 2018
//  OpenSplice V6.4.140320OSS
//  
//******************************************************************
#ifndef _TSN_H_
#define _TSN_H_

#include "sacpp_mapping.h"
#include "sacpp_DDS_DCPS.h"


namespace TSN
{
   struct user_information;
   struct node_request;
   struct request;
   struct response;
   typedef DDS::ULong serial_number;

   struct user_information
   {
         typedef DDS::Char _uuid_slice;
         typedef DDS::Char _uuid[17];
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
         typedef DDS::Char _fulfiller_uuid[17];
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
         typedef DDS::Char _uuid[17];
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

   struct response
   {
         typedef DDS::Char _uuid_slice;
         typedef DDS::Char _uuid[17];
         typedef _uuid _uuid_out;
         static _uuid_slice * _uuid_alloc ();
         static void _uuid_free (_uuid_slice *);
         static void _uuid_copy (_uuid_slice* to, const _uuid_slice* from);
         static _uuid_slice *_uuid_dup (const _uuid_slice* from);

         struct _uuid_uniq_ {};
         typedef DDS_DCPS_FArray_var< _uuid, _uuid_slice, struct _uuid_uniq_> _uuid_var;
         typedef DDS_DCPS_Array_forany< _uuid, _uuid_slice, struct _uuid_uniq_> _uuid_forany;
         _uuid uuid;
         DDS::ULong post_id;
         DDS::String_mgr post_body;
         DDS::Long date_of_creation;
   };

   typedef DDS_DCPSStruct_var < response> response_var;
   typedef DDS_DCPSStruct_out < response> response_out;
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
TSN::response::_uuid_slice* DDS_DCPS_ArrayHelper < TSN::response::_uuid, TSN::response::_uuid_slice, TSN::response::_uuid_uniq_>::alloc ();
template <>
void DDS_DCPS_ArrayHelper < TSN::response::_uuid, TSN::response::_uuid_slice, TSN::response::_uuid_uniq_>::copy (TSN::response::_uuid_slice *to, const TSN::response::_uuid_slice* from);
template <>
void DDS_DCPS_ArrayHelper < TSN::response::_uuid, TSN::response::_uuid_slice, TSN::response::_uuid_uniq_>::free (TSN::response::_uuid_slice *ptr);




#endif 
