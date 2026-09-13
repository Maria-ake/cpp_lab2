cmake_minimum_required(VERSION 3.14)
project(IpFilterLab VERSION 1.0.0)

set(CMAKE_CXX_STANDARD 17)

include(FetchContent)
FetchContent_Declare(
  googletest
  GIT_REPOSITORY https://github.com/google/googletest.git
  GIT_TAG        release-1.12.1
)
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(googletest)


add_library(ip_filter_lib src/ip_filter.cpp)
target_include_directories(ip_filter_lib PUBLIC include)


add_executable(ip_filter src/main.cpp)
target_link_libraries(ip_filter PRIVATE ip_filter_lib)


enable_testing()
add_executable(ip_filter_tests tests/test_ip_filter.cpp)
target_link_libraries(ip_filter_tests PRIVATE ip_filter_lib gtest_main)
include(GoogleTest)
gtest_discover_tests(ip_filter_tests)