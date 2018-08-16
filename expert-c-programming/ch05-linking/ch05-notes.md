Expert C Programming : Deep C Secrets
=====================================

Chapter 5: Thinking of Linking
------------------------------

> Program testing can be used to show the presence of bugs but never to show
> their absence. -- Dijkstra, 1972

### Libraries, Linking, and Loading
Compilers are in fact composed of many smaller programs (preprocessor,
syntactic/semantic checker, the assembler, the optimizer...), mainly because it
is easier to maintain many smaller files rather than a single large program.

`cc` can pass flags specifically to a compilation step with `-W` and then a
letter representing the step (for example, the code generator step is
represented by the letter `c` so that would give `cc -Wc,-m main.c` to pass the
flag `-m` only for this step).

**Linking**: action of converting object files to executables. The linker
identifies the main routine (starting point of program), maps symbols to memory
addresses, regroups all the object files and integrates the required libraries
to produce the executable.

* **Static linking**: add a copy of library binaries (used to call BIOS routines
  of machine) into each generated executable. Use the ̣`.a` files.
* **Dynamic linking**: store the binary libraries into system, the program will
  include the filename of these libraries so it can look for them at runtime. No
  need to add them into the executable. Use the `.so` files.

The **runtime loader** does not load libraries until a call from this library
happens at run time so *there's no penalty to linking against a library that you
may not call*.  Dynamic linking is now the norm as it can drastically reduce the
executable size (e.g. 506kB as 5kB).

Dynamic linking trades off more efficient use of the disk and a quicker
link-edit phase for a small runtime penalty (since some of the linker's work is
deferred until loadtimes).

Dynamic linking has two main advantages:
* smaller executables (less disk and virtual memory usage), only a part of a
  library is loaded (instead of the whole library).
* the kernel only loads the library once into memory, but multiple processes
  share and use it (instead of each one having its own); better I/O, improve
  system throughput
* when new version of libraries are installed into the system, executables
  automatically get the benefit, no need of relinking

Dynamic linking adds the path of needed libaries. But if the name or location of
the lib changed, there will be an error when the programm will be run. To create
a library, simply compile code without a main routine and process the resulting
`.o` with `ar` or `ld`.
