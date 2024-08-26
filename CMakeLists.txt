cmake_minimum_required(VERSION 3.10)
project(BearAdventure)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(SFML_DIR "${CMAKE_SOURCE_DIR}/SFML-2.6.1/lib/cmake/SFML")

find_package(SFML 2.6 REQUIRED COMPONENTS graphics window system audio)

include_directories(${CMAKE_SOURCE_DIR}/include)
include_directories(${CMAKE_SOURCE_DIR}/SFML-2.6.1/include)

file(GLOB SOURCES "src/*.cpp")

add_executable(BearAdventure ${SOURCES})

target_link_libraries(BearAdventure sfml-graphics sfml-window sfml-system sfml-audio)

set(CMAKE_BUILD_TYPE Release CACHE STRING "Build type" FORCE)

add_custom_command(TARGET BearAdventure POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_directory
    ${CMAKE_SOURCE_DIR}/resources $<TARGET_FILE_DIR:BearAdventure>/resources
)

if (WIN32)
    set(SFML_BIN_DIR "${CMAKE_SOURCE_DIR}/SFML-2.6.1/bin")
    add_custom_command(TARGET BearAdventure POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy_if_different
	${SFML_BIN_DIR}/openal32.dll
        ${SFML_BIN_DIR}/sfml-audio-2.dll
        ${SFML_BIN_DIR}/sfml-graphics-2.dll
        ${SFML_BIN_DIR}/sfml-window-2.dll
        ${SFML_BIN_DIR}/sfml-system-2.dll
        $<TARGET_FILE_DIR:BearAdventure>
    )
endif()
