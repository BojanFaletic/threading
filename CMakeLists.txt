cmake_minimum_required(VERSION 3.0.0)
project(threading VERSION 0.1.0 LANGUAGES C CXX)

###################### Build ######################
# set c++ standard
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

###################### Build ######################

###################### External Library ######################
# include GTest with vcpkg
find_package(GTest CONFIG REQUIRED)
###################### External Library ######################

# include all .tpp files in src
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/src)

# include_directories
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/inc)

###################### Program ######################
# build all source files in src
aux_source_directory(${CMAKE_CURRENT_SOURCE_DIR}/src SRC_LIST)

# program
add_executable(${PROJECT_NAME} ${SRC_LIST} ${CMAKE_CURRENT_SOURCE_DIR}/main.cpp)
###################### Program ######################


###################### Tests ######################
# test
add_executable(${PROJECT_NAME}_test ${SRC_LIST} ${CMAKE_CURRENT_SOURCE_DIR}/test/main.cpp)

# link GTest to ${PROJECT_NAME}_test
target_link_libraries(${PROJECT_NAME}_test PRIVATE GTest::gtest GTest::gtest_main GTest::gmock GTest::gmock_main)

# use Ctest to run ${PROJECT_NAME}_test
include(GoogleTest)
gtest_discover_tests(${PROJECT_NAME}_test)

# use CTest to run ${PROJECT_NAME}_test
enable_testing()
add_test(NAME ${PROJECT_NAME}_test COMMAND ${PROJECT_NAME}_test)
###################### Tests ######################
