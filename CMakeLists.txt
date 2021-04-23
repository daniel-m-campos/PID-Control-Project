cmake_minimum_required(VERSION 3.5)
project(PIDControl)

set(CMAKE_CXX_STANDARD 17)
set(CXX_FLAGS "-Wall")
set(CMAKE_CXX_FLAGS "${CXX_FLAGS}")

if (${CMAKE_SYSTEM_NAME} MATCHES "Darwin")
    include_directories(/usr/local/include)
    include_directories(/usr/local/opt/openssl/include)
    link_directories(/usr/local/lib)
    link_directories(/usr/local/opt/openssl/lib)
endif (${CMAKE_SYSTEM_NAME} MATCHES "Darwin")

include_directories(src)
add_subdirectory(src)

set(BUILD_TESTS NO CACHE BOOL "Build test target")
if (BUILD_TESTS)
    cmake_minimum_required(VERSION 3.14)
    add_subdirectory(test)
endif ()

add_executable(MAIN src/main.cpp)
target_link_libraries(MAIN PID)

add_executable(TRAIN src/train.cpp)
target_link_libraries(TRAIN PID)