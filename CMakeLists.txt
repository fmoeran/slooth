cmake_minimum_required(VERSION 3.1)
project(slooth)

set(CMAKE_CXX_STANDARD 17)


file(GLOB CORE_FILES src/core/*.hpp src/core/*.cpp)
file(GLOB GLAD_FILES libraries/glad/src/glad.c)
file(GLOB OBJECT_FILES src/objects/*.hpp src/objects/*.cpp)
file(GLOB SOURCE_FILES src/main.cpp src/core/*.hpp src/core/*.cpp libraries/glad/src/glad.c)


set(CMAKE_CXX_FLAGS_DEBUG "-g -Wall")

set(CMAKE_CXX_FLAGS_RELEASE "-O3")

add_executable(slooth src/main.cpp ${CORE_FILES} ${OBJECT_FILES} ${GLAD_FILES} )

# glad

target_include_directories(slooth PRIVATE libraries/glad/include)

# glfw

set(GLFW_BUILD_DOCS OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_TESTS OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_EXAMPLES OFF CACHE BOOL "" FORCE)

add_subdirectory(vendor/glfw)

target_link_libraries(slooth glfw)

target_include_directories(slooth PRIVATE vendor/glfw/include)

# opengl

find_package(OpenGL REQUIRED)

target_link_libraries(slooth OpenGL::GL)

# glm

target_include_directories(slooth PRIVATE vendor/glm)

