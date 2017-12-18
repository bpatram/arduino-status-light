/* Automatically generated nanopb header */
/* Generated by nanopb-0.4.0-dev at Mon Dec 18 02:19:42 2017. */

#ifndef PB_COMMANDS_PB_H_INCLUDED
#define PB_COMMANDS_PB_H_INCLUDED
#include <pb.h>

/* @@protoc_insertion_point(includes) */
#if PB_PROTO_HEADER_VERSION != 30
#error Regenerate this file with the current version of nanopb generator.
#endif

#ifdef __cplusplus
extern "C" {
#endif

/* Enum definitions */
typedef enum _Relay {
    Relay_ALL = 0,
    Relay_ONE = 1,
    Relay_TWO = 2,
    Relay_THREE = 3,
    Relay_FOUR = 4
} Relay;
#define _Relay_MIN Relay_ALL
#define _Relay_MAX Relay_FOUR
#define _Relay_ARRAYSIZE ((Relay)(Relay_FOUR+1))

typedef enum _StatusResponse_State {
    StatusResponse_State_OFF = 0,
    StatusResponse_State_ON = 1
} StatusResponse_State;
#define _StatusResponse_State_MIN StatusResponse_State_OFF
#define _StatusResponse_State_MAX StatusResponse_State_ON
#define _StatusResponse_State_ARRAYSIZE ((StatusResponse_State)(StatusResponse_State_ON+1))

typedef enum _CommandRequest_Command {
    CommandRequest_Command_STATUS = 0,
    CommandRequest_Command_HELP = 1,
    CommandRequest_Command_ON = 2,
    CommandRequest_Command_OFF = 3,
    CommandRequest_Command_INVERT = 4,
    CommandRequest_Command_SEQUENCE = 5,
    CommandRequest_Command_FLASH = 6,
    CommandRequest_Command_DEMO = 7
} CommandRequest_Command;
#define _CommandRequest_Command_MIN CommandRequest_Command_STATUS
#define _CommandRequest_Command_MAX CommandRequest_Command_DEMO
#define _CommandRequest_Command_ARRAYSIZE ((CommandRequest_Command)(CommandRequest_Command_DEMO+1))

/* Struct definitions */
typedef struct _StatusResponse {
    pb_callback_t status;
/* @@protoc_insertion_point(struct:StatusResponse) */
} StatusResponse;

typedef struct _CommandRequest {
    CommandRequest_Command command;
    bool has_relay;
    Relay relay;
    bool has_iterations;
    int32_t iterations;
    bool has_onMillis;
    int32_t onMillis;
    bool has_offMillis;
    int32_t offMillis;
    bool has_pauseMillis;
    int32_t pauseMillis;
/* @@protoc_insertion_point(struct:CommandRequest) */
} CommandRequest;

typedef struct _StatusResponse_Status {
    Relay relay;
    StatusResponse_State state;
/* @@protoc_insertion_point(struct:StatusResponse_Status) */
} StatusResponse_Status;

/* Default values for struct fields */
extern const Relay CommandRequest_relay_default;
extern const int32_t CommandRequest_iterations_default;
extern const int32_t CommandRequest_onMillis_default;
extern const int32_t CommandRequest_offMillis_default;
extern const int32_t CommandRequest_pauseMillis_default;

/* Initializer values for message structs */
#define StatusResponse_init_default              {{{NULL}, NULL}}
#define StatusResponse_Status_init_default       {_Relay_MIN, _StatusResponse_State_MIN}
#define CommandRequest_init_default              {_CommandRequest_Command_MIN, false, Relay_ALL, false, 1, false, 500, false, 500, false, 0}
#define StatusResponse_init_zero                 {{{NULL}, NULL}}
#define StatusResponse_Status_init_zero          {_Relay_MIN, _StatusResponse_State_MIN}
#define CommandRequest_init_zero                 {_CommandRequest_Command_MIN, false, _Relay_MIN, false, 0, false, 0, false, 0, false, 0}

/* Field tags (for use in manual encoding/decoding) */
#define StatusResponse_status_tag                1
#define CommandRequest_command_tag               1
#define CommandRequest_relay_tag                 2
#define CommandRequest_iterations_tag            3
#define CommandRequest_onMillis_tag              4
#define CommandRequest_offMillis_tag             5
#define CommandRequest_pauseMillis_tag           6
#define StatusResponse_Status_relay_tag          1
#define StatusResponse_Status_state_tag          2

/* Struct field encoding specification for nanopb */
extern const pb_field_t StatusResponse_fields[2];
extern const pb_field_t StatusResponse_Status_fields[3];
extern const pb_field_t CommandRequest_fields[7];

/* Maximum encoded size of messages (where known) */
/* StatusResponse_size depends on runtime parameters */
#define StatusResponse_Status_size               4
#define CommandRequest_size                      48

/* Message IDs (where set with "msgid" option) */
#ifdef PB_MSGID

#define COMMANDS_MESSAGES \


#endif

#ifdef __cplusplus
} /* extern "C" */
#endif
/* @@protoc_insertion_point(eof) */

#endif
