include(FetchContent)
FetchContent_Declare(
    CPM
    GIT_REPOSITORY https://github.com/TheLartians/CPM.cmake
    GIT_TAG v0.35.6
    GIT_SHALLOW True)
FetchContent_MakeAvailable(CPM)
include(${cpm_SOURCE_DIR}/cmake/CPM.cmake)

CPMAddPackage("gh:johelegp/jegp.cmake_modules#master")

list(APPEND CMAKE_MODULE_PATH "${jegp.cmake_modules_SOURCE_DIR}/modules")
