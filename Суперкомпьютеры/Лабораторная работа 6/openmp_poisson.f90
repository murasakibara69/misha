module openmp_poisson

  use, intrinsic :: iso_fortran_env, only: wp => real64
  use, intrinsic :: omp_lib
  
  implicit none
  
contains
  
  subroutine jacobi_first_method(omega)
    real(wp), dimension(:, :), intent(inout) :: omega
    real(wp), dimension(:, :), allocatable :: omega_old
    real(wp), parameter :: epsilon = 1e-6_wp
    real(wp) :: h, error
    integer :: i, j, n, m
    
    n = size(omega, dim=1)
    m = size(omega, dim=2)
    
    h = 2.0_wp / (m - 1)
    error = 1e6_wp
    allocate(omega_old(n, m))
    do while (error.gt.epsilon)
      error = 0.0_wp
      !$omp parallel private(i, j)
        !$omp workshare
        omega_old(1:n, 1:m) = omega(1:n, 1:m)
        !$omp end workshare
        !$omp do reduction(max : error)
        do j = 2, m - 1
          do i = 2, n - 1
            omega(i, j) = 0.25 * (omega_old(i-1, j) + omega_old(i+1, j) + omega_old(i, j-1) + omega_old(i, j+1) + h * h)
            error = max(error, abs(omega(i, j) - omega_old(i, j)))
          end do
        end do
        !$omp end do
      !$omp end parallel
    end do
    deallocate(omega_old)
    
  end subroutine jacobi_first_method
  
  subroutine jacobi_second_method(omega, niterations)
    real(wp), dimension(:, :), intent(inout) :: omega
    real(wp), dimension(:, :), allocatable :: omega_old
    integer, intent(in) :: niterations
    real(wp), parameter :: epsilon = 1e-6_wp
    real(wp) :: h, error
    integer :: i, j, k, n, m
    
    n = size(omega, dim=1)
    m = size(omega, dim=2)
    
    h = 2.0_wp / (m - 1)
    error = 1e6_wp
    allocate(omega_old(n, m))
    do while (error.gt.epsilon)
      do k = 1, niterations
        !$omp parallel private(i, j)
          !$omp workshare
          omega_old(1:n, 1:m) = omega(1:n, 1:m)
          !$omp end workshare
          !$omp do collapse(2)
          do j = 2, m - 1
            do i = 2, n - 1
              omega(i, j) = 0.25 * (omega_old(i-1, j) + omega_old(i+1, j) + omega_old(i, j-1) + omega_old(i, j+1) + h * h)
            end do
          end do
          !$omp end do
        !$omp end parallel
      end do
      error = 0.0_wp
      !$omp parallel do collapse(2) reduction(max : error)
      do j = 2, m - 1
        do i = 2, n - 1
          error = max(error, abs(omega(i, j) - omega_old(i, j)))
        end do
      end do
      !$omp end parallel do
    end do
    deallocate(omega_old)
    
  end subroutine jacobi_second_method
  
  subroutine output(xi, eta, omega)
    real(wp), dimension(:), intent(in) :: xi, eta
    real(wp), dimension(:, :), intent(in) :: omega
    integer, parameter :: io = 101
    character(len=256) :: str
    integer :: ios, i, j, n, m
    
    n = size(xi, dim=1)
    m = size(eta, dim=1)
    
    open(unit=io, file='result.dat', iostat=ios, iomsg = str, status="replace", action="write")
    if (ios /= 0) stop trim(str)
    do i = 1, n
      do j = 1, m
        write(io, *) xi(i), eta(j), omega(i, j)
      end do
      write(io, *)
    end do
    close(io)
    
  end subroutine output
  
  subroutine init_value(omega)
    real(wp), dimension(:, :), intent(out) :: omega
    integer :: n, m
    
    n = size(omega, dim=1)
    m = size(omega, dim=2)
    
    omega(1, :) = 0.0_wp
    omega(n, :) = 0.0_wp
    omega(:, 1) = 0.0_wp
    omega(:, m) = 0.0_wp
    omega(2:n-1, 2:m-1) = 0.5_wp
    
  end subroutine init_value
  
end module openmp_poisson
