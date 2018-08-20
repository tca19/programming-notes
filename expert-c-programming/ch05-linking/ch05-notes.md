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

Dynamic linking trades off more **efficient use of the disk** and a quicker
link-edit phase for a **small runtime penalty** (since some of the linker's work
is deferred until loadtimes).

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

**PICode** : position-independent code (for libraries). Every global data in the
code are accessed with an extra indirection (an offset or a pointer). At
runtime, the offset can be changed to still be able to access such data. Useful
for shared libraries.

### Five Special Secrets of Linking with Libraries (you need to master)
1. Dynamic libraries = ̣̣̣̣̣`lib*.so`, static libraries = `lib*.a`
2. Link with `libthread.so` with `-lthread` flag (`-lname` for `libname.so`)
3. Compiler looks for libraries into `/usr/lib/`. Another location can be
   indicated with `-Lpathname` and `-Rpathname` (the latter for runtime path)
4. For some `#include`, you need to add compiler flags (`-lm` for `<math.h>`,
   `-lthread` for `<thread.h>`). `<stdio.h>` rely on `libc.so` and is
   automatically linked during compilation.
5. With dynamic libraries, **all** the symbols are available at runtime (loaded
   into virtual address space). With static libraries, only load the **undefined
   symbols**. Furthermore, add the linking flags **at the end** of compilation
   command (like `cc main.c -lm`). Source files are read from left to right. If
   the libary is put before the written code, there won't be any undefined
   symbols so nothing will be extracted at linkink time.

### Watch Out for Interpositioning
Interpositioning : the practice of replacing a library function by a
user-written function of the same name (for performance or debugging purpose).

**This is dangerous** : if the user redefines a function (like `mktemp()`), all
library functions relying on this function will call the user defined one
instead of the original one from the library. The problem occurs because of
the **default global scope** of functions. To solve it, user declared functions
should be **static**.

Use `ldd name_of_executable` to know the dynamic dependencies of a dynamically
linked executable.

### Challenging the Turing Test
The test has been created by Alan Turing in 1950. Eliza, created in 1956 was
able to fool the secretary the doctor who created it. It barely look at the user
input and return one of the pre-built answer accordingly. It was even able to
fool the vice-president of Telcomp. Making two of these systems talking to each
other results in complete non-sense. The program is unable to answer a question.

> The reason it fools people is not because it is intelligent and thus passing
> the Turing test. It fools people because people are too easy to fool and thus
> the test is inadequate.

> The central weakness in the Turing test: simply exchanging semi-appropriate
> phrases does not indicate thought -- we have to look at the content of what is
> communicated.

Turing was a brilliant theoretician but was often hopeless when it came to
practical matters. He bought two silver ingots, hid them but then was unable to
remember their location. He killed himself by eating an apple that he had
injected with cyanide.

> The Turing test is a triump of theory over practical experience. The
> difference between theory and practice is a lot bigger in practice than in
> theory.

In 1983, the Turing Award was given to Dennis Ritchie and Ken Thompson in
recognition of their work on UNIX and C.
