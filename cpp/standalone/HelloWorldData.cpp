//******************************************************************
// 
//  Generated by IDL to C++ Translator
//  
//  File name: HelloWorldData.cpp
//  Source: ../../idl/HelloWorldData.idl
//  Generated: Fri Sep 14 16:37:02 2018
//  OpenSplice V6.4.140320OSS
//  
//******************************************************************

#include "HelloWorldData.h"


#if DDS_USE_EXPLICIT_TEMPLATES
template class DDS_DCPS_FArray_var< TSN::Response::_uuid, TSN::Response::_uuid_slice, struct TSN::Response::_uuid_uniq_>;
template class DDS_DCPS_Array_forany< TSN::Response::_uuid, TSN::Response::_uuid_slice, struct TSN::Response::_uuid_uniq_>;
#endif

template <>
TSN::Response::_uuid_slice* DDS_DCPS_ArrayHelper < TSN::Response::_uuid, TSN::Response::_uuid_slice, TSN::Response::_uuid_uniq_>::alloc ()
{
   return TSN::Response::_uuid_alloc ();
}

template <>
void DDS_DCPS_ArrayHelper < TSN::Response::_uuid, TSN::Response::_uuid_slice, TSN::Response::_uuid_uniq_>::copy (TSN::Response::_uuid_slice *to, const TSN::Response::_uuid_slice* from)
{
   TSN::Response::_uuid_copy (to, from);
}

template <>
void DDS_DCPS_ArrayHelper < TSN::Response::_uuid, TSN::Response::_uuid_slice, TSN::Response::_uuid_uniq_>::free (TSN::Response::_uuid_slice *ptr)
{
   TSN::Response::_uuid_free (ptr);
}

TSN::Response::_uuid_slice * TSN::Response::_uuid_alloc ()
{
   DDS::Char * ret = (DDS::Char*) new DDS::Char [17];
   return (_uuid_slice *) ret;
}

void TSN::Response::_uuid_free (_uuid_slice * s)
{
   delete [] s;
}

void TSN::Response::_uuid_copy
(
   _uuid_slice * to,
   const _uuid_slice * from
)
{
   const DDS::Char* sv = ( const DDS::Char*) from;
   DDS::Char* tv = (DDS::Char*) to;
   for (DDS::ULong i = 0; i < 17; i++) tv[i] = sv[i];
}

TSN::Response::_uuid_slice * TSN::Response::_uuid_dup
   (const _uuid_slice * from)
{
   _uuid_slice * to = _uuid_alloc ();
   _uuid_copy (to, from);
   return to;
}

#if DDS_USE_EXPLICIT_TEMPLATES
template class DDS_DCPSUVLSeq < TSN::NodeRequest, struct _user_requests_seq_uniq_>;
#endif

#if DDS_USE_EXPLICIT_TEMPLATES
template class DDS_DCPS_FArray_var< TSN::Request::_uuid, TSN::Request::_uuid_slice, struct TSN::Request::_uuid_uniq_>;
template class DDS_DCPS_Array_forany< TSN::Request::_uuid, TSN::Request::_uuid_slice, struct TSN::Request::_uuid_uniq_>;
#endif

template <>
TSN::Request::_uuid_slice* DDS_DCPS_ArrayHelper < TSN::Request::_uuid, TSN::Request::_uuid_slice, TSN::Request::_uuid_uniq_>::alloc ()
{
   return TSN::Request::_uuid_alloc ();
}

template <>
void DDS_DCPS_ArrayHelper < TSN::Request::_uuid, TSN::Request::_uuid_slice, TSN::Request::_uuid_uniq_>::copy (TSN::Request::_uuid_slice *to, const TSN::Request::_uuid_slice* from)
{
   TSN::Request::_uuid_copy (to, from);
}

template <>
void DDS_DCPS_ArrayHelper < TSN::Request::_uuid, TSN::Request::_uuid_slice, TSN::Request::_uuid_uniq_>::free (TSN::Request::_uuid_slice *ptr)
{
   TSN::Request::_uuid_free (ptr);
}

TSN::Request::_uuid_slice * TSN::Request::_uuid_alloc ()
{
   DDS::Char * ret = (DDS::Char*) new DDS::Char [17];
   return (_uuid_slice *) ret;
}

void TSN::Request::_uuid_free (_uuid_slice * s)
{
   delete [] s;
}

void TSN::Request::_uuid_copy
(
   _uuid_slice * to,
   const _uuid_slice * from
)
{
   const DDS::Char* sv = ( const DDS::Char*) from;
   DDS::Char* tv = (DDS::Char*) to;
   for (DDS::ULong i = 0; i < 17; i++) tv[i] = sv[i];
}

TSN::Request::_uuid_slice * TSN::Request::_uuid_dup
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
template class DDS_DCPS_FArray_var< TSN::NodeRequest::_fulfiller_uuid, TSN::NodeRequest::_fulfiller_uuid_slice, struct TSN::NodeRequest::_fulfiller_uuid_uniq_>;
template class DDS_DCPS_Array_forany< TSN::NodeRequest::_fulfiller_uuid, TSN::NodeRequest::_fulfiller_uuid_slice, struct TSN::NodeRequest::_fulfiller_uuid_uniq_>;
#endif

template <>
TSN::NodeRequest::_fulfiller_uuid_slice* DDS_DCPS_ArrayHelper < TSN::NodeRequest::_fulfiller_uuid, TSN::NodeRequest::_fulfiller_uuid_slice, TSN::NodeRequest::_fulfiller_uuid_uniq_>::alloc ()
{
   return TSN::NodeRequest::_fulfiller_uuid_alloc ();
}

template <>
void DDS_DCPS_ArrayHelper < TSN::NodeRequest::_fulfiller_uuid, TSN::NodeRequest::_fulfiller_uuid_slice, TSN::NodeRequest::_fulfiller_uuid_uniq_>::copy (TSN::NodeRequest::_fulfiller_uuid_slice *to, const TSN::NodeRequest::_fulfiller_uuid_slice* from)
{
   TSN::NodeRequest::_fulfiller_uuid_copy (to, from);
}

template <>
void DDS_DCPS_ArrayHelper < TSN::NodeRequest::_fulfiller_uuid, TSN::NodeRequest::_fulfiller_uuid_slice, TSN::NodeRequest::_fulfiller_uuid_uniq_>::free (TSN::NodeRequest::_fulfiller_uuid_slice *ptr)
{
   TSN::NodeRequest::_fulfiller_uuid_free (ptr);
}

TSN::NodeRequest::_fulfiller_uuid_slice * TSN::NodeRequest::_fulfiller_uuid_alloc ()
{
   DDS::Char * ret = (DDS::Char*) new DDS::Char [17];
   return (_fulfiller_uuid_slice *) ret;
}

void TSN::NodeRequest::_fulfiller_uuid_free (_fulfiller_uuid_slice * s)
{
   delete [] s;
}

void TSN::NodeRequest::_fulfiller_uuid_copy
(
   _fulfiller_uuid_slice * to,
   const _fulfiller_uuid_slice * from
)
{
   const DDS::Char* sv = ( const DDS::Char*) from;
   DDS::Char* tv = (DDS::Char*) to;
   for (DDS::ULong i = 0; i < 17; i++) tv[i] = sv[i];
}

TSN::NodeRequest::_fulfiller_uuid_slice * TSN::NodeRequest::_fulfiller_uuid_dup
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
template class DDS_DCPS_FArray_var< TSN::UserInformation::_uuid, TSN::UserInformation::_uuid_slice, struct TSN::UserInformation::_uuid_uniq_>;
template class DDS_DCPS_Array_forany< TSN::UserInformation::_uuid, TSN::UserInformation::_uuid_slice, struct TSN::UserInformation::_uuid_uniq_>;
#endif

template <>
TSN::UserInformation::_uuid_slice* DDS_DCPS_ArrayHelper < TSN::UserInformation::_uuid, TSN::UserInformation::_uuid_slice, TSN::UserInformation::_uuid_uniq_>::alloc ()
{
   return TSN::UserInformation::_uuid_alloc ();
}

template <>
void DDS_DCPS_ArrayHelper < TSN::UserInformation::_uuid, TSN::UserInformation::_uuid_slice, TSN::UserInformation::_uuid_uniq_>::copy (TSN::UserInformation::_uuid_slice *to, const TSN::UserInformation::_uuid_slice* from)
{
   TSN::UserInformation::_uuid_copy (to, from);
}

template <>
void DDS_DCPS_ArrayHelper < TSN::UserInformation::_uuid, TSN::UserInformation::_uuid_slice, TSN::UserInformation::_uuid_uniq_>::free (TSN::UserInformation::_uuid_slice *ptr)
{
   TSN::UserInformation::_uuid_free (ptr);
}

TSN::UserInformation::_uuid_slice * TSN::UserInformation::_uuid_alloc ()
{
   DDS::Char * ret = (DDS::Char*) new DDS::Char [17];
   return (_uuid_slice *) ret;
}

void TSN::UserInformation::_uuid_free (_uuid_slice * s)
{
   delete [] s;
}

void TSN::UserInformation::_uuid_copy
(
   _uuid_slice * to,
   const _uuid_slice * from
)
{
   const DDS::Char* sv = ( const DDS::Char*) from;
   DDS::Char* tv = (DDS::Char*) to;
   for (DDS::ULong i = 0; i < 17; i++) tv[i] = sv[i];
}

TSN::UserInformation::_uuid_slice * TSN::UserInformation::_uuid_dup
   (const _uuid_slice * from)
{
   _uuid_slice * to = _uuid_alloc ();
   _uuid_copy (to, from);
   return to;
}




