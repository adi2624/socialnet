#include "tsnSplDcps.h"
#include "ccpp_tsn.h"

#include <v_copyIn.h>
#include <v_topic.h>
#include <os_stdlib.h>
#include <string.h>
#include <os_report.h>

v_copyin_result
__TSN_user_information__copyIn(
    c_base base,
    const struct ::TSN::user_information *from,
    struct _TSN_user_information *to)
{
    v_copyin_result result = V_COPYIN_RESULT_OK;
    (void) base;

    {
        /* Allocate the length of the array (and null terminator) as a database
        * string
        */
        to->uuid = c_stringMalloc(base, (37 + 1));
        if(to->uuid)
        {
            /* Copy the value of the array into the database string */
           strncpy(to->uuid, from->uuid, 37);
            to->uuid[37] = '\0';
        }
    }
#ifdef OSPL_BOUNDS_CHECK
    if(from->first_name){
        if(((unsigned int)strlen(from->first_name)) <= 70){
            to->first_name = c_stringNew_s(base, from->first_name);
            if(to->first_name == NULL) {
                result = V_COPYIN_RESULT_OUT_OF_MEMORY;
            }
        } else {
            OS_REPORT (OS_ERROR, "copyIn", 0,"Member 'TSN::user_information.first_name' of type 'C_STRING<70>' is out of range.");
            result = V_COPYIN_RESULT_INVALID;
        }
    } else {
        OS_REPORT (OS_ERROR, "copyIn", 0,"Member 'TSN::user_information.first_name' of type 'C_STRING<70>' is NULL.");
        result = V_COPYIN_RESULT_INVALID;
    }
#else
    to->first_name = c_stringNew_s(base, from->first_name);
    if(to->first_name == NULL) {
        result = V_COPYIN_RESULT_OUT_OF_MEMORY;
    }
#endif
#ifdef OSPL_BOUNDS_CHECK
    if(from->last_name){
        if(((unsigned int)strlen(from->last_name)) <= 70){
            to->last_name = c_stringNew_s(base, from->last_name);
            if(to->last_name == NULL) {
                result = V_COPYIN_RESULT_OUT_OF_MEMORY;
            }
        } else {
            OS_REPORT (OS_ERROR, "copyIn", 0,"Member 'TSN::user_information.last_name' of type 'C_STRING<70>' is out of range.");
            result = V_COPYIN_RESULT_INVALID;
        }
    } else {
        OS_REPORT (OS_ERROR, "copyIn", 0,"Member 'TSN::user_information.last_name' of type 'C_STRING<70>' is NULL.");
        result = V_COPYIN_RESULT_INVALID;
    }
#else
    to->last_name = c_stringNew_s(base, from->last_name);
    if(to->last_name == NULL) {
        result = V_COPYIN_RESULT_OUT_OF_MEMORY;
    }
#endif
    to->date_of_birth = (c_long)from->date_of_birth;
    {
/* Code generated by /home/dds/OvernightTests/michielb/opensplice-test/tags/OSPL_V6_7_180404OSS_RELEASE/ubuntu1604-64a/x86_64.linux-release/build/src/tools/idlpp/code/idl_genCorbaCxxCopyin.c at line 826 */

        static c_type type0 = NULL;
        c_type subtype0;
        c_ulong length0;
        c_string *dest0;
        const ::TSN::user_information::_interests_seq *src = &from->interests;

        if (type0 == NULL) {
            subtype0 = c_type(c_metaResolve (c_metaObject(base), "c_string"));
            type0 = c_metaSequenceTypeNew(c_metaObject(base),"C_SEQUENCE<c_string>",subtype0,0);
            c_free(subtype0);
        }
        length0 = (c_ulong)(*src).length();
#ifdef OSPL_BOUNDS_CHECK
         dest0 = (c_string *)c_newSequence_s(c_collectionType(type0),length0);
         if(dest0 != NULL) {
            /* Code generated by /home/dds/OvernightTests/michielb/opensplice-test/tags/OSPL_V6_7_180404OSS_RELEASE/ubuntu1604-64a/x86_64.linux-release/build/src/tools/idlpp/code/idl_genCorbaCxxCopyin.c at line 2080 */
            unsigned int i0;
            for (i0 = 0; (i0 < length0) && V_COPYIN_RESULT_IS_OK(result); i0++) {
#ifdef OSPL_BOUNDS_CHECK
                if((*src)[i0]){
                    dest0[i0] = c_stringNew_s(base, (*src)[i0]);
                    if(dest0[i0] == NULL) {
                        result = V_COPYIN_RESULT_OUT_OF_MEMORY;
                    }
                } else {
                    OS_REPORT (OS_ERROR, "copyIn", 0,"Element of 'TSN::user_information.*src' of type 'c_string' is NULL.");
                    result = V_COPYIN_RESULT_INVALID;
                }
#else
                dest0[i0] = c_stringNew_s(base, (*src)[i0]);
                if(dest0[i0] == NULL) {
                    result = V_COPYIN_RESULT_OUT_OF_MEMORY;
                }
#endif
            }
            to->interests = (c_sequence)dest0;
         } else {
             result = V_COPYIN_RESULT_OUT_OF_MEMORY;
          }
#else
        dest0 = (c_string *)c_newSequence_s(c_collectionType(type0),length0);
        if(dest0 != NULL) {
            /* Code generated by /home/dds/OvernightTests/michielb/opensplice-test/tags/OSPL_V6_7_180404OSS_RELEASE/ubuntu1604-64a/x86_64.linux-release/build/src/tools/idlpp/code/idl_genCorbaCxxCopyin.c at line 2080 */
            unsigned int i0;
            for (i0 = 0; (i0 < length0) && V_COPYIN_RESULT_IS_OK(result); i0++) {
#ifdef OSPL_BOUNDS_CHECK
                if((*src)[i0]){
                    dest0[i0] = c_stringNew_s(base, (*src)[i0]);
                    if(dest0[i0] == NULL) {
                        result = V_COPYIN_RESULT_OUT_OF_MEMORY;
                    }
                } else {
                    OS_REPORT (OS_ERROR, "copyIn", 0,"Element of 'TSN::user_information.*src' of type 'c_string' is NULL.");
                    result = V_COPYIN_RESULT_INVALID;
                }
#else
                dest0[i0] = c_stringNew_s(base, (*src)[i0]);
                if(dest0[i0] == NULL) {
                    result = V_COPYIN_RESULT_OUT_OF_MEMORY;
                }
#endif
            }
            to->interests = (c_sequence)dest0;
        } else {
            result = V_COPYIN_RESULT_OUT_OF_MEMORY;
        }
#endif
    }
    to->number_of_highest_post = (c_ulonglong)from->number_of_highest_post;
    return result;
}

v_copyin_result
__TSN_node_request__copyIn(
    c_base base,
    const struct ::TSN::node_request *from,
    struct _TSN_node_request *to)
{
    v_copyin_result result = V_COPYIN_RESULT_OK;
    (void) base;

    {
        typedef c_char _DestType[37];
        _DestType *dest = &to->fulfiller_uuid;
        memcpy (dest, from->fulfiller_uuid, sizeof (*dest));
    }
    {
/* Code generated by /home/dds/OvernightTests/michielb/opensplice-test/tags/OSPL_V6_7_180404OSS_RELEASE/ubuntu1604-64a/x86_64.linux-release/build/src/tools/idlpp/code/idl_genCorbaCxxCopyin.c at line 826 */

        static c_type type0 = NULL;
        c_type subtype0;
        c_ulong length0;
        _TSN_serial_number *dest0;
        const ::TSN::node_request::_requested_posts_seq *src = &from->requested_posts;

        if (type0 == NULL) {
            subtype0 = c_type(c_metaResolve (c_metaObject(base), "TSN::serial_number"));
            type0 = c_metaSequenceTypeNew(c_metaObject(base),"C_SEQUENCE<TSN::serial_number>",subtype0,0);
            c_free(subtype0);
        }
        length0 = (c_ulong)(*src).length();
#ifdef OSPL_BOUNDS_CHECK
         dest0 = (_TSN_serial_number *)c_newSequence_s(c_collectionType(type0),length0);
         if(dest0 != NULL) {
            /* Code generated by /home/dds/OvernightTests/michielb/opensplice-test/tags/OSPL_V6_7_180404OSS_RELEASE/ubuntu1604-64a/x86_64.linux-release/build/src/tools/idlpp/code/idl_genCorbaCxxCopyin.c at line 2025 */
            const _TSN_serial_number *buf0;
            buf0 = (const _TSN_serial_number *)(*src).get_buffer();
            memcpy (dest0,buf0,length0* sizeof(*dest0));
            to->requested_posts = (c_sequence)dest0;
         } else {
             result = V_COPYIN_RESULT_OUT_OF_MEMORY;
          }
#else
        dest0 = (_TSN_serial_number *)c_newSequence_s(c_collectionType(type0),length0);
        if(dest0 != NULL) {
            /* Code generated by /home/dds/OvernightTests/michielb/opensplice-test/tags/OSPL_V6_7_180404OSS_RELEASE/ubuntu1604-64a/x86_64.linux-release/build/src/tools/idlpp/code/idl_genCorbaCxxCopyin.c at line 2025 */
            const _TSN_serial_number *buf0;
            buf0 = (const _TSN_serial_number *)(*src).get_buffer();
            memcpy (dest0,buf0,length0* sizeof(*dest0));
            to->requested_posts = (c_sequence)dest0;
        } else {
            result = V_COPYIN_RESULT_OUT_OF_MEMORY;
        }
#endif
    }
    return result;
}

v_copyin_result
__TSN_request__copyIn(
    c_base base,
    const struct ::TSN::request *from,
    struct _TSN_request *to)
{
    v_copyin_result result = V_COPYIN_RESULT_OK;
    (void) base;

    {
        /* Allocate the length of the array (and null terminator) as a database
        * string
        */
        to->uuid = c_stringMalloc(base, (37 + 1));
        if(to->uuid)
        {
            /* Copy the value of the array into the database string */
           strncpy(to->uuid, from->uuid, 37);
            to->uuid[37] = '\0';
        }
    }
    {
/* Code generated by /home/dds/OvernightTests/michielb/opensplice-test/tags/OSPL_V6_7_180404OSS_RELEASE/ubuntu1604-64a/x86_64.linux-release/build/src/tools/idlpp/code/idl_genCorbaCxxCopyin.c at line 826 */

        static c_type type0 = NULL;
        c_type subtype0;
        c_ulong length0;
        struct _TSN_node_request *dest0;
        const ::TSN::request::_user_requests_seq *src = &from->user_requests;

        if (type0 == NULL) {
            subtype0 = c_type(c_metaResolve (c_metaObject(base), "TSN::node_request"));
            type0 = c_metaSequenceTypeNew(c_metaObject(base),"C_SEQUENCE<TSN::node_request>",subtype0,0);
            c_free(subtype0);
        }
        length0 = (c_ulong)(*src).length();
#ifdef OSPL_BOUNDS_CHECK
         dest0 = (struct _TSN_node_request *)c_newSequence_s(c_collectionType(type0),length0);
         if(dest0 != NULL) {
            /* Code generated by /home/dds/OvernightTests/michielb/opensplice-test/tags/OSPL_V6_7_180404OSS_RELEASE/ubuntu1604-64a/x86_64.linux-release/build/src/tools/idlpp/code/idl_genCorbaCxxCopyin.c at line 2080 */
            unsigned int i0;
            for (i0 = 0; (i0 < length0) && V_COPYIN_RESULT_IS_OK(result); i0++) {
                extern v_copyin_result __TSN_node_request__copyIn(c_base base,
                    const TSN::node_request *From,
                    struct _TSN_node_request *To);

                result = __TSN_node_request__copyIn(base, &(*src)[i0], (struct _TSN_node_request *)&dest0[i0]);
            }
            to->user_requests = (c_sequence)dest0;
         } else {
             result = V_COPYIN_RESULT_OUT_OF_MEMORY;
          }
#else
        dest0 = (struct _TSN_node_request *)c_newSequence_s(c_collectionType(type0),length0);
        if(dest0 != NULL) {
            /* Code generated by /home/dds/OvernightTests/michielb/opensplice-test/tags/OSPL_V6_7_180404OSS_RELEASE/ubuntu1604-64a/x86_64.linux-release/build/src/tools/idlpp/code/idl_genCorbaCxxCopyin.c at line 2080 */
            unsigned int i0;
            for (i0 = 0; (i0 < length0) && V_COPYIN_RESULT_IS_OK(result); i0++) {
                extern v_copyin_result __TSN_node_request__copyIn(c_base base,
                    const TSN::node_request *From,
                    struct _TSN_node_request *To);

                result = __TSN_node_request__copyIn(base, &(*src)[i0], (struct _TSN_node_request *)&dest0[i0]);
            }
            to->user_requests = (c_sequence)dest0;
        } else {
            result = V_COPYIN_RESULT_OUT_OF_MEMORY;
        }
#endif
    }
    return result;
}

v_copyin_result
__TSN_response__copyIn(
    c_base base,
    const struct ::TSN::response *from,
    struct _TSN_response *to)
{
    v_copyin_result result = V_COPYIN_RESULT_OK;
    (void) base;

    {
        /* Allocate the length of the array (and null terminator) as a database
        * string
        */
        to->uuid = c_stringMalloc(base, (37 + 1));
        if(to->uuid)
        {
            /* Copy the value of the array into the database string */
           strncpy(to->uuid, from->uuid, 37);
            to->uuid[37] = '\0';
        }
    }
    to->post_id = (c_ulong)from->post_id;
#ifdef OSPL_BOUNDS_CHECK
    if(from->post_body){
        to->post_body = c_stringNew_s(base, from->post_body);
        if(to->post_body == NULL) {
            result = V_COPYIN_RESULT_OUT_OF_MEMORY;
        }
    } else {
        OS_REPORT (OS_ERROR, "copyIn", 0,"Member 'TSN::response.post_body' of type 'c_string' is NULL.");
        result = V_COPYIN_RESULT_INVALID;
    }
#else
    to->post_body = c_stringNew_s(base, from->post_body);
    if(to->post_body == NULL) {
        result = V_COPYIN_RESULT_OUT_OF_MEMORY;
    }
#endif
    to->date_of_creation = (c_long)from->date_of_creation;
    return result;
}

void
__TSN_user_information__copyOut(
    const void *_from,
    void *_to)
{
    const struct _TSN_user_information *from = (const struct _TSN_user_information *)_from;
    struct ::TSN::user_information *to = (struct ::TSN::user_information *)_to;
    {
       strncpy((char *)to->uuid, from->uuid, 37);
    }
    to->first_name = DDS::string_dup(from->first_name ? from->first_name : "");
    to->last_name = DDS::string_dup(from->last_name ? from->last_name : "");
    to->date_of_birth = (::DDS::Long)from->date_of_birth;
    {
        long size0;
        const c_string *src0 = (const c_string *)from->interests;
        ::TSN::user_information::_interests_seq *dst = &to->interests;

        size0 = c_arraySize(c_sequence(from->interests));
        to->interests.length(size0);
        {
            long i0;
            for (i0 = 0; i0 < size0; i0++) {
                (*dst)[i0] = DDS::string_dup(src0[i0]);
            }
        }
    }
    to->number_of_highest_post = (::DDS::ULongLong)from->number_of_highest_post;
}

void
__TSN_node_request__copyOut(
    const void *_from,
    void *_to)
{
    const struct _TSN_node_request *from = (const struct _TSN_node_request *)_from;
    struct ::TSN::node_request *to = (struct ::TSN::node_request *)_to;
    {
        typedef c_char _DestType[37];
        const _DestType *src = &from->fulfiller_uuid;

        memcpy ((void *)to->fulfiller_uuid, src, sizeof (*src));
    }
    {
        long size0;
        const _TSN_serial_number *src0 = (const _TSN_serial_number *)from->requested_posts;
        ::TSN::node_request::_requested_posts_seq *dst = &to->requested_posts;

        size0 = c_arraySize(c_sequence(from->requested_posts));
        to->requested_posts.length(size0);
        {
            _TSN_serial_number *buf0;
            buf0 = (_TSN_serial_number *)(*dst).get_buffer();
            memcpy ((void *)buf0,src0,size0* sizeof(*buf0));
        }
    }
}

void
__TSN_request__copyOut(
    const void *_from,
    void *_to)
{
    const struct _TSN_request *from = (const struct _TSN_request *)_from;
    struct ::TSN::request *to = (struct ::TSN::request *)_to;
    {
       strncpy((char *)to->uuid, from->uuid, 37);
    }
    {
        long size0;
        const struct _TSN_node_request *src0 = (const struct _TSN_node_request *)from->user_requests;
        ::TSN::request::_user_requests_seq *dst = &to->user_requests;

        size0 = c_arraySize(c_sequence(from->user_requests));
        to->user_requests.length(size0);
        {
            long i0;
            for (i0 = 0; i0 < size0; i0++) {
                extern void __TSN_node_request__copyOut(const void *from, void *to);
                __TSN_node_request__copyOut((const void *)&src0[i0], (void *)&(*dst)[i0]);
            }
        }
    }
}

void
__TSN_response__copyOut(
    const void *_from,
    void *_to)
{
    const struct _TSN_response *from = (const struct _TSN_response *)_from;
    struct ::TSN::response *to = (struct ::TSN::response *)_to;
    {
       strncpy((char *)to->uuid, from->uuid, 37);
    }
    to->post_id = (::DDS::ULong)from->post_id;
    to->post_body = DDS::string_dup(from->post_body ? from->post_body : "");
    to->date_of_creation = (::DDS::Long)from->date_of_creation;
}

