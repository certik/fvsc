
CC=gcc-4.6
FC=gfortran-4.6

CFLAGS=-O3 -g -Wall -msse2 -march=native -ffast-math -fomit-frame-pointer -malign-double -fstrict-aliasing
LDFLAGS=-lm

FFLAGS=$(CFLAGS)

OBJS=daxpy_f.o daxpy_c.o daxpy_cvec.o test.o

default: test

%.o: Makefile

%.o: %.c Makefile
	$(CC) -c $(CFLAGS) $< -o $@
	$(CC) -c $(CFLAGS) $< -dA -S

%.o: %.f Makefile
	$(FC) -c $(FFLAGS) $< -o $@
	$(FC) -c $(FFLAGS) $< -dA -S

test: $(OBJS)
	gcc $(LDFLAGS) $^ -o test

icctest_f: test.f90 m_blas.f90 Makefile
	ifort -fast -parallel -par-threshold:50 m_blas.f90 test.f90 -o icctest_f

icctest_c: icctest.c Makefile
	icc -fast -parallel -par-threshold:50 icctest.c -o icctest_c

mm_test_f: mm_test.f90 Makefile
	ifort -fast -parallel -par-threshold:50 mm_test.f90 -o mm_test_f

mm_test_c: mm_test.c Makefile
	icc -fast -parallel -par-threshold:50 mm_test.c -o mm_test_c

all: test icctest_f icctest_c mm_test_f mm_test_c

clean:
	rm -f $(OBJS) test
