cmake_minimum_required(VERSION 3.1)
project(slooth)

set(CMAKE_CXX_STANDARD 17)

file(GLOB SOURCE_FILES src/*.hpp src/*.cpp libraries/glad/src/glad.c)

set(CMAKE_CXX_FLAGS_DEBUG "-g -Wall")

set(CMAKE_CXX_FLAGS_RELEASE "-O3")


add_executable(slooth ${SOURCE_FILES})

#glad


target_include_directories(slooth PRIVATE libraries/glad/include)


# glfw



set(GLFW_BUILD_DOCS OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_TESTS OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_EXAMPLES OFF CACHE BOOL "" FORCE)

add_subdirectory(libraries/glfw)

target_link_libraries(slooth glfw)

target_include_directories(slooth PRIVATE libraries/glfw/include)

#opengl

find_package(OpenGL REQUIRED)

target_link_libraries(slooth OpenGL::GL)



#glm

target_include_directories(slooth PRIVATE libraries/glm/include)

