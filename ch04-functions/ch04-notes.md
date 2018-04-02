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
