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
Here are some conversion specifiers:

1. d, i

    > The int argument is converted to signed decimal notation. The precision, if any, gives the minimum number of digits
    that must appear; if the converted value requires fewer digits, it is padded on the left with zeros. The default
    precision is 1. When 0 is printed with an explicit precision 0, the output is empty.
    

    ```c
    printf("%i", 100);    // 100
    printf("%i", -100);   // -100
    printf("%d", 100);    // 100
    printf("%.10d", 100); // 0000000100
    ```
    
2. o, u, x, X

    > The unsigned int argument is converted to unsigned octal (o), unsigned decimal (u), or unsigned hexadecimal
    (x and X) notation. The letters abcdef are used for x conversions; the letters ABCDEF are used for X conversions. 
    The precision, if any, gives the minimum number of digits that must appear; if the converted value requires 
    fewer digits, it is padded on the left with zeros. The default precision is 1. When 0 is printed with an 
    explicit precision 0, the output is empty.
    
    ```c
    printf("%o", 07);      // 7
    printf("%u", 7);       // 7
    printf("%x", 0x7);     // 7
    printf("%x", 0xFF);    // ff
    printf("%X", 0xff);    // FF
    printf("%.10X", 0xff); // 00000000FF
    ```
    
3. e, E

    > The double argument is rounded and converted in the style [-]d.ddde±dd where there is one digit before 
    the decimal-point character and the number of digits after it is equal to the precision; if the precision 
    is missing, it is taken as 6; if the precision is zero, no decimal-point character appears. An E conversion 
    uses the letter E (rather than e) to introduce the exponent. The exponent always contains at least two 
    digits; if the value is zero, the exponent is 00.
    
    ```c
    printf("%e", 100.0);    // 1.000000e+02
    printf("%.0e", 100.0);  // 1e+02
    printf("%.10e", 100.0); // 1.0000000000e+02
    ```
    
4. f, F

    > The double argument is rounded and converted to decimal notation in the style [-]ddd.ddd, where the number 
    of digits after the decimal-point character is equal to the precision specification. If the precision is 
    missing, it is taken as 6; if the precision is explicitly zero, no decimal-point character appears. 
    If a decimal point appears, at least one digit appears before it.
    
    ```c
    printf("%f", 100.0);    // 100.000000
    printf("%.0f", 100.0);  // 100
    printf("%.10f", 100.0); // 100.0000000000
    ```
    
5. g, G

    > The double argument is converted in style f or e (or F or E for G conversions). The precision specifies 
    the number of significant digits. If the precision is missing, 6 digits are given; if the precision is 
    zero, it is treated as 1. Style e is used if the exponent from its conversion is less than -4 or greater 
    than or equal to the precision. Trailing zeros are removed from the fractional part of the result; a 
    decimal point appears only if it is followed by at least one digit.
    
    ```c
    printf("%f\n", 10000000.0); // 10000000.000000
    printf("%e\n", 10000000.0); // 1.000000e+07
    printf("%g\n", 10000000.0); // 1e+07
    
    printf("%f\n", 0.123456);   // 0.123456
    printf("%e\n", 0.123456);   // 1.234560e-01
    printf("%g\n", 0.123456);   // 0.123456
    ```
