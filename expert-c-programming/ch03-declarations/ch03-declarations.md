Expert C Programming : Deep C Secrets
=====================================

Chapter 3: Unscrambling Declarations in C
-----------------------------------------

`typedef char * string;
string punchline = "I'm a frayed knot";`

The type of variable **is** `char *` but **is called** `string`, the variable
**is** `"I'm a frayed knot"` but **is called** `punchline`.

### Syntax Only a Compiler Could Love
The syntax of C declarations is a *truly horrible mess* that permeates the use
of the entire language. Originally, the declaration of an object was supposed to
look like its use (`int * p[5]` is an array of pointers to integers) but is no
longer true with the addition of special keywords:
* `const int * grape`: object pointed to is const
* `int const * grape`: object pointed to is const
* `int * const grape_jelly`: pointer is read-only

Question: what is `char* const *(*next)();` ?
