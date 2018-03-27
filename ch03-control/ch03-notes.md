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
All case expressions must be different. `default` is optional. You can regroup
some case with the same statement. `break` exits the switch, otherwise the code
would continue to check other const-expr (_fall through_).
