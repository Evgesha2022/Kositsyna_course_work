cmake_minimum_required(VERSION 3.17.1)
project(json-api)
set(CMAKE_CXX_STANDARD 14)

include_directories(include thirdparty)

add_subdirectory(include)

set(SOURCES json-api.cpp json-api_test.cpp)
set(HEADERS json-api.h)
add_subdirectory(src)
include(GNUInstallDirs)

set(EXECUTABLE_OUTPUT_PATH ${CMAKE_BINARY_DIR})
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR})
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR})
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR})
install(TARGETS json-api_test DESTINATION json-api )
install (FILES resourse/output.json 
resourse/posttime_for_tablet.json 
resourse/posttime_of_day.json
resourse/postuser.json
resourse/putfn.json
resourse/puttabletafter_time.json
resourse/puttabletname.json
resourse/puttabletstartdate.json
DESTINATION json-api)


