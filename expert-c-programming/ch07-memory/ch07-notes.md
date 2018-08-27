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

