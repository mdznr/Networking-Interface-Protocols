#include <stdio.h>

/* debug print function */
void debug_print( char *caller, char *buf, int len )
{
    int i;
    
    printf( "%s: ", caller );
    for (i = 0; i < len; i++) {
        if ((0x20 <= buf[i]) && (buf[i] <= 0x7E))
            printf( "%c", buf[i] );
        else
            printf( "[0x%02x]", buf[i] & 0xff);
    }
    printf( " (%d bytes)\n", len );
}
