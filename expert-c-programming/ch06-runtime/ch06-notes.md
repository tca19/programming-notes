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

Sometimes PAR are stored in registers instead of stack (more efficient).

When using multithread, each thread gets a dedicated stack of 1Mb.

#### The `auto` and `static` keywords
*dangling pointer* : pointer to something that no longer exists, like the
address of a local variable of a function once the function has returned. The
pointer still exist but its content might be overwritten by the stack.

When a variable is defined as `static`, it will be allocated in the data
segment, not in the stack. The `auto` keyword is **never** needed (because it's
default behavior).

### Threads of Control
`longjmp` can jump out of a function (even if it is in a different file), `goto`
can't. `setjmp` and `longjmp` are mainly used to handle errors recovery.

```C

#include <stdio.h>
#include <setjmp.h>

jmp_buf buf;
int banana()
{
	  printf("in banana()\n");
	  longjmp(buf, 1);

	  printf("you'll never see this, because I longjmp'd");
}

int main(void)
{
	  if (setjmp(buf))
		    printf("back in main\n");
	  else
	  {
		    printf("first time through\n");
		    banana();
	  }
}
```

### The Stack Segment
#### Under UNIX
The stack grows automatically and (almost) indefinitely. When the user try to
access an address **outside** the allocated stack, the hardware send a *page
fault* signal. The kernel either stops the program with `Segmentation fault` or
increase the stack size.

#### Under MS-DOS
Size if specified at compile time. If program uses more memory than the stack
size => **STACK OVERFLOW**.

### Helpful C Tools
* `ldd` : print the dynamic libraries used by an executable
* `nm` : print the symbol table of an executable
* `strings` : print the strings embedded into executable
* `gdb` : debugger. Need to compile with the `-g` flag
* `time` : measure total and CPU time used by a program

> You can use the hex constants `deadbeef` and `abadcoffee` in your code

At Carnegie-Mellon University, a programming contest was organized for incoming
graduate students. The winner was the person who produced the fastest `read and
process all the numbers of this file`. The best program was smashing the stack
to overwrote the CPU time with a large value leading the OS misinterpreting it
as a negative value (hence a negative execution time). The second best one was
computing the result, writing the result to a file and read back this value
during the second submission eval (several submissions were accepted and the one
with the smaller execution time was kept). These hacks caused the competition to
be cancelled for the following years.

### Assembly in C
It is possible to embed assembly code into C code with the keywords `asm` or
`__asm__`.

```C
/* copy src to dst; add 1 to dst */
int src = 1;
int dst;

asm ("mov %1, %0\n\t"
    "add $1, %0"
    : "=r" (dst)
    : "r" (src));

printf("%d\n", dst);
```
