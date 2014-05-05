# Exercise 1: Dust Off That Compiler
## Extra Credit
### Open the ex1 file in your text editor and change or delete random parts. Try running it and see what happens.
Here are some examples:  

1. Change `int main` to `main`

    ```
    $ make ex1
    cc     ex1.c   -o ex1
    ex1.c:3:1: warning: type specifier missing, defaults to 'int' [-Wimplicit-int]
    main(int argc, char *argv[])
    ^~~~
    1 warning generated.
    ```
2. Remove the second brace

    ```
    $ make ex1
    cc     ex1.c   -o ex1
    ex1.c:7:1: error: expected '}'
    ^
    ex1.c:4:1: note: to match this '{'
    {
    ^
    1 error generated.
    make: *** [ex1] Error 1
    ```
3. Type `put` instead of `puts`

    ```
    $ make ex1
    cc     ex1.c   -o ex1
    ex1.c:5:5: warning: implicit declaration of function 'put' is invalid in C99
          [-Wimplicit-function-declaration]
        put("Hello world.");
        ^
    1 warning generated.
    Undefined symbols for architecture x86_64:
      "_put", referenced from:
          _main in ex1-f86544.o
    ld: symbol(s) not found for architecture x86_64
    clang: error: linker command failed with exit code 1 (use -v to see invocation)
    make: *** [ex1] Error 1
    ```
