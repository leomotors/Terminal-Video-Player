cmake_minimum_required(VERSION 3.16)
project(Terminal-Video-Player VERSION 2.0.16)

# Config
set(APP_VERSION "${CMAKE_PROJECT_VERSION}")
configure_file(config/AppProps.h.in ${CMAKE_CURRENT_BINARY_DIR}/gen/AppProps.h)

set(EXECUTABLE_NAME "tplay")
set(AUDIOLIB_NAME "playAudio")
set(WINSIZELIB_NAME "winSize")
set(GETCHLIB_NAME "getch")

# Import OpenCV
find_package(OpenCV REQUIRED)
include_directories(${OpenCV_INCLUDE_DIRS})

# SRC FILE
file(GLOB APP_SRC "src/*.cpp")
set(AUDIOPLAY_SRC "src/lib/playAudio.c")
set(WINSIZE_SRC "src/lib/winSize.c")
set(GETCH_SRC "src/lib/getch.c")
include_directories(src)

# Compiling
add_library(${AUDIOLIB_NAME} ${AUDIOPLAY_SRC})
add_library(${WINSIZELIB_NAME} ${WINSIZE_SRC})
add_library(${GETCHLIB_NAME} ${GETCH_SRC})
add_executable(${EXECUTABLE_NAME} ${APP_SRC})

target_compile_options(${AUDIOLIB_NAME} PRIVATE -Wall -Wextra -Wno-unused-result -O3 -lm)
target_compile_options(${WINSIZELIB_NAME} PRIVATE -Wall -Wextra -Wno-unused-result -O3 -lm)
set(CMAKE_CXX_FLAGS "-Wall -Wextra -Wno-unused-result -Wno-unused-variable -O3 -lm -pthread -fconcepts")

# Linking Libraries for playAudio
target_link_libraries(${AUDIOLIB_NAME} mpg123 ao)

# Linking Libraries for main
target_link_libraries(${EXECUTABLE_NAME} ${AUDIOLIB_NAME})
target_link_libraries(${EXECUTABLE_NAME} ${WINSIZELIB_NAME})
target_link_libraries(${EXECUTABLE_NAME} ${GETCHLIB_NAME})
target_link_libraries(${EXECUTABLE_NAME} ${OpenCV_LIBS})
target_include_directories(${EXECUTABLE_NAME} PRIVATE ${CMAKE_CURRENT_BINARY_DIR}/gen)

# CPP STANDARD
set_property(TARGET ${EXECUTABLE_NAME} PROPERTY CXX_STANDARD 20)
target_compile_Features(${EXECUTABLE_NAME} PRIVATE cxx_std_20)

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
