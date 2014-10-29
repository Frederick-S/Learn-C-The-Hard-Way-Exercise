# Exercise 14: Writing And Using Functions
## How To Break It
### Confuse the compiler by removing the forward declarations so it complains about can_print_it and print_letters.
```c
#include <stdio.h>
#include <ctype.h>

void print_arguments(int argc, char *argv[])
{
    int i = 0;
    
    for (i = 0; i < argc; i++) {
        print_letters(argv[i]);
    }
}

void print_letters(char arg[])
{
    int i = 0;
    
    for (i = 0; arg[i] != '\0'; i++) {
        char ch = arg[i];
        
        if (can_print_it(ch)) {
            printf("'%c' == %d ", ch, ch);
        }
    }
    
    printf("\n");
}

int can_print_it(char ch)
{
    return isalpha(ch) || isblank(ch);
}

int main(int argc, char *argv[])
{
    print_arguments(argc, argv);
    return 0;
}
```
```
cc -Wall -g    ex14.c   -o ex14
ex14.c: In function ‘print_arguments’:
ex14.c:9:9: warning: implicit declaration of function ‘print_letters’ [-Wimplicit-function-declaration]
         print_letters(argv[i]);
         ^
ex14.c: At top level:
ex14.c:13:6: warning: conflicting types for ‘print_letters’ [enabled by default]
 void print_letters(char arg[])
      ^
ex14.c:9:9: note: previous implicit declaration of ‘print_letters’ was here
         print_letters(argv[i]);
         ^
ex14.c: In function ‘print_letters’:
ex14.c:20:9: warning: implicit declaration of function ‘can_print_it’ [-Wimplicit-function-declaration]
         if (can_print_it(ch)) {
         ^
ex14.c: At top level:
ex14.c:28:5: error: conflicting types for ‘can_print_it’
 int can_print_it(char ch)
     ^
ex14.c:29:1: note: an argument type that has a default promotion can’t match an empty parameter name list declaration
 {
 ^
ex14.c:20:13: note: previous implicit declaration of ‘can_print_it’ was here
         if (can_print_it(ch)) {
             ^
make: *** [ex14] Error 1
```

### When you call print_arguments inside main try adding 1 to argc so that it goes past the end of the argv array.
```c
#include <stdio.h>
#include <ctype.h>

// forward declarations
int can_print_it(char ch);
void print_letters(char arg[]);

void print_arguments(int argc, char *argv[])
{
    int i = 0;
    
    for (i = 0; i < argc; i++) {
        print_letters(argv[i]);
    }
}

void print_letters(char arg[])
{
    int i = 0;
    
    for (i = 0; arg[i] != '\0'; i++) {
        char ch = arg[i];
        
        if (can_print_it(ch)) {
            printf("'%c' == %d ", ch, ch);
        }
    }
    
    printf("\n");
}

int can_print_it(char ch)
{
    return isalpha(ch) || isblank(ch);
}

int main(int argc, char *argv[])
{
    print_arguments(argc + 1, argv);
    return 0;
}
```
```
$ ./ex14
'e' == 101 'x' == 120
Segmentation fault (core dumped)
```

## Extra Credit
### Rework these functions so that you have fewer functions. For example, do you really need can_print_it?
```c
#include <stdio.h>
#include <ctype.h>

// forward declarations
void print_letters(char arg[]);

void print_letters(char arg[])
{
    int i = 0;
    
    for (i = 0; arg[i] != '\0'; i++) {
        char ch = arg[i];
        
        if (isalpha(ch) || isblank(ch)) {
            printf("'%c' == %d ", ch, ch);
        }
    }
    
    printf("\n");
}

int main(int argc, char *argv[])
{
    int i = 0;
    
    for (i = 0; i < argc; i++) {
        print_letters(argv[i]);
    }
    
    return 0;
}
```
```
$ ./ex14
'e' == 101 'x' == 120
```

### Have print_arguments figure how long each argument string is using the strlen function, and then pass that length to print_letters. Then, rewrite print_letters so it only processes this fixed length and doesn't rely on the '\0' terminator. You will need the #include <string.h> for this.
