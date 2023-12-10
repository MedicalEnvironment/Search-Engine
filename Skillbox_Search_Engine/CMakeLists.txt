cmake_minimum_required (VERSION 3.11)

project (Skillbox_Search_Engine VERSION 1.0.1)

set(CMAKE_CXX_STANDARD 17)
SET(CMAKE_CXX_STANDARD_REQUIRED ON)

configure_file(
        configuration.h
        ${CMAKE_CURRENT_BINARY_DIR}/config.h
)

add_subdirectory(Tests)

include(FetchContent)
FetchContent_Declare(
        json URL https://github.com/nlohmann/json/releases/download/v3.10.5/json.tar.xz
)
FetchContent_MakeAvailable(
        json
)

set(Headers
        include/ConverterJSON.h
        include/InvertedIndex.h
        include/SearchServer.h
        )

set(Sources
        Src/ConverterJSON.cpp
        Src/InvertedIndex.cpp
        Src/SearchServer.cpp
        )

add_library(Project_library ${Headers} ${Sources})

add_executable (Skillbox_Search_Engine Skillbox_Search_Engine.cpp Skillbox_Search_Engine.h)

if (CMAKE_VERSION VERSION_GREATER 3.12)
    set_property(TARGET Skillbox_Search_Engine PROPERTY CXX_STANDARD 20)
endif()

# TODO: Добавьте тесты и целевые объекты, если это необходимо.
target_link_libraries(Project_library nlohmann_json::nlohmann_json)
target_link_libraries(Skillbox_Search_Engine Project_library)
target_include_directories(Project_library PRIVATE ${CMAKE_CURRENT_BINARY_DIR})
target_include_directories(Skillbox_Search_Engine PRIVATE ${CMAKE_CURRENT_BINARY_DIR})