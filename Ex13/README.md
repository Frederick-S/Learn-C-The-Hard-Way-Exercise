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
## Extra Credit
### Write another program that uses math on the letter to convert it to lowercase, and then remove all the extraneous uppercase letters in the switch.
```c
#include <stdio.h>

char toLowerCase(char letter)
{
    if (letter >= 97 && letter <= 122) {
        return letter;
    } else if (letter >= 65 && letter <=90) {
        return letter + 32;
    } else {
        return letter;
    }
}

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
        char lowerCaseLetter = toLowerCase(letter);

        switch (lowerCaseLetter) {
            case 'a':
                printf("%d: 'A'\n", i);
                break;
            case 'e':
                printf("%d: 'E'\n", i);
                break;
            case 'i':
                printf("%d: 'I'\n", i);
                break;
            case 'o':
                printf("%d: 'O'\n", i);
                break;
            case 'u':
                printf("%d: 'U'\n", i);
                break;
            case 'y':
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
$ ./ex13 "Zed Shaw"
0: Z is not a vowel
1: 'E'
2: d is not a vowel
3:   is not a vowel
4: S is not a vowel
5: h is not a vowel
6: 'A'
7: w is not a vowel
```

### Use the ',' (comma) to initialize letter in the for-loop.
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
    char letter = 0;
    for (i = 0; letter = argv[1][i], letter != '\0'; i++) {
        switch (letter) {
            case 'a':
            case 'A':
                printf("%d: 'A'\n", i);
                break;
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
$ ./ex13 "Zed Shaw"
0: Z is not a vowel
1: 'E'
2: d is not a vowel
3:   is not a vowel
4: S is not a vowel
5: h is not a vowel
6: 'A'
7: w is not a vowel
```
### Make it handle all of the arguments you pass it with yet another for-loop.
```c
#include <stdio.h>

int main(int argc, char *argv[])
{
    if (argc == 1) {
        printf("ERROR: You have no argument.\n");
        
        // this is how you abort a program
        return 1;
    }

    int j = 0;
    int i = 0;
    char letter = 0;
    char *arr;
    
    for (j = 1; j < argc; j++) {
        arr = argv[j];
        printf("Argument %d: %s\n", j, arr);
        
        for (i = 0; letter = arr[i], letter != '\0'; i++) {
            switch (letter) {
                case 'a':
                case 'A':
                    printf("%d: 'A'\n", i);
                    break;
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
    }

    return 0;
}
```
```
$ ./ex13 Zed Shaw
Argument 1: Zed
0: Z is not a vowel
1: 'E'
2: d is not a vowel
Argument 2: Shaw
0: S is not a vowel
1: h is not a vowel
2: 'A'
3: w is not a vowel
```

### Convert this switch-statement to an if-statement. Which do you like better?
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

        if (letter == 'a' || letter == 'A') {
            printf("%d: 'A'\n", i);
        } else if (letter == 'e' || letter == 'E') {
            printf("%d: 'E'\n", i);
        } else if (letter == 'i' || letter == 'I') {
            printf("%d: 'I'\n", i);
        } else if (letter == 'o' || letter == 'O') {
            printf("%d: 'O'\n", i);
        } else if (letter == 'u' || letter == 'U') {
            printf("%d: 'U'\n", i);
        } else if (letter == 'y' || letter == 'Y') {
            if (i > 2) {
                // it's only sometimes Y
                printf("%d: 'Y'\n", i);
            }
        } else {
            printf("%d: %c is not a vowel\n", i, letter);
        }
    }

    return 0;
}
```
```
$ ./ex13 "Zed Shaw"
0: Z is not a vowel
1: 'E'
2: d is not a vowel
3:   is not a vowel
4: S is not a vowel
5: h is not a vowel
6: 'A'
7: w is not a vowel
```

### In the case for 'Y' I have the break outside the if-statement. What's the impact of this and what happens if you move it inside the if-statement. Prove to yourself that you're right.
If the break is outside the if-statement, then it can correctly end the switch-statement, otherwise, it will continue executing the code in `default` branch under some conditions.

break outside the if-statement:
```
$ ./ex13 you
1: 'O'
2: 'U'
```
break inside the if-statement:
```
$ ./ex13 you
0: y is not a vowel
1: 'O'
2: 'U'
```
