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
```c
#include <stdio.h>

int main(int argc, char *argv[])
{
    int i = 0;

    if (argc == 1) {
        printf("You only have one argument. You suck.\n");
    } else if (argc & 1) {
        printf("Here's your odd arguments:\n");

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
$ ./ex12 a b
Here's your odd arguments:
./ex12 a b
```
### Go back to Exercises 10 and 11, and use if-statements to make the loops exit early. You'll need the break statement to do that. Go read about it.
Ex10:
```c
#include <stdio.h>

int main (int argc, char *argv[])
{
    int i = 0;

    // go through each string in argv
    // why am I skipping argv[0]?
    for (i = 1; i < argc; i++) {
        printf("arg %d: %s\n", i, argv[i]);
    }

    // let's make our own array of strings
    char *states[] = {
        "California", "Oregon",
        "Washington", "Texas"
    };

    int num_states = 4;

    for (i = 0; i < num_states; i++) {
        if (i == 2) {
            break;
        }

        printf("state %d: %s\n", i, states[i]);
    }

    return 0;
}
```
```
$ ./ex10
state 0: California
state 1: Oregon
```
Ex11:
```c
#include <stdio.h>

int main(int argc, char *argv[])
{
    // go through each string in argv

    int i = 0;
    while (i < argc) {
        printf("arg %d: %s\n", i, argv[i]);
        i++;
    }

    // let's make our own array of strings
    char *states[] = {
        "California", "Oregon",
        "Washington", "Texas"
    };

    int num_states = 4;

    // watch for this
    i = 0;
    while (i < num_states) {
        printf("state %d: %s\n", i, states[i]);
        i++;

        if (i == 2) {
            break;
        }
    }

    return 0;
}
```
```
$ ./ex11
arg 0: ./ex11
state 0: California
state 1: Oregon
```
### Is the first test really saying the right thing? To you the "first argument" isn't the same first argument a user entered. Fix it.
```c
#include <stdio.h>

int main(int argc, char *argv[])
{
    int i = 0;

    if (argc == 1) {
        printf("You don't have any argument.\n");
    } else if (argc == 2) {
        printf("You only have one argument. You suck.\n");
    } else if (argc > 1 && argc < 4) {
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
$ ./ex12
You don't have any argument.

$ ./ex12 a
You only have one argument. You suck.

$ ./ex12 a b
Here's your arguments:
./ex12 a b
```
