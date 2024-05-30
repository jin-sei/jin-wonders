cmake_minimum_required(VERSION 3.10)
project(jin-wonders)

# Specify the C++ standard
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# Include directories (headers)
include_directories(include)

# Automatically add all .cpp files in the src directory
#file(GLOB_RECURSE SOURCES "src/*.cpp")

# Liens vers les fichiers source C++
add_executable(Game src/main.cpp src/box.cpp src/plateau.cpp src/layout.cpp src/carte.cpp src/wonders.cpp)

# Link libraries (if any)
# target_link_libraries(MyExecutable PRIVATE some_library)