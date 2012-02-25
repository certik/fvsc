module blas

   interface axpy
     module procedure saxpy,daxpy
   end interface

 contains

   subroutine daxpy(x,y,a)
     implicit none
     real(8) :: x(:),y(:),a
     y=a*x+y
   end subroutine daxpy

   subroutine saxpy(x,y,a)
     implicit none
     real(4) :: x(:),y(:),a
     y=a*x+y
   end subroutine saxpy

end module blas

