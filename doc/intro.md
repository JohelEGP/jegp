# Scope                                                                  [scope]

This document specifies the public API of the _JEGP library_.

# References                                                              [refs]

The following documents are referred to in the text
in such a way that some or all of their content
constitutes requirements of this document.

- ISO/IEC 14882:2020, _Programming Languages -- C++_

ISO/IEC 14882 is herein called the _C++ Standard_.

# Introduction                                                           [intro]

## General                                                       [intro.general]

The library specification subsumes the C++ Standard's [library],
assumingly amended to the context of this library.
[ _Example:_
- Per C++ Standard's [namespace.future], `::jegp2` is reserved.
- Per C++ Standard's [contents]#3, a name `x` means `::jegp::x`.
-- _end example_ ]

   Library categories      [tab:intro.general]

   | Clause      | Category                  |
   | ----------- | ------------------------- |
   | [utilities] | General utilities library |

## Library-wide requirements                                      [requirements]

### Library contents                                                  [contents]

Whenever a name is qualified with `X::`,
`::X::` is meant,
where `X` is any identifier.

### Reserved names                                              [reserved.names]

The JEGP library reserves macro names starting with `JEGP_`.
