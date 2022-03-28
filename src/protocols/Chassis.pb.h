/* Automatically generated nanopb header */
/* Generated by nanopb-0.4.6-dev */

#ifndef PB_PROTOCOLS_CHASSIS_PB_H_INCLUDED
#define PB_PROTOCOLS_CHASSIS_PB_H_INCLUDED
#include <pb.h>

#if PB_PROTO_HEADER_VERSION != 40
#error Regenerate this file with the current version of nanopb generator.
#endif

/* Enum definitions */
typedef enum _Log_Type { 
    Log_Type_INVALID = 0, 
    Log_Type_DEBUG = 1, 
    Log_Type_INFO = 2, 
    Log_Type_WARNING = 3, 
    Log_Type_ERROR = 4 
} Log_Type;

/* Struct definitions */
typedef struct _Log { 
    Log_Type type; 
    char content[251]; 
} Log;


/* Helper constants for enums */
#define _Log_Type_MIN Log_Type_INVALID
#define _Log_Type_MAX Log_Type_ERROR
#define _Log_Type_ARRAYSIZE ((Log_Type)(Log_Type_ERROR+1))


#ifdef __cplusplus
extern "C" {
#endif

/* Initializer values for message structs */
#define Log_init_default                         {_Log_Type_MIN, ""}
#define Log_init_zero                            {_Log_Type_MIN, ""}

/* Field tags (for use in manual encoding/decoding) */
#define Log_type_tag                             1
#define Log_content_tag                          2

/* Struct field encoding specification for nanopb */
#define Log_FIELDLIST(X, a) \
X(a, STATIC,   SINGULAR, UENUM,    type,              1) \
X(a, STATIC,   SINGULAR, STRING,   content,           2)
#define Log_CALLBACK NULL
#define Log_DEFAULT NULL

extern const pb_msgdesc_t Log_msg;

/* Defines for backwards compatibility with code written before nanopb-0.4.0 */
#define Log_fields &Log_msg

/* Maximum encoded size of messages (where known) */
#define Log_size                                 255

#ifdef __cplusplus
} /* extern "C" */
#endif

#endif
