The C programming language (K&R, 2nd edition)
=============================================

Chapter 2 : Types, Operators, and Expressions
---------------------------------------------

### 2.1 Variable Names
First character in a variable name **must be a letter (or _)**. Usually, lower
case for variable names, UPPER CASE for symbolic constants. Keywords like `if,
else, int, float` must be in lower case.

### 2.2 Data Types and Sizes
Only 4 basic data types :
  * char (1 byte)
  * int
  * float (single-precision floating point)
  * double (double-precision floating point)

Can add the word `short` and `long` for `int`. `short` is at least 16 bits,
`long` is at least 32 bits and `int` is either 16 or 32 bits.

Can also specify `unsigned` (positive or zero) or `signed` for `int` and `char`.
