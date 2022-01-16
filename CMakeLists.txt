cmake_minimum_required (VERSION 3.19.2)
project (MediaKeys VERSION 1.0.0.0)

include_directories("${PROJECT_SOURCE_DIR}/src")

file(
  GLOB
  SOURCES
  "src/*.c"
)

SET(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/bin)

IF (WIN32)
  SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /UMBCS /D_UNICODE /DUNICODE")
  add_executable(MediaKeys WIN32 ${SOURCES})
ELSE()
  find_package(X11 REQUIRED)
  include_directories(${X11_INCLUDE_DIR})
  add_executable(MediaKeys ${SOURCES})
  target_link_options(MediaKeys PRIVATE -lX11 -lXtst)
  target_link_libraries(MediaKeys PRIVATE ${X11_LIBRARIES})
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