Expert C Programming : Deep C Secrets
=====================================

Chapter 2: It's Not a Bug, It's a Language Feature
--------------------------------------------------

### Why Language Features Matter
`malloc(strlen(str))` is a bug because is does not allocate space for the nul
terminator. Correct usage is `malloc(strlen(str)+1)`.\
3 categories of flaws in programming languages :
* things the languages does that it shouldn't do
* things it doesn't do that it should
* things that are completely off the wall

> That's why C++ is so disappointing: it does nothing to address some of the
> most fundamental problems in C, and its most important addition (class) build
> on the deficient C type model.

`NUL` end an ASCII string. `NULL` points to nothing.
