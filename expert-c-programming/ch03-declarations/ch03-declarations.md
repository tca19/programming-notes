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

#### `enum`
A simple way to associate a series of names with a series of integers.
```C
enum sizes { small=7, medium, large=10, xxlarge };
/* medium is 8, xxlarge is 11. If a value is assigned, the next value is one
greater */
```

### The Precedence Rule
1. Declarations are read by starting with the name (**leftmost identifier)** and
   then reading in precedence order
2. From high to low:
    1. things grouped in parentheses
    2. postfix operators (either `()` for function or `[]` for array)
    3. prefix operator (`*`, denoting pointer to)
3. `const` or `volatile` keyword
4. tokens remaining are the basic type of the declaration

If `const` is next to a type specifier (`int/long`) it applies to the type
specifier. Otherwise, it applies to the pointer asterisk on its immediate left.
`const` means **read-only**, not necessarily that the content is constant.

### `typedef` Can Be Your Friend
Similar to a macro text replacement: doesn't introduce a new type, just a name
for an existing type (*this name is a synomym for the stated type*).
```C
/* before (note: void (*func)(int) is a pointer `func` to a function taking int
and returning void */
void (*signal(int sig, void (*func)(int)) )(int);

/* after (factorizing common parts with a typedef) */
typedef void (*ptr_to_func) (int); /* ptr_to_func is a pointer to a function
that takes an int and return void */
ptr_to_func signal(int, ptr_to_func);
```

Don't declare several `typedef` at once (`typedef int *ptr, (*func)(), arr[5];`.

**How to declare typedef?**: Just write a declaration for a variable with the
type you desire. Have the name of the variable be the name you want for the
alias. Write the keyword `typedef` at the start like:
`typedef int (*array_ptr)[100];`.

`typedef` is not **exactly** the same as a macro replacement. A macro can be
extended, not a `typedef`.
```C
#define peach int
usigned peach i; /* valid */

typedef int banana;
unsigned banana i; /* not valid */
