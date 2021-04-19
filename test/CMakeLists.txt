include(FetchContent)
FetchContent_Declare(
        googletest
        GIT_REPOSITORY https://github.com/google/googletest.git
        GIT_TAG release-1.10.0
)
FetchContent_MakeAvailable(googletest)

add_executable(
        UNIT_TEST
        test.cpp
        test_pid.cpp)

target_link_libraries(UNIT_TEST PID gtest gtest_main)