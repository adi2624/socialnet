#ifndef HELLOWORLDDATASPLTYPES_H
#define HELLOWORLDDATASPLTYPES_H

#include "ccpp_HelloWorldData.h"

#include <c_base.h>
#include <c_misc.h>
#include <c_sync.h>
#include <c_collection.h>
#include <c_field.h>

extern c_metaObject __HelloWorldData_TSN__load (c_base base);

extern c_metaObject __TSN_serial_number__load (c_base base);
typedef c_ulong _TSN_serial_number;

extern c_metaObject __TSN_UserInformation__load (c_base base);
extern const char * __TSN_UserInformation__keys (void);
extern const char * __TSN_UserInformation__name (void);
struct _TSN_UserInformation ;
extern  c_bool __TSN_UserInformation__copyIn(c_base base, struct TSN::UserInformation *from, struct _TSN_UserInformation *to);
extern  void __TSN_UserInformation__copyOut(void *_from, void *_to);
struct _TSN_UserInformation {
    c_string uuid;
    c_string first_name;
    c_string last_name;
    c_long dateOfBirth;
    c_sequence interests;
};

extern c_metaObject __TSN_NodeRequest__load (c_base base);
extern const char * __TSN_NodeRequest__keys (void);
extern const char * __TSN_NodeRequest__name (void);
struct _TSN_NodeRequest ;
extern  c_bool __TSN_NodeRequest__copyIn(c_base base, struct TSN::NodeRequest *from, struct _TSN_NodeRequest *to);
extern  void __TSN_NodeRequest__copyOut(void *_from, void *_to);
struct _TSN_NodeRequest {
    c_char fulfiller_uuid[17];
    c_sequence requested_posts;
};

extern c_metaObject __TSN_Request__load (c_base base);
extern const char * __TSN_Request__keys (void);
extern const char * __TSN_Request__name (void);
struct _TSN_Request ;
extern  c_bool __TSN_Request__copyIn(c_base base, struct TSN::Request *from, struct _TSN_Request *to);
extern  void __TSN_Request__copyOut(void *_from, void *_to);
struct _TSN_Request {
    c_string uuid;
    c_sequence user_requests;
};

extern c_metaObject __TSN_Response__load (c_base base);
extern const char * __TSN_Response__keys (void);
extern const char * __TSN_Response__name (void);
struct _TSN_Response ;
extern  c_bool __TSN_Response__copyIn(c_base base, struct TSN::Response *from, struct _TSN_Response *to);
extern  void __TSN_Response__copyOut(void *_from, void *_to);
struct _TSN_Response {
    c_string uuid;
    _TSN_serial_number post_id;
    c_string post_body;
    c_long dateOfCreation;
};

#endif
