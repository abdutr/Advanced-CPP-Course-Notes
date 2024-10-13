cmake_minimum_required(VERSION 3.16)
project(advancedCpp)

# Set the C and C++ compilers to Clang 18
# set(CMAKE_C_COMPILER "/usr/bin/clang-19")
# set(CMAKE_CXX_COMPILER "/usr/bin/clang++-19")


set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Find and link libraries
find_package(fmt REQUIRED)
find_package(Boost REQUIRED)
# find_package(absl REQUIRED)
find_package(Protobuf REQUIRED)

add_subdirectory(Lessons)

add_executable(advancedCpp ${LESSONS_SOURCE} )

# Link libraries to the executable
target_link_libraries(advancedCpp 
    fmt::fmt 
    Boost::boost 
    # absl::strings 
    # absl::flat_hash_map
    ${PROTOBUF_LIBRARIES})