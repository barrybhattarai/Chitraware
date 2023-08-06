cmake_minimum_required(VERSION 3.24)
project(Chitraware)

set(CMAKE_CXX_STANDARD 17)

find_package(glfw3 REQUIRED)
find_package(OpenGL REQUIRED)
find_package(GLEW REQUIRED)
configure_file(Chitraware.h.in Chitrware.h)

add_executable(Chitraware main.cpp renderer.cpp shader.cpp vertexBuffer.cpp)

target_link_libraries(Chitraware PRIVATE glfw OpenGL ${GLEW_LIBRARIES} )


target_include_directories(Chitraware PUBLIC ${PROJECT_BINARY_DIR} ${GLEW_INCLUDE_DIRS})
