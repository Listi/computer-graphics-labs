# Top-Level CMakeList.txt

cmake_minimum_required (VERSION 2.6)
project(SecondLab)

add_executable(mathLab main.cpp)

find_package(OpenGL REQUIRED)
find_package(GLUT REQUIRED)

include_directories(
    ${OPENGL_INCLUDE_DIRS}
    ${GLUT_INCLUDE_DIRS}
)
target_link_libraries( mathLab
    ${OPENGL_LIBRARIES}
    ${GLUT_LIBRARY}
)
