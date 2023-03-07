set(BINARY ${CMAKE_PROJECT_NAME})

set(CMAKE_CXX_STANDARD 17)

######### GTEST GMOCK FETCH
include(FetchContent)
FetchContent_Declare(
    googletest
    GIT_REPOSITORY https://github.com/google/googletest.git
    GIT_TAG        release-1.11.0
)

set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(googletest)

set(BUILD_GMOCK ON CACHE BOOL "" FORCE)
set(BUILD_GTEST ON CACHE BOOL "" FORCE)

include_directories(../src)
#########
include_directories(.)

file(GLOB_RECURSE TEST_SOURCES LIST_DIRECTORIES true *.h *.cpp)

add_executable(${BINARY}_tests ${TEST_SOURCES})

target_link_libraries(${BINARY}_tests ${BINARY}_lib gtest gmock)
