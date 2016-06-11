cmake_minimum_required(VERSION 2.6)

project(dbhp)

SET(EXTRA_CXX_COMPILE_FLAGS "-std=c++14 -I./src -I./test -I/opt/local/include -O2 -Werror -Wall")

SET(CMAKE_CXX_FLAGS  "${CMAKE_CXX_FLAGS} ${EXTRA_CXX_COMPILE_FLAGS}")

include_directories(include/)

SET(TEST_FILES test/polynomial_tests.cpp)
SET(HEADERS include/dbhp/polynomial.h
	    include/dbhp/division.h)

SET(CPPS )

SET(SRCS ${CPPS} ${HEADERS})

add_executable(all-tests ${SRCS} ${TEST_FILES})

