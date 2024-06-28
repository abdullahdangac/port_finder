cmake_minimum_required(VERSION 3.5)
project(port_finder)

# Default to C++14
if(NOT CMAKE_CXX_STANDARD)
  set(CMAKE_CXX_STANDARD 14)
endif()

if(CMAKE_COMPILER_IS_GNUCXX OR CMAKE_CXX_COMPILER_ID MATCHES "Clang")
  add_compile_options(-Wall -Wextra -Wpedantic)
endif()

find_package(ament_cmake REQUIRED)

set(PROJECT_INCLUDE_DIR "include/${PROJECT_NAME}")

include_directories(${PROJECT_INCLUDE_DIR}) 

add_library(port_finder_lib src/port_finder.cpp)

ament_export_targets(port_finder_lib HAS_LIBRARY_TARGET)

install(
  DIRECTORY include/port_finder
  DESTINATION include
)

install(
  TARGETS port_finder_lib
  EXPORT port_finder_lib
  LIBRARY DESTINATION lib
  ARCHIVE DESTINATION lib
  RUNTIME DESTINATION bin
  INCLUDES DESTINATION include
)

ament_package()