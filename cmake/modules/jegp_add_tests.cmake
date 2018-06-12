if(NOT BUILD_TESTING)
    return()
endif()

function(jegp_add_test name)
    add_executable(test_${name} test/${name}.cpp)
    target_compile_options(test_${name} PRIVATE ${ARGN})
    target_link_libraries(test_${name} PRIVATE jegp::jegp)
    add_test(jegp_test_${name} test_${name})
endfunction()

jegp_add_test(include_utility)
jegp_add_test(all_includes)
jegp_add_test(utility
    $<$<CXX_COMPILER_ID:Clang>:-Wno-missing-braces -Wno-inaccessible-base>)
