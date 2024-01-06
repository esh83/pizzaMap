cmake_minimum_required(VERSION 3.5)

project(pizzaMap LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_executable(pizzaMap main.cpp
    kdtree.h kdtree.cpp
    hashtable.h hashtable.cpp
    schemma.h
)

include(GNUInstallDirs)
install(TARGETS pizzaMap
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)
