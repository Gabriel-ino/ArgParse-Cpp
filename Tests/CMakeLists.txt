set(FETCHCONTENT_QUIET OFF CACHE BOOL "Desabilite quiet mode off FetchContent" FORCE)
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)

FetchContent_Declare(
	googletest
	GIT_REPOSITORY https://github.com/google/googletest.git
	GIT_TAG	       release-1.11.0
	)

FetchContent_MakeAvailable(googletest)

add_executable(testArgumentParser
       	"testArgumentParser.cpp"
	"${CMAKE_SOURCE_DIR}/ArgParser.h"
	"${CMAKE_SOURCE_DIR}/utils.h")

target_include_directories(testArgumentParser PRIVATE ${CMAKE_SOURCE_DIR})
target_link_libraries(testArgumentParser PRIVATE gtest_main)
