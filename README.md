# JEGP

Generic library components for my C++ projects.

## Specification

This project uses [Semantic Versioning 2.0.0](http://semver.org/).
The public API is in the [doc](doc) directory,
starting at [doc/intro.md](doc/intro.md).

### JEGP library compatibility

TBD.

## Getting started

JEGP is a header-only library.
[CMake](#cmake) is the primary way of depending on it.

### Dependencies

This project uses C++17.
CMake takes care of the following missing dependencies.

- [Range v3](https://github.com/ericniebler/range-v3)

### Installation

Execute these commands from the root of your project's clone
to configure, build and install the library:

    cmake -E make_directory build
    cmake -E chdir build cmake ..
    cmake --build build --target install

### Testing

All testing is done at compile-time.
The lack of compile-time errors after building the library
means that the tests passed.

### CMake

The JEGP library doesn't impose how it can become a dependency.
You can use `find_package` (if installed or by defining `jegp_DIR`),
`add_subdirectory` (to an existing clone or a git submodule),
and, by extension, `FetchContent` and `ExternalProject`.
The simplest way is installing it so that it can be used like:

    find_package(jegp)
    target_link_libraries(<your_target> jegp::jegp)
