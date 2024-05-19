cmake_minimum_required(VERSION 3.8)


project (ConsoleMinesweeper)
set(CMAKE_CXX_STANDARD 20)
file (GLOB_RECURSE MINESWEEPER_SOURCES CONFIGURE_DEPENDS "src/*.cpp")
file (GLOB_RECURSE MINESWEEPER_HEADERS CONFIGURE_DEPENDS "src/*.h")

set (MINESWEEPER_INCLUDE_DIRS "")
foreach (_headerFile ${MINESWEEPER_HEADERS})
    get_filename_component(_dir ${_headerFile} PATH)
    list (APPEND MINESWEEPER_INCLUDE_DIRS ${_dir})
endforeach()
list (REMOVE_DUPLICATES MINESWEEPER_INCLUDE_DIRS)


find_package(Curses REQUIRED)

add_executable (MineSweeper ${MINESWEEPER_SOURCES})
target_include_directories(MineSweeper PRIVATE ${MINESWEEPER_INCLUDE_DIRS})

if(WIN32)
	target_link_libraries(MineSweeper Curses::Curses)
else()
	target_link_libraries(MineSweeper ${CURSES_NCURSES_LIBRARY})
endif()