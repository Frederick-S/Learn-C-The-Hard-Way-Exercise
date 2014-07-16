# Exercise 7: More Variables, Some Math
## How To Break It
### Print out nul_byte variable with %s
```c
printf("%s\n", nul_byte);
```
And the warning:
```
$ make ex7
cc -Wall -g    ex7.c   -o ex7
ex7.c: In function ‘main’:
ex7.c:6:5: warning: format ‘%s’ expects argument of type ‘char *’, but argument 2 has type ‘int’ [-Wformat=]
     printf("%s\n", nul_byte);
     ^
```
It prints `(null)`:
```
$ ./ex7
(null)
```
### Print out nul_byte variable with %c
```c
printf("%c\n", nul_byte);
```
`make` runs successfully:
```
$ make ex7
cc -Wall -g    ex7.c   -o ex7
```
It prints nothing.
## Extra Credit
### Make the number you assign to universe_of_defects various sizes until you get a warning from the compiler.
I assigned `universe_of_defects` to `1L * 1024L * 1024L * 1024L * 1024L * 1024L * 1024L * 1024L`, and I met the warning:
```
$ make ex7
cc -Wall -g    ex7.c   -o ex7
ex7.c: In function ‘main’:
ex7.c:10:83: warning: integer overflow in expression [-Woverflow]
     long universe_of_defects = 1L * 1024L * 1024L * 1024L * 1024L * 1024L * 1024L * 1024L;
                                                                                   ^
```
### What do these really huge numbers actually print out?
```
$ ./ex7
The entire universe has 0 bugs.
```
### Change long to unsigned long and try to find the number that makes that one too big.
#### Change long to unsigned long
```c
unsigned long universe_of_defects = 1UL * 1024UL * 1024UL * 1024UL;
printf("The entire universe has %lu bugs.\n", universe_of_defects);
```
#### Try to find the number that makes that one too big
We can include `limits.h` and use `ULONG_MAX` to get the max value of `unsigned long`, then plus 1 to make it bigger:
```c
unsigned long universe_of_defects = ULONG_MAX + 1UL;
printf("The entire universe has %lu bugs.\n", universe_of_defects);
```
The output:
```
$ ./ex7
The entire universe has 0 bugs.
```
### Go search online to find out what unsigned does.
`unsigned` means the integer is not negative.
### Try to explain to yourself (before I do in the next exercise) why you can multiply a char and an int.
> Char values are encoded as numbers using the ASCII encoding.
