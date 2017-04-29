cmake_minimum_required(VERSION 3.3.0)

project(jegp VERSION 3.2.0 LANGUAGES CXX)

add_library(jegp INTERFACE)
target_include_directories(jegp INTERFACE
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
    $<INSTALL_INTERFACE:include>
)

if (NOT 3.8.0 VERSION_GREATER CMAKE_VERSION)
    target_compile_features(jegp INTERFACE cxx_std_17)
else()
    target_compile_options(jegp INTERFACE -std=c++1z)
endif()

include(${CMAKE_CURRENT_SOURCE_DIR}/cmake/find_dependencies.cmake)
target_link_libraries(jegp INTERFACE
    $<$<BOOL:${Boost.Hana_FOUND}>:hana>
    $<$<NOT:$<BOOL:${Boost.Hana_FOUND}>>:Boost::boost>
    type_safe)

install(TARGETS jegp EXPORT jegpTargets)
install(DIRECTORY include/ DESTINATION include)

include(CMakePackageConfigHelpers)
write_basic_package_version_file(jegpConfigVersion.cmake
    VERSION ${jegp_VERSION}
    COMPATIBILITY SameMajorVersion)

export(EXPORT jegpTargets)
file(COPY cmake/ DESTINATION .)

install(EXPORT jegpTargets DESTINATION lib/cmake/jegp)
install(DIRECTORY cmake/   DESTINATION lib/cmake/jegp)
install(FILES ${CMAKE_CURRENT_BINARY_DIR}/jegpConfigVersion.cmake
    DESTINATION lib/cmake/jegp)
