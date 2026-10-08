cmake_minimum_required(VERSION 3.20)

project(Grabins LANGUAGES C CXX)

# A toolchain file can set this when cross-compiling, so dependencies build
# for the target platform rather than the host platform.
if(CMAKE_CROSSCOMPILING AND CMAKE_SYSTEM_NAME STREQUAL "Windows")
    set(PLATFORM Desktop CACHE STRING "" FORCE)
endif()

include(FetchContent)

set(BUILD_EXAMPLES OFF CACHE BOOL "" FORCE)
set(BUILD_GAMES OFF CACHE BOOL "" FORCE)
set(BUILD_SHARED_LIBS OFF CACHE BOOL "" FORCE)

FetchContent_Declare(
    raylib
    GIT_REPOSITORY https://github.com/raysan5/raylib.git
    GIT_TAG 5.5
    GIT_SHALLOW TRUE
)
FetchContent_MakeAvailable(raylib)

add_executable(Grabins
    main.cpp
    Window.cpp
    font.cpp
    CameraControls.cpp
)
if(APPLE)
    set_target_properties(Grabins PROPERTIES MACOSX_BUNDLE TRUE)
endif()

target_link_libraries(Grabins PRIVATE raylib)

install(TARGETS Grabins
    RUNTIME DESTINATION .
    BUNDLE DESTINATION .
)
