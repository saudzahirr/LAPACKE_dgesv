cmake_minimum_required(VERSION 3.10)
project(LapackExample C Fortran)

# Enable FetchContent module
include(FetchContent)

# Fetch LAPACK source and enable LAPACKE
FetchContent_Declare(
  lapack
  GIT_REPOSITORY https://github.com/Reference-LAPACK/lapack.git
  GIT_TAG        v3.12.0
)

set(LAPACKE ON)  # Ensure LAPACKE is enabled
set(BUILD_LAPACKE ON CACHE BOOL "" FORCE)  # Force building of LAPACKE

# Make LAPACK available
FetchContent_MakeAvailable(lapack)

# Configure lapacke_mangling.h
configure_file(
  ${lapack_SOURCE_DIR}/LAPACKE/include/lapacke_mangling_with_flags.h.in
  ${lapack_SOURCE_DIR}/LAPACKE/include/lapacke_mangling.h
)

# Create an executable
add_executable(solve solve.c)

# Include LAPACK directories
target_include_directories(solve PRIVATE 
  ${lapack_BINARY_DIR}/LAPACKE/include 
  ${lapack_SOURCE_DIR}/LAPACKE/include
)

# Link LAPACK and BLAS libraries
target_link_libraries(solve PRIVATE
  lapacke
  lapack
  blas
  gfortran
  m
)

# Specify the location of the LAPACK libraries if they are not in the default path
link_directories(${lapack_BINARY_DIR}/lib)
