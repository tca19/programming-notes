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

When the compiler finds something like `ar[10] = 2;`, it can add 10 to the
address given to `ar` at compile time. For a pointer, the value needs to be
dereferenced to know it (only possible at runtime) and then read the content of
this value (the address pointed to).
```C
char *p = "abcdef"; /* ... */ c = p[i];
/* 1. get the value/content in p (ie the pointed address)
   2. get the value of i, add it to content fetched in 1.
   3. get the content of address+i
*/

char p[] = "abcdef"; /* ... */ c = p[i];
/* 1. get the value of i, add it to address of p (the one given by compiler)
   2. get the content of address+i
*/
```
Things get wrong when something is defined as an array (`char p[10];`) but read
as a pointer (`exter char p;`) because the program will interpret ASCII values
as address. To solve this problem, **always match the declarations with the
definition**.

###### Other Differences Between Arrays and Pointers
* pointer:
    * holds the address of data
    * data is accessed indirectly (need to first get the address pointed to)
    * commonly used for dynamic data structures, with `malloc()` and `free()`
* array:
    * holds data
    * data is accessed directly (`a[i] get the content of i location past `a`)
    * implicitly allocated and deallocated

