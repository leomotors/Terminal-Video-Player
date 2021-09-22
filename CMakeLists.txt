cmake_minimum_required(VERSION 3.16)
project(Terminal-Video-Player VERSION 1.0.0)

set(APP_VERSION "${CMAKE_PROJECT_VERSION}")

set(EXECUTABLE_NAME "tplay")
set(AUDIOLIB_NAME "playAudio")

# Import OpenCV
find_package(OpenCV REQUIRED)
include_directories(${OpenCV_INCLUDE_DIRS})

# SRC FILE
file(GLOB APP_SRCFILE "src/*.cpp")
file(GLOB LIB_SRCFILE "src/lib/*.c")
include_directories(src)

# Compiling
add_library(${AUDIOLIB_NAME} ${LIB_SRCFILE})
add_executable(${EXECUTABLE_NAME} ${APP_SRCFILE})
set(CMAKE_CXX_FLAGS "-Wall -Wextra -Wno-unused-result -O3 -lm -pthread")

# Linking Libraries
target_link_libraries(${AUDIOLIB_NAME} mpg123 ao)
target_link_libraries(${EXECUTABLE_NAME} ${AUDIOLIB_NAME})
target_link_libraries(${EXECUTABLE_NAME} ${OpenCV_LIBS})

# CPP STANDARD
set_property(TARGET ${EXECUTABLE_NAME} PROPERTY CXX_STANDARD 17)

# Install
install(
    TARGETS ${EXECUTABLE_NAME}
    RUNTIME DESTINATION /usr/local/bin
)

if(CMAKE_BUILD_TYPE MATCHES Debug)
    add_custom_command(TARGET ${EXECUTABLE_NAME} POST_BUILD
        COMMAND mv ${EXECUTABLE_NAME} ..
        COMMENT "[Debug]: Moving Executable to Project Root..."
    )
endif()
