The C programming language (K&R, 2nd edition)
=============================================

Appendix A : Reference Manual
-----------------------------

6 classes of tokens :
* indentifiers (sequence of letters and digits)
* keywords (`auto`, `break`, `case`, `char`...)
* constants (integer, character, floating, enumeration)
* string literals (sequence of characters wrapped by `"`)
* operators
* other separators

Integer constants can be suffixed by `u` or `U` to specify it is unsigned, or
`l` or `L` to specify it is a long. Character constants can be octal or
hexadecimal numbers (`\ooo` or `\xhh`). Floating constants can be suffixed by
`f`, `F` to indicate it is a float, `l` or `L` to indicate it is a long double.

Adjacent string literals like `"hello" " world"` are concatenated and a NUL
character (`\0`) is appended to the concatenated string. `wchar_t` is a wide
character.

An object (also called a variable) has two main attributes :
* a storage class : lifetime of associated storage, automatic or static
* a type

Automatic variables only live inside the block where they are declared. Static
variables (`static`) continue to live even after the block where they are
declared is exited.
