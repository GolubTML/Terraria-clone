cmake_minimum_required(VERSION 3.10)
project(TerrariaClone)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

file(GLOB SRC_FILES
    src/*.cpp
    src/imgui/imgui*.cpp
)

add_executable(Terka ${SRC_FILES})

target_include_directories(Terka PRIVATE src src/imgui)

if (WIN32)
    target_link_libraries(Terka
        glfw3
        opengl32
        glew32
    )
else()
    target_link_libraries(Terka
        glfw
        GL
        dl
        pthread
        X11
        GLEW
    )
endif()

add_custom_target(run
    COMMAND ${CMAKE_CURRENT_BINARY_DIR}/Terka
    DEPENDS Terka
    WORKING_DIRECTORY ${CMAKE_SOURCE_DIR}
)
