program main
  
  use, intrinsic :: iso_fortran_env, only: wp => real64, dp => real64
  use, intrinsic :: omp_lib, only: omp_get_wtime
  use openmp_poisson
  
  implicit none
  
  integer, parameter :: m = 101
  real(wp), parameter :: chi = 3.0_wp
  real(wp), dimension(:, :), allocatable :: omega
  real(wp), dimension(:), allocatable :: xi, eta
  real(dp) :: start_time, end_time
  integer :: i, n

  n = chi * (m - 1) + 1
  
  allocate(omega(n, m))
  
  call init_value(omega)
  
  start_time = omp_get_wtime()
  ! call jacobi_first_method(omega)
  call jacobi_second_method(omega, 500)
  end_time = omp_get_wtime()
  print*, 'time = ', end_time - start_time
  
  allocate(xi(n), eta(m))
  
  xi = [(-chi + 2.0_wp * chi / (n - 1) * i, i = 1, n)]
  
  eta = [(-1.0_wp + 2.0_wp / (m - 1) * i, i = 1, m)]
  
  call output(xi, eta, omega)
  
  deallocate(xi, eta, omega)
  
end program main
