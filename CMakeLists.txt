cmake_minimum_required (VERSION 3.19.2)
project (MediaKeys VERSION 1.0.0.0)

include_directories("${PROJECT_SOURCE_DIR}/src")

file(
  GLOB
  SOURCES
  "src/*.c"
)

IF (WIN32)
  SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /UMBCS /D_UNICODE /DUNICODE")
  add_executable (MediaKeys WIN32 ${SOURCES})
ELSE()
  SET(CMAKE_C_COMPILER gcc)
  find_package(X11 REQUIRED)
  add_executable(MediaKeys ${SOURCES} include/stdafx.h)
  link_libraries(${X11_LIBRARIES})
  include_directories(${X11_INCLUDE_DIR})
ENDIF()

# Set include directory search paths
target_include_directories(MediaKeys 
  PRIVATE
    "${PROJECT_BINARY_DIR}"
    "${CMAKE_CURRENT_SOURCE_DIR}/include/"
)

# Set executable RPATH
set_target_properties(MediaKeys
  PROPERTIES
      INSTALL_RPATH
        "${CMAKE_INSTALL_PREFIX}/lib"
)

# Set executable install location
install(TARGETS MediaKeys DESTINATION bin)

# Set install location for resources
install(DIRECTORY content
  DESTINATION "${CMAKE_INSTALL_PREFIX}/share/${CMAKE_PROJECT_NAME}"
)