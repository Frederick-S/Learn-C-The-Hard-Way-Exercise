# Exercise 3: Formatted Printing
## Extra Credit
### Find as many other ways to break ex3.c as you can.
1. Remove `%d` in `printf("I am %d years old.\n", age);`

    ```
    $ make ex3
    cc -Wall -g    ex3.c   -o ex3
    ex3.c: In function ‘main’:
    ex3.c:8:5: warning: too many arguments for format [-Wformat-extra-args]
         printf("I am years old.\n", age);
         ^
    ```
2. Replace `%d` with `%s` in `printf("I am %d years old.\n", age);`

    ```
    $ make ex3
    cc -Wall -g    ex3.c   -o ex3
    ex3.c: In function ‘main’:
    ex3.c:8:5: warning: format ‘%s’ expects argument of type ‘char *’, but argument 2 has type ‘int’ [-Wformat=]
         printf("I am %s years old.\n", age);
         ^
    ```
3. Change `printf("I am %d years old.\n", age);` to `printf("I am %d years old.\n", age, height);`

    ```
    $ make ex3
    cc -Wall -g    ex3.c   -o ex3
    ex3.c: In function ‘main’:
    ex3.c:8:5: warning: too many arguments for format [-Wformat-extra-args]
         printf("I am %d years old.\n", age, height);
         ^
    ```

### Run man 3 printf and read about the other '%' format characters you can use. These should look familiar if you used them in other languages (printf is where they come from).
1. d, i

    ```
    The int argument is converted to signed decimal notation. The precision, if any, gives the minimum number of digits
    that must appear; if the converted value requires fewer digits, it is padded on the left with zeros. The default
    precision is 1. When 0 is printed with an explicit precision 0, the output is empty.
    ```

    ```c
    printf("%d", 100);    // 100
    printf("%.10d", 100); // 0000000100
    ```
    
2. o, u, x, X
