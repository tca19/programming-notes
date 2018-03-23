The C programming language (K&R, 2nd edition)
=============================================

Chapter 2 : Types, Operators, and Expressions
---------------------------------------------

### 2.1 Variable Names
First character in a variable name **must be a letter (or _)**. Usually, lower
case for variable names, UPPER CASE for symbolic constants. Keywords like `if,
else, int, float` must be in lower case.

### 2.2 Data Types and Sizes
Only 4 basic data types :
  * char (1 byte)
  * int
  * float (single-precision floating point)
  * double (double-precision floating point)

Can add the word `short` and `long` for `int`. `short` is at least 16 bits,
`long` is at least 32 bits and `int` is either 16 or 32 bits.

Can also specify `unsigned` (positive or zero) or `signed` for `int` and `char`.
```C
printf("%d") -> int/short/char
printf("%u") -> unsigned int/unsigned short/unsigned char
printf("%ld") -> long
printf("%lu") -> unsigned long
```

### 2.3 Constants
`long` constants are written with a terminal `l` or `L`. Unsigned contstants are
written with a terminal `u` or `U` (`ul` or `UL` for `unsigned long`).
Floating-point constants are written with a terminal `f` or `F`.

Integers can be specified in **octal** (with a leading 0) and **hexadecimal**
(with a leading 0x).

**Character constants** are integers, written as a simple character (`'r'`). Its
value is the numeric value of the character in the machine's character set. We
can define character constant in :
  * octal (`\O13` for vertical tab)
  * hexedecimal (`\x7`)

`\0` represents the character with value zero, the **null character**. Its value
is 0.

**String constants** (or _string literal_) are sequences of zero or more
characters surrounded by double quotes like `"hello world"`. String constants
are _concatenated at compile time_ so `"hello" ", world"` is equivalent to
`"hello, world"`. This can be useful to split long string on several lines. The
storage needed to store a string is LEN+1 (need to store the implicit `\0`
character). Function to compute length of a string :

```C
/* strlen: return length of s, excluding the \0 character */
int strlen(char s[])
{
    int i;
    while (s[i] != '\0')
        ++i;
    return i;
}
```

**Enumeration constants** : a list of constant integer values like `enum boolean
{NO, YES};` (alternative to `#define`). First name in an enumeration has value 0, the second one has value
1 and so on. We can also specify the value of each element in an enumeration :
```C
enum escape {BELL = '\a', BACKSPACE = '\b', TAB = '\t',
             NEWLINE = '\n', VTAB = '\v', RETURN = '\r' };
```
