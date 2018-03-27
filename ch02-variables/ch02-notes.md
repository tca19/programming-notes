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
{NO, YES};` (alternative to `#define`). First name in an enumeration has value
0, the second one has value
1 and so on. We can also specify the value of each element in an enumeration :
```C
enum escape {BELL = '\a', BACKSPACE = '\b', TAB = '\t',
             NEWLINE = '\n', VTAB = '\v', RETURN = '\r' };
```

### 2.4 Declarations
A declaration specifies a type and contains a list of one or more variable of
that type :
```
int lower, upper, step;
char c, line[1000];
```

We can also initialize a variable in its declaration :
```C
int limit = MAXLINE-1;
float eps = 1.0e-5;
```

Initializer must be a constant expression. External and static variables are
**initialized to zero** by default.

We can add the keyword `const` to specify that the variable value will not be
modified (same thing goes with an array). We can also add `const` in a function
argument list to indicate that an array will not be modified.
```C
const double = 2.71828182845905;

int strlen(const char[]);
```

### 2.5 Arithmetic Operators
They are `+, -, *, /, %`. We **cannot** apply `%` on **float and double**. `*, /
,%` have higher precedence than `+, -`.

### 2.6 Relational and Logical Operators
 * **Relational operators** : `>, >=, <, <=`, all the same precedence. Also the
   `==` and `!=`.

 * **Logical operators** : `&&` and `||`. Evaluation of an expresion stops when
   the output of evaluation is known (_passive evaluation_).

It is better to use `if (!valid)` than `if (valid == 0)`. The precedence of `!=`
is higher than assignement, that's why we need parentheses in `(c = getchar())
!= '\n'`.

### 2.7 Type Conversions
In `a+b`, if `a` and `b` are not of the same type, one of them is converted,
usually the "narrower" becomes "wider" (like int to float) so no loss of
information. Most of the time, `char` is used as an integer :
```C
/* atoi: converts s to integer */
int atoi(char s[])
{
    int i, n;

    for (n = 0, i = 0; s[i] >= '0' && s[0] <= '9'; ++i)
        n = 10*n + (s[i]-'0'); /* implicit char to int conversion */

    return n;
}
```
Some conversion function are implemented in `<ctype.h>` :
  * `tolower(c)`
  * `isdigit(c)`

**BE CAREFUL** : when converting a char with leftmost bit set to 1 to integer,
it can becomes negative (depends on the architecture of the machine). It is
better to indicate if such char is `signed` or `unsigned`.

Floats are not automatically converted to double (but most of the functions in
`<math.h>` use double). The main reason to use float is to save storage in large
arrays, or save time in computations (less expensive than using double).

Conversion rules :
  * if either operand is `long double`, convert the other to `long double`
  * if either operand is `double`, convert the other to `double`
  * if either operand is `float`, convert the other to `float`
  * convert `char` and `short` to `int`
  * if either operand is `long`, convert the other to `long`

We can force conversion with `(type) expression;` (cast). A cast does not change
the value of the expression.
```C
unsigned long int next = 1;

/* rand: return pseudo-random integer on 0..32767 */
int rand(void)
{
    next = next * 1103515245 + 12345;
    return (unsigned int)(next/65536) % 32768;
}

/* srand: set seed for rand() */
void srand(unsigned int seed)
{
    next = seed;
}
```

### 2.8 Increment and Decrement Operators
With **prefix** (`++n`), n is incremented before its value is used). With
**postfix** (`n++`) n is incremented after its value is used.
Increment/Decrement operators can only be applied to variables (not on 3 for
example).
```C
/* strcat: concatenate t to end of s; s must be big enough */
void strcat(char s[], char t[])
{
    int i, j;

    i = j = 0;
    while (s[i] != '\0')               /* move to end of s */
        ++i;
    while ((s[i++] = t[j++]) != '\0')  /* copy t */
        ;
}
```

### 2.9 Bitwise Operators
Six operators for bit manipulations; only on integers (char, short, int, long).
  * `&    (AND)`
  * `|    (OR)`
  * `^    (XOR)`
  * `<<   (left shift)`
  * `>>   (right shift)`
  * `~    (one's complement)`

`<< n` shift the bits to left by n positions, filling vacated bits with `0`.
Right shifting **unsigned** integer always fill with vacated bits with `0` while
it depends on the machine architecture for **signed** integers.

`~` converts each 1 to 0 and each 0 to 1. So `~0` is all 1 bits.
```C
/* getbits: get n bits from position p */
unsigned getbits(unsigned x, int p, int n)
{
    /* ~(~0 << n) is a mask of the rightmost n bits */
    return (x >> (p+1-n)) & ~(~0 << n);
}
```

### 2.10 Assignment Operators and Expressions
**Assignment operators** : like `+=`, `-=`, `|=`... The statement `x *= y + 1`
is equivalent to `x = x * (y + 1)`. (_preferable for conciseness and
readability_).
```C
/* bitcount: count 1 bits in x */
int bitcount(unsigned int x)
{
    int b;

    for (b = 0; x > 0; x >>= 1)
        if (x & 01)
            ++b;
    return b;
}
```
In code above, we indicate that x is **unsigned** so when it is right shifted,
vacated bits are filled with `0`, not sign bits. In two's complement number
system, `x &= (x-1)` **deletes the rightmost 1-bit** in x.

### 2.11 Conditional Expressions
Using the **ternary operator** `?:` (expr1) ? expr2 : expr3. If expr1 is true,
then expr2 is evaluated, otherwise expr3 is evaluated.
```C
z = (a > b) ? a : b;   /* z = max(a, b) */

/* print an array, 10 elements by line, each colum separated by a blank */
for (i = 0; i < n; ++i)
    printf("%6d%c", a[i], (i%10 == 9 | i==n-1) ? '\n' : ' ');

printf("You have %d items%s.\n", n, n==1 ? "" : "s");
```

### 2.12 Precedence and Order of Evaluation
Operators precedence in decreasing order (the ones at the top have
high-priority) :
  * `() [] -> .`
  * `! - ++ -- + - * & sizeof`
  * `* / %`
  * `+ -`
  * `<< >>`
  * `< <= > >=`
  * `== !=`
  * `&`
  * `^`
  * `|`
  * `&&`
  * `||`
  * `?:`
  * `= += -= (all other assignment operators)`
  * ,

In the expression `x = f() + g()`, the order of evaluation is not defined.
Sometimes f() is executed first, sometimes it's g(), so **be careful** if one of
them modify a variable also used by the other. We can store intermediate result
in a _temporary variable_ to ensure the order.
