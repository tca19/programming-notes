Expert C Programming : Deep C Secrets
=====================================

Chapter 2: It's Not a Bug, It's a Language Feature
--------------------------------------------------

### Why Language Features Matter
`malloc(strlen(str))` is a bug because is does not allocate space for the nul
terminator. Correct usage is `malloc(strlen(str)+1)`.\
3 categories of flaws in programming languages :
* things the languages does that it shouldn't do
* things it doesn't do that it should
* things that are completely off the wall

> That's why C++ is so disappointing: it does nothing to address some of the
> most fundamental problems in C, and its most important addition (class) build
> on the deficient C type model.

`NUL` ends an ASCII string. `NULL` points to nothing.

### Sins of Commission
Things the language does that it shouldn't do. In a `switch` statement, the
default case can appear anywhere in the list of cases (not necessarily at the
end).
In C, you can allocate memory for variables right after an opening brace (and
before some statement) :
```C
if (a > b) /* swap a,b */
{
    int tmp = a;
    a = b; b = tmp;
}
```

In a `switch`, the flow of control continues down (fallthrough) if there is no
`break` and one statement is executed (this will print 3 lines).
```C
switch (2) {
    case 1: /* statemnents1 */
    case 2: /* statemnents2 */
    case 3: /* statemnents3 */
    default: printf("default\n');
```
Be careful when using ̣`break` inside a `switch` : it exits nearest
iteration/switch statement, so sometimes it exits the `switch` even if that was not
intended.

In ANSI C, adjacent strings are concatenated. But if the intention is to declare
an array of string and a comma between 2 elements is missing, it will causes
these 2 strings to be concatenated.

To declare a function that does something different during the first call :
```C
generate_initializer(char *string)
{
    static char separator='';
    printf("%c %s \n", separator, string);
    separator = ',';
}
```

Adding `static` when declaring a function restricts the visibility of the
function only to the file where it's declared. Default behavior is to be
globally visible (same as adding the keyword `extern`) -> **BAD : Software
objects should have the most limited scope by default.** The problem is that if
two libraries need to share an object, there is no other options than make it
globally visible.
Internal functions (for one big functions of a library) should be made `static`
(so not visible to anyone linking that library).

### Sins of Mission
Things that are completely off the wall (bad fit).

Many symbols or keywords in C can have **different meaning depending on the
context** : `static` inside a function indicates a variable that retains value
between calls but `static` used at the function level indicates a function only
visible to one file. `&` can be the bitwise operator or the address of a
variable.

`sizeof (type)` **AND** `sizeof variable` like:
* `sizeof (float)`
* `sizeof *arr`
**DO NOT** write ambiguous things like `apple = sizeof (int) * p`

According to Kerninghan and Ritchie :
> some of the operators have the wrong precedences

* `*p.f` : should take the `f` field of object pointed by `p`, but in fact it
 uses `p.f`as a pointer
* `c=getchar() != EOF` : should do `(c=getchar()) != EOF` but it does `c =
  (getchar() != EOF)`
* arithmetic `+` is higher than bitwise `<<` (`msb << (4+lsb)`)

**ALWAYS put parentheses around expressions that mixe booleans, arithmetic...**

In an expression like `a = b = c`, the rightmost operation is evaluated first.

Order of evaluation of the arguments in a function call is unspecified.

The function `gets(line)` read a line from standard input into buffer `line`,
but it does not check if the line can overwrite the buffer, thus it can be used
to overwrite an existing entry in the middle of the stack. The function
`fgets()` was introduced to solve this problem and can only read up to a certain
limit of characters.
```C
char line[512];

/* not secure */
gets(line);

/* secure */
if (fgets(line, sizeof(line), stdin) == NULL)
    exit(1);
```

### Sins of Omission
Things the language doesn't do that it should (like missing standard argument
processing).

C has no way to distinguish flag and positional commnd arguments. For example,
you can't remove a file that starts with an hyphen, you need to give entire
pathname of the file, otherwise `rm` thinks it's a command flag.

Escaping newline with "\ *newline*" (for macro or string concatenation) can be
bad because if a space is inadvertenly inserted like "\ *whitespace newline*",
it will not work the way it is supposed to, and this error won't be easy to see.
Comments can be opened without wanting to (`ratio = *x/*y`). C++ comments can
make valid C code not working (`x = a//* */b;`).

If a function declares a local array (`char buffer[120];`) and returns this array
(`return buffer;`), the code **will compile fine, but will produce garbage value
at running time.** Indeed the local variable `buffer` will be cleared when
function exits, and overwritten by other variables (because declared on the
stack so memory is reused). Multiple solutions :
* use a global declared variable (but can be modified by other functions)
* declare `buffer` as a static variable (but will be overwitten at next function
  calls)
* use `malloc()` to allocate memory (don't have the previous inconvenients)
* pass a pointer to array as function argument and allocate memory somewhere
  else (like in main())

To make good code, make sure it is `link` clean and it passes `cstyle`.
