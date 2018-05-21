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
declared is exited. _Objects declared at the same level as function definitions
are always static_. Identifiers preceeded by the ̣̣`extern` keyword are available
to the whole program (external linkage).

`unsigned char` consumes the same amount of space as `signed char` and `char`.
The _derived_ types are : arrays, functions, pointers, structures and unions.
Object = named region of storage; lvalue = expression referring to an object.


