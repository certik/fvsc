
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

    double *mat_a , *mat_b , *mat_c, irm = 1.0 / RAND_MAX;
    ticks start, finish;
    int i, j, k, n;
    
    /* Get n from the command line. */
    if ( argc < 2 ) {
        printf( "usage: %s <size of matrix>.\n" , argv[0] );
        return 0;
        }
    n = atoi( argv[1] );
    
    /* Allocate and fill the matrices with random numbers. */
    mat_a = (double *)malloc( sizeof(double) * n * n );
    mat_b = (double *)malloc( sizeof(double) * n * n );
    mat_c = (double *)malloc( sizeof(double) * n * n );
    for ( k = 0 ; k < n*n ; k++ ) {
        mat_a[k] = rand() * irm;
        mat_b[k] = rand() * irm;
        mat_c[k] = 0.0;
        }
        
    /* Tripple Do loop. */
    start = getticks();
    for ( i = 0 ; i < n ; i++ )
        for ( j = 0 ; j < n ; j++ )
            for ( k = 0 ; k < n ; k++ )
                mat_c[n*i+j] += mat_a[n*i+k] * mat_b[n*k+j];
    finish = getticks();
    printf( "triple do time %.15f\n" , (finish - start) / CPU_TPS );

    /* Free allocated memory. */
    free( mat_a ); free( mat_b ); free( mat_c );
    
    /* Goodbye. */
    return 0;

    }
