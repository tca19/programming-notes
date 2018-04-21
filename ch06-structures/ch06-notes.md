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
