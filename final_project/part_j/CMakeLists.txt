cmake_minimum_required(VERSION 3.10)

set(CMAKE_CXX_STANDARD 17)

set(TEST_RUNNER_PATH ${CMAKE_CURRENT_SOURCE_DIR})


include_directories(${TEST_RUNNER_PATH})


add_executable(main 
    src/main.cpp
    src/database.cpp
    src/request.cpp
    src/map.cpp
    src/svg.cpp
    src/json.cpp
    src/transport_router.cpp
)
target_link_libraries(main)
