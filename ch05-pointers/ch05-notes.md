The C programming language (K&R, 2nd edition)
=============================================

Chapter 5 Pointers and Arrays
-----------------------------

### 5.1 Pointers and Addresses
Memory = a consecutive numbered addresses of memory cells. Any byte can be a
`char`, a pair of one-byte can be treated as a `short` and 4 adjacent bytes can
be treated as an `int`.

The `&` operator gives the address of an **object** (`p = &c`). It does not work
for expr, constants and register variables. The `*` operator is the
_indirection_ or _dereferencing_ operator : access the object the pointers
points to (`int *ip = &c; *ip = 3;`). It specifies that `*ip` is an _integer_.

**Every pointer points to a specific data type.** Only exception : pointer to
`void` (generic pointer).

`*` and `++` (or `--`) have the same order of precedence and are associated
_right to left_, so if an expression combines these two operators, we sometimes
need parentheses (`(*ip)++` to increment the value pointed by ip; otherwise it
first increment the pointer then try to dereference it).

### 5.2 Pointers and Function Arguments
C passes arguments to functions by value (copy). So a function `swap(int x, int
y)` _does not_ swap the variables, only copies of it. To actually change the
variables passed to `swap()`, we need to pass **pointers** : `swap(int *px, int
*py)`.

With pointers, functions can return more than 1 info, for example return the
status code (EOF or not) and store the parsed integer from input stream into the
passed pointer.
