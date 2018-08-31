Expert C Programming : Deep C Secrets
=====================================

Chapter 7 : Thanks for the Memory
---------------------------------

### The Intel 80x86 Family
Intel created the Intel 4004 (4-bit microcontroller) in 1970. It was a
general-purpose chip (not specialized for each different customer). In 1974, the
8080 8-bit was created (first to be called a microcomputer). The processors at
this time were using 16-bit addresses, so at most 2^16 = 64 Kbytes of memory.
The 8086 came in 1978, with 16-bit data bus and 20-bit addresses (at most
1Mbytes of memory). In 1979, IBM selected an Intel chip in their PC, making the
fortune of Intel. The same goes for the selected OS, MS-DOS (Microsoft). In
fact, Bill Gates bought QDOS (Quick and Dirty OS, Seattle computer), cleaned it
and rebranded it as MS-DOS.

The 8086 overlaps two 16-bit words (one called the offset, the other called the
segment) to create a 20-bit address. Concatenating them would allow 32-bit
addresses (4BG of memory) but was considered overkill at the time.

Then followed a series of new processor under the names 80x86 (the letter x was
replaced by digits, making 80186, 80286, ... until 80486. There is no 80586,
this one is called Pentium).

Modern Pentium is a descendant of the 8086 and is backward compatible with it,
meaning that programs compiled for a 8086 will run on a Pentium.

### The Intel 80x86 Memory Model and How It Got That Way
A segment can either be a section of related stuff in a binary or a 64 KB range
in the address space of x86 memory.

When the 8086 overlaps two 16-bit words:
  * it goes to the right segment (a 64 KB region) using the segment register and
    shifting it by 4 places (or appending four 0)
  * goes to the right address within this segment using the offset (i.e. it adds
    the offset)

The 8086 has 16 region of 64KB memory (16 * 64KB = 1024KB) but 6 are for the
system, leaving only 10 (640KB) for the applications. In comparison, the first
PC came with only 16KB as standard.

2^10: kilo; 2^20: Mega; 2^30: Giga; 2^40: Tera; 2^64: 18 billion billion

With 2^64 addresses, it could be possible to store 36 million of 500GB files.
The challenge is not about memory *capacity* but about memory *speed*. There is
an increasing gap between memory and CPU performance : when the CPU speed is
multiplied by 2 every 1.5 years, memory access time only increases by 10%.

The 8086 memory uses *real-addresses* and every applications run with unlimited
privileges. There would not be so many PC viruses if MS-DOS used the memory and
task protection hardware built into every 80x86 processors.

### Virtual Memory
Virtual memory = using disk space to extend memory. When regions of memory lie
untouched for a while, they are likely to be saved on the disk, freeing up some
memory space. At first, this operation was done manually. This is called
*multilevel store*. The same things happens with registers and main memory.

Memory media (from fast to slow / from low capacity to high capacity)
* CPU registers
* Cache
* Main memory
* Disk

The memory management unit (MMU) hardware translates virtual addresses to
physical addresess. Programmers only sees the virtual addresses and can't know
if their data is in RAM or on disk. They can only know with the command `ps`.

Virtual memory is organized into *pages*, a few KB memory images the OS moves
from memory to disk (paging out) or from disk to memory (paging in). Paging
happens in the *swap area*.

**Only user processes ever page and swap. Kernel is always memory-resident**.

Process only operates on pages that are in memory. When it needs a page that is
not in memory, MMU raise a **page fault**. The kernel handles this event by
checking if the requested page exist. If yes, it load it from the disk to memory
and process continue without even knowing it was stopped by a page fault.
Otherwise, it raise a **segmentation violation**.

### Cache memory
Extremly fast but small memory either on the CPU or physical memory side of the
MMU. In the first case, it caches *virtual addresses*, in the second case, it
caches *physical addresses*.

When data is read from memory, an entire line (16 or 32 bytes) is brought into
the cache. Future data read can then directly be loaded from cache rather than
from the slow main memory. The cache contains a list of lines, composed of an
address and a data section (a block, 32 bytes). The OS look if the requested
address is already in the cache.

Cache operates at the same speed as the cycle time of the system. Main memory is
usually 4 times slower.

There are different types of cache : write-through, write-back, instructions
cache, data cache, I/O bus cache...

> In UNIX, disk inodes are cached in memory. This is why the filesystem can be
> corrupted by powering the machine off without first flushing the cache to disk
> with the `sync` command.

Using `memcpy` is ~10x faster than a dumb copy `dest[i] = src[i]` because
`memcpy` is tuned for high performance and uses SIMD instructions and directly
copies lines (which are 4-bytes). The naive solution copies bytes by bytes.

### The Data Segment and Heap
The data segment contains the **heap**. It is used for dynamically allocated
storage, like `malloc`. Everything in the heap is anonymous. You cannot access
it by name, only by pointer. `malloc/calloc/realloc` are the only way to get
storage from the heap.

Unordered `malloc/free` cause heap fragmentation. The heap keeps track of
available and unvailable regions (with a linked list of available blocks).

Memory obtained with `malloc` can be free-ed and then reused, but this memory
can't be given back to the OS until the program terminates.

The end of heap is marked by a pointer known as `break`. When the heap manager
needs more memory, it calls `brk/sbrk` (routines to adjust size of the data
segment). `malloc` uses `brk/sbrk` so don't use `sbrk` if you use `malloc`.

### Memory Leaks
When a program terminates, all the memory allocated is freed by the OS (even if
the programmer doesn't write explicit `free` in its program).

If a program has a long execution time (like an OS), it needs to carefully
manage the memory it uses. Two sources of problem :
* freeing or overwriting something that is still in use (memory corruption)
* not freeing something no longer in use (memory leak)

The function `alloca` (used in a function) allocates memory on the stack and
automatically frees it (so no leak).

> Whenever you write a `malloc`, write a corresponding `free` statement.

*Memory leak* because a scarce resource is draining away in a process. The
faulty process might be swapped out more often as it becomes larger, and will
slow down **the entire system**, not only the offending program.

A simple memory leak :
```C
for (i = 0; i < 10; ++i)
    p = malloc(1024);
```

At each new iteration, the content of `p` is overwritten so the memory address
can no longer be accessed or freed. It *has leaked* (= is lost).

Memory leaks in the kernel are more dangerous : when a kernel routine asks for
memory, it usualy waits until some are availabe. If none is available, every
routine will wait -- the machine is hung.

#### How to Check for a Memory Leak
Look at the output of the command `free` every 10 seconds. If the available swap
space keeps decreasing, there might be a memory leak somewhere.

Another command is `ps -lu username` : it shows the size of all processes of
`username` (in the column `sz`, in pages). If a process size always grows but
never decreases, it might have a memory leak.

> Some public domain X-Window applications are notorious for leaking like the
> Apple Computer board of directors.

### Bus Error, Take the Train
Two errors that often happen :
* bus error (core dumped)
* segmentation fault (core dumped)

These errors are detected by the OS, so the terms used are convenient *for the
OS* (not really precise for a programmer). The hardware tells the OS there is a
problem with a memory reference and the OS sends a signal (either "bus error" or
"segmentation fault") to the faulty process. This process will dump core and
terminate. The word *core* has the meaning of main memory.

#### Bus Error
Caused by a misaligned read or write. Alignment means that data items can only
be stored at an address that is a multiple of their size. For example, 8-byte
double can only be stored at addresses which are multiple of 8 (24, 8080...).
A bus error can also be generated by referencing memory that does not physically
exists (but this is a rare case).
