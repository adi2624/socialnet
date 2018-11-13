#ifndef TSNSPLTYPES_H
#define TSNSPLTYPES_H

#include "ccpp_tsn.h"

#include <c_base.h>
#include <c_misc.h>
#include <c_sync.h>
#include <c_collection.h>
#include <c_field.h>

extern c_metaObject __tsn_TSN__load (c_base base);

extern c_metaObject __TSN_serial_number__load (c_base base);
typedef c_ulong _TSN_serial_number;

extern c_metaObject __TSN_user_information__load (c_base base);
extern const char * __TSN_user_information__keys (void);
extern const char * __TSN_user_information__name (void);
struct _TSN_user_information ;
extern  c_bool __TSN_user_information__copyIn(c_base base, struct TSN::user_information *from, struct _TSN_user_information *to);
extern  void __TSN_user_information__copyOut(void *_from, void *_to);
struct _TSN_user_information {
    c_string uuid;
    c_string first_name;
    c_string last_name;
    c_long date_of_birth;
    c_sequence interests;
    c_ulonglong number_of_highest_post;
};

extern c_metaObject __TSN_node_request__load (c_base base);
extern const char * __TSN_node_request__keys (void);
extern const char * __TSN_node_request__name (void);
struct _TSN_node_request ;
extern  c_bool __TSN_node_request__copyIn(c_base base, struct TSN::node_request *from, struct _TSN_node_request *to);
extern  void __TSN_node_request__copyOut(void *_from, void *_to);
struct _TSN_node_request {
    c_char fulfiller_uuid[37];
    c_sequence requested_posts;
};

extern c_metaObject __TSN_request__load (c_base base);
extern const char * __TSN_request__keys (void);
extern const char * __TSN_request__name (void);
struct _TSN_request ;
extern  c_bool __TSN_request__copyIn(c_base base, struct TSN::request *from, struct _TSN_request *to);
extern  void __TSN_request__copyOut(void *_from, void *_to);
struct _TSN_request {
    c_string uuid;
    c_sequence user_requests;
};

extern c_metaObject __TSN_response__load (c_base base);
extern const char * __TSN_response__keys (void);
extern const char * __TSN_response__name (void);
struct _TSN_response ;
extern  c_bool __TSN_response__copyIn(c_base base, struct TSN::response *from, struct _TSN_response *to);
extern  void __TSN_response__copyOut(void *_from, void *_to);
struct _TSN_response {
    c_string uuid;
    _TSN_serial_number post_id;
    c_string post_body;
    c_long date_of_creation;
};

#endif
