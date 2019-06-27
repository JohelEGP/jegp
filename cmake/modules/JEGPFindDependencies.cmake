include(FetchContent)

FetchContent_Declare(jegp_cmake_modules
    GIT_REPOSITORY https://github.com/johelegp/jegp.cmake_modules
    GIT_SHALLOW True)
FetchContent_Declare(range-v3
    GIT_REPOSITORY https://github.com/ericniebler/range-v3.git
    GIT_TAG master
    GIT_SHALLOW True)

FetchContent_MakeAvailable(range-v3 jegp_cmake_modules)

FetchContent_GetProperties(jegp_cmake_modules)
list(APPEND CMAKE_MODULE_PATH "${jegp_cmake_modules_SOURCE_DIR}")
