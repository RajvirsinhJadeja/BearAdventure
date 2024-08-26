cmake_minimum_required(VERSION 3.10)
project(BearAdventure)

include(FetchContent)

FetchContent_Declare(
    SFML
    GIT_REPOSITORY https://github.com/SFML/SFML.git
    GIT_TAG 2.6.x
)
FetchContent_MakeAvailable(SFML)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

if(NOT CMAKE_BUILD_TYPE)
    set(CMAKE_BUILD_TYPE Release)
endif()

file(GLOB SOURCES "src/*.cpp")

add_executable(BearAdventure ${SOURCES})

target_include_directories(BearAdventure PUBLIC ${PROJECT_SOURCE_DIR}/include)

if(UNIX AND NOT APPLE)
    find_package(X11 REQUIRED)
    target_link_libraries(BearAdventure sfml-graphics sfml-window sfml-system sfml-audio X11)
else()
    target_link_libraries(BearAdventure sfml-graphics sfml-window sfml-system sfml-audio)
endif()

set(RESOURCES_DIR "${PROJECT_SOURCE_DIR}/resources")

add_custom_command(
    TARGET BearAdventure POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_directory
    "${RESOURCES_DIR}" $<TARGET_FILE_DIR:BearAdventure>/resources
)

if(WIN32)
    add_custom_command(
        TARGET BearAdventure POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy_if_different
        $<TARGET_RUNTIME_DLLS:BearAdventure> $<TARGET_FILE_DIR:BearAdventure>
        COMMAND_EXPAND_LISTS
    )
endif()

