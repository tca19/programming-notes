The C programming language (K&R, 2nd edition)
=============================================

Chapter 3 : Control Flow
------------------------

### 3.1 Statements and Blocks
**Statement** : expression followed by a semi-colon, like `x = 0;`. `;` is a
_statement terminator_.

**Block (or compound statement)** : grouped statements with `{ }` like function
body of if-else.

### 3.2 If-Else
`else` part is _optionnal_ but sometimes can be ambiguous without it :
```C
if (n > 0)
    if (a > b)
        z = a;
    else        /* goes with 2nd if, not first */
        z = b;
```
`else` always goes with the **closest** previous else-less `if`.

### 3.3 Else-If
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
Last `else` can also be omitted, but usually used to catch an _impossible_
situation.

### 3.4 Switch
To test whether an expression matches a _constant integer value_ :
```C
switch (expression)
{
    case const-expr:
        statements
        break;
    case const-expr:
        statements
        break;
    case const-expr1: case const-expr2: case const-expr3:
        statements
        break;
    default:
        statements
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
initialization and an increment step.

From `<ctype.h>`, there are the functions `isspace()` and `isdigit()`.

We can place multiple expressions in the same part of a `for` loop with the `,`
operator :
```C
#include <string.h>

/* reverse: reverse string s in place */
void reverse(char s[])
{
    int c, i, j;

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
body (not **before** like the other two loops) -> _therefor, the body is always
executed at least once_.
```C
/* itoa: convert n to characters in s */
void itoa(int n, char s[])
{
    int i, sign;

    if ((sign = n) < 0) /* record sign */
        n = -n;         /* make n positive */
    i = 0;
    do
    {           /* generate digits in reverse order */
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