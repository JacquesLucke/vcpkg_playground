cmake_minimum_required(VERSION 3.10)

# Automatically download vcpkg if CMAKE_TOOLCHAIN_FILE isn't set
if(NOT DEFINED CMAKE_TOOLCHAIN_FILE)
    include(FetchContent)
    FetchContent_Declare(
        vcpkg
        GIT_REPOSITORY https://github.com/microsoft/vcpkg.git
        GIT_TAG        2026.06.24
    )
    FetchContent_MakeAvailable(vcpkg)
    set(CMAKE_TOOLCHAIN_FILE "${vcpkg_SOURCE_DIR}/scripts/buildsystems/vcpkg.cmake"
        CACHE FILEPATH "vcpkg toolchain file")
endif()

project(hello_vcpkg)

find_package(fmt CONFIG REQUIRED)

add_executable(Hello hello.cc)

target_link_libraries(Hello PRIVATE fmt::fmt)