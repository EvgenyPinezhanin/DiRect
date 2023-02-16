cmake_minimum_required(VERSION 3.0)

set(PROJECT_NAME direct)
project(${PROJECT_NAME})

if(CMAKE_COMPILER_IS_GNUCXX)
  add_definitions(-Wno-deprecated)
  set(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE} -O3")
endif()

if(MSVC)
  add_definitions("-D_VARIADIC_MAX=10")
endif()

set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY_RELEASE ${CMAKE_BINARY_DIR}/bin/release)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY_DEBUG ${CMAKE_BINARY_DIR}/bin/debug)

set(DIRECT_LIBRARY ${PROJECT_NAME})
set(DIRECT_INCLUDE ${CMAKE_CURRENT_SOURCE_DIR}/include)
set(DIRECT_SOURCE ${CMAKE_CURRENT_SOURCE_DIR}/src)

set(DIRECT_LIB_NAME ${PROJECT_NAME} CACHE STRING "" FORCE)
set(DIRECT_INC_NAME ${DIRECT_INCLUDE} CACHE PATH "" FORCE)

include_directories(${DIRECT_INCLUDE})

# BUILD
add_subdirectory(src)
add_subdirectory(samples)

# REPORT
message(STATUS "")
message(STATUS "General configuration for ${PROJECT_NAME}")
message(STATUS "======================================")
message(STATUS "")
message(STATUS "   Configuration: ${CMAKE_BUILD_TYPE}")
message(STATUS "")
