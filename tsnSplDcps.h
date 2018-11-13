#ifndef TSNSPLTYPES_H
#define TSNSPLTYPES_H

#include <c_base.h>
#include <c_misc.h>
#include <c_sync.h>
#include <c_collection.h>
#include <c_field.h>
#include <v_copyIn.h>

#include "ccpp_tsn.h"


extern c_metaObject __tsn_TSN__load (c_base base);

extern c_metaObject __TSN_serial_number__load (c_base base);
typedef c_ulong _TSN_serial_number;

extern const char *TSN_user_information_metaDescriptor[];
extern const int TSN_user_information_metaDescriptorArrLength;
extern const int TSN_user_information_metaDescriptorLength;
extern c_metaObject __TSN_user_information__load (c_base base);
struct _TSN_user_information ;
extern  v_copyin_result __TSN_user_information__copyIn(c_base base, const struct TSN::user_information *from, struct _TSN_user_information *to);
extern  void __TSN_user_information__copyOut(const void *_from, void *_to);
struct _TSN_user_information {
    c_string uuid;
    c_string first_name;
    c_string last_name;
    c_long date_of_birth;
    c_sequence interests;
    c_ulonglong number_of_highest_post;
};

extern const char *TSN_node_request_metaDescriptor[];
extern const int TSN_node_request_metaDescriptorArrLength;
extern const int TSN_node_request_metaDescriptorLength;
extern c_metaObject __TSN_node_request__load (c_base base);
struct _TSN_node_request ;
extern  v_copyin_result __TSN_node_request__copyIn(c_base base, const struct TSN::node_request *from, struct _TSN_node_request *to);
extern  void __TSN_node_request__copyOut(const void *_from, void *_to);
struct _TSN_node_request {
    c_char fulfiller_uuid[37];
    c_sequence requested_posts;
};

extern const char *TSN_request_metaDescriptor[];
extern const int TSN_request_metaDescriptorArrLength;
extern const int TSN_request_metaDescriptorLength;
extern c_metaObject __TSN_request__load (c_base base);
struct _TSN_request ;
extern  v_copyin_result __TSN_request__copyIn(c_base base, const struct TSN::request *from, struct _TSN_request *to);
extern  void __TSN_request__copyOut(const void *_from, void *_to);
struct _TSN_request {
    c_string uuid;
    c_sequence user_requests;
};

extern const char *TSN_post_data_metaDescriptor[];
extern const int TSN_post_data_metaDescriptorArrLength;
extern const int TSN_post_data_metaDescriptorLength;
extern c_metaObject __TSN_post_data__load (c_base base);
struct _TSN_post_data ;
extern  v_copyin_result __TSN_post_data__copyIn(c_base base, const struct TSN::post_data *from, struct _TSN_post_data *to);
extern  void __TSN_post_data__copyOut(const void *_from, void *_to);
struct _TSN_post_data {
    c_char owner_uuid[37];
    _TSN_serial_number post_id;
};

extern const char *TSN_response_metaDescriptor[];
extern const int TSN_response_metaDescriptorArrLength;
extern const int TSN_response_metaDescriptorLength;
extern c_metaObject __TSN_response__load (c_base base);
struct _TSN_response ;
extern  v_copyin_result __TSN_response__copyIn(c_base base, const struct TSN::response *from, struct _TSN_response *to);
extern  void __TSN_response__copyOut(const void *_from, void *_to);
struct _TSN_response {
    c_string uuid;
    _TSN_serial_number post_id;
    c_string post_body;
    c_long date_of_creation;
    struct _TSN_post_data parent_post;
    c_sequence child_posts;
};

extern const char *TSN_private_message_metaDescriptor[];
extern const int TSN_private_message_metaDescriptorArrLength;
extern const int TSN_private_message_metaDescriptorLength;
extern c_metaObject __TSN_private_message__load (c_base base);
struct _TSN_private_message ;
extern  v_copyin_result __TSN_private_message__copyIn(c_base base, const struct TSN::private_message *from, struct _TSN_private_message *to);
extern  void __TSN_private_message__copyOut(const void *_from, void *_to);
struct _TSN_private_message {
    c_string receiver_uuid;
    c_char sender_uuid[37];
    c_string message_body;
    c_long date_of_creation;
};

#undef OS_API
#endif
