cmake_minimum_required (VERSION 3.1)
set (CMAKE_CXX_STANDARD 11)
project (twisty-passages)
file(GLOB twisty_SRC
	"src/*.h"
	"src/*.cpp"
)
add_executable(twisty-passages ${twisty_SRC})

target_link_libraries(twisty-passages curses)
