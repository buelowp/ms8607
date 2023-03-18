cmake_minimum_required(VERSION 3.0)
project(ms8607)

option(BUILD_TESTS "Build Google test capability (default OFF)" OFF)
option(PROJECT_BUILD_SHARED "Build as a shared object (default ON)" ON)

file(GLOB SOURCES "${CMAKE_CURRENT_SOURCE_DIR}/*.c")
file(GLOB HEADERS "${CMAKE_CURRENT_SOURCE_DIR}/*.h")
set(CMAKE_C_STANDARD 11)
set(CMAKE_CXX_STANDARD 14)

set(PROJ_VERSION_MAJOR 1)
set(PROJ_VERSION_MINOR 0)
set(PROJ_VERSION_PATCH 0)
set(PROJ_VERSION ${PROJ_VERSION_MAJOR}.${PROJ_VERSION_MINOR}.${PROJ_VERSION_PATCH})

if(PROJECT_BUILD_SHARED)
    add_library (${PROJECT_NAME} SHARED ${SOURCES})
    set_target_properties(${PROJECT_NAME} PROPERTIES VERSION ${PROJ_VERSION} SOVERSION ${PROJ_VERSION_MAJOR} )
else()
    add_library (${PROJECT_NAME} STATIC ${SOURCES})
endif()
target_compile_options(${PROJECT_NAME} PRIVATE -Wall -pedantic)
target_include_directories(${PROJECT_NAME} PUBLIC "${CMAKE_CURRENT_SOURCE_DIR}")

install(TARGETS ${PROJECT_NAME} DESTINATION lib)

if (BUILD_TESTS)
    enable_testing()

    find_package(GTest REQUIRED)
    add_executable(ms8607_test ${CMAKE_CURRENT_SOURCE_DIR}/test/ms8607-test.cpp ${HEADERS})
    target_link_libraries(ms8607_test ${PROJECT_NAME} GTest::gtest_main)
    target_include_directories(ms8607_test PUBLIC "${CMAKE_CURRENT_SOURCE_DIR}")
    target_link_directories(ms8607_test PUBLIC ${CMAKE_CURRENT_BINARY_DIR})

    include(GoogleTest)
    gtest_discover_tests(ms8607_test)
endif()
