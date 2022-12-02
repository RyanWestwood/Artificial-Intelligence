cmake_minimum_required (VERSION 3.8)
project (ArtificialIntelligenceDLL)
set (CMAKE_CXX_STANDARD 20)
file(GLOB_RECURSE SOURCE "include/*.*")
add_library(ArtificialIntelligenceDLL SHARED ${SOURCE})
set_target_properties(  ArtificialIntelligenceDLL
  PROPERTIES
  ARCHIVE_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/../libs/ai/lib"
  LIBRARY_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/../libs/ai/lib"
  RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/../libs/ai/lib"
)

function (SetFolder src dst var )
    FILE(GLOB src
    ${PROJECT_SOURCE_DIR}/${var}
    )
    SOURCE_GROUP(${dst} FILES ${src})
endfunction()

SetFolder(BT_H, bt_h include/bt/*/*.h)
SetFolder(BT, bt include/bt/*/*.cpp)
SetFolder(BT_H, bt_h include/bt/*.h)
SetFolder(BT, bt include/bt/*.cpp)

SetFolder(FSM_H, fsm_h include/fsm/*.h)
SetFolder(FSM, fsm include/fsm/*.cpp)

SetFolder(MATH_H, math_h include/math/*.h)
SetFolder(MATH, math include/math/*.cpp)

SetFolder(PATHFINDING_H, pathfinding_h include/pathfinding/*.h)
SetFolder(PATHFINDING, pathfinding include/pathfinding/*.cpp)
