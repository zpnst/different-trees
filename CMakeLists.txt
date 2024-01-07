
cmake_minimum_required(VERSION 3.25) 
project(different_trees)

set(CMAKE_CXX_STANDARD 20)

add_executable(comparison "comparison-of-trees/comparison.cpp")

file(GLOB ${PROJECT_NAME}_HEADERS "splay-tree/*.hpp" "splay-tree/*/*.hpp")
file(GLOB ${PROJECT_NAME}_HEADERS "binary-tree/*.hpp" "binary-tree/*/*.hpp")
file(GLOB ${PROJECT_NAME}_HEADERS "two_three_tree/*.hpp" "two_three_tree/*/*.hpp")
file(GLOB ${PROJECT_NAME}_HEADERS "red-black-tree/*.hpp" "red-black-tree/*/*.hpp")
file(GLOB ${PROJECT_NAME}_HEADERS "avl-binary-tree/*.hpp" "avl-binary-tree/*/*.hpp")

file(GLOB ${PROJECT_NAME}_SOURCES "comparison-of-trees/*.cpp" "comparison-of-trees/*/*.cpp")

add_library(${PROJECT_NAME} 
            ${${PROJECT_NAME}_HEADERS} 
            ${${PROJECT_NAME}_SOURCES})

target_include_directories(${PROJECT_NAME} 
                            PUBLIC $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/trees>)

target_link_libraries(comparison PRIVATE ${PROJECT_NAME})