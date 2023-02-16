set(target ${DIRECT_LIBRARY})

file(GLOB hdrs "${DIRECT_INCLUDE}/*.h*")
file(GLOB srcs "${DIRECT_SOURCE}/*.c*")

add_library(${target} STATIC ${srcs} ${hdrs})
target_link_libraries(${target} ${LIBRARY_DEPS} m)

# REPORT
message( STATUS "")
message( STATUS "General configuration for lib_${target}")
message( STATUS "OK")
message( STATUS "")
