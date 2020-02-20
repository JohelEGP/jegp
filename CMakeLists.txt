cmake_minimum_required(VERSION 3.14.0)
project(jegp
    VERSION 4.0.0
    DESCRIPTION "Generic library components for JohelEGP's C++ projects."
    HOMEPAGE_URL https://github.com/johelegp/jegp
    LANGUAGES CXX)

list(APPEND CMAKE_MODULE_PATH ${CMAKE_CURRENT_SOURCE_DIR}/cmake/)
include(JEGPOptions)
include(JEGPFindDependencies)

add_library(jegp INTERFACE)
add_library(jegp::jegp ALIAS jegp)
target_compile_features(jegp INTERFACE cxx_std_17)
target_link_libraries(jegp INTERFACE range-v3::concepts)
target_include_directories(jegp INTERFACE
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
    $<INSTALL_INTERFACE:include>)

install(TARGETS jegp EXPORT jegp-targets)

export(EXPORT jegp-targets NAMESPACE jegp::)
file(COPY cmake/jegp-config.cmake DESTINATION .)
include(CMakePackageConfigHelpers)
write_basic_package_version_file(jegp-config-version.cmake
    VERSION ${jegp_VERSION}
    COMPATIBILITY SameMajorVersion)

install(EXPORT jegp-targets
    DESTINATION lib/cmake/jegp
    NAMESPACE jegp::)
install(
    FILES
        cmake/jegp-config.cmake
        ${CMAKE_CURRENT_BINARY_DIR}/jegp-config-version.cmake
    DESTINATION lib/cmake/jegp)
install(DIRECTORY include/ DESTINATION include)

include(CTest)
if(BUILD_TESTING AND JEGP_TEST)
    add_subdirectory(test)
endif()
