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
    GIT_SHALLOW True)

list(APPEND CMAKE_MODULE_PATH "${jegp_cmake_modules_SOURCE_DIR}")
