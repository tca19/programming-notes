Expert C Programming : Deep C Secrets
=====================================

Chapter 3: Unscrambling Declarations in C
-----------------------------------------

`typedef char * string;
string punchline = "I'm a frayed knot";`

The type of variable **is** `char *` but **is called** `string`, the variable
**is** `"I'm a frayed knot"` but **is called** `punchline`.

### Syntax Only a Compiler Could Love
The syntax of C declarations is a *truly horrible mess* that permeates the use
of the entire language. Originally, the declaration of an object was supposed to
look like its use (`int * p[5]` is an array of pointers to integers) but is no
longer true with the addition of special keywords:
* `const int * grape`: object pointed to is const
* `int const * grape`: object pointed to is const
* `int * const grape_jelly`: pointer is read-only

Question: what is `char* const *(*next)();` ?

### How a Declaration is Formed
A function cannot return a function or an array, so you can't see `foo()()` or
`foo()[]`, but you can have:
* `int (* fun())()`: a function returning a pointer to a function
* `int (* foo())[]`: a funtion returning a pointer to an array

#### `struct`
`struct` are a bunch of data items grouped together. An optional tag can be
added right after the `struct` keyword so there is no need to rewrite the {}
block each time we want to use again. After the closing `}`, some variable
definitions (to declare objects of the `struct` type) can be found but it is
recommended to declare them on a separate statement.

`struct optional_flag {stuff ...} optional_var1, optional_var2;`

To copy an array, enclose it in a `struct`, then copy the `struct`:
```C
struct s_tag { int a[100]; };
struct s_tag orange, lemon;
/* for loop to initialize orange.a with random values [...] */
orange = lemon;
```

#### `union`
Similar to `struct`, contains several fields of different types, but only one
field can be set at a time (all members share the same memory adress, so writing
to one overwrite the others). *Problem*:  there is no way to know which field is
set. `union` is usually used to save space by not storing all possibilities for
certain data items. In this example, an animal can either have fur or more than
4 legs.
```C
union secondary_characteristics {
    char has_fur;
    short num_of_legs_in_excess_of_4;
};
```
Unions can also be used to represent the same data in several ways.
```C
union bits32_tag {
    int whole;                        /* one 32-bit value */
    struct {char c0,c1,c2,c3; } byte; /* four 8-bit bytes */
} value;
```
The bytes can be accessed individually with `value.byte.c0`
