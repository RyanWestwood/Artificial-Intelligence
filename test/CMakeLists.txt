cmake_minimum_required(VERSION 3.0)
project(Unit-Tests)
set (CMAKE_CXX_STANDARD 20)
enable_testing()
set(BINARY_FILES "${CMAKE_PREFIX_PATH}/bin")
set(LIBRARY_FILES "${CMAKE_PREFIX_PATH}/lib")
set(INCLUDE_FILES "${CMAKE_PREFIX_PATH}/include")

find_package(SDL2_IMAGE REQUIRED)
find_package(SDL2_MIXER REQUIRED)
find_package(SDL2 REQUIRED)
find_package(SDL2_TTF REQUIRED)

set(LIB_FILES 
    "${SDL2_LIBRARIES}"
    "${LIBRARY_FILES}/SDL2_image.lib"
    "${LIBRARY_FILES}/SDL2_mixer.lib" 
    "${LIBRARY_FILES}/SDL2_ttf.lib"
    "${LIBRARY_FILES}/AIL.lib"
    "${LIBRARY_FILES}/ArtificialIntelligence_static.lib"
    ) 

file(GLOB DLLS "${BINARY_FILES}/*.dll")
file(COPY ${DLLS} DESTINATION ${CMAKE_CURRENT_SOURCE_DIR}/build/Release)

function(AddTest TestName Sources)
    add_executable(${TestName} ${Sources})        
    target_link_libraries(${TestName} ${LIB_FILES})
    target_include_directories(${TestName}
        PUBLIC
        ${INCLUDE_FILES}
        "${CMAKE_PREFIX_PATH}/../source"
        )
    add_test(${TestName} ${TestName})
endfunction()
        
AddTest(Renderer source/test_renderer.cpp)
AddTest(Texture source/test_texture.cpp)
AddTest(Sound source/test_sound.cpp)
AddTest(Font source/test_font.cpp)
AddTest(Pathing source/test_pathing.cpp)
AddTest(Collision source/test_collision.cpp)
AddTest(Tilemap source/test_tilemap.cpp)
AddTest(Blackboard source/test_blackboard.cpp)
AddTest(BehaviourTree source/test_behaviour_tree.cpp)
AddTest(BehaviourTreeRunning source/test_behaviour_tree_running.cpp)
AddTest(Pathsmoothing source/test_pathsmoothing.cpp)
AddTest(Vector2 source/test_vector2.cpp)