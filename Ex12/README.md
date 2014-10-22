# Exercise 12: If, Else-If, Else
## How To Break It
### Remove the else at the end and it won't catch the edge case.
```c
#include <stdio.h>

int main(int argc, char *argv[])
{
    int i = 0;

    if (argc == 1) {
        printf("You only have one argument. You suck.\n");
    } else if (argc > 1 && argc < 4) {
        printf("Here's your arguments:\n");

        for (i = 0; i < argc; i++) {
            printf("%s ", argv[i]);
        }

        printf("\n");
    }

    return 0;
}
```
```
$ ./ex12 a b
Here's your arguments:
./ex12 a b

$ ./ex12 a b c
// Doesn't print anything
```
### Change the && to a || so you get an "or" instead of "and" test and see how that works.
```c
#include <stdio.h>

int main(int argc, char *argv[])
{
    int i = 0;

    if (argc == 1) {
        printf("You only have one argument. You suck.\n");
    } else if (argc > 1 || argc < 4) {
        printf("Here's your arguments:\n");

        for (i = 0; i < argc; i++) {
            printf("%s ", argv[i]);
        }

        printf("\n");
    } else {
        printf("You have too many arguments. You suck.\n");
    }

    return 0;
}
```
```
$ ./ex12 a b c d
Here's your arguments:
./ex12 a b c d
```
## Extra Credit
### You were briefly introduced to &&, which does an "and" comparison, so go research online the different "boolean operators".
[Wiki](http://en.wikipedia.org/wiki/Operators_in_C_and_C%2B%2B#Logical_operators).
### Write a few more test cases for this program to see what you can come up with.
