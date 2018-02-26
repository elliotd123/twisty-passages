cmake_minimum_required (VERSION 2.6)
project (twisty-passages)
file(GLOB twisty_SRC
	"src/*.h"
	"src/*.cpp"
)
add_executable(twisty-passages ${twisty_SRC})

target_link_libraries(twisty-passages curses)
