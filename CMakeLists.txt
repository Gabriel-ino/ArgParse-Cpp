cmake_minimum_required(VERSION 3.12)

project(PhotoBatch)

add_executable(PhotoBatch
    "PhotoBatch.cpp"
    "ArgParser.h"
    "utils.h"
	"Mode.h"
	"Mode.cpp"
	"RenameMode.h"
	"RenameMode.cpp"
	"ConvertMode.h"
	"ConvertMode.cpp")

set_target_properties(PhotoBatch PROPERTIES CXX_STANDARD 17)

set(FETCHCONTENT_QUIET OFF CACHE BOOL "Disable quiet mode from FetchContent" FORCE)
include(FetchContent)

add_subdirectory(Tests)
add_subdirectory(External)

target_link_libraries(PhotoBatch PRIVATE stb)
