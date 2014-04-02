#include <stdio.h>      /* printf, fprintf, etc */
#include <unistd.h>     /* need this for read(), write() */
#include <stdlib.h>     /* needed for exit()  */
#include <string.h>     /* strlen, etc */

#define MAX_MESSAGE_SIZE 1024

/* function prototypes */
int layer3_write( char *msg, int len );
int layer3_read( char *msg, int max );
void debug_print( char *caller, char *buf, int len );


int main( int argc, char *argv[] )
{
    char msg[MAX_MESSAGE_SIZE];
    int len;

    if ( argc != 2 )
    {
        /* I'm a reader - read the structure */

        if ((len = layer3_read( msg, MAX_MESSAGE_SIZE )) == -1 )
        {
            fprintf( stderr, "Reading error\n" );
            exit( 1 );
        }

        /* print out the chunk */
        debug_print( "layer3_test", msg, len );

    } 
    else 
    {
        /* I'm a writer (argv == 2) */
        if ( (len = strlen( argv[1] )) > MAX_MESSAGE_SIZE )
        {
            fprintf( stderr, "Error - message is too long(%d)\n", len );
            return 0;
        }

        /*  the first command-line argument is the chunk */

        if ( layer3_write( argv[1], len ) == -1 )
        {
            /* something went wrong when sending */
            fprintf( stderr, "Error sending message\n" );
            exit( 1 );
        }

    }

    return 1;
}
