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
