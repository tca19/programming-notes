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
