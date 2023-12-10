cmake_minimum_required (VERSION 3.11)

include(FetchContent)
FetchContent_Declare(
        googletest
        URL https://github.com/google/googletest/archive/609281088cfefc76f9d0ce82e1ff6c30cc3591e5.zip
)
include_directories(${gtest_SOURCE_DIR}/include ${gtest_SOURCE_DIR})
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(googletest)

add_executable (Tests test_search.cpp test_search.h)

if (CMAKE_VERSION VERSION_GREATER 3.12)
    set_property(TARGET Tests PROPERTY CXX_STANDARD 20)
endif()

target_link_libraries(Tests Project_library gtest_main)
include(GoogleTest)
gtest_discover_tests(Tests)