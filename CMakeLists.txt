cmake_minimum_required(VERSION 3.28)
project(TrabalhoP1)

set(CMAKE_CXX_STANDARD 17)

link_libraries(glfw)

file(COPY shaders DESTINATION ${CMAKE_BINARY_DIR})

include_directories("${GLFW_SOURCE_DIR}/include")
add_compile_options(-lglfw3 -lGL -lX11 -lpthread -lXrandr -lXi -ldl)

add_executable(Trabalho src/main.cpp
        src/Shader.cpp
        src/Shader.h
        src/Window.cpp
        src/Window.h
)

include(FetchContent)

FetchContent_Declare(
        glm
        GIT_REPOSITORY	https://github.com/g-truc/glm.git
        GIT_TAG 	bf71a834948186f4097caa076cd2663c69a10e1e #refs/tags/1.0.1
)

FetchContent_MakeAvailable(glm)

target_link_libraries(Trabalho PRIVATE glm::glm)

