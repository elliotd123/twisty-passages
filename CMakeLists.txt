cmake_minimum_required(VERSION 3.0.0)
set(CMAKE_CXX_STANDARD 11)
project(twisty-passages VERSION 0.1.0)
project(twisty-test VERSION 0.1.0)

file(GLOB twisty_SRC
	"src/*.h"
	"src/*.cpp"
)

file(GLOB twisty-test_SRC
	"test/catch.hpp"
	"test/test_main.cpp"
	"src/Utilities.cpp"
	"src/Room.cpp"
	"src/Sqare.cpp"
	"src/Level.cpp"
	"src/Square.cpp"
)


include(CTest)
enable_testing()

add_executable(twisty-passages ${twisty_SRC})
add_executable(twisty-test ${twisty-test_SRC})

target_include_directories(twisty-test PUBLIC "src")

target_link_libraries(twisty-passages curses)
target_link_libraries(twisty-test curses)

set(CPACK_PROJECT_NAME ${PROJECT_NAME})
set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})
include(CPack)

add_custom_command(TARGET twisty-test POST_BUILD
	COMMAND ${CMAKE_CURRENT_BINARY_DIR}/twisty-test)
