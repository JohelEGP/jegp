include(FetchContent)

FetchContent_Declare(range-v3
    GIT_REPOSITORY https://github.com/ericniebler/range-v3.git
    GIT_TAG master
    GIT_SHALLOW True)

FetchContent_MakeAvailable(range-v3)

if(range-v3_FOUND)
    set(JEGP_DEPENDENCIES_IMPORTED TRUE)
endif()
