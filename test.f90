program main

   use blas
   implicit none

   real(4), allocatable :: x(:),y(:)
   real(4) :: a
   integer :: n, k

   n=10000
   allocate(x(n),y(n))
   x=1.0
   y=2.0
   a=5.0
   
   do k=1,1000000
     call axpy(x,y,a)
   enddo
   
   deallocate(x,y)

end program main
