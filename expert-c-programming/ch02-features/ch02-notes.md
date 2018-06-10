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

`NUL` ends an ASCII string. `NULL` points to nothing.

### Sins of Commission
Things the language does that it shouldn't do.

In a `switch` statement, the default case can appear anywhere in the list of
cases. If no case is matched and there is no default case, nothing happens. Some
variables can be declared right after the opening bracket of a switch statement,
but it won't be executed, only the statements in the right case will.

The ̣`const` keyword does not really mean constant in C.
```C
const int two=2;

swicth(i)
{
  case 1: printf("case 1\n");
  case two: printf("case 2\n); /* error, constant expression required */
  default: ;
}
```
