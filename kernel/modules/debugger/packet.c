#include <debugger/debugger.h>
#include <base/serial.h>
#include <base/stdint.h>
#include <base/string.h>

bool is_debug_packet( dbg_packet_t *pack ){
	uint8_t dbg_head[] = { 0x8f, 'D', 'B', 'G' };

	return memcmp( pack->header, dbg_head, 4 ) == 0;
}

bool checksum_valid( uint8_t *data, uint16_t length, uint16_t checksum ){
	uint16_t check;
	uint16_t i;

	for ( i = 0; i < length; i++ )
		check += data[i];

	return check == checksum;
}
