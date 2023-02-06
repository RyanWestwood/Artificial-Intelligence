cmake_minimum_required (VERSION 3.8)
project(ArtificialIntelligence VERSION 1.0)
set_property(DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR} PROPERTY VS_STARTUP_PROJECT ${PROJECT_NAME})
set (CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} -DLOGGING")
set(CMAKE_CXX_FLAGS_RELWITHDEBINFO "${CMAKE_CXX_FLAGS_RELWITHDEBINFO} -DLOGGING")

include_directories(${PROJECT_SOURCE_DIR}/library_binaries/include)
find_package(SDL2_IMAGE REQUIRED PATHS ${PROJECT_SOURCE_DIR}/library_binaries)
find_package(SDL2_MIXER REQUIRED PATHS ${PROJECT_SOURCE_DIR}/library_binaries)
find_package(SDL2_TTF REQUIRED PATHS ${PROJECT_SOURCE_DIR}/library_binaries)
find_package(SDL2 REQUIRED PATHS ${PROJECT_SOURCE_DIR}/library_binaries)

set(LIB_FILES 
    "${SDL2_LIBRARIES}"
    "${PROJECT_SOURCE_DIR}/library_binaries/lib/SDL2_image.lib"
    "${PROJECT_SOURCE_DIR}/library_binaries/lib/SDL2_mixer.lib"
    "${PROJECT_SOURCE_DIR}/library_binaries/lib/SDL2_ttf.lib"
    "${PROJECT_SOURCE_DIR}/library_binaries/lib/AI_LIBRARY.lib"
    ) 

file(GLOB DLLS "library_binaries/bin/*.dll")
set(DESTINATIONS Release Debug MinSizeRel RelWithDebInfo)
foreach(DEST ${DESTINATIONS})
  file(COPY ${DLLS} DESTINATION "${CMAKE_CURRENT_SOURCE_DIR}/build/${DEST}")
endforeach()
file(GLOB AI "library_binaries/Debug/bin/AI_LIBRARY.dll")
file(COPY ${AI} DESTINATION ${CMAKE_CURRENT_SOURCE_DIR}/build/Debug)

file(GLOB_RECURSE SOURCE "source/*.*")
add_executable (${PROJECT_NAME} ${SOURCE})
target_link_libraries(${PROJECT_NAME} ${LIB_FILES})

add_library(ArtificialIntelligence_static STATIC ${SOURCE})
target_include_directories(ArtificialIntelligence_static PUBLIC ${PROJECT_SOURCE_DIR}/library_binaries/include)
target_link_libraries(ArtificialIntelligence_static ${LIB_FILES})

install(
    TARGETS ArtificialIntelligence_static EXPORT AI_STATIC_APP
    LIBRARY DESTINATION lib
    ARCHIVE DESTINATION lib
    RUNTIME DESTINATION bin
    PUBLIC_HEADER DESTINATION include
    )