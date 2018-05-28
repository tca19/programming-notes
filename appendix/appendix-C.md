The C programming language (K&R, 2nd edition)
=============================================

Appendix C : Summary of Changes
-------------------------------

* Concatenation in preprocessing lines, `#elif`, `#pragma`, line splicing
* Trigraphs (symbols starting by `??`)
* New keywords (`void, const, volatile, signed, enum`)
* Escape sequences in string/character constants
* `void *` for generic pointer types
* Adjacent strings are concatenated. String are immutable and placed in
  read-only memory.
* `sizeof` operator return `size_t` (defined in `<stddef.h>`)
