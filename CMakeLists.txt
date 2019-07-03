cmake_minimum_required(VERSION 3.8.0)
project(tevianDLL)

set(CMAKE_AUTOMOC ON)

find_package(Qt5 COMPONENTS Core Network REQUIRED)

set(tevianDLL_SRCS
    detectRequest.cpp
    loginrequest.cpp
    request.cpp
    teviandll.cpp
)

add_library(tevianDLL SHARED ${tevianDLL_SRCS})

target_link_libraries(tevianDLL Qt5::Core Qt5::Network)
qt5_use_modules(tevianDLL core network)

