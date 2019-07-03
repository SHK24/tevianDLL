cmake_minimum_required(VERSION 3.8.0)
project(tevianDLL)

set(CMAKE_AUTOMOC ON)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

find_package(Qt5 COMPONENTS Core Network REQUIRED)

set(SOURCES
    detectRequest.cpp
    loginrequest.cpp
    request.cpp
    teviandll.cpp
)

add_library(tevianDLL SHARED ${SOURCES})
qt5_use_modules(tevianDLL core network)

target_link_libraries(tevianDLL Qt5::Core Qt5::Network)

target_compile_definitions(tevianDLL PRIVATE TEVIANDLL_LIBRARY)

