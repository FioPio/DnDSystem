cmake_minimum_required(VERSION 3.12)
project(DnDSystem)

# Set C++ standard
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

# Include directories
include_directories(${CMAKE_SOURCE_DIR}/include)

# Source files
file(GLOB_RECURSE SOURCES src/*.cpp)


# Find SFML
find_package(SDL2 REQUIRED)
find_package(OpenGL REQUIRED)


include_directories(${SDL2_INCLUDE_DIRS})
include_directories(${OPENGL_INCLUDE_DIR})

# Add executable
add_executable(${PROJECT_NAME} ${SOURCES} src/main.cpp)

# Link against SFML
#target_link_libraries(${PROJECT_NAME} sfml-graphics sfml-window sfml-system)
# Link against the ncursesw library
#target_link_libraries(${PROJECT_NAME} ncursesw)
target_link_libraries(${PROJECT_NAME} ${SDL2_LIBRARIES} ${OPENGL_LIBRARIES} m)
# Install executable
install(TARGETS ${PROJECT_NAME} DESTINATION bin)