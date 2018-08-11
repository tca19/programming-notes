Expert C Programming : Deep C Secrets
=====================================

Chapter 5: Thinking of Linking
------------------------------

> Program testing can be used to show the presence of bugs but never to show
> their absence. -- Dijkstra, 1972

### Libraries, Linking, and Loading
Compilers are in fact composed of many smaller programs (preprocessor,
syntactic/semantic checker, the assembler, the optimizer...), mainly because it
is easier to maintain many smaller files rather than a single large program.

`cc` can have flags specific to one step with `-W` and then a letter
representing the step.
