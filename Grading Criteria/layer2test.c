#include <stdio.h>      /* printf, fprintf, etc */
#include <unistd.h>     /* need this for read(), write() */
#include <stdlib.h>     /* needed for exit()  */
#include <string.h>     /* strlen, etc */

#define CHUNK_SIZE 16

/* function prototypes */
int layer2_write( char *chunk, int len );
int layer2_read( char *chunk, int max );
void debug_print( char *caller, char *buf, int len );


int main( int argc, char *argv[] )
{
    char chunk[CHUNK_SIZE];
    int len;

    if ( argc != 2 )
    {
        /* I'm a reader - read the structure */

        if ((len = layer2_read( chunk, CHUNK_SIZE )) == -1 )
        {
            fprintf( stderr, "Reading error\n" );
            exit( 1 );
        }

        /* print out the chunk */
        debug_print( "layer2_test", chunk, len );

    } 
    else 
    {
        /* I'm a writer (argv == 2) */
        if ( (len = strlen( argv[1] )) > CHUNK_SIZE )
        {
            fprintf( stderr, "Error - chunk is too long(%d)\n", len );
            return 0;
        }

        /*  the first command-line argument is the chunk */

        if ( layer2_write( argv[1], len ) == -1 )
        {
            /* something went wrong when sending */
            fprintf( stderr, "Error sending chunk\n" );
            exit( 1 );
        }

    }

    return 1;
}
