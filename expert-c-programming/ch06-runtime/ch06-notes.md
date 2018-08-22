Expert C Programming : Deep C Secrets
=====================================

Chapter 6 : Poetry in Motion -- Runtime Data Structures
-------------------------------------------------------

Most of the programming languages (like C) make the distinction between:
  * **code** : translated by the compiler
  * **data** : storage managed at runtime

### `a.out` and `a.out` Folklore
The name `a.out` comes from **assembler output**. But it is not assembler
output, it is linker output. The name was invented when there was no linker and
the name stayed.

Every `a.out` start with the same 4 bytes: `7f`, and the 3 letters `E`, `L` and
`F` (for Executable and Linking Format).

### Segments
* Segments = areas within a binary file where all the information of a
  particular type is kept.
* Sections = smallest units of organization in an ELF file. A segment typically
  contain several sections.

`size a.out` : tells the size of 4 segments (text/data/bss/dec) of executable.

BSS (Block Started by Symbol or Better Save Space) only holds variable that
don't have any value yet, so it does not store the image of these variables.
Data segment store the initialized (both global and static) variables.
Text segment store the executable instructions.


`nm a.out` : list all symbols in the executable. For each symbol, indicates the
segment it belongs to as well as the virtual memory address given by linker.

```C
/* source file                              a.out file */
                                      /* a.out magic number + other content */
char pear[40];                        /* into BSS segment, global */
static double peach;                  /* into BSS segment, local */

int mango = 13;                       /* into data segment, global */
static long melon = 2001;             /* into data segment, local */

main()
{
	  int i = 3, j, *ip;                /*  local variables, created at runtime */
    ip=malloc(sizeof(i));             /*  into text segment   */
	  pear[5] = i;                      /*            "         */
	  peach = 2.0*mango;                /*            "         */
}
```

* Using the debugging flag `-g` makes the executable size bigger but does not
  change the segment sizes.
* Using the optimization flag `-O3` can reduce the text segment size.
* When an array is defined inside a function (whether initialized or not), it
  does not change the size of data or bss segments, but increase the text
  segment size.
* When a global array is *initialized*, it will move the array from the BSS to
  the data segment and **increase** the executable size.

### What the OS Does with Your `a.out`
The running linker takes each segment (text, data, bss) and load them into
memory. The text segment contains the program instructions and is directly
copied from `a.out` to memory with `mmap()`. Then the same thing happens for
initialized variables from data segment. Then a zeroed block of the same size as
BSS is claimed by program. Finally, a block of memory is allocated for the stack
of the program. Everything is continuous in memory, from the text segment
(lowest address) to the stack (high address). A heap space is also dynamically
allocated on demand (like with a `malloc()` call).

When a shared library is also included into the executable, text and data
segments of the library are also loaded, but **after the text/data segment** of
the program (and there is a hole between the two).

### What the C Runtime Does with Your `a.out`

#### The Stack Segment
LIFO memory structure (like a stock of plates in restaurant). Only 2 ops :
**push** and **pop**. Three major uses :
* storage of *automatic* variables (local ones created inside functions)
* *stack frame* : information created when a function is called (parameters,
  jump-back address)
* temporary storage of *partial* expression evaluation

A stack is mainly required for **recursive calls**. Without them, everything
else (automatic variables, return address) could be determined at compile time
and included into BSS.

C runtime routines are lightweight (that's why it is an efficient language). C
creates a **procedure activation record** in the stack (a data structure) for
each call statement executed. In contains information to call a procedure (local
variables, arguments, pointer to previous frame).

Each time a function is called, a new procedure activation record (PAR) is
pushed on the stack. If a function is called recursively (like *factorial*),
each new call produce a new PAR (the stack grows). When it stops calling
functions, the PAR are unpiled thank to the *previous frame* pointer.
