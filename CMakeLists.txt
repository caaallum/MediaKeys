cmake_minimum_required(VERSION 3.19.2)

project(MediaKeys VERSION 1.0.0.0)

set(FETCHCONTENT_QUIET OFF)

include(FetchContent)
FetchContent_Declare(winui
    GIT_REPOSITORY      https://github.com/caaallum/winui.git
    GIT_SHALLOW         TRUE
)

FetchContent_Declare(json
  URL https://github.com/nlohmann/json/releases/download/v3.11.2/json.tar.xz
)

FetchContent_MakeAvailable(winui json)

add_subdirectory(MediaConfig)
add_subdirectory(MediaKeys)

FILE(GLOB SRC
	src/mediakeys.cxx
	src/config.cxx
	src/config.h
	src/window.cxx
	src/window.h
)
