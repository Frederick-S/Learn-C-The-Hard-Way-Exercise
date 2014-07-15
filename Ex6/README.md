# Exercise 6: Types Of Variables
## Extra Credit
### Come up with other ways to break this C code by changing the printf, then fix them.
1. Change `%d` to `%s` in `printf("You are %d miles away.\n", distance);`

    ```
    $ make ex6
    cc -Wall -g    ex6.c   -o ex6
    ex6.c: In function ‘main’:
    ex6.c:12:5: warning: format ‘%s’ expects argument of type ‘char *’, but argument 2 has type ‘int’ [-Wformat=]
         printf("You are %s miles away.\n", distance);
         ^
    ```
2. Change `%f` to `%d` in `printf("You have %f levels of power.\n", power);`

    ```
    $ make ex6
    cc -Wall -g    ex6.c   -o ex6
    ex6.c: In function ‘main’:
    ex6.c:13:5: warning: format ‘%d’ expects argument of type ‘int’, but argument 2 has type ‘double’ [-Wformat=]
         printf("You have %d levels of power.\n", power);
         ^
    ```
3. Remove `last_name` in `printf("My whole name is %s %c. %s.\n", first_name, initial, last_name);`

    ```
    $ make ex6
    cc -Wall -g    ex6.c   -o ex6
    ex6.c: In function ‘main’:
    ex6.c:18:5: warning: format ‘%s’ expects a matching ‘char *’ argument [-Wformat=]
         printf("My whole name is %s %c. %s.\n", first_name, initial);
         ^
    ```
    
### Go search for "printf formats" and try using a few of the more exotic ones.
Check [Exercise 3: Formatted Printing](https://github.com/Frederick-S/Learn-C-The-Hard-Way-Exercise/tree/master/Ex3#run-man-3-printf-and-read-about-the-other--format-characters-you-can-use-these-should-look-familiar-if-you-used-them-in-other-languages-printf-is-where-they-come-from).
### Research how many different ways you can write a number. Try octal, hexadecimal, and others you can find.

1. Octal number

    ```c
    int number = 07;
    ```
2. Hexadecimal number

    ```c
    int number = 0x7a;
    ```
3. Exponential number 

    ```c
    double number = 1.0e+2;
    ```

### Try printing an empty string that's just "".
```c
#include <stdio.h>

int main(int argc, char *argv[])
{
    printf("");
    
    return 0; 
}
```
But warning occurs:
```
$ make ex6
cc -Wall -g    ex6.c   -o ex6
ex6.c: In function ‘main’:
ex6.c:5:5: warning: zero-length gnu_printf format string [-Wformat-zero-length]
     printf("");
     ^
```
You can use this one:
```c
#include <stdio.h>

int main(int argc, char *argv[])
{
    printf("%s", "");
    
    return 0; 
}
```
