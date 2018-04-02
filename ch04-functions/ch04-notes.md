The C programming language (K&R, 2nd edition)
=============================================

Chapter 4 : Functions and Program Structure
-------------------------------------------

Functions break large computing tasks into smaller ones, clarifying the whole
program. Many small functions are better than a few big ones.

### 4.1 Basics of Functions
We want the function `strindex(s, t)` to return the position in the string `s`
where the string `t` begins. So the returned position is positive (it's an array
index). Therefore, _-1 is a good error code_ to indicate that string `t` is not
found in `s`.

Each function definition has the form :
```C
return-type function-name(argument declarations)
{
    declarations and statements;
}
```
If return type is omitted, `int` is assumed. **Communication between the
functions is by arguments and values returned by the functions**.  If `main()`
returns a status code, it can be used by the environment that called the
program.

If a program is separated into multiple source files, then `cc main.c getline.c
strindex.c` will compile each file, producing `main.o, getline.o, strindex.o`
then link all `*.o` files to produce `a.out`.
