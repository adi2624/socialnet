//******************************************************************
// 
//  Generated by IDL to C++ Translator
//  
//  File name: tsn.cpp
//  Source: idl/tsn.idl
//  Generated: Thu Nov  1 14:03:43 2018
//  OpenSplice 6.7.180404OSS
//  
//******************************************************************

#include "tsn.h"


#if DDS_USE_EXPLICIT_TEMPLATES
template class DDS_DCPS_FArray_var< TSN::response::_uuid, TSN::response::_uuid_slice, struct TSN::response::_uuid_uniq_>;
template class DDS_DCPS_Array_forany< TSN::response::_uuid, TSN::response::_uuid_slice, struct TSN::response::_uuid_uniq_>;
#endif

template <>
TSN::response::_uuid_slice* DDS_DCPS_ArrayHelper < TSN::response::_uuid, TSN::response::_uuid_slice, TSN::response::_uuid_uniq_>::alloc ()
{
   return TSN::response::_uuid_alloc ();
}

template <>
void DDS_DCPS_ArrayHelper < TSN::response::_uuid, TSN::response::_uuid_slice, TSN::response::_uuid_uniq_>::copy (TSN::response::_uuid_slice *to, const TSN::response::_uuid_slice* from)
{
   TSN::response::_uuid_copy (to, from);
}

template <>
void DDS_DCPS_ArrayHelper < TSN::response::_uuid, TSN::response::_uuid_slice, TSN::response::_uuid_uniq_>::free (TSN::response::_uuid_slice *ptr)
{
   TSN::response::_uuid_free (ptr);
}

TSN::response::_uuid_slice * TSN::response::_uuid_alloc ()
{
   DDS::Char * ret = (DDS::Char*) new DDS::Char [37];
   return (_uuid_slice *) ret;
}

void TSN::response::_uuid_free (_uuid_slice * s)
{
   delete [] s;
}

void TSN::response::_uuid_copy
(
   _uuid_slice * to,
   const _uuid_slice * from
)
{
   const DDS::Char* sv = ( const DDS::Char*) from;
   DDS::Char* tv = (DDS::Char*) to;
   for (DDS::ULong i = 0; i < 37; i++) tv[i] = sv[i];
}

TSN::response::_uuid_slice * TSN::response::_uuid_dup
   (const _uuid_slice * from)
{
   _uuid_slice * to = _uuid_alloc ();
   _uuid_copy (to, from);
   return to;
}

#if DDS_USE_EXPLICIT_TEMPLATES
template class DDS_DCPSUVLSeq < TSN::node_request, struct _user_requests_seq_uniq_>;
#endif

#if DDS_USE_EXPLICIT_TEMPLATES
template class DDS_DCPS_FArray_var< TSN::request::_uuid, TSN::request::_uuid_slice, struct TSN::request::_uuid_uniq_>;
template class DDS_DCPS_Array_forany< TSN::request::_uuid, TSN::request::_uuid_slice, struct TSN::request::_uuid_uniq_>;
#endif

template <>
TSN::request::_uuid_slice* DDS_DCPS_ArrayHelper < TSN::request::_uuid, TSN::request::_uuid_slice, TSN::request::_uuid_uniq_>::alloc ()
{
   return TSN::request::_uuid_alloc ();
}

template <>
void DDS_DCPS_ArrayHelper < TSN::request::_uuid, TSN::request::_uuid_slice, TSN::request::_uuid_uniq_>::copy (TSN::request::_uuid_slice *to, const TSN::request::_uuid_slice* from)
{
   TSN::request::_uuid_copy (to, from);
}

template <>
void DDS_DCPS_ArrayHelper < TSN::request::_uuid, TSN::request::_uuid_slice, TSN::request::_uuid_uniq_>::free (TSN::request::_uuid_slice *ptr)
{
   TSN::request::_uuid_free (ptr);
}

TSN::request::_uuid_slice * TSN::request::_uuid_alloc ()
{
   DDS::Char * ret = (DDS::Char*) new DDS::Char [37];
   return (_uuid_slice *) ret;
}

void TSN::request::_uuid_free (_uuid_slice * s)
{
   delete [] s;
}

void TSN::request::_uuid_copy
(
   _uuid_slice * to,
   const _uuid_slice * from
)
{
   const DDS::Char* sv = ( const DDS::Char*) from;
   DDS::Char* tv = (DDS::Char*) to;
   for (DDS::ULong i = 0; i < 37; i++) tv[i] = sv[i];
}

TSN::request::_uuid_slice * TSN::request::_uuid_dup
   (const _uuid_slice * from)
{
   _uuid_slice * to = _uuid_alloc ();
   _uuid_copy (to, from);
   return to;
}

#if DDS_USE_EXPLICIT_TEMPLATES
template class DDS_DCPSUFLSeq < TSN::serial_number, struct _requested_posts_seq_uniq_>;
#endif

#if DDS_USE_EXPLICIT_TEMPLATES
template class DDS_DCPS_FArray_var< TSN::node_request::_fulfiller_uuid, TSN::node_request::_fulfiller_uuid_slice, struct TSN::node_request::_fulfiller_uuid_uniq_>;
template class DDS_DCPS_Array_forany< TSN::node_request::_fulfiller_uuid, TSN::node_request::_fulfiller_uuid_slice, struct TSN::node_request::_fulfiller_uuid_uniq_>;
#endif

template <>
TSN::node_request::_fulfiller_uuid_slice* DDS_DCPS_ArrayHelper < TSN::node_request::_fulfiller_uuid, TSN::node_request::_fulfiller_uuid_slice, TSN::node_request::_fulfiller_uuid_uniq_>::alloc ()
{
   return TSN::node_request::_fulfiller_uuid_alloc ();
}

template <>
void DDS_DCPS_ArrayHelper < TSN::node_request::_fulfiller_uuid, TSN::node_request::_fulfiller_uuid_slice, TSN::node_request::_fulfiller_uuid_uniq_>::copy (TSN::node_request::_fulfiller_uuid_slice *to, const TSN::node_request::_fulfiller_uuid_slice* from)
{
   TSN::node_request::_fulfiller_uuid_copy (to, from);
}

template <>
void DDS_DCPS_ArrayHelper < TSN::node_request::_fulfiller_uuid, TSN::node_request::_fulfiller_uuid_slice, TSN::node_request::_fulfiller_uuid_uniq_>::free (TSN::node_request::_fulfiller_uuid_slice *ptr)
{
   TSN::node_request::_fulfiller_uuid_free (ptr);
}

TSN::node_request::_fulfiller_uuid_slice * TSN::node_request::_fulfiller_uuid_alloc ()
{
   DDS::Char * ret = (DDS::Char*) new DDS::Char [37];
   return (_fulfiller_uuid_slice *) ret;
}

void TSN::node_request::_fulfiller_uuid_free (_fulfiller_uuid_slice * s)
{
   delete [] s;
}

void TSN::node_request::_fulfiller_uuid_copy
(
   _fulfiller_uuid_slice * to,
   const _fulfiller_uuid_slice * from
)
{
   const DDS::Char* sv = ( const DDS::Char*) from;
   DDS::Char* tv = (DDS::Char*) to;
   for (DDS::ULong i = 0; i < 37; i++) tv[i] = sv[i];
}

TSN::node_request::_fulfiller_uuid_slice * TSN::node_request::_fulfiller_uuid_dup
   (const _fulfiller_uuid_slice * from)
{
   _fulfiller_uuid_slice * to = _fulfiller_uuid_alloc ();
   _fulfiller_uuid_copy (to, from);
   return to;
}

#if DDS_USE_EXPLICIT_TEMPLATES
template class DDS_DCPSUVLSeq < DDS::String, struct _interests_seq_uniq_>;
#endif

#if DDS_USE_EXPLICIT_TEMPLATES
template class DDS_DCPS_FArray_var< TSN::user_information::_uuid, TSN::user_information::_uuid_slice, struct TSN::user_information::_uuid_uniq_>;
template class DDS_DCPS_Array_forany< TSN::user_information::_uuid, TSN::user_information::_uuid_slice, struct TSN::user_information::_uuid_uniq_>;
#endif

template <>
TSN::user_information::_uuid_slice* DDS_DCPS_ArrayHelper < TSN::user_information::_uuid, TSN::user_information::_uuid_slice, TSN::user_information::_uuid_uniq_>::alloc ()
{
   return TSN::user_information::_uuid_alloc ();
}

template <>
void DDS_DCPS_ArrayHelper < TSN::user_information::_uuid, TSN::user_information::_uuid_slice, TSN::user_information::_uuid_uniq_>::copy (TSN::user_information::_uuid_slice *to, const TSN::user_information::_uuid_slice* from)
{
   TSN::user_information::_uuid_copy (to, from);
}

template <>
void DDS_DCPS_ArrayHelper < TSN::user_information::_uuid, TSN::user_information::_uuid_slice, TSN::user_information::_uuid_uniq_>::free (TSN::user_information::_uuid_slice *ptr)
{
   TSN::user_information::_uuid_free (ptr);
}

TSN::user_information::_uuid_slice * TSN::user_information::_uuid_alloc ()
{
   DDS::Char * ret = (DDS::Char*) new DDS::Char [37];
   return (_uuid_slice *) ret;
}

void TSN::user_information::_uuid_free (_uuid_slice * s)
{
   delete [] s;
}

void TSN::user_information::_uuid_copy
(
   _uuid_slice * to,
   const _uuid_slice * from
)
{
   const DDS::Char* sv = ( const DDS::Char*) from;
   DDS::Char* tv = (DDS::Char*) to;
   for (DDS::ULong i = 0; i < 37; i++) tv[i] = sv[i];
}

TSN::user_information::_uuid_slice * TSN::user_information::_uuid_dup
   (const _uuid_slice * from)
{
   _uuid_slice * to = _uuid_alloc ();
   _uuid_copy (to, from);
   return to;
}




