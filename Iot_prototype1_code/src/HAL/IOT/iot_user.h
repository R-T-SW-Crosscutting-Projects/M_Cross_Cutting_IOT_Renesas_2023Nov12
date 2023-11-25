#ifndef IOT_USER_H
#define IOT_USER_H
#include "../../MIDDLEWARE/Middleware.h"
#define iot_buffer_size 200

extern tbyte Options[max_num];
tbyte send_buffer[16]={0} ;


tword send_buffer_size = sizeof(send_buffer) / sizeof(send_buffer[0]);

tbyte recieve_buffer[23];

#define recieve_buffer_size 23

#endif
