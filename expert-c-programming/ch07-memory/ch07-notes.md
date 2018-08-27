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

2^10: kilo; 2^20: Mega; 2^30: Giga; 2^40: Tera; 2^64: 18 billion billion

With 2^64 addresses, it could be possible to store 36 million of 500GB files.
The challenge is not about memory *capacity* but about memory *speed*. There is
an increasing gap between memory and CPU performance : when the CPU speed is
multiplied by 2 every 1.5 years, memory access time only increase by 10%.
