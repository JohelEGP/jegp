include(JEGPTestUtilities)

jegp_add_header_test()
jegp_add_test(
    utility COMPILE_ONLY
    COMPILE_OPTIONS $<$<CXX_COMPILER_ID:Clang,AppleClang>: -Wno-missing-braces
                    -Wno-inaccessible-base>)
