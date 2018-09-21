//******************************************************************
// 
//  Generated by IDL to C++ Translator
//  
//  File name: tsnDcps.cpp
//  Source: tsnDcps.idl
//  Generated: Fri Sep 21 11:29:42 2018
//  OpenSplice V6.4.140320OSS
//  
//******************************************************************

#include "tsnDcps.h"

#if DDS_USE_EXPLICIT_TEMPLATES
template class DDS_DCPSUVLSeq < TSN::response, struct responseSeq_uniq_>;
#endif
#if DDS_USE_EXPLICIT_TEMPLATES
template class DDS_DCPSUVLSeq < TSN::request, struct requestSeq_uniq_>;
#endif
#if DDS_USE_EXPLICIT_TEMPLATES
template class DDS_DCPSUVLSeq < TSN::user_information, struct user_informationSeq_uniq_>;
#endif

const char * TSN::user_informationTypeSupportInterface::_local_id = "IDL:TSN/user_informationTypeSupportInterface:1.0";

TSN::user_informationTypeSupportInterface_ptr TSN::user_informationTypeSupportInterface::_duplicate (TSN::user_informationTypeSupportInterface_ptr p)
{
   if (p) p->m_count++;
   return p;
}

DDS::Boolean TSN::user_informationTypeSupportInterface::_local_is_a (const char * _id)
{
   if (strcmp (_id, TSN::user_informationTypeSupportInterface::_local_id) == 0)
   {
      return true;
   }

   typedef DDS::TypeSupport NestedBase_1;

   if (NestedBase_1::_local_is_a (_id))
   {
      return true;
   }

   return false;
}

TSN::user_informationTypeSupportInterface_ptr TSN::user_informationTypeSupportInterface::_narrow (DDS::Object_ptr p)
{
   TSN::user_informationTypeSupportInterface_ptr result = NULL;
   if (p && p->_is_a (TSN::user_informationTypeSupportInterface::_local_id))
   {
      result = dynamic_cast < TSN::user_informationTypeSupportInterface_ptr> (p);
      if (result) result->m_count++;
   }
   return result;
}

TSN::user_informationTypeSupportInterface_ptr TSN::user_informationTypeSupportInterface::_unchecked_narrow (DDS::Object_ptr p)
{
   TSN::user_informationTypeSupportInterface_ptr result;
   result = dynamic_cast < TSN::user_informationTypeSupportInterface_ptr> (p);
   if (result) result->m_count++;
   return result;
}

const char * TSN::user_informationDataWriter::_local_id = "IDL:TSN/user_informationDataWriter:1.0";

TSN::user_informationDataWriter_ptr TSN::user_informationDataWriter::_duplicate (TSN::user_informationDataWriter_ptr p)
{
   if (p) p->m_count++;
   return p;
}

DDS::Boolean TSN::user_informationDataWriter::_local_is_a (const char * _id)
{
   if (strcmp (_id, TSN::user_informationDataWriter::_local_id) == 0)
   {
      return true;
   }

   typedef DDS::DataWriter NestedBase_1;

   if (NestedBase_1::_local_is_a (_id))
   {
      return true;
   }

   return false;
}

TSN::user_informationDataWriter_ptr TSN::user_informationDataWriter::_narrow (DDS::Object_ptr p)
{
   TSN::user_informationDataWriter_ptr result = NULL;
   if (p && p->_is_a (TSN::user_informationDataWriter::_local_id))
   {
      result = dynamic_cast < TSN::user_informationDataWriter_ptr> (p);
      if (result) result->m_count++;
   }
   return result;
}

TSN::user_informationDataWriter_ptr TSN::user_informationDataWriter::_unchecked_narrow (DDS::Object_ptr p)
{
   TSN::user_informationDataWriter_ptr result;
   result = dynamic_cast < TSN::user_informationDataWriter_ptr> (p);
   if (result) result->m_count++;
   return result;
}

const char * TSN::user_informationDataReader::_local_id = "IDL:TSN/user_informationDataReader:1.0";

TSN::user_informationDataReader_ptr TSN::user_informationDataReader::_duplicate (TSN::user_informationDataReader_ptr p)
{
   if (p) p->m_count++;
   return p;
}

DDS::Boolean TSN::user_informationDataReader::_local_is_a (const char * _id)
{
   if (strcmp (_id, TSN::user_informationDataReader::_local_id) == 0)
   {
      return true;
   }

   typedef DDS::DataReader NestedBase_1;

   if (NestedBase_1::_local_is_a (_id))
   {
      return true;
   }

   return false;
}

TSN::user_informationDataReader_ptr TSN::user_informationDataReader::_narrow (DDS::Object_ptr p)
{
   TSN::user_informationDataReader_ptr result = NULL;
   if (p && p->_is_a (TSN::user_informationDataReader::_local_id))
   {
      result = dynamic_cast < TSN::user_informationDataReader_ptr> (p);
      if (result) result->m_count++;
   }
   return result;
}

TSN::user_informationDataReader_ptr TSN::user_informationDataReader::_unchecked_narrow (DDS::Object_ptr p)
{
   TSN::user_informationDataReader_ptr result;
   result = dynamic_cast < TSN::user_informationDataReader_ptr> (p);
   if (result) result->m_count++;
   return result;
}

const char * TSN::user_informationDataReaderView::_local_id = "IDL:TSN/user_informationDataReaderView:1.0";

TSN::user_informationDataReaderView_ptr TSN::user_informationDataReaderView::_duplicate (TSN::user_informationDataReaderView_ptr p)
{
   if (p) p->m_count++;
   return p;
}

DDS::Boolean TSN::user_informationDataReaderView::_local_is_a (const char * _id)
{
   if (strcmp (_id, TSN::user_informationDataReaderView::_local_id) == 0)
   {
      return true;
   }

   typedef DDS::DataReaderView NestedBase_1;

   if (NestedBase_1::_local_is_a (_id))
   {
      return true;
   }

   return false;
}

TSN::user_informationDataReaderView_ptr TSN::user_informationDataReaderView::_narrow (DDS::Object_ptr p)
{
   TSN::user_informationDataReaderView_ptr result = NULL;
   if (p && p->_is_a (TSN::user_informationDataReaderView::_local_id))
   {
      result = dynamic_cast < TSN::user_informationDataReaderView_ptr> (p);
      if (result) result->m_count++;
   }
   return result;
}

TSN::user_informationDataReaderView_ptr TSN::user_informationDataReaderView::_unchecked_narrow (DDS::Object_ptr p)
{
   TSN::user_informationDataReaderView_ptr result;
   result = dynamic_cast < TSN::user_informationDataReaderView_ptr> (p);
   if (result) result->m_count++;
   return result;
}

const char * TSN::requestTypeSupportInterface::_local_id = "IDL:TSN/requestTypeSupportInterface:1.0";

TSN::requestTypeSupportInterface_ptr TSN::requestTypeSupportInterface::_duplicate (TSN::requestTypeSupportInterface_ptr p)
{
   if (p) p->m_count++;
   return p;
}

DDS::Boolean TSN::requestTypeSupportInterface::_local_is_a (const char * _id)
{
   if (strcmp (_id, TSN::requestTypeSupportInterface::_local_id) == 0)
   {
      return true;
   }

   typedef DDS::TypeSupport NestedBase_1;

   if (NestedBase_1::_local_is_a (_id))
   {
      return true;
   }

   return false;
}

TSN::requestTypeSupportInterface_ptr TSN::requestTypeSupportInterface::_narrow (DDS::Object_ptr p)
{
   TSN::requestTypeSupportInterface_ptr result = NULL;
   if (p && p->_is_a (TSN::requestTypeSupportInterface::_local_id))
   {
      result = dynamic_cast < TSN::requestTypeSupportInterface_ptr> (p);
      if (result) result->m_count++;
   }
   return result;
}

TSN::requestTypeSupportInterface_ptr TSN::requestTypeSupportInterface::_unchecked_narrow (DDS::Object_ptr p)
{
   TSN::requestTypeSupportInterface_ptr result;
   result = dynamic_cast < TSN::requestTypeSupportInterface_ptr> (p);
   if (result) result->m_count++;
   return result;
}

const char * TSN::requestDataWriter::_local_id = "IDL:TSN/requestDataWriter:1.0";

TSN::requestDataWriter_ptr TSN::requestDataWriter::_duplicate (TSN::requestDataWriter_ptr p)
{
   if (p) p->m_count++;
   return p;
}

DDS::Boolean TSN::requestDataWriter::_local_is_a (const char * _id)
{
   if (strcmp (_id, TSN::requestDataWriter::_local_id) == 0)
   {
      return true;
   }

   typedef DDS::DataWriter NestedBase_1;

   if (NestedBase_1::_local_is_a (_id))
   {
      return true;
   }

   return false;
}

TSN::requestDataWriter_ptr TSN::requestDataWriter::_narrow (DDS::Object_ptr p)
{
   TSN::requestDataWriter_ptr result = NULL;
   if (p && p->_is_a (TSN::requestDataWriter::_local_id))
   {
      result = dynamic_cast < TSN::requestDataWriter_ptr> (p);
      if (result) result->m_count++;
   }
   return result;
}

TSN::requestDataWriter_ptr TSN::requestDataWriter::_unchecked_narrow (DDS::Object_ptr p)
{
   TSN::requestDataWriter_ptr result;
   result = dynamic_cast < TSN::requestDataWriter_ptr> (p);
   if (result) result->m_count++;
   return result;
}

const char * TSN::requestDataReader::_local_id = "IDL:TSN/requestDataReader:1.0";

TSN::requestDataReader_ptr TSN::requestDataReader::_duplicate (TSN::requestDataReader_ptr p)
{
   if (p) p->m_count++;
   return p;
}

DDS::Boolean TSN::requestDataReader::_local_is_a (const char * _id)
{
   if (strcmp (_id, TSN::requestDataReader::_local_id) == 0)
   {
      return true;
   }

   typedef DDS::DataReader NestedBase_1;

   if (NestedBase_1::_local_is_a (_id))
   {
      return true;
   }

   return false;
}

TSN::requestDataReader_ptr TSN::requestDataReader::_narrow (DDS::Object_ptr p)
{
   TSN::requestDataReader_ptr result = NULL;
   if (p && p->_is_a (TSN::requestDataReader::_local_id))
   {
      result = dynamic_cast < TSN::requestDataReader_ptr> (p);
      if (result) result->m_count++;
   }
   return result;
}

TSN::requestDataReader_ptr TSN::requestDataReader::_unchecked_narrow (DDS::Object_ptr p)
{
   TSN::requestDataReader_ptr result;
   result = dynamic_cast < TSN::requestDataReader_ptr> (p);
   if (result) result->m_count++;
   return result;
}

const char * TSN::requestDataReaderView::_local_id = "IDL:TSN/requestDataReaderView:1.0";

TSN::requestDataReaderView_ptr TSN::requestDataReaderView::_duplicate (TSN::requestDataReaderView_ptr p)
{
   if (p) p->m_count++;
   return p;
}

DDS::Boolean TSN::requestDataReaderView::_local_is_a (const char * _id)
{
   if (strcmp (_id, TSN::requestDataReaderView::_local_id) == 0)
   {
      return true;
   }

   typedef DDS::DataReaderView NestedBase_1;

   if (NestedBase_1::_local_is_a (_id))
   {
      return true;
   }

   return false;
}

TSN::requestDataReaderView_ptr TSN::requestDataReaderView::_narrow (DDS::Object_ptr p)
{
   TSN::requestDataReaderView_ptr result = NULL;
   if (p && p->_is_a (TSN::requestDataReaderView::_local_id))
   {
      result = dynamic_cast < TSN::requestDataReaderView_ptr> (p);
      if (result) result->m_count++;
   }
   return result;
}

TSN::requestDataReaderView_ptr TSN::requestDataReaderView::_unchecked_narrow (DDS::Object_ptr p)
{
   TSN::requestDataReaderView_ptr result;
   result = dynamic_cast < TSN::requestDataReaderView_ptr> (p);
   if (result) result->m_count++;
   return result;
}

const char * TSN::responseTypeSupportInterface::_local_id = "IDL:TSN/responseTypeSupportInterface:1.0";

TSN::responseTypeSupportInterface_ptr TSN::responseTypeSupportInterface::_duplicate (TSN::responseTypeSupportInterface_ptr p)
{
   if (p) p->m_count++;
   return p;
}

DDS::Boolean TSN::responseTypeSupportInterface::_local_is_a (const char * _id)
{
   if (strcmp (_id, TSN::responseTypeSupportInterface::_local_id) == 0)
   {
      return true;
   }

   typedef DDS::TypeSupport NestedBase_1;

   if (NestedBase_1::_local_is_a (_id))
   {
      return true;
   }

   return false;
}

TSN::responseTypeSupportInterface_ptr TSN::responseTypeSupportInterface::_narrow (DDS::Object_ptr p)
{
   TSN::responseTypeSupportInterface_ptr result = NULL;
   if (p && p->_is_a (TSN::responseTypeSupportInterface::_local_id))
   {
      result = dynamic_cast < TSN::responseTypeSupportInterface_ptr> (p);
      if (result) result->m_count++;
   }
   return result;
}

TSN::responseTypeSupportInterface_ptr TSN::responseTypeSupportInterface::_unchecked_narrow (DDS::Object_ptr p)
{
   TSN::responseTypeSupportInterface_ptr result;
   result = dynamic_cast < TSN::responseTypeSupportInterface_ptr> (p);
   if (result) result->m_count++;
   return result;
}

const char * TSN::responseDataWriter::_local_id = "IDL:TSN/responseDataWriter:1.0";

TSN::responseDataWriter_ptr TSN::responseDataWriter::_duplicate (TSN::responseDataWriter_ptr p)
{
   if (p) p->m_count++;
   return p;
}

DDS::Boolean TSN::responseDataWriter::_local_is_a (const char * _id)
{
   if (strcmp (_id, TSN::responseDataWriter::_local_id) == 0)
   {
      return true;
   }

   typedef DDS::DataWriter NestedBase_1;

   if (NestedBase_1::_local_is_a (_id))
   {
      return true;
   }

   return false;
}

TSN::responseDataWriter_ptr TSN::responseDataWriter::_narrow (DDS::Object_ptr p)
{
   TSN::responseDataWriter_ptr result = NULL;
   if (p && p->_is_a (TSN::responseDataWriter::_local_id))
   {
      result = dynamic_cast < TSN::responseDataWriter_ptr> (p);
      if (result) result->m_count++;
   }
   return result;
}

TSN::responseDataWriter_ptr TSN::responseDataWriter::_unchecked_narrow (DDS::Object_ptr p)
{
   TSN::responseDataWriter_ptr result;
   result = dynamic_cast < TSN::responseDataWriter_ptr> (p);
   if (result) result->m_count++;
   return result;
}

const char * TSN::responseDataReader::_local_id = "IDL:TSN/responseDataReader:1.0";

TSN::responseDataReader_ptr TSN::responseDataReader::_duplicate (TSN::responseDataReader_ptr p)
{
   if (p) p->m_count++;
   return p;
}

DDS::Boolean TSN::responseDataReader::_local_is_a (const char * _id)
{
   if (strcmp (_id, TSN::responseDataReader::_local_id) == 0)
   {
      return true;
   }

   typedef DDS::DataReader NestedBase_1;

   if (NestedBase_1::_local_is_a (_id))
   {
      return true;
   }

   return false;
}

TSN::responseDataReader_ptr TSN::responseDataReader::_narrow (DDS::Object_ptr p)
{
   TSN::responseDataReader_ptr result = NULL;
   if (p && p->_is_a (TSN::responseDataReader::_local_id))
   {
      result = dynamic_cast < TSN::responseDataReader_ptr> (p);
      if (result) result->m_count++;
   }
   return result;
}

TSN::responseDataReader_ptr TSN::responseDataReader::_unchecked_narrow (DDS::Object_ptr p)
{
   TSN::responseDataReader_ptr result;
   result = dynamic_cast < TSN::responseDataReader_ptr> (p);
   if (result) result->m_count++;
   return result;
}

const char * TSN::responseDataReaderView::_local_id = "IDL:TSN/responseDataReaderView:1.0";

TSN::responseDataReaderView_ptr TSN::responseDataReaderView::_duplicate (TSN::responseDataReaderView_ptr p)
{
   if (p) p->m_count++;
   return p;
}

DDS::Boolean TSN::responseDataReaderView::_local_is_a (const char * _id)
{
   if (strcmp (_id, TSN::responseDataReaderView::_local_id) == 0)
   {
      return true;
   }

   typedef DDS::DataReaderView NestedBase_1;

   if (NestedBase_1::_local_is_a (_id))
   {
      return true;
   }

   return false;
}

TSN::responseDataReaderView_ptr TSN::responseDataReaderView::_narrow (DDS::Object_ptr p)
{
   TSN::responseDataReaderView_ptr result = NULL;
   if (p && p->_is_a (TSN::responseDataReaderView::_local_id))
   {
      result = dynamic_cast < TSN::responseDataReaderView_ptr> (p);
      if (result) result->m_count++;
   }
   return result;
}

TSN::responseDataReaderView_ptr TSN::responseDataReaderView::_unchecked_narrow (DDS::Object_ptr p)
{
   TSN::responseDataReaderView_ptr result;
   result = dynamic_cast < TSN::responseDataReaderView_ptr> (p);
   if (result) result->m_count++;
   return result;
}



