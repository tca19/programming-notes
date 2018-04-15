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
```
`point` is the **structure tag**. Variables named in a structure are called
**members**.

