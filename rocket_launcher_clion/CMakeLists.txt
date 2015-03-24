
cmake_minimum_required(VERSION 2.8)

project(Luminis-DevCon C)

set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "/Users/abroekhuis/Development/Celix/usr/local/share/celix/cmake/modules")

find_package(CELIX REQUIRED)
find_package(Jansson REQUIRED)

include_directories(${CELIX_INCLUDE_DIRS})

#TODO add sub directory for every bundle
#e.g. 
#add_subdirectory(mybundle)

#add_subdirectory(rocket_launcher)
add_subdirectory(rocket_launcher)

deploy_targets()
