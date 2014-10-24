# Exercise 13: Switch Statement
## How To Break It
### Forget a break and it'll run two or more blocks of code you don't want it to run.
```c
#include <stdio.h>

int main(int argc, char *argv[])
{
    if (argc != 2) {
        printf("ERROR: You need one argument.\n");

        // this is how you abort a program
        return 1;
    }

    int i = 0;
    for (i = 0; argv[1][i] != '\0'; i++) {
        char letter = argv[1][i];

        switch (letter) {
            case 'a':
            case 'A':
                printf("%d: 'A'\n", i);
            case 'e':
            case 'E':
                printf("%d: 'E'\n", i);
                break;
            case 'i':
            case 'I':
                printf("%d: 'I'\n", i);
                break;
            case 'o':
            case 'O':
                printf("%d: 'O'\n", i);
                break;
            case 'u':
            case 'U':
                printf("%d: 'U'\n", i);
                break;
            case 'y':
            case 'Y':
                if (i > 2) {
                    // it's only sometimes Y
                    printf("%d: 'Y'\n", i);
                }

                break;
            default:
                printf("%d: %c is not a vowel\n", i, letter);
        }
    }

    return 0;
}
```
```
$ ./ex13 Apple
0: 'A'
0: 'E'
1: p is not a vowel
2: p is not a vowel
3: l is not a vowel
4: 'E'
```
### Forget a default and have it silently ignore values you forgot.
```c
#include <stdio.h>

int main(int argc, char *argv[])
{
    if (argc != 2) {
        printf("ERROR: You need one argument.\n");

        // this is how you abort a program
        return 1;
    }

    int i = 0;
    for (i = 0; argv[1][i] != '\0'; i++) {
        char letter = argv[1][i];

        switch (letter) {
            case 'a':
            case 'A':
                printf("%d: 'A'\n", i);
            case 'e':
            case 'E':
                printf("%d: 'E'\n", i);
                break;
            case 'i':
            case 'I':
                printf("%d: 'I'\n", i);
                break;
            case 'o':
            case 'O':
                printf("%d: 'O'\n", i);
                break;
            case 'u':
            case 'U':
                printf("%d: 'U'\n", i);
                break;
            case 'y':
            case 'Y':
                if (i > 2) {
                    // it's only sometimes Y
                    printf("%d: 'Y'\n", i);
                }

                break;
        }
    }

    return 0;
}
```
```
$ ./ex13 Zed
1: 'E'
```
### Accidentally put in variable into the switch that evaluates to something unexpected, like an int that becomes weird values.
```

```
