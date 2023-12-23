
cmake_minimum_required(VERSION 3.25) 
project(different_trees)

add_executable(comparison "comparison-of-trees/comparison.cpp")

file(GLOB ${PROJECT_NAME}_HEADERS "trees/*.hpp" "trees/*/*.hpp")
file(GLOB ${PROJECT_NAME}_SOURCES "comparison-of-trees/*.cpp" "comparison-of-trees/*/*.cpp")

add_library(${PROJECT_NAME} 
            ${${PROJECT_NAME}_HEADERS} 
            ${${PROJECT_NAME}_SOURCES})

target_include_directories(${PROJECT_NAME} 
                            PUBLIC $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>)

target_link_libraries(comparison PRIVATE ${PROJECT_NAME})