include(FetchContent)

FetchContent_Declare(range-v3
    GIT_REPOSITORY https://github.com/ericniebler/range-v3.git
    GIT_SHALLOW True)

find_package(range-v3 0.3.6 QUIET)
if(NOT range-v3_FOUND)
    FetchContent_GetProperties(range-v3)
    if(NOT range-v3_POPULATED)
        FetchContent_Populate(range-v3)
        add_subdirectory(${range-v3_SOURCE_DIR} ${range-v3_BINARY_DIR})
    endif()
endif()

if(range-v3_FOUND)
    set(JEGP_DEPENDENCIES_IMPORTED TRUE)
endif()
