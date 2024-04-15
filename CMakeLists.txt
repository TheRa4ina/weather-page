cmake_minimum_required(VERSION 3.5)
project(weather_wizardry CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

add_executable(server main.cc)

# ##############################################################################
# If you include the drogon source code locally in your project, use this method
# to add drogon 
# add_subdirectory(drogon) 
# target_link_libraries(${PROJECT_NAME} PRIVATE drogon)
#
# and comment out the following lines
find_package(Drogon CONFIG REQUIRED)
target_link_libraries(server PRIVATE Drogon::Drogon)

# ##############################################################################
configure_file(config.json ${CMAKE_CURRENT_BINARY_DIR} COPYONLY)
configure_file(style.css ${CMAKE_CURRENT_BINARY_DIR} COPYONLY)

target_include_directories(server
PRIVATE 
    ${CMAKE_CURRENT_SOURCE_DIR})
target_sources(server
               PRIVATE
               index.cc)