

add_library(server server.h server.cpp)

add_library(client client.h client.cpp)

target_link_libraries(server client)



