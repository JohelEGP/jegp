include(FetchContent)

FetchContent_Declare(range-v3
    GIT_REPOSITORY https://github.com/ericniebler/range-v3.git
    GIT_TAG 0.4.0
    GIT_SHALLOW True)

FetchContent_GetProperties(range-v3)
if(NOT range-v3_POPULATED)
    find_package(range-v3 0.4.0 QUIET)
    if(NOT range-v3_FOUND)
        FetchContent_Populate(range-v3)
        add_subdirectory(${range-v3_SOURCE_DIR} ${range-v3_BINARY_DIR})
    endif()
endif()

if(range-v3_FOUND)
    set(JEGP_DEPENDENCIES_IMPORTED TRUE)
endif()
