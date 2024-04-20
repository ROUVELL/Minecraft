cmake_minimum_required(VERSION 3.28)

set(CMAKE_CXX_STANDARD 17)

project(MyProject)

file(GLOB_RECURSE HEADERS ${CMAKE_CURRENT_SOURCE_DIR}/src/*.hpp)
file(GLOB_RECURSE SOURCES ${CMAKE_CURRENT_SOURCE_DIR}/src/*.cpp)

add_executable(${PROJECT_NAME} ${HEADERS} ${SOURCES})

if(NOT CMAKE_BUILD_TYPE)
  set(CMAKE_BUILD_TYPE Release CACHE STRING "Build type" FORCE)
endif()

if(CMAKE_BUILD_TYPE EQUAL "Release")
  target_compile_options(${PROJECT_NAME} PRIVATE -Wall -Wextra /O2)
else()
  target_compile_options(${PROJECT_NAME} PRIVATE -Wall -Wextra)
endif()

find_package(OpenGL REQUIRED)
find_package(GLEW REQUIRED)

target_link_libraries(${PROJECT_NAME} glfw OpenGL::GL GLEW::GLEW ${CMAKE_DL_LIBS})

