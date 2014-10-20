# Exercise 10: Arrays Of Strings, Looping
## How To Break It
### Take your favorite other language, and use it to run this program, but with as many command line arguments as possible. See if you can bust it by giving it way too many arguments.
Here is some simple python code to run this program:
```py
#!/usr/bin/env python

import sys
from subprocess import call

if len(sys.argv) > 1:
    try:
        times = int(sys.argv[1])
        arguments = [str(i) for i in range(times)]
        arguments.insert(0, "./ex10")

        # Run ex10
        call(arguments)
    except Exception, e:
        print e
```
And the usage:
```
$ ./run_ex10.py 5
arg 1: 0
arg 2: 1
arg 3: 2
arg 4: 3
arg 5: 4
state 0: California
state 1: Oregon
state 2: Washington
state 3: Texas
```
I bust it when the length of argument list is 5000000:
```
$ ./run_ex10.py 5000000
[Errno 7] Argument list too long
```
### Initialize i to 0 and see what that does. Do you have to adjust argc as well or does it just work? Why does 0-based indexing work here?
Initialize `i` to 0, it prints the name of the program:
```
arg 0: ./ex10
state 0: California
state 1: Oregon
state 2: Washington
state 3: Texas
```
It's not necessary to adjust `argc`, because it is the number of arguments passed into the program from the command line, including the name of the program. So if `i` is initialized to 0, and no additional arguments are passed in, `argc` is 1, `i < argc` still works. 

### Set num_states wrong so that it's a higher value and see what it does.
I set `num_states` to 5:
```
state 0: California
state 1: Oregon
state 2: Washington
state 3: Texas
state 4: (null)
```
Well, it seems work correctly, state 4 is null. Then I set `num_states` to 10, bad things happened:
```
state 0: California
state 1: Oregon
state 2: Washington
state 3: Texas
state 4: (null)
state 5: ▒▒财
state 6: (null)
state 7: ▒▒▒q
Segmentation fault (core dumped)
```
So we can not trust it. And here is an [answer](http://stackoverflow.com/questions/1239938/c-accesses-an-array-out-of-bounds-gives-no-error-why#1239977) that explains this behaviour.

## Extra Credit
### Figure out what kind of code you can put into the parts of a for-loop.
The first part is the initialization expression, usually it is used to initialize a loop counter. The second part is a boolean expression, it is evaluated at the beginning of each iteration. And the last part is the increment expression, it is used to increase or decrease the loop counter variable. 

The 3 parts can all be empty and moved into the for-loop body, but it's not a good practice.
```c
#include <stdio.h>

{
    int i = 0;

    // let's make our own array of strings
    char *states[] = {
        "California", "Oregon",
        "Washington", "Texas"
    };

    int num_states = 4;

    for (; ;) {
        if (i >= num_states) {
            break;
        }

        printf("state %d: %s\n", i, states[i]);

        i++;
    }

    return 0;
}
```
```
$ ./ex10
state 0: California
state 1: Oregon
state 2: Washington
state 3: Texas
```
### Look up how to use the ',' (comma) character to separate multiple statements in the parts of the for-loop, but between the ';' (semicolon) characters.
Here is an example:
```c
#include <stdio.h>

int main (int argc, char *argv[])
{
    int i = 0;

    // let's make our own array of strings
    char *states[] = {
        "California", "Oregon",
        "Washington", "Texas"
    };

    int num_states = 0;

    for (i = 0, num_states = 4; i < num_states; i++) {
        printf("state %d: %s\n", i, states[i]);
    }

    return 0;
}
```
```
$ ./ex10
state 0: California
state 1: Oregon
state 2: Washington
state 3: Texas
```
### Read what a NULL is and try to use it in one of the elements of the states array to see what it'll print.
NULL is a macro, defined in as a null pointer constant.

I set the last element in states array to `NULL`, and it printed `(null)`.
```c
#include <stdio.h>

int main (int argc, char *argv[])
{
    int i = 0;

    // let's make our own array of strings
    char *states[] = {
        "California", "Oregon",
        "Washington", NULL
    };

    int num_states = 4;

    for (i = 0; i < num_states; i++) {
        printf("state %d: %s\n", i, states[i]);
    }

    return 0;
}
```
```
$ ./ex10
state 0: California
state 1: Oregon
state 2: Washington
state 3: (null)
```
### See if you can assign an element from the states array to the argv array before printing both. Try the inverse.
Set an element from the states array to the argv array:
```c
#include <stdio.h>

int main (int argc, char *argv[])
{
    int i = 0;

    char *states[] = {
        "California", "Oregon",
        "Washington", "Texas"
    };

    argv[1] = states[1];

    // go through each string in argv
    // why am I skipping argv[0]?
    for (i = 1; i < argc; i++) {
        printf("arg %d: %s\n", i, argv[i]);
    }

    int num_states = 4;

    for (i = 0; i < num_states; i++) {
        printf("state %d: %s\n", i, states[i]);
    }

    return 0;
}
```
```
$ ./ex10 hello
arg 1: Oregon
state 0: California
state 1: Oregon
state 2: Washington
state 3: Texas
```
Set an element from the argv array to the states array:
```c
#include <stdio.h>

int main (int argc, char *argv[])
{
    int i = 0;

    char *states[] = {
        "California", "Oregon",
        "Washington", "Texas"
    };

    states[0] = argv[1];

    // go through each string in argv
    // why am I skipping argv[0]?
    for (i = 1; i < argc; i++) {
        printf("arg %d: %s\n", i, argv[i]);
    }

    int num_states = 4;

    for (i = 0; i < num_states; i++) {
        printf("state %d: %s\n", i, states[i]);
    }

    return 0;
}
```
```
$ ./ex10 hello
arg 1: hello
state 0: hello
state 1: Oregon
state 2: Washington
state 3: Texas
```
