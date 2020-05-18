if(NOT EXISTS ${CMAKE_CURRENT_LIST_DIR}/CPM.cmake)
    message(STATUS "Downloading CPM.cmake")
    file(DOWNLOAD
         https://github.com/TheLartians/CPM.cmake/raw/master/cmake/CPM.cmake
         ${CMAKE_CURRENT_LIST_DIR}/CPM.cmake)
endif()

include(CPM)

CPMFindPackage(
    NAME jegp_cmake_modules
    GITHUB_REPOSITORY johelegp/jegp.cmake_modules
    GIT_TAG master
    GIT_SHALLOW True)
CPMFindPackage(
    NAME range-v3
    GITHUB_REPOSITORY ericniebler/range-v3
    GIT_TAG master
    GIT_SHALLOW True
    DOWNLOAD_ONLY True)

list(APPEND CMAKE_MODULE_PATH "${jegp_cmake_modules_SOURCE_DIR}")

if(range-v3_ADDED)
    add_library(range-v3::range-v3 INTERFACE IMPORTED GLOBAL)
    target_include_directories(range-v3::range-v3
                               INTERFACE ${range-v3_SOURCE_DIR}/include)
endif()
