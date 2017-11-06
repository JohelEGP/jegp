cmake_minimum_required(VERSION 3.8.0)
project(jegp VERSION 3.2.0 LANGUAGES CXX)

find_package(BCM)
include(BCMDeploy)

add_library(jegp INTERFACE)
add_library(jegp::jegp ALIAS jegp)

find_package(Boost 1.61.0 REQUIRED)
find_package(type_safe REQUIRED)

target_compile_features(jegp INTERFACE cxx_std_17)
target_link_libraries(jegp INTERFACE
    Boost::boost
    type_safe)

bcm_deploy(TARGETS jegp
    INCLUDE include
    NAMESPACE jegp::
    COMPATIBILITY SameMajorVersion)
