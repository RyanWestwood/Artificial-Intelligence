cmake_minimum_required (VERSION 3.8)
project(ArtificialIntelligence VERSION 1.0)
set_property(DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR} PROPERTY VS_STARTUP_PROJECT ArtificialIntelligence)
set (CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} -DLOGGING")
set(CMAKE_CXX_FLAGS_RELWITHDEBINFO "${CMAKE_CXX_FLAGS_RELWITHDEBINFO} -DLOGGING")

find_package(SDL2_IMAGE REQUIRED PATHS ${PROJECT_SOURCE_DIR}/libs/SDL2_image-2.6.2)
find_package(SDL2_MIXER REQUIRED PATHS ${PROJECT_SOURCE_DIR}/libs/SDL2_mixer-2.6.2)
find_package(SDL2_TTF REQUIRED PATHS ${PROJECT_SOURCE_DIR}/libs/SDL2_ttf-2.20.1)
find_package(SDL2 REQUIRED PATHS ${PROJECT_SOURCE_DIR}/libs/SDL2-2.24.0)

set(SDL2_IMAGE_INCLUDE_DIRS "${PROJECT_SOURCE_DIR}/libs/SDL2_image-2.6.2/include")
set(SDL2_MIXER_INCLUDE_DIRS "${PROJECT_SOURCE_DIR}/libs/SDL2_mixer-2.6.2/include")
set(SDL2_TTF_INCLUDE_DIRS "${PROJECT_SOURCE_DIR}/libs/SDL2_ttf-2.20.1/include")

include_directories(${SDL2_IMAGE_INCLUDE_DIRS})
include_directories(${SDL2_MIXER_INCLUDE_DIRS})
include_directories(${SDL2_TTF_INCLUDE_DIRS})
include_directories(${SDL2_INCLUDE_DIRS})

file(GLOB SOURCE
    "src/*.h"
    "src/*.cpp"
)

if(CMAKE_SIZEOF_VOID_P EQUAL 8)
    file(GLOB DLLS
        "dlls/x64/*.dll"
    )
    set(SDL2_IMAGE_LIBRARIES "${PROJECT_SOURCE_DIR}/libs/SDL2_image-2.6.2/lib/x64/SDL2_image.lib")
    set(SDL2_MIXER_LIBRARIES "${PROJECT_SOURCE_DIR}/libs/SDL2_mixer-2.6.2/lib/x64/SDL2_mixer.lib")
    set(SDL2_TTF_LIBRARIES "${PROJECT_SOURCE_DIR}/libs/SDL2_ttf-2.20.1/lib/x64/SDL2_ttf.lib")

    file(COPY ${DLLS} DESTINATION ${CMAKE_CURRENT_SOURCE_DIR}/build/Release)
    file(COPY ${DLLS} DESTINATION ${CMAKE_CURRENT_SOURCE_DIR}/build/Debug)
    file(COPY ${DLLS} DESTINATION ${CMAKE_CURRENT_SOURCE_DIR}/build/MinSizeRel)
    file(COPY ${DLLS} DESTINATION ${CMAKE_CURRENT_SOURCE_DIR}/build/RelWithDebInfo)
elseif(CMAKE_SIZEOF_VOID_P EQUAL 4)
    file(GLOB DLLS
        "dlls/x86/*.dll"
    )
    set(SDL2_IMAGE_LIBRARIES "${PROJECT_SOURCE_DIR}/libs/SDL2_image-2.6.2/lib/x86/SDL2_image.lib")
    set(SDL2_MIXER_LIBRARIES "${PROJECT_SOURCE_DIR}/libs/SDL2_mixer-2.6.2/lib/x86/SDL2_mixer.lib")
    set(SDL2_TTF_LIBRARIES "${PROJECT_SOURCE_DIR}/libs/SDL2_ttf-2.20.1/lib/x86/SDL2_ttf.lib")

    file(COPY ${DLLS} DESTINATION ${CMAKE_CURRENT_SOURCE_DIR}/build/Release)
    file(COPY ${DLLS} DESTINATION ${CMAKE_CURRENT_SOURCE_DIR}/build/Debug)
    file(COPY ${DLLS} DESTINATION ${CMAKE_CURRENT_SOURCE_DIR}/build/MinSizeRel)
    file(COPY ${DLLS} DESTINATION ${CMAKE_CURRENT_SOURCE_DIR}/build/RelWithDebInfo)
endif()

add_executable (ArtificialIntelligence ${SOURCE})

target_link_libraries(ArtificialIntelligence ${SDL2_IMAGE_LIBRARIES})
target_link_libraries(ArtificialIntelligence ${SDL2_MIXER_LIBRARIES})
target_link_libraries(ArtificialIntelligence ${SDL2_TTF_LIBRARIES})
target_link_libraries(ArtificialIntelligence ${SDL2_LIBRARIES})