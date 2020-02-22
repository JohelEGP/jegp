# JEGP library

Generic library components for JohelEGP's C++ projects.

## Documentation

The public API is in [doc/](doc/).
It abides to [Semantic Versioning 2.0.0](https://semver.org/),
with the versions being [git tags](
https://github.com/johelegp/jegp/releases).

### Compatibility

[SD-8][] states the rights the JEGP library reserves for itself.

[SD-8]:
https://isocpp.org/std/standing-documents/sd-8-standard-library-compatibility
"SD-8: Standard Library Compatibility"

No guarantee of ABI stability is made.

## [CMake][] buildsystem

[CMake]: https://cmake.org/

The project's name is `jegp`.
The library's target is `jegp::jegp`.

### Options

| Option      | Description                       | Default value |
| ----------- | --------------------------------- | ------------- |
| `JEGP_TEST` | Whether to test the JEGP library. | `OFF`         |

### Build, test, install

Run [these commands](
https://gist.github.com/johelegp/65cbb2ffdb815c8ebce22ae847ab76b1
"How to portably build, test and install modern CMake projects")
(reproduced below)
from the root of your project's clone.

```
cmake -E make_directory build
cmake -E chdir build cmake .. -DJEGP_TEST=ON
cmake --build build
cmake -E chdir build ctest
cmake --install build
```
