#include <stdio.h>      /* printf, fprintf, etc */
#include <unistd.h>     /* need this for read(), write() */
#include <stdlib.h>     /* needed for exit()  */


void debug_print( char *caller, char *buf, int len );


/* sample layer1_read just calls read on stdin */
char *keyword = "Rens";
int curr_pos = 0;
int keyword_len = 4;

int layer1_read( char * b )
{
#ifdef ERROR_TEST1
    /* see if the protocol stack propagates a layer 1 error */
    return -1;
#else
    if ( read( 0, b, 1 ) != 1 )
    {
        return -1;
    }
    else
    {
        #ifdef ERROR_TEST2 
        if ((curr_pos < keyword_len) && (*b == keyword[curr_pos])) {
            curr_pos++;
            if (curr_pos == keyword_len) {
                /* replace "Rens" with "Renn" */
                *b = 'n';
            }
        }
        #endif

        #ifndef NO_DEBUG
        debug_print( "layer1_read", b, 1 );
        #endif

        return 1;
    }
#endif /* ERROR_TEST1 */

}

/* sample layer1_write just calls write to stdout */
int layer1_write( char b )
{
    if ( write( 1, &b, 1 ) != 1 )
    {
        return -1;
    }
    else
    {
        return 1;
    }
}
