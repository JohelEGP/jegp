include(CMakeFindDependencyMacro)

find_dependency(range-v3 0.10.0)

include(${CMAKE_CURRENT_LIST_DIR}/jegp-targets.cmake)

add_library(jegp::jegp INTERFACE IMPORTED)
target_link_libraries(jegp::jegp INTERFACE jegp)
