cmake_minimum_required(VERSION 2.6)

project(simplex_root)

set(PROJECT_ROOT ${CMAKE_CURRENT_SOURCE_DIR})
set(PROJECT_INCLUDE ${PROJECT_ROOT}/include)
set(PROJECT_LIB ${PROJECT_ROOT}/lib)
set(PROJECT_SRC ${PROJECT_ROOT}/src)
set(PROJECT_BIN ${PROJECT_ROOT}/bin)

MESSAGE( STATUS "PROJECT_ROOT:     " ${PROJECT_ROOT})
MESSAGE( STATUS "PROJECT_INCLUDE:  " ${PROJECT_INCLUDE})
MESSAGE( STATUS "PROJECT_LIB:      " ${PROJECT_LIB})
MESSAGE( STATUS "PROJECT_BIN:      " ${PROJECT_BIN})

# ------------- EXTERNAL LIBRARIES --------------

# We need thread support
find_package(Threads REQUIRED)

# Enable ExternalProject CMake module
include(ExternalProject)


# Download and install GoogleTest
ExternalProject_Add(
	gtest
	URL https://googletest.googlecode.com/files/gtest-1.7.0.zip
	PREFIX ${PROJECT_INCLUDE}/gtest
	# Disable install step
	INSTALL_COMMAND ""
)

# Create a libgtest target to be used as a dependency by test programs
add_library(libgtest IMPORTED STATIC GLOBAL)
add_dependencies(libgtest gtest)

# Set gtest properties
ExternalProject_Get_Property(gtest source_dir binary_dir)
set_target_properties(libgtest PROPERTIES
	IMPORTED_LOCATION "${binary_dir}/libgtest.a"
	IMPORTED_LINK_INTERFACE_LIBRARIES "${CMAKE_THREAD_LIBS_INIT}"
#	"INTERFACE_INCLUDE_DIRECTORIES" "${source_dir}/include"
)
# I couldn't make it work with INTERFACE_INCLUDE_DIRECTORIES
set(GTEST_LIB "${source_dir}/include")

# Download and install GoogleMock
ExternalProject_Add(
	gmock
	URL https://googlemock.googlecode.com/files/gmock-1.7.0.zip
	PREFIX ${PROJECT_INCLUDE}/gmock
	# Disable install step
	INSTALL_COMMAND ""
)

# Create a libgmock target to be used as a dependency by test programs
add_library(libgmock IMPORTED STATIC GLOBAL)
add_dependencies(libgmock gmock)

# Set gmock properties
ExternalProject_Get_Property(gmock source_dir binary_dir)
set_target_properties(libgmock PROPERTIES
	"IMPORTED_LOCATION" "${binary_dir}/libgmock.a"
	"IMPORTED_LINK_INTERFACE_LIBRARIES" "${CMAKE_THREAD_LIBS_INIT}"
#	"INTERFACE_INCLUDE_DIRECTORIES" "${source_dir}/include"
)
# I couldn't make it work with INTERFACE_INCLUDE_DIRECTORIES
set(GMOCK_LIB "${source_dir}/include")

# thanks to http://www.kaizou.org/2014/11/gtest-cmake/

set(TENSOR_LIB ${PROJECT_LIB}/tensor)
set(TENSOR_TEST ${PROJECT_LIB}/tensor/test)
set(VECTOR_LIB ${PROJECT_LIB}/vector)
set(VECTOR_TEST ${PROJECT_LIB}/vector/test)
set(MATRIX_LIB ${PROJECT_LIB}/matrix)
set(MATRIX_TEST ${PROJECT_LIB}/matrix/test)

message( STATUS "GTEST_LIB:                 " ${GTEST_LIB} )
message( STATUS "GMOCK_LIB:                 " ${GMOCK_LIB} )
message( STATUS "TENSOR_LIB                 " ${TENSOR_LIB} )
message( STATUS "VECTOR_LIB                 " ${VECTOR_LIB} )
message( STATUS "MATRIX_LIB                 " ${MATRIX_LIB} )

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${PROJECT_BIN})
add_subdirectory(${PROJECT_LIB})
add_subdirectory(${PROJECT_SRC})
add_subdirectory(${TENSOR_TEST})
add_subdirectory(${VECTOR_TEST})
add_subdirectory(${MATRIX_TEST})

enable_testing()
add_test(Tensors ./bin/_testtensor)
add_test(Vectors ./bin/_testvector)
add_test(Matrices ./bin/_testmatrix)
