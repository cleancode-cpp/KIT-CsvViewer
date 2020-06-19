cmake_minimum_required(VERSION 3.15.2)
project(CsvViewer)
enable_testing()

set (CMAKE_CXX_STANDARD 11)
set (gtest_force_shared_crt ON CACHE BOOL "MSVC defaults to shared CRT" FORCE)

add_subdirectory(third_party/googletest/googletest)
target_compile_definitions(gtest
    PUBLIC
        GTEST_LANG_CXX11
        GTEST_HAS_TR1_TUPLE=0
)

# domain library
add_library(csv_lib)
target_sources(csv_lib
    PRIVATE
        Hints.cc
    PUBLIC
        Hints.h
        Parser.h
)
set_target_properties(csv_lib PROPERTIES
    COMPILE_FLAGS "${cxx_strict}"
)

# text tests
add_executable(csv_viewer)
target_sources(csv_viewer
    PRIVATE
        main.cc
)
set_target_properties(csv_viewer PROPERTIES
    COMPILE_FLAGS "${cxx_strict}"
)
target_link_libraries(csv_viewer
    PRIVATE
        csv_lib
)

# unit tests
add_executable(csv_tests)
target_sources(csv_tests
    PRIVATE
        HintsUnitTests.cc
        ParserUnitTests.cc
)
set_target_properties(csv_tests PROPERTIES
    COMPILE_FLAGS "${cxx_strict}"
)
target_link_libraries(csv_tests
    PRIVATE
        csv_lib
        gtest
        gtest_main
)
add_test(csv_tests csv_tests)
