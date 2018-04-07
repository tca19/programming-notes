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

### 5.3 Pointers and Arrays
Any operation that can be achieved by array subscripting can also be done with
pointers. In general, pointer version is faster.

`int a[10];` defines a block of 10 consecutive objects in memory. If `int *pa;
pa = &a[0];`,  then `pa` points to the first cell of the array, `pa+1` points to
the next cell, `pa+i` points to the i-th cell of `a`.

The name of an array is the location of the initial element (in this case, `a`
is the adress of `a[0]`). An **array name is not a variable** so `a=pa` or `a++`
are illegal. When an array name is passed to a function, it becomes a local
variable so a pointer.
```C
/* strlen: return the length of string s */
int strlen(char *s)
{
    int n;

    /* incrementing s has no effect on original string since s is a private copy
    of the pointer */
    for (n = 0; *s != '\0'; ++s)
        ++n;
    return n;
}
```
In function arguments, `char *s` is prefered to `char s[]` (more explicit that it
is a pointer) but both are **equivalent**. A function can operate on _subarray_
(`f(&a[2])`). `p[-1]`, `p[-2]` are valid if the elements before `p[0]` exist.
