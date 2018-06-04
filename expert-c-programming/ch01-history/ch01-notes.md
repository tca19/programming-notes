Expert C Programming : Deep C Secrets
=====================================

Introduction
------------
`time_t` is represented with a `long`. The `ctime()` function format a `time_t`
variable to a string representin the **local** date. To print the GMT date :
`asctime(gmtime(time_t *))`.

Chapter 1 : C Through the Mists of Time
---------------------------------------

### The Prehistory of C
> C is quirky, flawed and an enormous success. -- *Dennis Ritchie*

Story of C begins in 1969 with the failure of the Multics project (creation of
an OS). It failed because it was too big to run on too small hardware. Ken
Thompson created in 1970 the much lighter OS **UNIX** (opposite of _Multics_),
showing that **small is beautiful**. UNIX was at first written in assembler.

> This is why UNIX time is measured since January 1, 1970 -- that's when time
> began.

> Performance is *almost* everything.

Compiler performances has 2 aspects : how fast the code runs and how long it
takes to compile. Runtime performances usually dominates so compilers have many
optimizations, but a too agressive optimization can lead to code producing wrong
results. So performance is not everyhing.

C was created after Thompson has reimplemented UNIX in assembler for PDP-11.
Ritchie created "a new B" (C) because B was typeless and PDP-11 hardware had
support for datatypes.

### Early Experiences with C
* Arrays start at 0 rather than 1 : compiler-writers are used to think in terms
  of offset.
* Types map directly onto underlying hardware (int, float)
* `auto` keyword is useless (variables declared in block are automatic by
  default)
* `float` _were_ expanded to `double` (PDP-11 hardware could only do `float` or
  `double`, not the two at the same time; need a reset to switch mode)

### The Standard I/O Library and C Preprocessor
I/O is not defined within C, but provided by libraries (so manual is smaller and
laguage is faster to learn). The C preprocessor has 2 main purposes : - macro
replacement; - inclusion of files. Better to define macro names in upper case so
it is no confused with function names.

> The UNIX Version 7 shell was written by Steve Bourne. The shell does not used
> `malloc`, but has its own storage management with `sbrk` making the code much
> harder to maintain.

### K&R C
* 1972-73: early C (addding keywords like `unsigned` and `long` to match new
  hardware)
* 1976-79: K&R C (published in 1978)
* 1983-89: ANSI C
* 1985-89: C++

### The Present Day: ANSI C
ANSI C is defined in a 200 pages manual. People should work with ANSI C, not K&R
C. ANSI C was finally adopted in 1989.

### It's Nice, but Is It Standard ?
When something is written as _implementation defined_ or _unspecified_, the code
is unportable. If something is _undefined_ or violating a _constraint_, the code
is bad.\
A _strictly-conforming_ program :
* only uses _specified features_
* has no output that depends on _implementation-defined_, _unspecified_ or
  _undefined_ features.

Differences between K&R C and ANSI C ?
* function prototype with parameter types
* new keywords ẹ̣̣̣̣̣̣̣̣̣̣̣̣̣`enum, const, signed, void`.
* adjacent strings are concatenated

It's better to leave parameter names in function signatures, they contain
_semantic_ information (`char *strcpy(char *dest, const char *src)`).

`const char**` and `char **` are incompatible types : the first one is a pointer
to a pointer to a qualified type (because of `const`). The second one is a
pointer to a pointer to an unqualified type.

A `const` variable can be modified via pointers but not via identifie. Mostly
useful to indicate a function tha takes a `const` poointer will not modify the
pointer value ("i am giving you a pointer to this thing, but you may not change
it").

ANSI C add more conversion rules (if one operand is `double`, convert the other
one to `double`, if one is `long` ...)

In `(-1 < sizeof(ar) / sizeof(ar[0]))` can be evaluated as true. `sizeof` type
is unsigned, so `-1` is promoted to unsigned, which yields a very big positive
integer. This can occur in ANSI C. Add an `(int)` before the first `sizeof` so
no promotion to unsigned happens.

> Don't use an `unsigned` type to represent a quantity just because it will
> never be negative (no hidden promotion with mixed types).
> Only use `unsigned` for bitfields or binary masks.

> Original meaning of **hacker** : a gifted programmer.

The **F**ree **S**oftware **F**oundation (founded by Richard Stallman) has the
ambition to create a public-domain implementation of UNIX called GNU. Some of
the best products developed by the FSF are **gcc** and **gdb**. The `#pragma`
command was specified by ANSI to have an implementation-defined effect, so
developers of **gcc** decided to launch a game everytime it encounters the
command in source code.
