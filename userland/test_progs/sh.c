#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <dalibc/syscalls.h>

int running = 1;

char *getline( char *buf, unsigned len ){
	unsigned i;
	char c;

	c = getchar( );
	for ( i = 0; i < len && c != '\n'; ){

		if ( c == '\b' && i > 0 ){
			putchar( '\b' );
			buf[i] = 0;
			i--;

		} else if ( c != '\b' ){
			buf[i] = c;
			putchar( c );
			i++;
		}

		c = getchar( );
	}

	buf[i] = 0;

	return buf;
}

char **split_str( char *s, char split ){
	unsigned i, nchars, j;
	char **ret = NULL;

	for ( nchars = i = 0; s[i]; i++ ){
		if ( s[i] == split )
			nchars++;
	}

	if ( nchars ){
		ret = malloc( sizeof( char *[nchars + 2] ));

		for ( j = 0, i = 0; s[i]; i++ ){
			if ( i == 0 ){
				ret[j] = s;
				j++;

			} else if ( s[i] == split ){
				s[i] = 0;
				ret[j] = s + i + 1;
				j++;
			}
		}

		ret[j] = NULL;

	} else {
		ret = malloc( sizeof( char *[2] ));
		ret[0] = s;
		ret[1] = NULL;
	}

	return ret;
}

int exec_cmd( char *args[], char *env[] ){
	int pid;
	int ret = 0;

	if ( args ){
		if ( strlen( args[0] ) > 0 ){
			if ( strcmp( args[0], "cd" ) == 0 ){
				if ( args[1] ){
					printf( "Changing directory to \"%s\"\n", args[1] );
					if ( syscall_chdir( args[1] ) >= 0 ){
						puts( "Changed directory." );

					} else {
						printf( "Could not change directory to \"%s\"\n", args[1] );
					}

				} else {
					printf( "Changing directory to root\n" );
					syscall_chdir( "/" );
				}

			} else if ( strcmp( args[0], "exit" ) == 0 ){
				running = 0;

			} else if ( strcmp( args[0], "help" ) == 0 ){
				puts( "Helix shell v0.1" );
				puts( "Help message coming soon." );

			} else {
				pid = _spawn( args[0], args, NULL );

				if ( pid > 0 ){
					syscall_waitpid( pid, &ret, 0 );

				} else {
					puts( "Command not found." );
				}
			}
		}
	}

	return ret;
}

int main( int argc, char *argv[], char *envp[] ){
	char *buf = malloc( 128 );
	int ret;

	while ( running ){
		printf( "$ " );
		getline( buf, 128 );
		putchar( '\n' );
		ret = exec_cmd( split_str( buf, ' ' ), NULL );
	}

	return ret;
}
