# Exercise 11: While-Loop And Boolean Expressions
## How To Break It
### Forget to initialize the first int i; so have it loop wrong.
```c
#include <stdio.h>

int main(int argc, char *argv[])
{
    // go through each string in argv

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
    }

    return 0;
}
```
```
$ make ex11

cc -Wall -g    ex11.c   -o ex11
ex11.c: In function ‘main’:
ex11.c:7:12: error: ‘i’ undeclared (first use in this function)
     while (i < argc) {
            ^
ex11.c:7:12: note: each undeclared identifier is reported only once for each function it appears in
ex11.c:13:11: warning: variable ‘states’ set but not used [-Wunused-but-set-variable]
     char *states[] = {
           ^
make: *** [ex11] Error 1
```
### Forget to initialize the second loop's i so that it retains the value from the end of the first loop. Now your second loop might or might not run.
It depends on the length of `argv`.
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

    while (i < num_states) {
        printf("state %d: %s\n", i, states[i]);
        i++;
    }

    return 0;
}
```
```
$ ./ex11
arg 0: ./ex11
state 1: Oregon
state 2: Washington
state 3: Texas

$ ./ex11 a b c d 
arg 0: ./ex11
arg 1: a
arg 2: b
arg 3: c
arg 4: d
```
### Forget to do a i++ increment at the end of the loop and you get a "forever loop", one of the dreaded problems of the first decade or two of programming.
```c
#include <stdio.h>

int main(int argc, char *argv[])
{
    // go through each string in argv

    int i = 0;
    while (i < argc) {
        printf("arg %d: %s\n", i, argv[i]);
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
    }

    return 0;
}
```
```
$ ./ex11 a
arg 0: ./ex11
arg 0: ./ex11
arg 0: ./ex11
arg 0: ./ex11
arg 0: ./ex11
arg 0: ./ex11
arg 0: ./ex11
arg 0: ./ex11
arg 0: ./ex11
arg 0: ./ex11
arg 0: ./ex11
arg 0: ./ex11
arg 0: ./ex11
arg 0: ./ex11
arg 0: ./ex11
arg 0: ./ex11
arg 0: ./ex11
arg 0: ./ex11
arg 0: ./ex11
arg 0: ./ex11
arg 0: ./ex11
arg 0: ./ex11
...

Infinite loop.
```
