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
In a `switch`, the flow of control continues down (fallthrough) if there is not
`break` and one statement is executed (this will priny 3 lines).
```C
swicth (2) {
    case 1: /* statemnents1 */
    case 2: /* statemnents2 */
    case 3: /* statemnents3 */
    default: printf("default\n');
```
