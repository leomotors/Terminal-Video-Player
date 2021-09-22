cmake_minimum_required(VERSION 3.16)
project(Terminal-Video-Player VERSION 1.0)

set(APP_VERSION "${CMAKE_PROJECT_VERSION}")

set(EXECUTABLE_NAME "tplay")

# Import OpenCV
find_package(OpenCV REQUIRED)
include_directories(${OpenCV_INCLUDE_DIRS})

# SRC FILE
file(GLOB APP_SRCFILE "src/*.cpp")
include_directories(src)

# Compiling
add_executable(${EXECUTABLE_NAME} ${APP_SRCFILE})
set(CMAKE_CXX_FLAGS "-Wall -Wextra -Wno-unused-result -O3 -lm -pthread")

# Linking
target_link_libraries(${EXECUTABLE_NAME} ${OpenCV_LIBS})

# CPP STANDARD
set_property(TARGET ${EXECUTABLE_NAME} PROPERTY CXX_STANDARD 20)

# For Linux
add_custom_command(TARGET ${EXECUTABLE_NAME} POST_BUILD
    COMMAND mv ${EXECUTABLE_NAME} ..
    COMMENT "Moving Executable to Project Root..."
)
