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
Else part is _optionnal_ but sometimes can be ambiguous :
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
