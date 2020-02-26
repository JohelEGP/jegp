# [CMake][] buildsystem

[CMake]: https://cmake.org/

The project's name is `jegp`.
The library's target is `jegp::jegp`.

## Options

| Option          | Description                         | Default value |
| --------------- | ----------------------------------- | ------------- |
| `JEGP_TEST`     | Test the library.                   | `OFF`         |
| `JEGP_DOC_PDF`  | Make a PDF of the documentation.    | `OFF`         |
| `JEGP_DOC_HTML` | Generate HTML of the documentation. | `OFF`         |

## Build, test, install

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
