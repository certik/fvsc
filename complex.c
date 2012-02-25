
/* Some standard headers. */
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

/* The timer, define CPU_TPS as the nr. of ticks per second on this CPU. */
#include "cycle.h"
#ifndef CPU_TPS
#define CPU_TPS 2.67e9
#endif


/* Main routine. */
int main ( int argc , char *argv[] ) {

    __complex__ double a = 0.1i, b, c;
    
    /* Get b from the command line. */
    if ( argc < 3 ) {
        printf( "usage: %s <real part of b> <imag part of b>\n" , argv[0] );
        return 0;
        }
    __real__ b = atoi( argv[1] );
    __imag__ b = atoi( argv[2] );
    
    /* Multiply a and b. */
    c = a * b;
    
    /* Output. */
    printf( "a * b = %e + %ei.\n" , __real__ c , __imag__ c );

    /* Goodbye. */
    return 0;

    }
