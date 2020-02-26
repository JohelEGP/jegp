include(ExternalProject)

ExternalProject_Add(draft-jegp
    GIT_REPOSITORY https://github.com/johelegp/draft.git
    GIT_TAG jegp
    GIT_SHALLOW ON
    CONFIGURE_COMMAND ""
    BUILD_COMMAND ""
    INSTALL_COMMAND "")

ExternalProject_Add_Step(draft-jegp copy-sources
    DEPENDEES download
    COMMAND ${CMAKE_COMMAND} -E copy_directory
        ${CMAKE_CURRENT_SOURCE_DIR} <SOURCE_DIR>/source/)

if(JEGP_DOC_PDF)
    ExternalProject_Add_Step(draft-jegp make-pdf
        DEPENDEES copy-sources
        COMMAND ${CMAKE_COMMAND} -E chdir <SOURCE_DIR>/source/ make
        COMMAND ${CMAKE_COMMAND} -E copy
            <SOURCE_DIR>/source/std.pdf ${CMAKE_CURRENT_SOURCE_DIR}/jegp.pdf)
    return()
endif()
