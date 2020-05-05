cmake_minimum_required(VERSION 3.0.0)
set(CMAKE_CXX_STANDARD 11)
project(twisty-passages VERSION 0.1.0)

file(GLOB twisty_SRC
	"src/*.h"
	"src/*.cpp"
)


include(CTest)
enable_testing()

add_executable(twisty-passages ${twisty_SRC})

target_link_libraries(twisty-passages curses)

set(CPACK_PROJECT_NAME ${PROJECT_NAME})
set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})
include(CPack)
