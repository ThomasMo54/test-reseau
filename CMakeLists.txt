cmake_minimum_required(VERSION 3.28)
project(test_reseau)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_SOURCE_DIR}/cmake")
list(APPEND CMAKE_PREFIX_PATH "/usr/lib/x86_64-linux-gnu")

find_package(SDL2 REQUIRED)
find_package(SDL2_net REQUIRED)
include_directories(${CMAKE_CURRENT_SOURCE_DIR} ${SDL2_INCLUDE_DIRS} ${SDL2_NET_INCLUDE_DIRS})

add_executable(server
        Server/server.cpp
        Server/Server.cpp
        Server/Server.hpp
        Server/ServerException.hpp
)
add_executable(client
        Client/client.cpp
        Client/Client.cpp
        Client/Client.hpp
        Client/ClientException.hpp
)

target_link_libraries(server ${SDL2_LIBRARIES} ${SDL2_NET_LIBRARIES})
target_link_libraries(client ${SDL2_LIBRARIES} ${SDL2_NET_LIBRARIES})
