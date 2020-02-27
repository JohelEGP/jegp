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
    DEPENDS
        ${CMAKE_CURRENT_SOURCE_DIR}/intro.tex
        ${CMAKE_CURRENT_SOURCE_DIR}/utilities.tex
    COMMAND ${CMAKE_COMMAND} -E copy_directory
        ${CMAKE_CURRENT_SOURCE_DIR} <SOURCE_DIR>/source/)

if(JEGP_DOC_PDF)
    ExternalProject_Add_Step(draft-jegp make-pdf
        DEPENDEES copy-sources
        BYPRODUCTS ${CMAKE_CURRENT_SOURCE_DIR}/jegp.pdf
        COMMAND ${CMAKE_COMMAND} -E chdir <SOURCE_DIR>/source/ make
        COMMAND ${CMAKE_COMMAND} -E copy
            <SOURCE_DIR>/source/std.pdf ${CMAKE_CURRENT_SOURCE_DIR}/jegp.pdf)
endif()

if(NOT JEGP_DOC_HTML)
    return()
endif()

ExternalProject_Add_Step(draft-jegp copy-sources-back
    DEPENDEES copy-sources
    COMMAND ${CMAKE_COMMAND} -E copy_directory
        <SOURCE_DIR>/source/ ${CMAKE_CURRENT_SOURCE_DIR})

ExternalProject_Add(cxxdraft-htmlgen-jegp
    GIT_REPOSITORY https://github.com/johelegp/cxxdraft-htmlgen.git
    GIT_TAG jegp
    GIT_SHALLOW ON
    CONFIGURE_COMMAND ""
    BUILD_COMMAND ${CMAKE_COMMAND} -E chdir <SOURCE_DIR> stack build
    INSTALL_COMMAND ""
    DEPENDS draft-jegp)

if(${JEGP_DOC_HTML})
    set(JEGP_DOC_HTML WithExtension CACHE)
endif()

ExternalProject_Add_Step(cxxdraft-htmlgen-jegp generate-html
    DEPENDEES build
    COMMAND ${CMAKE_COMMAND} -E chdir <SOURCE_DIR>
        stack exec cxxdraft-htmlgen ${CMAKE_CURRENT_SOURCE_DIR} ${JEGP_DOC_HTML})

ExternalProject_Add_Step(cxxdraft-htmlgen-jegp copy-html-back
    DEPENDEES generate-html
    COMMAND ${CMAKE_COMMAND} -E copy_directory
        <SOURCE_DIR>/14882/ ${CMAKE_CURRENT_SOURCE_DIR}/jegp/)
