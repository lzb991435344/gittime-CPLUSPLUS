cmake_minimum_required(VERSION 3.13)
project(boost_examples)

set(CMAKE_CXX_STANDARD 17)

set(Boost_USE_MULTITHREADED OFF)
find_package(Boost REQUIRED program_options)
include_directories(${Boost_INCLUDE_DIRS})

add_executable(boost_test01_typeindex       test01_typeindex.cpp)
add_executable(boost_test02_demangle        test02_demangle.cpp)
add_executable(boost_test03_lexical_cast    test03_lexical_cast.cpp)
add_executable(boost_test04_scope_exit      test04_scope_exit.cpp)
add_executable(boost_test05_program_options test05_program_options.cpp)
add_executable(boost_test06_hana            test06_hana.cpp)

target_link_libraries(boost_test05_program_options
                      PRIVATE Boost::program_options)
