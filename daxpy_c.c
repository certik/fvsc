
/*  Re-worked output from f2c of daxpy.f
*/

int daxpy_c( int n , double da , double *dx,  int incx , double *dy , int incy )
{

    /* Local variables */
    int i, ix, iy;


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

        for ( i = 0 ; i < n ; i++ )
            dy[i] += da * dx[i];
        
        }
        
    return 0;
} /* daxpy_ */

