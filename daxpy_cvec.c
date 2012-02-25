
/*  Re-worked output from f2c of daxpy.f
*/

int daxpy_cvec ( int n , double da , double *dx,  int incx , double *dy , int incy )
{

    /* Typedef for general vectors. */
    #define vector(elcount, type)  __attribute__((vector_size((elcount)*sizeof(type)))) type

    /* Local variables */
    int i, ix, iy;
    vector(2,double) va = { da , da }, *vx, *vy;


/*     constant times a vector plus a vector.   
       uses unrolled loops for increments equal to one.   
       jack dongarra, linpack, 3/11/78.   
       modified 12/3/93, array(1) declarations changed to array(*)   */


    
    if (n <= 0 || da == 0.)
	    return 0;
    if (incx != 1 || incy != 1) {

    /*        code for unequal increments or equal increments   
                not equal to 1 */

        ix = 0; iy = 0;
        if (incx < 0)
	        ix = (-(n) + 1) * incx;
        if (incy < 0)
	        iy = (-(n) + 1) * incy;
        for (i = 0; i < n; i++) {
	        dy[iy] += da * dx[ix];
	        ix += incx;
	        iy += incy;
            }
        
        }
        
    else {

/*        code for both increments equal to 1   */

        vx = (void *)dx; vy = (void *)dy;
        for ( i = 0 ; i < (n/2 & ~1) ; i += 2 ) {
	        vy[i] += va * vx[i];
	        vy[i+1] += va * vx[i+1];
            }

        /* Leftovers? */
        for ( i = n & ~3 ; i < n ; i++ )
            dy[i] += da * dx[i];
            
        }
        
    return 0;
} /* daxpy_ */

