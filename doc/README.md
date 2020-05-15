# Documentation

The public API is at https://johelegp.github.io/jegp/.
It abides to [Semantic Versioning 2.0.0](https://semver.org/),
with the versions being [git tags](
https://github.com/johelegp/jegp/releases).

## Compatibility

[SD-8][] states the rights the JEGP library reserves for itself.

[SD-8]:
https://isocpp.org/std/standing-documents/sd-8-standard-library-compatibility
"SD-8: Standard Library Compatibility"

No guarantee of ABI stability is made.

## Make PDF

1. Follow the "Getting Started" at https://github.com/cplusplus/draft.

2. Set `JEGP_DOC_PDF` `ON` when generating the project.

## Generate HTML

1. Meet the prerequisites at https://github.com/Eelis/cxxdraft-htmlgen.
Optionally see the "sectionfilestyle".

2. Set `JEGP_DOC_HTML` to `ON` or a "sectionfilestyle"
when generating the project.
