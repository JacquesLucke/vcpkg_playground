cmake_minimum_required(VERSION 3.20)
project(hello_vcpkg)

enable_testing()

# Prepare GTest library.
find_package(GTest CONFIG REQUIRED)

# Prepare fmt library.
find_package(fmt CONFIG REQUIRED)

# Prepare LLVM and Clang libraries.
find_package(LLVM CONFIG REQUIRED)
find_package(Clang CONFIG REQUIRED)
list(APPEND CMAKE_MODULE_PATH "${LLVM_CMAKE_DIR}")
include(HandleLLVMOptions)
add_definitions(${LLVM_DEFINITIONS})
llvm_map_components_to_libnames(llvm_libs Support native)
set(clang_libs
    clangAST
    clangBasic
    clangDriver
    clangFrontend
    clangLex
    clangSerialization
    clangTooling
)

# Prepare TBB library.
find_package(TBB CONFIG REQUIRED)

# Prepare cppzmq library.
find_package(cppzmq CONFIG REQUIRED)

add_executable(hello hello.cc)
set_target_properties(hello PROPERTIES
    CXX_STANDARD 20
    CXX_STANDARD_REQUIRED ON
    CXX_EXTENSIONS OFF
)
target_link_libraries(hello PRIVATE fmt::fmt)
target_link_libraries(hello PRIVATE ${llvm_libs})
target_link_libraries(hello PRIVATE ${clang_libs})
target_link_libraries(hello PRIVATE TBB::tbb)
target_link_libraries(hello PRIVATE cppzmq-static)


add_executable(hello_test hello_test.cc)
set_target_properties(hello_test PROPERTIES
    CXX_STANDARD 20
    CXX_STANDARD_REQUIRED ON
    CXX_EXTENSIONS OFF
)
target_link_libraries(hello_test PRIVATE fmt::fmt)
target_link_libraries(hello_test PRIVATE ${llvm_libs})
target_link_libraries(hello_test PRIVATE ${clang_libs})
target_link_libraries(hello_test PRIVATE TBB::tbb)
target_link_libraries(hello_test PRIVATE cppzmq-static)
target_link_libraries(hello_test PRIVATE GTest::gtest GTest::gtest_main GTest::gmock GTest::gmock_main)

# Add test to ctest.
add_test(AllTests hello_test)