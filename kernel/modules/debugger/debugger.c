#include <base/logger.h>
#include <base/serial.h>
#include <base/debug.h>
#include <debugger/debugger.h>
#include <base/tasking/task.h>

char *depends[] = { "base", 0 };
char *provides = "debugger";
static pid_t thread_pid;

static void handle_packet( dbg_packet_t *pkt, void *buf );

void debug_thread( ){
	dbg_packet_t packet;

	while ( 1 ){
		kprintf( "[%s] Listening for packet (size %d)\n", provides, sizeof(packet));
		while ( !serial_recieved( ))
			usleep( 1000 );

		read_serial( &packet, sizeof( packet ));

		if ( is_debug_packet( &packet )){
			kprintf( "[%s] Got a debug packet, type = %d, length = %d "
					 "checksum = %d\n",
					provides, packet.type, packet.length, packet.checksum );

			uint8_t *buf = knew( uint8_t[packet.length] );
			read_serial( buf, packet.length );

			kprintf( "[%s] Got data \"%s\"\n", provides, buf );
			kprintf( "[%s] Checksum valid: %d\n", provides,
					checksum_valid( buf, packet.length, packet.checksum ));

			if ( checksum_valid( buf, packet.length, packet.checksum )){
				handle_packet( &packet, buf );
			}

			kfree( buf );

		} else {
			kprintf( "[%s] Got some weird input, skipping\n", provides );
		}
	}
}

static void handle_symbol_pack( dbg_packet_t *pkt, dbg_symbol_packet_t *sympack ){

}

static void handle_packet( dbg_packet_t *pkt, void *buf ){
	kprintf( "[%s;:%s] Got here\n", provides, __func__ );

	switch( pkt->type ){
		case DBG_TYPE_SYMBOL:
			handle_symbol_pack( pkt, buf );
			break;
	}
}

int init( ){
	debugp( DEBUG_MODULE, MASK_VERBOSE, "[%s] initialising debugger\n", provides );
	thread_pid = create_thread( debug_thread );
	debugp( DEBUG_MODULE, MASK_CHECKPOINT, "[%s} debug thread created\n", provides );

	return 0;
}

void remove( ){
	debugp( DEBUG_MODULE, MASK_VERBOSE, "[%s] Mkkay, I'm out.\n", provides ); 
}
