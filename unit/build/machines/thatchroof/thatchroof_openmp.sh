#!/bin/bash

source /usr/share/modules/init/bash
module purge

../../cmakeclean.sh

unset GATOR_DISABLE
export OMP_NUM_THREADS=24

export CC=gcc-8
export CXX=g++-8
export FC=gfortran-8
unset CXXFLAGS
unset FFLAGS

cmake -DYAKL_ARCH="OPENMP"               \
      -DYAKL_OPENMP_FLAGS="-O3 -fopenmp -I`nc-config --includedir`" \
      -DYAKL_F90_FLAGS="-O3"             \
      -DNETCDF_LINK_FLAGS="`nc-config --libs`"        \
      ../../..

