
program hello
    use fast_sorting
    use iso_fortran_env
    use sorting_int32
    implicit none

    integer, parameter :: N = 16
    integer, parameter :: NTEST = 1000000
    integer, parameter :: MAXI  = 100000
    integer :: isort(N),i,siz,ntests(N)
    real(real32) :: x(N),s(NTEST),t0,t1,times(N),time,sums(N)

    call random_number(x)
    call random_number(s)
    isort = nint(MAXI*x)
    ntests = 0

    time = 0.0
    sums = 0.0

    do siz=1,N
        time = 0.0
        call random_number(x)
    do i=1,NTEST

        isort(1:siz) = nint(MAXI*x(1:siz))
        call cpu_time(t0)
        call sort_IKIND(siz,isort(1:siz))
        call cpu_time(t1)
        ntests(siz) = ntests(siz)+1
        time = time+t1-t0
        sums(siz) = sums(siz) + sum(isort(1:siz))


    end do
        times(siz) = time

    end do

    print *, 'Fast sort: per 1M elems=',times
    print *, 'sums=',sum(sums)

    isort = nint(MAXI*x)
    ntests = 0
    times = 0.0
    sums = 0.0

    time = 0.0
    do siz=1,N
        time = 0.0
        call random_number(x)
    do i=1,NTEST

        isort(1:siz) = nint(MAXI*x(1:siz))
        call cpu_time(t0)
        call sort(isort(1:siz))
        call cpu_time(t1)
        ntests(siz) = ntests(siz)+1
        time = time+t1-t0
        sums(siz) = sums(siz) + sum(isort(1:siz))

    end do
        times(siz) = time
    end do
    print *, 'Quick sort: per 1M elems=',times
    print *, 'sums=',sum(sums)

end program

