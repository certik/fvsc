
/* Some standard headers. */
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

/* The timer, define CPU_TPS as the nr. of ticks per second on this CPU. */
#include "cycle.h"
#ifndef CPU_TPS
#define CPU_TPS 2.67e9
#endif

/* Declarations for the external functions. */
int daxpy_f_ ( int *n , double *da , double *dx , int *incx , double *dy , int *incy );
int daxpy_c ( int n , double da , double *dx ,  int incx , double *dy , int incy );
int daxpy_cvec ( int n , double da , double *dx ,  int incx , double *dy , int incy );


/* Main driver routine. */
int main ( int argc , char *argv[] ) {

    ticks tic, toc;
    double itpms = 1000.0 / CPU_TPS;
    int N, runs, k, one = 1;
    double a = 0.1, *x, *y;
    
    /* Get the number of runs and the problem size. */
    if ( argc < 3 ) {
        printf( "usage: %s <nr runs> <vector size>.\n" , argv[0] );
        return 0;
        }
    runs = atoi( argv[1] );
    N = atoi( argv[2] );
    printf( "timing %i runs with a vector of length %i.\n" , runs , N );
    
    /* Allocate and fill the data with junk. Note that we use posix_memalign
       to make sure that memory is properly aligned for vectors of size 4 (optimistic).*/
    /* x = malloc( sizeof(double) * N );
    y = malloc( sizeof(double) * N ); */
    if ( posix_memalign( (void **)&x , 4*sizeof(double) , sizeof(double) * N ) != 0 ||
         posix_memalign( (void **)&y , 4*sizeof(double) , sizeof(double) * N ) != 0 ) {
        printf( "something went wrong allocating memory. N=%i too large?\n" , N );
        return 0;
        }
    for ( k = 0 ; k < N ; k++ ) {
        x[k] = ((double)rand()) / RAND_MAX;
        y[k] = ((double)rand()) / RAND_MAX;
        }
    
    /* Run the fortran code. */
    tic = getticks();
    for ( k = 0 ; k < runs ; k++ )
        daxpy_f_( &N , &a , x , &one , y , &one );
    toc = getticks();
    printf( "daxpy_f took %.1f ms.\n" , (toc - tic) * itpms );

    /* Re-set the values. */
    for ( k = 0 ; k < N ; k++ ) {
        x[k] = ((double)rand()) / RAND_MAX;
        y[k] = ((double)rand()) / RAND_MAX;
        }
    
    /* Run the polished-up f2c code. */
    tic = getticks();
    for ( k = 0 ; k < runs ; k++ )
        daxpy_c( N , a , x , 1 , y , 1 );
    toc = getticks();
    printf( "daxpy_c took %.1f ms.\n" , (toc - tic) * itpms );

    /* Re-set the values. */
    for ( k = 0 ; k < N ; k++ ) {
        x[k] = ((double)rand()) / RAND_MAX;
        y[k] = ((double)rand()) / RAND_MAX;
        }
    
    /* Run the explicitly vectorized code. */
    tic = getticks();
    for ( k = 0 ; k < runs ; k++ )
        daxpy_cvec( N , a , x , 1 , y , 1 );
    toc = getticks();
    printf( "daxpy_cvec took %.1f ms.\n" , (toc - tic) * itpms );

    /* Exit gracefully. */
    return 0;

    }
