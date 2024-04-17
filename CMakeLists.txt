cmake_minimum_required(VERSION 3.5)
project(weather_wizardry CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

# ##############################################################################
# If you include the drogon source code locally in your project, use this method
# to add drogon 
# add_subdirectory(drogon) 
# target_link_libraries(${PROJECT_NAME} PRIVATE drogon)
#
# and comment out the following lines
find_package(Drogon CONFIG REQUIRED)

# ##############################################################################
configure_file(config.json ${CMAKE_CURRENT_BINARY_DIR} COPYONLY)
configure_file(style.css ${CMAKE_CURRENT_BINARY_DIR} COPYONLY)
add_executable(server 
    main.cc
    fetching.cc
    index.cc)
target_link_libraries(server PRIVATE Drogon::Drogon)

target_include_directories(server
PRIVATE 
    ${CMAKE_CURRENT_SOURCE_DIR})

# ###############################################################################

include(FetchContent)
FetchContent_Declare(
  googletest
  # Specify the commit you depend on and update it regularly.
  URL https://github.com/google/googletest/archive/dddb219c3eb96d7f9200f09b0a381f016e6b4562.zip
)
# For Windows: Prevent overriding the parent project's compiler/linker settings
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(googletest)

enable_testing()
add_executable(tests
fetching.cc
    main.tests.cc)
    
target_link_libraries(tests
PRIVATE 
    Drogon::Drogon
    GTest::gtest_main)

target_include_directories(tests
PRIVATE 
    ${CMAKE_CURRENT_SOURCE_DIR})

include(GoogleTest)


gtest_discover_tests(tests)