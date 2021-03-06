#ifndef DISPATCHER_CONTROL_PROTOCOL
#define DISPATCHER_CONTROL_PROTOCOL

/* 
 * TODO: Authentication commands!
 * TODO: Typedef maybe?
 */

/* Basement constantd and structures for all plane protocols */
#include "protoskel.h"

/* --------------- (0) Extern functions ---------------- */

struct msg_raw* cmd_handon();
struct msg_raw* cmd_handoff();
struct msg_heartbeat* cmd_heartbeat(struct state st);
struct msg_reqconfirm* cmd_reqconfirm(uint16_t cmdnum);
struct msg_confirm* cmd_confirm(uint16_t cmdnum, uint8_t status);
struct msg_report* cmd_report(uint16_t cmdnum, uint8_t report);
struct msg_zerobaroalt* cmd_zerobaroalt(uint16_t zerobaroalt);
struct msg_updcpt* cmd_updcpd(uint16_t routenum, struct checkpoint pt);
struct msg_raw* cmd_cleanroute();
struct msg_route* cmd_route(uint16_t count, struct checkpoint *queue);
struct msg_raw* cmd_emergency();

/* --------------- (1) Messages to board --------------- */

struct msg_route
{
	struct message msg;
	uint16_t count; // checkpoints quantity in route
	struct checkpoint queue[0]; // checkpoint pointer 
};

struct msg_updcpt // = update checkpoint
{
	struct message msg;
	uint16_t routenum; // ordinal number in route
	struct checkpoint pt;
};

struct msg_raw // raw command can be used for all purposes: emergency, clean route, hand control, power control.
{
	struct message msg;
};

// correction of relative barometric altitude
struct msg_zerobaroalt
{
	struct message msg;
	uint16_t zerobaroalt; 
};

/* --------------- (2) Messages from board --------------- */

struct msg_heartbeat
{
	struct message msg;
	struct state st;
};

/* --------------- (3) Control messages --------------- */

// Request of command confirmation 
struct msg_reqconfirm 
{
	struct message msg;
	uint16_t cmdnum; 
};

// Command confirmation
struct msg_confirm
{
	struct message msg;
	uint16_t cmdnum; // message number of command to confirm 
	uint8_t status; 
};

// Command report
struct msg_report
{
	struct message msg;
	uint16_t cmdnum;
	uint8_t report;
};

#endif


