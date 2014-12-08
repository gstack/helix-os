#ifndef _helix_debugger_module_h
#define _helix_debugger_module_h
#include <base/stdint.h>
#include <base/lib/stdbool.h>

typedef enum {
	DBG_FLAG_NONE,
	DBG_FLAG_GET,
	DBG_FLAG_SET,
	DBG_FLAG_REMOVE,
} dbg_flag_t;

typedef enum {
	DBG_TYPE_NONE,
	DBG_TYPE_REGISTERS,
	DBG_TYPE_BREAKPOINT,
	DBG_TYPE_MEMORY,
	DBG_TYPE_SYMBOL,
	DBG_FLAG_ERROR,
} dbg_type_t;

typedef struct dbg_packet {
	uint8_t  header[4]; // = { 0x8f, 'D', 'B', 'G' };
	uint8_t  type;
	uint16_t flags;
	uint16_t length;
	uint16_t checksum;

	// Data of `length` immediately follows the packet
} dbg_packet_t;

typedef struct dbg_symbol_packet {
	char module[32];
	char symbol[32];

	void *address;
} dbg_symbol_packet_t;

// packet functions
bool is_debug_packet( dbg_packet_t *pack );
bool checksum_valid( uint8_t *data, uint16_t length, uint16_t checksum );

#endif
