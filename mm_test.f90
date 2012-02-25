program mm_test

  ! use mkl95_blas ! F95 wrappers for Intel's MKL
  implicit none

  real(8), allocatable :: mat_a(:,:), mat_b(:,:), mat_c(:,:)
  real(8)  :: start, finish
  integer  :: i, j, k, n, runs, r, status
  character*10 :: argv

  ! --- Get n from the command line
  call GET_COMMAND_ARGUMENT( 1 , argv , status=status )
  if ( status /= 0 ) then
    print*, 'usage: mm_test <nr of iterations> <size of matrix>.'
    call exit(0)
  endif
  read( argv , '(i10)' ) runs
  call GET_COMMAND_ARGUMENT( 2 , argv , status=status )
  if ( status /= 0 ) then
    print*, 'usage: mm_test <nr of iterations> <size of matrix>.'
    call exit(0)
  endif
  read( argv , '(i10)' ) n

  allocate (mat_a(n,n),mat_b(n,n))
  call random_number (mat_a)
  call random_number (mat_b)

  ! --- Fortrans 'matmul' intrinsic
  allocate (mat_c(n,n))
  call cpu_time(start)
  do r=1,runs
      mat_c=0.0d0
      mat_c=matmul(mat_a,mat_b)
  enddo
  call cpu_time(finish)
  print*, 'matmul    time',finish-start

  ! --- Triple Do loop
  call cpu_time(start)
  do r=1,runs
      mat_c=0.0d0
      do i=1,n
         do j=1,n
            do k=1,n
               mat_c(i,j)=mat_c(i,j)+mat_a(i,k)*mat_b(k,j)
            end do
         end do
      end do
  enddo
  call cpu_time(finish)
  print*, 'triple do time',finish-start

  deallocate (mat_a,mat_b,mat_c)

end program mm_test
