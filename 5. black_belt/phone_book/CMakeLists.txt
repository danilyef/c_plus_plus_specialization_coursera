cmake_minimum_required(VERSION 3.10)
project(PhoneBookProtobuf LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Find Protocol Buffers package
find_package(Protobuf REQUIRED)

# Find Abseil package
find_package(absl REQUIRED)

include_directories(${Protobuf_INCLUDE_DIRS})
include_directories(${CMAKE_CURRENT_BINARY_DIR})

# Generate protobuf files from proto directory
protobuf_generate_cpp(PROTO_SRCS PROTO_HDRS proto/contact.proto)

# Add all source files
add_executable(main
    src/main.cpp
    src/phone_book.cpp
    src/phone_book.h
    src/iterator_range.h
    src/test_runner.h
    ${PROTO_SRCS}
    ${PROTO_HDRS}
)

# Link necessary libraries
target_link_libraries(main 
    ${Protobuf_LIBRARIES}
    absl::log
    absl::log_internal_message
    absl::log_internal_check_op
)
