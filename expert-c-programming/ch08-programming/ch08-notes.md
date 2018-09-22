Expert C Programming : Deep C Secrets
=====================================

Chapter 8 : Why Programmers Can't Tell Halloween from Christmas Day
-------------------------------------------------------------------

### The Potrzebie System of Weigths and Measures
Donald Knuth wrote *The Art of Computer Programming* and designed the TeX
typesetting system.

31 in octal is 25 in decimal, hence `OCT 31 = DEC 25` and programmers can't tell
the difference between Halloween and Christmas day. Moreover, `OCT 31 = NOV 27`.

### Making a Glyph from Bit Patterns
A black and white icon can be represented as series of integers, if we represent
black pixels with the value 1 and white ones with 0. In a program, these
integers correspond to the value of the bit pattern (like `10110` for `0x16`).
Some `#define` macros can help to represent hex values as an ascii art (see page
176 of the book).

### Types Changed While You Wait
The code `printf(" %d ", sizeof 'A');` will print `4` because `'A'` is an
integer (a character literal). In an expression, `char`, `short`, `enum` are
promoted to `int`, `float` are promoted to `double`. This also happens for
function arguments (type widening).

In ANSI C, arguments are not promoted if a prototype is used. In `printf`, `%d`
works for `int`, `short` and `char`. It is easier for the compiler to convert
every type to `int` : it no longer need to know the size of each argument, only
the number of them (when retrieving from the stack).

### Prototype Painfulness
Prototypes are intended to reduce the number of mismatch between formal and
actual parameter types. With ANSI C, a function definition is now : `int
foot(int a, int b) { ... }` instead of `int foo(a, b) int a; int b; { ... }`.
The declaration of function also indicates the type of each argument.

In ANSI C, to express that a function does not take any argument, it needs the
`void` keyword (`int foo(void)`). When there is no `void`, like `int foo()` it
is considered to be a declaration prototype in K&R style (number and type of
arguments where not mandatory in declarations).

With old K&R protoptypes, promoted types are passed (even if an argument is
defined as a `char`, an `int` was passed when the function is called. **If the
declaration style is different from the definition style (K&R vs ANSI), it will
fail. One expect the promoted type, the other one the actual type.**

Function prototypes (declarations) should be placed in `.h` files and include in
the same file containing the definition. That way, the compiler sees both at
once and can detect mismatch.

### Getting a Char Without a Carriage Return
On UNIX, terminal input is read line by line (because it needs to be
preprocessed before being passed to runing program) so user needs to press
RETURN to send text to program.
