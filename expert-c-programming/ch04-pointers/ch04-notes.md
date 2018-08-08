Expert C Programming : Deep C Secrets
=====================================

Chapter 4 : The Shocking Truth : C Arrays and Pointers Are NOT the Same!
------------------------------------------------------------------------

### Arrays Are NOT Pointers!
```C
/* file 1, define an int array */
int mango[100];

/* file 2, declare an int pointer */
extern int *mango; /* then some code using mango[i] */
```
This code won't work. Arrays and pointers can be equivalent in **some context**
but it is not always the case.

### What's a Declaration? What's a Definition?
Objects in C **must have exactly one definition, and may have multiple external
declarations**.
* definition: special kind of declaration, used to **create new objects** (so
  reserve storage space for it)
* declaration: describe type of an object, used to **refer to objects defined
  elsewhere**

When an array is *declared*, no memory is set aside so indicating the size is
not mandatory.

### How Arrays and Pointers Are Acessed
In `x = y`:
* `x` is an l-value. The compiler allocates an l-value (or address) to each
  variable. This address is known at compile time and is where the variable will
  be stored at runtime.
* `y` is an r-value. It is the value *stored* in a variable and is not known
  until runtime.

If the value stored in a variable is required, the compiler emits code to read
the value from the given address and put it in register.
