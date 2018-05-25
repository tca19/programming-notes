The C programming language (K&R, 2nd edition)
=============================================

Appendix A : Reference Manual
-----------------------------

### A.2 Lexical conventions
6 classes of tokens :
* indentifiers (sequence of letters and digits)
* keywords (`auto`, `break`, `case`, `char`...)
* constants (integer, character, floating, enumeration)
* string literals (sequence of characters wrapped by `"`)
* operators
* other separators

#### A.2.5 Constants
Integer constants can be suffixed by `u` or `U` to specify it is unsigned, or
`l` or `L` to specify it is a long. Character constants can be octal or
hexadecimal numbers (`\ooo` or `\xhh`). Floating constants can be suffixed by
`f`, `F` to indicate it is a float, `l` or `L` to indicate it is a long double.

Adjacent string literals like `"hello" " world"` are concatenated and a NUL
character (`\0`) is appended to the concatenated string. `wchar_t` is a wide
character.

### A.4 Meaning of Identifiers
An object (also called a variable) has two main attributes :
* a storage class : lifetime of associated storage, automatic or static
* a type

Automatic variables only live inside the block where they are declared. Static
variables (`static`) continue to live even after the block where they are
declared is exited. _Objects declared at the same level as function definitions
are always static_. Identifiers preceeded by the ̣̣`extern` keyword are available
to the whole program (external linkage).

`unsigned char` consumes the same amount of space as `signed char` and `char`.\
The _derived_ types are : arrays, functions, pointers, structures and unions.\
Object = named region of storage; lvalue = expression referring to an object.

### A.6 Conversions
A `char`, `short int` or integer bit-field can be used in an expression where an
integer is expected. It is cast as `(unsigned) int` (depending or the range).
This is called _integral promotion_.

Only pointers **of the same type, in the same array** can be substracted.
Pointers can be converted to `void *` and back to their orihginal type without
change.

### A.7 Expressions
Declaring an "array of T" = pointer to first element of array; "function
returning T" = pointer to function returning T.\
`E1[E2] = *((E1)+(E2))`\
_Argument_ : expression passed by a function call.\
_Parameter_ : input object received by a function definition.

All arguments passed to a function are **copies**, including pointers.\
`E1->MoS = (*E1).MoS` (Member of Structure)\
If type of operand is T, `&T` is a "pointer to T". If the type of V is "pointer to
T", `*V` is of type T.

`sizeof` uses parenthesis with **type-name**, but does not require some with
expressions. `sizeof` char is always 1, `sizeof` an array return the total
number of bytes of the array. It returns a `size_t` type.

Difference of two pointers from the same array has type `ptrdiff_t` and
represent the number of cells between the two pointers.

`E1<<E2` is undefined if E2 is greather than or equal to the number of bits in
the type of `E1`. This is equivalent to multiply `E1` by 2^E2. In the same way,
`E1>>E2` is equivalent to `E1` divided by 2^E2.

Relational operators (`>, <, >=, <=`) yield an `int` that has value 1 if
relation is true or 0 if false. Pointers of same object are equal. Pointers of
struct members can be compared. Members declared first have lower value. Lazy
evaluation for `&&` and `||` : if first operand is 0 or 1, it directly returns 0
or 1 (as an `int`).

If an lvalue is declared as `const`, or is a structure/union with one of its
member declared as `const`, assignment expressions (`+=, /=, <<=, &=...`) are
not applicable.

### A.8 Declarations
Declarations that reserve storage are called _definitions_. Declarators list can
be preceeded with : `auto, register, static, extern, typedef`.\
`auto` and `register` can only be used within functions. They cause **storage to
be set aside**. When `extern` is used within a function, it specified that that
the storage for the declared object is stored elsewhere.
Within functions, if not specifier is given, objects are taken as `auto`,
function as `extern`.\
Outside functions, declared objects and functions are all taken as `static` with
external linkage.\
`const` objects are placed in **read-only** memory. It can increase
opportunities for _optimization_.

`struct` or `union` can not contain an instance of itself, but it's ok to have a
**pointer** to an instance of itself.\
If a pointer to a structure is cast to the type of a pointer to its first
member, the result refers to the first member.\
`struct tnode s, *sp;` : declares `s` to be a structure, `sp` a pointer to a
structure.

`int *ap[]` : array of pointers to `int`.\
`int *const cpi` : constant pointer to `int`. Address can not be modified but
pointed value can.\
`const int *pci` : pointer to `const int`. Address can be modified, not pointed
value.\
`int f(), *fpi(), (*pfi)()` : function returning an `int`, returning a pointer
to `int`, and a pointer to a function returning an `int`.\

`static` objects no explicitly initialized are initialized with value `0`.
`auto` objects not explicitly initialized have undefined value. Character arrays
can be initialized with string literal.\
`float y[4][3] = { {1}, {2}, {3}, {4} }` initializes the first column of `y`,
all other values are `0`.\

Declarations with `typedef` do not declare objects, but define identifiers that
name types. `typedef` does not introduce new types, only synonyms for types.

### A.9 Statements
`case` _constant-expression_ : _statement_.\
Compound statements: regroup multiple statements in `{ }` where only one is
expected.\
Statement after a `if` is executed is expression compares unequal to `0`.\
If there is no `default` label in a `switch` and no `case` is matched, nothing
happens.\
When `return` is followed by an expression, the expression is converted to the
type returned by the function.

### A.10 External Declarations
C files consists of a sequence of declarations and functions definitions.\
Functions can not return an array or a function. During the call of a function,
the arguments are converted as necessary.\
External declarations are _externarl_ because they are _outside_ functions.
External declaration for an object is a definition if it has an identifier. Each
object must have exactly one definition.
