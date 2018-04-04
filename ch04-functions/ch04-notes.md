The C programming language (K&R, 2nd edition)
=============================================

Chapter 4 : Functions and Program Structure
-------------------------------------------

Functions break large computing tasks into smaller ones, clarifying the whole
program. Many small functions are better than a few big ones.

### 4.1 Basics of Functions
We want the function `strindex(s, t)` to return the position in the string `s`
where the string `t` begins. So the returned position is positive (it's an array
index). Therefore, _-1 is a good error code_ to indicate that string `t` is not
found in `s`.

Each function definition has the form :
```C
return-type function-name(argument declarations)
{
    declarations and statements;
}
```
If return type is omitted, `int` is assumed. **Communication between the
functions is by arguments and values returned by the functions**.  If `main()`
returns a status code, it can be used by the environment that called the
program.

If a program is separated into multiple source files, then `cc main.c getline.c
strindex.c` will compile each file, producing `main.o, getline.o, strindex.o`
then link all `*.o` files to produce `a.out`.

### 4.2 Functions Returning Non-integers
The (true) `atof()` function is declared in `<stdlib.h>`. We need to tell `main`
that `atof()` returns something else than an `int`.
```C
int main()
{
    double sum, atof(char []);
    /* ... */
        printf("\t%g\n", sum += atof(line)); /* add to sum, print sum */
}
```
If there is no function prototype, a function is **implicitly declared by its
first appearance** in an expression. If a function does not have an argument
list, as `double function()`, it means that parameters checking is turned off.
**Use (void) to declare that a function does not take any arguments**.

### 4.3 External Variables
* External objects : either variables or functions defined in the program,
  _outside_ any function (so available for many functions).
* Internal objects : arguments and variables defined _inside_ functions.

External variables are an alternative to arguments/return value for
communicating data between functions (they retain value, have greater scope and
lifetime).

The `push()` and `pop()` functions use an array as a stack and a variable to
store the current free position in this array. These variables (and respective
`#define`) **are declared AFTER** `main()` so main() can not access them. If you
don't want an external variable to be accessible to a function, declare it
_after_ this function.

Programs can not determine if they have read enough input until they have read
too much. So they read characters with `getch()`, and when they have read too
much, they un-read it with `ungetch()` (in fatc, it puts the character into a
buffer, and each call to `getch()` first check the buffer before reading input).
```C
#define BUFSIZE 100

char buf[BUFSIZE];     /* buffer for ungetch */
int bufp = 0;          /* next free position in buf */

int getch(void) /* get a (possibly pushed back character */
{
    return (bufp > 0) ? buf[--bufp] : getchar();
}

void ungetch(int c) /* push character back on input */
{
    if (bufp >= BUFSIZE)
        printf("ungetch: too many characters\n");
    else
        buf[bufp++] = c;
}
```

### 4.4 Scope Rules
External variables and functions of a C program are not all compiled at the same
time : some are in different files, some are precompiled in libraries.

* **Scope** of a name : part of a program within the name can be used.
  Parameters of a function are local variables and can only be used in this
  function.
* Scope of an external variable : from where it is declared to the end of the
  file compiled. In the calculator program, _sp_ and _val_ were accessible to
  `pop()` and `push()` but not to `main()` because they were defined
  **AFTER**.

The line `int sp;` is a **definition** (storage is set aside) but `extern int
sp;` is a **declaration** (only announces the properties of _sp_, do not create
the variable or reserve storage for it). No need to indicate array size in
extern declaration (`extern double val[];`).

**Only ONE definition of an external variable among all the files of the
program.**

### 4.5 Header Files
If we want to separate our reverse polish calculator into several files, we
would create :
* `main.c`
* `stack.c` (for push, pop and their variables)
* `getop.c`
* `getch.c` (most likely to come from a library)

We need to _centralize_ all declarations and definitions (easier to manage).
Usually we place this into a **header** file; here `calc.h` :
```C
#define NUMBER '0'
void push(double);
double pop(void);
int getop(char []);
int getch(void);
void ungetch(int);
```
Then in each `.c` file, we add the line `#include "calc.h"`.

### 4.6 Static Variables
The prefix `static` added to an external variable or function limits its scope to
the rest of that source file.
```C
/* no functions in other files will be able to access these variables */
static char buf[BUFSIZE];
static int bufp = 0;
```

Normally, function names are **global**, visible to any part of the entire
program.  If we add `static` in front of a function name, it **becomes invisible
outside the file** in which it is declared.

If a variable inside a function is declared `static`, it remains in existence
between each call. So they provide a **private, permanent storage** inside a
function.

### 4.7 Register Variables
`register int x;` : indicate to the compiler that the variable will be used a
lot so it might be a good idea to put it in register. Compilers can ignore this
indication. Can only be used on _automatic variables_ and _formal parameters of
a function_ (`f(register unsigned x, register char n)`.

It is **not possible to take the address of a register** variable.

### 4.8 Block Structure
We can declare variables inside the block of a compound statement. In this case,
the scope of these variables is that block (they remain in existence until the
final `}` of the block).

Variables declared inside a block **hide** external variables which have the
same name.
```C
int x;
int y;

f(double x)
{
    double y;

    /* any reference to x or y is a double, not an int */
    ...
}
```

### 4.9 Initialization
Without explicit initialization, **external and static** variables are
**guaranteed to be initialized to 0**. Automatic and register variables have
_undefined_ initial values. We can initialize when we define variables : `long
day = 1000L * 60L * 60L * 24L;`.

External and static variables **must** be initialized with _constant
expression_.

When initializing an array (`int ar[10] = {1, 2, 3}`), if there are fewer
initializers than the specified size, missing values are set to `0`.

We can directly initialize char arrays with a string :
```C
char pattern = "ould";
/* equivalent to char pattern = { 'o', 'u', 'l', 'd', '\0' }; */
```

### 4.10 Recursion
**Recursion** : when a function calls itself.
```C
#include <stdio.h>

/* printd: print n in decimal. Start by printing leading digits */
void printd(int n)
{
    if (n < 0)
    {
        putchar('-');
        n = -n;
    }
    if (n / 10)
        printd(n / 10);
    putchar(n % 10 + '0');
}
```
Another common recursion example is `quicksort(int [], int, int)` (choose pivot,
create subarrays of elements less/greater than pivot, sort these subarrays).
