The C programming language (K&R, 2nd edition)
=============================================

Chapter 3 : Control Flow
------------------------

### 3.1 Statements and Blocks
**Statement** : expression followed by a _statement terminator_ `;` : (`x = 0;`)

**Block (or compound statement)** : statements grouped with `{ }` so they act
like a single statement (function body or if-else block).

### 3.2 If-Else
`if/else` is always followed by statements. `else` part is _optional_ but
sometimes can be ambiguous without it :
```C
/* test if expression has a non-zero value */
if (n > 0)
    if (a > b)
        z = a;
    else        /* goes with 2nd if, not first */
        z = b;
```
`else` always goes with the **closest** previous else-less `if`. Use `{ }` for
nested `if` to avoid any confusion (which `if` does this `else` match?). Prefer
`if (expr)` to `if (expr != 0)`.

### 3.3 Else-If
See [binary_search.c](examples/binary_search.c) for a complete example.

```C
if (expression)
    statement
else if (expression)
    statement
else if (expression)
    statement
else
    statement
```
Last `else` can also be omitted, but usually is used to catch an _impossible_
situation.

### 3.4 Switch
To test whether an expression matches one or multiple  _constant integer
values_ :
```C
switch (expression)
{
    case const-expr:
        statements;
        break; /* cause immediate exit of swicth. Can also use return to exit */
    case const-expr:
        statements;
        break;
    case const-expr1: case const-expr2: case const-expr3:
        statements;
        break;
    default:
        statements;
        break;
}

/* example to count occurrence of each character type */
switch (c)
{
    case '0': case '1': case '2': case '3': case '4':
    case '5': case '6': case '7': case '8': case '9':
        ++ndigits[c-'0'];
        break;
    case ' ': case '\n': case '\t':
        ++nwhite;
        break;
}
```
All `case` expressions must be different. `default` is optional. You can regroup
several `case` with the same statement. `break` exits the switch, otherwise the
code would continue to check other const-expr (_fall through_).

### 3.5 Loops - While and For
In `while (expr) {...}`, block is executed until `expr` becomes `0`. The
`for(expr1; expr2; expr3)` loop is just a `while` loop formatted :
```C
expr1;
while (expr2)
{
    statements;
    expr3;
}
```
`for (;;)` is an **infinite** loop. `for` loop is preferable when there is an
*initialization* and an *increment* step. At the end of `for` loop that uses
variable `i`, the value remains in `i`.

From `<ctype.h>`, there are the functions `isspace()`, `isdigit()` and
`strtol()` (string to long).

We can place multiple expressions in the same part of a `for` loop with the `,`
operator :
```C
#include <string.h> /* strlen */

/* reverse: reverse string s in place */
void reverse(char s[])
{
    int c, i, j;

    /* can manage two indexes (i, j) in parallel in for loop */
    fot (i = 0, j = strlen(s)-1; i < j; i++, j--)
    {
        c = s[i];
        s[i] = s[j];
        s[j] = c;

        /* or with a single statement */
        /*c = s[i], s[i] = s[j], s[j] = c;*/
    }
}
```

### 3.6 Loops - Do-While
In a `do-while` loop, the termination condition is tested **after** the loop
body (not **before** like the other two loops) -> _therefore, the body is always
executed **at least once**_.
```C
/* itoa: convert n to characters in s */
void itoa(int n, char s[])
{
    int i, sign;

    if ((sign = n) < 0) /* record sign */
        n = -n;         /* make n positive */
    i = 0;
    do
    {   /* generate digits in reverse order */
        s[i++] = n % 10 + '0';   /* get next digit */
    } while (( n /= 10) > 0);    /* delete it */

    if (sign < 0)
        s[i++] = '-';
    s[i] = '\0';
    reverse(s);
}
```

### 3.7 Break and Continue
The `break` statement causes the **innermost** enclosing loop or `switch` to be
exited immediately.
```C
/* trim: remove trailing blanks, tabs, newlines */
int trim(char s[])
{
    int n;

    for (n = strlen(s)-1; n >= 0; n--)
        if (s[n] != ' ' && s[n] != '\t' && s[n] != '\n')
            break;
    s[n+1] = '\0';
    return n;
}
```
The `continue` statement causes the next iteration of the loop to begin (or go
to the increment step in the `for` loop).

### 3.8 Goto and Labels
Most common usage is to exit more than 2 nested loops. Should be **rarely**
used.
```C
for (i = 0; i < n; ++i)
    for (j = 0; j < m; ++j)
        if (a[i] == b[i])
            goto found;
/* didn't find any common element */
...
found:   /* <- a label, same as a variable but colon (:) at the end */
    /* got one: a[i] == b[j] */
