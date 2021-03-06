#ifndef _kernel_panic_c
#define _kernel_panic_c
#include <base/kstd.h>
#include <arch/interrupts.h>

// TODO: Make the panic function output better debug info
void panic( char *fmt, ... ){
	va_list args;
	va_start( args, fmt );

	kprintf( "\n----: Kernel love letters\n" );
	kprintf( "Dear Kernel Debugger,\n\n"
		 "\tIt appears that due to some difficulties, I have had to halt\n"
		 "the normal operating procedure. I tried to resolve the situation,\n"
		 "but it seems the errors encountered are unrecoverable. I have attached\n"
		 "a collection of debugging information which may be useful to you.\n\n"
		 "Sincerely,\n"
		 "\tThe Helix Kernel <3\n" );
	kprintf( "----\n\n" );

	kvprintf( fmt, args );

	debug_registers( );
	disable_interrupts( );

	while (1);

	/*
	asm volatile( "int $0x30" ); // Dump registers

	asm volatile( "cli" );
	asm volatile( "hlt" );
	*/
}

#endif
