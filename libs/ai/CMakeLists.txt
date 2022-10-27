cmake_minimum_required (VERSION 3.8)
project (ArtificialIntelligenceDLL)
set (CMAKE_CXX_STANDARD 20)
file(GLOB SOURCE
        "include/*" "include/*/*" "include/*/*/*"
)
add_library(ArtificialIntelligenceDLL SHARED ${SOURCE})
set_target_properties(  ArtificialIntelligenceDLL
  PROPERTIES
  ARCHIVE_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/../libs/ai/lib"
  LIBRARY_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/../libs/ai/lib"
  RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/../libs/ai/lib"
)
