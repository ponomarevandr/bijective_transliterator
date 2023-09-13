cmake_minimum_required(VERSION 3.0)


project(BijectiveTransliterator)

set(SOURCES
	sources/RuEnTransliterator.cpp
	sources/symbolic_analyser/encoding.cpp
	sources/automata/nondeterministic_automaton.cpp
	sources/automata/deterministic_automaton.cpp
	sources/automata/determinizer.cpp
	sources/rules/rules_processor.cpp
	sources/rules/automata_creator.cpp
	sources/translator/translator.cpp
	sources/utils/file_io_utils.cpp
)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} $ENV{CUSTOM_FLAGS}")

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${PROJECT_SOURCE_DIR}/bin)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${PROJECT_SOURCE_DIR}/lib)
include_directories(${PROJECT_SOURCE_DIR}/include ${PROJECT_SOURCE_DIR}/sources)
link_directories(${PROJECT_SOURCE_DIR}/lib)


add_library(RuEnTransliterator SHARED ${SOURCES})

add_executable(russian_to_english sources/russian_to_english.cpp)
target_link_libraries(russian_to_english RuEnTransliterator)

add_executable(english_to_russian sources/english_to_russian.cpp)
target_link_libraries(english_to_russian RuEnTransliterator)

add_executable(tests sources/tests.cpp sources/tester/tester.cpp)
target_link_libraries(tests RuEnTransliterator)