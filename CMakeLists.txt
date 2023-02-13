cmake_minimum_required(VERSION 3.24)
project(Chitraware)

set(CMAKE_CXX_STANDARD 17)

find_package(glfw3 REQUIRED)
find_package(OpenGL REQUIRED)
find_package(GLEW REQUIRED)


add_executable(Chitraware main.cpp renderer.cpp shader.cpp vertexBuffer.cpp)

target_link_libraries(Chitraware PRIVATE glfw OpenGL ${GLEW_LIBRARIES} )


target_include_directories(Chitraware PUBLIC ${GLEW_INCLUDE_DIRS})
