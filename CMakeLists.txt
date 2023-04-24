cmake_minimum_required(VERSION 3.0)


project(BijectiveTransliterator)

set(SOURCES
	sources/RuEnTransliterator.cpp
	sources/symbolic_analyser/encoding.cpp
)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} $ENV{CUSTOM_FLAGS}")

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${PROJECT_SOURCE_DIR}/bin)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${PROJECT_SOURCE_DIR}/lib)
include_directories(${PROJECT_SOURCE_DIR}/include ${PROJECT_SOURCE_DIR}/sources)
link_directories(${PROJECT_SOURCE_DIR}/lib)

add_library(RuEnTransliterator SHARED ${SOURCES})
add_executable(demonstration sources/main.cpp)
target_link_libraries(demonstration RuEnTransliterator)