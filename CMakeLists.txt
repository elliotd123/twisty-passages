cmake_minimum_required(VERSION 3.0.0)
set(CMAKE_CXX_STANDARD 11)
project(twisty-passages VERSION 0.1.0)
project(twisty-test VERSION 0.1.0)

set(YAML_CPP_BUILD_TESTS OFF CACHE BOOL "disable yaml tests")
set(YAML_CPP_BUILD_TOOLS OFF CACHE BOOL "disable yaml tools")
set(YAML_CPP_BUILD_CONTRIB OFF CACHE BOOL "disable yaml contrib")

add_subdirectory(ext/yaml-cpp/)

file(GLOB twisty_SRC
	"src/*.h"
	"src/*.cpp"
)

file(GLOB twisty-test_SRC
	"test/catch.hpp"
	"test/test_character_data.cpp"
	"test/test_main.cpp"
	"test/test_square.cpp"
	"test/test_utilities.cpp"
	"src/Character.cpp"
	"src/CharacterData.cpp"
	"src/Config.cpp"
	"src/Fight.cpp"
	"src/Monster.cpp"
	"src/MonsterData.cpp"
	"src/Utilities.cpp"
	"src/Room.cpp"
	"src/Sqare.cpp"
	"src/Level.cpp"
	"src/Square.cpp"
	"src/Logger.cpp"
	"src/YAMLExtractor.cpp"
)


include(CTest)
enable_testing()

add_executable(twisty-passages ${twisty_SRC})
add_executable(twisty-test ${twisty-test_SRC})

target_include_directories(twisty-passages PUBLIC "${CMAKE_SOURCE_DIR}/ext/yaml-cpp/include")

target_include_directories(twisty-test PUBLIC "src")
target_include_directories(twisty-test PUBLIC "${CMAKE_SOURCE_DIR}/ext/yaml-cpp/include")

target_link_libraries(twisty-passages SDL2)
target_link_libraries(twisty-passages SDL2_ttf)
target_link_libraries(twisty-passages yaml-cpp)

target_link_libraries(twisty-test yaml-cpp)

set(CPACK_PROJECT_NAME ${PROJECT_NAME})
set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})
include(CPack)

configure_file(${CMAKE_SOURCE_DIR}/config.yaml ${CMAKE_CURRENT_BINARY_DIR}/config.yaml COPYONLY)
file(COPY data DESTINATION .)

add_custom_command(TARGET twisty-test POST_BUILD
	COMMAND ${CMAKE_CURRENT_BINARY_DIR}/twisty-test || true)
