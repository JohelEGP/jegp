include(FetchContent)
FetchContent_Declare(
    CPM
    GIT_REPOSITORY https://github.com/TheLartians/CPM.cmake
    GIT_TAG master
    GIT_SHALLOW True)
FetchContent_MakeAvailable(CPM)
include(${cpm_SOURCE_DIR}/cmake/CPM.cmake)

CPMFindPackage(
    NAME jegp_cmake_modules
    GITHUB_REPOSITORY johelegp/jegp.cmake_modules
    GIT_TAG master
    GIT_SHALLOW True)

list(APPEND CMAKE_MODULE_PATH "${jegp_cmake_modules_SOURCE_DIR}")
