The C programming language (K&R, 2nd edition)
=============================================

Chapter 5 Pointers and Arrays
-----------------------------

### 5.1 Pointers and Addresses
Pointer = variable that contains address of another variable. Can also be seen
as a group of memory cells (2 or 4) that holds an address.

Memory = consecutive numbered addresses of memory cells. Any byte can be a
`char`, a pair of one-byte can be treated as a `short` and 4 adjacent bytes can
be treated as an `int`.

The `&` operator gives the address of an **object**. `p = &c` : address of `c`
stored in `p`. `&` can not be applied to expressions, constants and register
variables. The `*` operator is the _indirection_ or _dereferencing_ operator :
access the object the pointer points to.

```C
int x = 1, y = 2, z[10];
int *ip;    /* says that *ip (object pointed by ip) is an int */
ip = &x;    /* ip points to x */
y = *ip;    /* y is now 1 */
*ip = 0;    /* x is now 0 */
ip = &z[0]; /* ip points to z[0] */
```

**Every pointer points to a specific data type.** Only exception : `void*` is a
pointer to `void`, a generic pointer.

We can copy pointers so they point to the same location `ip = iq;`.

`*` and `++` (or `--`) have the same order of precedence and are associated
_**right to left**_, so if an expression combines these two operators, we
sometimes need parentheses (`(*ip)++` to increment the value pointed by `ip`;
otherwise it first increments the pointer then try to dereference it).

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
In function arguments, `char *s` is prefered to `char s[]` (more explicit that
it is a pointer) but both are **equivalent**. A function can operate on
_subarray_ (`f(&a[2])`). `p[-1]`, `p[-2]` are valid if the elements before
`p[0]` exist.

### 5.4 Address Arithmetic
To implement a basic storage allocator, two variables are required :
* `allocbuf` : large character array
* `allocp` : position of the next free position in `allocbuf`

```C
#define ALLOCSIZE 10000 /* size of available space */

static char allocbuf[ALLOCSIZE];  /* storage for alloc */
static char *allocp = allocbuf;   /* next free position */

char *alloc(int n)  /* return pointer to n characters */
{
    if (allocbuf + ALLOCSIZE - allocp >= n) /* if fits */
    {
        allocp += n;
        return allocp - n; /* old position */
    }
    else                   /* not enough space */
        return 0;
}

void afree(char *p) /* free storage pointed to by p */
{
    if (p >= allocbuf && p < allocbuf + ALLOCSIZE)
        allocp = p;
}
```
The function `alloc()` returns `0` to indicate there is no space left because
**`0` is never a valid address**. The symbolic constant `NULL` is used to
indicate the zero pointer. The subtraction between two pointers gives the number
of cells between them (when they point to the same array).
```C
/* strlen: return length of string s */
int strlen(char *s)
{
    char *p = s;

    while (*p != '\0')
        ++p;
    return p - s;
}
```

### 5.5 Character Pointers and Functions
_String constant_ : words or sentence between double quotes `"`, is an _array of
characters_. Always implicitly terminated by `\0` (null character). Accessed by
a **pointer to its first element**.

In the code below; `amessage` is an array so we can modify each character.
`apointer` is a pointer (that can points to something else) but result is
undefined if we try to modify the string pointed to. Most of the function that
operate on strings (including `strcpy` and `strcmp` are in `<string.h>`.
```C
char amessage[] = "now is the time"; /* an array */
char *pmessage = "now is the time";  /* a pointer */
```
Another implementation of `strcpy()`:
```C
void strcpy(char *s, char *t)
{
    while (*t++ = *s++)
        ;
}
```

### 5.6 Pointer Arrays; Pointers to Pointers
Pointers are **variables** that can also be stored in arrays. To sort multiple
lines, first store them in a long continuous character array, and access each
line by storing the pointer to each first character in an array.  Then sort the
pointers instead of the lines (no need to operate or move the lines).

`char *lineptr[MAXLINES];` is an **array of MAXLINES** elements, each one is a
**pointer to a char**. `lineptr[i]` is a pointer and `*lineptr[i]` is a string
constant.

### 5.7 Multi-dimensional Arrays
To get multiple values from a function, we pass pointers to the list of
arguments (`month_day(1988, 60, &m, &d)`.
```C
static char daytab[2][13] = {
    {0, 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31},
    {0, 31, 29, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31}
};

/* day_of_year: set day of year from month & day */
int day_of_year(int year, int month, int day)
{
    int i, leap;

    leap = year%4 == 0 && year%100 != 0 || year%400 == 0;
    for (i = 1; i < month; ++i)
        day += daytab[leap][i];
    return day;
}

/* month_day: set month, day from day of year */
void month_day(int year, int yearday, int *pmonth, int *pday)
{
    int i, leap;

    leap = year%4 == 0 && year%100 != 0 || year%400 == 0;
    for (i = 0; yearday > daytab[leap][i]; ++i)
        yearday -= daytab[leap][i];
    *pmonth = i;
    *pday = yearday;
}
```
true (1) or false (0) can be used as an array index. `daytab` is made of `char`
because the integers are small.

When passed to a function, **2D arrays declaration must include number of
columns**, number of rows is irrelevant. These declarations are valid :
* `f(int daytab[2][13]) { ... }`
* `f(int daytab[][13]) { ... }`
* `f(int (*daytab)[13]) { ... }`

### 5.8 Initialization of Pointer Arrays
```C
/* month_name: return name of the n-th month */
char month_name(int n)
{
    static char *name[] = {
        "Illegal month",
        "January", "February", "March", "April",
        "May", "June", "July", "August",
        "September", "October", "November", "December"
    };

    return (n < 1 && n > 12) ? name[0] : name[n];
}
```
`name` is a array of pointers to `char`. Strings are stored somewhere and a
pointer to each string is placed in `name[i]`.

### 5.9 Pointers vs Multi-dimensional Arrays
* `int a[10][20];` : a _true_ 2D array, composed of 200 integers. Memory has
  been set aside.
* `int *b[10];` : only allocates memory to store 10 pointers. Pointers are not
  initialized. The rows of the array may be of different sizes (first is 10
  integers, second is 3, third is 45...).

Most common use case happens with string. In `char aname[][15] = {...}`, all
rows are 15 characters long, even if some of them are smaller than 15 characters
(so there is **wasted memory**). With `char *name[] = {...}`, each row has the
right amount of characters.

### 5.10 Command-line Arguments
When `main` is called, it receives two arguments :
* `argc` : (argument _count_), number of CLI args
* `argv` : (argument _vector_), pointer to an array of character strings, each
  one is a CLI arg

`argv[0]` is the name of the program, `argc` is always >= 1. `argv[argc]` is
`NULL` pointer. `*++argv` first moves `argv` to next position (because position
0 is the name of the program) then dereference it.
```C
#include <stdio.h>

/* echo command-line arguments; pointer version */
int main(int argc, char *argv[])
{
    while (--argc > 0)
        printf((argc > 1) ? "%s " : "%s", *++argv);
    printf("\n");
    return 0;
}
```
`strstr(s, t)` returns a pointer to the first occurrence of t in s, `NULL` if
none. CLI flags (like `-x` or `-n`) can be in any order or combined (`-xn`).

* `(*++argv)[0]` : move `argv` to next arg pointer, then take first char of
  that argument
* `*++(argv[0])` : iterates over the characters of `argv[0]` (by going to
  `argv[1]` then `argv[2]`...)

### 5.11 Pointers to Functions
Functions are not variables, it is possible to define pointers to functions,
store these pointers in arrays or pass function pointers to other functions.

A sort requires 3 parts :
1. a comparison that determines order
2. an exchange operation to swap two elements
3. a sorting algorithm.

The sorting algorithm is independent of the comparison/exchange operations. So
passing the comparison function as an argument can change the behavior of the
sort. When passing a function as an argument, no need of the `&` operator (same
as an array name).

`void *` is a generic pointer to tell that a function can receive **any
types** of pointers. Casting a pointer to `void *` then back to its original
type do not occur in loss of information. So pointers are casted to `void *`
before being passed to `qsort`.

```C
void qsort(void *v[], int left, int right,
           int (*comp)(void *, void *)) {...}
```
Last argument of `qsort()` : `comp` is a pointer to a function that has two
`void*` arguments and returns and int. Then `comp` is used with `(*comp)(v[i],
v[left]) < 0`. `*comp` **IS the function**.

Without parentheses, `int *comp(void *, void *)` indicates that `comp` is a
function that returns a pointer to an `int`.

### 5.12 Complicated Declarations
* `int *f()`: f is a function returning pointer to int
* `int (*pf)()`: pf is a pointer to a function returning int
* `char **argv`: pointer to pointer to char
* `int (*daytab)[13]`: pointer to array[13] of int
* `int *daytab[13]`: array[13] of pointer to int
* `void *comp()`: function returning pointer to void
* `void (*comp)(): pointer to function returning void
