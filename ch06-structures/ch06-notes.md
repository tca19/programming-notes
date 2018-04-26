The C programming language (K&R, 2nd edition)
=============================================

Chapter 6 : Structures
----------------------

### 6.1 Basics of Structures
A **structure** is a collection of _one or more variables_ grouped together.
They permit to treat related variables as a unit instead of as separate
entities.
```C
/* represent a point in a 2D space */
struct point
{
    int x; /* list of declarations */
    int y;
};

struct point pt;             /* not initialized */
struct point M = {300, 100}; /* initialized */
```
`point` is the **structure tag**. Variables named in a structure are called
**members** and are accessible with the `.` operator : `printf("%d %d\n", M.x,
M.y);`.

A `struct` declaration defines **a type** so a list of variable can follow `}`
like `struct P {...} x, y, z;`. The variables are of type `struct P`.

`struct` declaration can use other `struct` as members :
```C
struct rectangle
{
    struct point p1;
    struct point p2;
};
```

### 6.2 Structures and Functions
Structures can be used in functions by :
* passing components separately
  ```C
  /* makepoint: make a point from x and y components */
  struct point makepoint(int x, int y)
  {
      struct point temp;

      temp.x = x;
      temp.y = y;
      return temp;
  }

  struct rectangle screen;
  screen.p1 = makepoint(0, 0);
  screen.p2 = makepoint(1000, 1000);
  ```
* passing entire structure
  ```C
  struct point addpoint(struct point p1, struct point p2)
  {
      p1.x += p2.x;
      p1.y += p2.y;
      return p1;
  }
  ```
* passing pointer to a structure (more efficient if structure is large because
  no need to copy (passed by value by default))

`struct point *pp` is **a pointer to a structure of type point**. Members are
accessed with `(*pp).x` and `(*pp).y`. Parentheses are _necessary_ because `.`
has higher precedence than `*` (so it would be interpreted as `*(pp.x)`).

Shorthand notation : `pp->x` and `pp->y`.

### 6.3 Arrays of Structures
Declare a structure, define an array of this structure (memory is set aside) :
```C
struct key {
    char *word;
    int count;
} keytab[NKEYS];
```
Struct array can be also be initialized when defined :
```C
struct key {
    char *word;
    int count;
} keytab[] = {
    "auto", 0,  /* braces are not necessary in {"auto", 0}, ... */
    "break", 0,
    /* ... */
    "while", 0
};
```

Size of an array is _known at compile time_. The number of elements in keytab is
**size of keytab / size of struct key**, which can be computed with :
* `sizeof object` : object is variable or array or structure
* `sizeof(type-name)` : type-name is basic type or structure or pointer

So number of elements is :
```C
/* the latter also works if the type of keytab change */
#define NKEYS (sizeof keytab / sizeof(struct key))
#define NKEYS (sizeof keytab / sizeof keytab[0])
```

### 6.4 Pointers to Structures
`struct key *binsearch()` : a function returning a pointer to a `key` structure.

If two pointers represent both sides of a subarray, middle element is accessed
with :
```C
struct key *low  = &tab[0];
struct key *high = &tab[n];
struct key *mid  = low + (high-low) / 2;
```

**Don't assume that the size of a structure is the sum of the sizes of its
members**. A struct composed of a `char` (1 byte) and an `long` (8 bytes) might
require 16 bytes instead of 9 (because of data alignment). `sizeof` always
return proper size of a structure.

### 6.5 Self-referential Structures
A structure **can't contain an instance of itself**, but it can contain a
pointer to the same type of structure.
```C
struct tnode              /* the tree node: */
{
    char *word;            /* points to the text */
    int count;             /* number of occurrences */
    struct tnode *lchild;  /* left child */
    struct tnode *rchild;  /* right child */
};
```

Two structures can refer to each other : `struct t { ...; struct s *p; };` and
`struct s { ...; struct t *q; };`.

Some machines require _data alignment_ (for example, integers must at even
addresses). The `alloc()` of chapter 5 does not cope with data alignment;
`malloc()` does. It also return a `void*` pointer that needs to be casted.

### 6.6 Table Lookup
The macro processor or compiler routines usually have a hash table to manage
symbols. For the line `#define IN 1`, the table will store the name `IN` and the
replacement text `1` (both as string). Then it parses the program and calls
`lookup("IN")` to know the replacement text everytime it encounters `IN`.

A hash table is an array of pointers to structure like :
```C
struct nlist
{
    struct nlist *next; /* linked list, need to know next element */
    char *name;
    char *defn;
};
static struct nlist *hashtab[HASHSIZE];
```

To navigate a linked list : `for (ptr = head; ptr != NULL; ptr = ptr->next)`

### 6.7 Typedef
Allows to create new data type **names** :
```C
typedef int Length; /* makes the name Length a synonym for int */
Length *lengths[];

typedef char *String; /* String is now a synonym for char* */
p = (String) malloc(100);

/* syntax: typedef <type> <typedef-name>. type can be basic type (int, char) or
struct */

typedef struct tnode *Treeptr;

typedef struct tnode
{
    char *word;
    int count;
    Treeptr left;
    Treeptr right;
} Treenode;
```

`typedef` declarations **does not create a new type** : it adds a name for an
existing type (like `#define` but interpreted by compiler).

### 6.8 Unions
Union : a variable that can hold objects of different types and sizes.
```C
union u_tag
{
    int ival;
    float fval;
    char *sval;
} u;
```

Variable `u` will be large enough to store the largest of its data types.
Members are accessed with `.` or `->` (for union pointer), like for `struct`.

Unions can be found inside `struct` or arrays. It can **only be initialized with
a value of its first member** (`int` in this case).
