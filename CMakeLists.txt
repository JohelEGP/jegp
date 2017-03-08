cmake_minimum_required(VERSION 3.7.0)

project(jegp VERSION 3.0.0 LANGUAGES CXX)

add_library(jegp INTERFACE)
target_include_directories(jegp INTERFACE
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
    $<INSTALL_INTERFACE:include>
)
set_property(TARGET jegp APPEND PROPERTY
    COMPATIBLE_INTERFACE_STRING jegp_VERSION_MAJOR)

if (CMAKE_VERSION VERSION_GREATER_EQUAL 3.8.0)
    target_compile_features(jegp INTERFACE cxx_std_17)
else()
    target_compile_options(jegp INTERFACE -std=c++1z)
endif()

find_package(Boost.Hana QUIET)
if (Boost.Hana_FOUND)
    target_link_libraries(jegp INTERFACE hana)
else()
    find_package(Boost 1.61.0 REQUIRED)
    target_link_libraries(jegp INTERFACE Boost::boost)
endif()

install(TARGETS jegp EXPORT jegpConfig)
install(DIRECTORY include/ DESTINATION include)

include(CMakePackageConfigHelpers)
write_basic_package_version_file(jegpConfigVersion.cmake
    VERSION ${jegp_VERSION}
    COMPATIBILITY SameMajorVersion)

install(EXPORT jegpConfig DESTINATION cmake)
install(FILES ${CMAKE_CURRENT_BINARY_DIR}/jegpConfigVersion.cmake
    DESTINATION cmake)

export(EXPORT jegpConfig FILE jegpConfig.cmake)
