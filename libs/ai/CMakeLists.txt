cmake_minimum_required (VERSION 3.8)
project (ArtificialIntelligenceDLL)
set (CMAKE_CXX_STANDARD 17)
file(GLOB SOURCE
        "include/*" "include/*/*"
)
add_library(ArtificialIntelligenceDLL SHARED ${SOURCE})
set_target_properties(  ArtificialIntelligenceDLL
  PROPERTIES
  ARCHIVE_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/../lib"
  LIBRARY_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/../lib"
  RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/../lib"
)
