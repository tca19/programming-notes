Expert C Programming : Deep C Secrets
=====================================

Chapter 6 : Poetry in Motion -- Runtime Data Structures
-------------------------------------------------------

Most of the programming languages (like C) make the distinction between:
  * code : translated by the compiler
  * data : storage managed at runtime

### `a.out` and `a.out` Folklore
The name `a.out` comes from **assembler output**. But it is not assembler
output, it is linker output. The name was invented when there was no linker and
the name stayed.

Every `a.out` start with the same 4 bytes: `7f`, and the 3 letters `E`, `L` and
`F`.
