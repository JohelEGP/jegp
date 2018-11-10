function(jegp_add_test name)
    add_executable(jegp_test_${name} test/${name}.cpp)
    target_compile_options(jegp_test_${name} PRIVATE ${ARGN})
    target_link_libraries(jegp_test_${name} PRIVATE jegp::jegp)
    add_test(jegp_test_${name} jegp_test_${name})
endfunction()

jegp_add_test(include_utility)
jegp_add_test(all_includes)
jegp_add_test(utility
    $<$<OR:$<CXX_COMPILER_ID:Clang>,$<CXX_COMPILER_ID:AppleClang>>:
        -Wno-missing-braces -Wno-inaccessible-base>)
