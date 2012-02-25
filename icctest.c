
/* Some standard headers. */
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

/* Quick and dirty daxpy. */
void daxpy ( int n , double a , double *x , double *y ) {
    int k;
    for ( k = 0 ; k < n ; k++ )
        y[k] += a * x[k];
    }

/* Quick and dirty saxpy. */
void saxpy ( int n , float a , float *x , float *y ) {
    int k;
    for ( k = 0 ; k < n ; k++ )
        y[k] += a * x[k];
    }

/* Main routine. */
int main ( int argc , char *argv[] ) {
    
    /* double *xd, *yd; */
    float a, *xf, *yf;
    int k, n=10000;
    
    /* allocate(x(n),y(n)) */
    xf = (float *)malloc( sizeof(float) * n );
    yf = (float *)malloc( sizeof(float) * n );
    /* xd = (double *)malloc( sizeof(double) * n );
    yd = (double *)malloc( sizeof(double) * n ); */
    
    /* x=1.0; y=2.0; a=5.0 */
    a = 5.0;
    for ( k = 0 ; k < n ; k++ ) {
        xf[k] = 1.0f;
        yf[k] = 1.0f;
        }
    /* for ( k = 0 ; k < n ; k++ ) {
        xd[k] = 1.0;
        yd[k] = 1.0;
        } */
    
    /* call axpy(x,y,a) */
    for ( k = 0 ; k < 1000000 ; k++ )
        saxpy( n , a , xf , yf );
        
    /* daxpy( n , a , xd , yd ); */
    printf( "yf[0] = %e.\n" , yf[0] );
    
    /* deallocate(x,y) */
    free(xf); free(yf);
    /* free(xd); free(yd); */
    
    return 0;
    
    }
