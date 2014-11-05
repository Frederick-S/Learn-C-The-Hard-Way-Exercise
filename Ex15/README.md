# Exercise 15: Pointers Dreaded Pointers
## How To Break It
### Try to make cur_age point at names. You'll need to use a C cast to force it, so go look that up and try to figure it out.
```c
#include <stdio.h>

int main(int argc, char *argv[])
{
    // create two arrays we care about
    int ages[] = { 23, 43, 12, 89, 2 };
    char *names[] = {
        "Alan", "Frank",
        "Mary", "John", "Lisa"
    };

    // safely get the size of ages
    int count = sizeof(ages) / sizeof(int);
    int i = 0;

    // first way using indexing
    for (i = 0; i < count; i++) {
        printf("%s has %d years alive.\n", names[i], ages[i]);
    }

    printf("---\n");

    // setup the pointers to the start of the arrays
    int *cur_age = (int*)names;
    char **cur_name = names;

    // second way using pointers
    for (i = 0; i < count; i++) {
        printf("%s is %d years old.\n", *(cur_name + i), *(cur_age + i));
    }

    printf("---\n");

    // third way, pointers are just arrays
    for (i = 0; i < count; i++) {
        printf("%s is %d years old again.\n", cur_name[i], cur_age[i]);
    }

    printf("---\n");

    // fourth way with pointers in a stuipd conplex way
    for (cur_name = names, cur_age = ages; (cur_age - ages) < count; cur_name++, cur_age++) {
        printf("%s lived %d years so far.\n", *cur_name, *cur_age);
    }

    return 0;
}
```
```
$ ./ex15
Alan has 23 years alive.
Frank has 43 years alive.
Mary has 12 years alive.
John has 89 years alive.
Lisa has 2 years alive.
---
Alan is 4196324 years old.
Frank is 0 years old.
Mary is 4196329 years old.
John is 0 years old.
Lisa is 4196335 years old.
---
Alan is 4196324 years old again.
Frank is 0 years old again.
Mary is 4196329 years old again.
John is 0 years old again.
Lisa is 4196335 years old again.
---
Alan lived 23 years so far.
Frank lived 43 years so far.
Mary lived 12 years so far.
John lived 89 years so far.
Lisa lived 2 years so far.
```

### In the final for-loop try getting the math wrong in weird ways.
```c
#include <stdio.h>

int main(int argc, char *argv[])
{
    // create two arrays we care about
    int ages[] = { 23, 43, 12, 89, 2 };
    char *names[] = {
        "Alan", "Frank",
        "Mary", "John", "Lisa"
    };

    // safely get the size of ages
    int count = sizeof(ages) / sizeof(int);
    int i = 0;

    // first way using indexing
    for (i = 0; i < count; i++) {
        printf("%s has %d years alive.\n", names[i], ages[i]);
    }

    printf("---\n");

    // setup the pointers to the start of the arrays
    int *cur_age = ages;
    char **cur_name = names;

    // second way using pointers
    for (i = 0; i < count; i++) {
        printf("%s is %d years old.\n", *(cur_name + i), *(cur_age + i));
    }

    printf("---\n");

    // third way, pointers are just arrays
    for (i = 0; i < count; i++) {
        printf("%s is %d years old again.\n", cur_name[i], cur_age[i]);
    }

    printf("---\n");

    // fourth way with pointers in a stuipd conplex way
    for (cur_name = names, cur_age = ages; (cur_age - ages) <= count; cur_name++, cur_age++) {
        printf("%s lived %d years so far.\n", *cur_name, *cur_age);
    }

    return 0;
}
```
```
$ ./ex15
Alan has 23 years alive.
Frank has 43 years alive.
Mary has 12 years alive.
John has 89 years alive.
Lisa has 2 years alive.
---
Alan is 23 years old.
Frank is 43 years old.
Mary is 12 years old.
John is 89 years old.
Lisa is 2 years old.
---
Alan is 23 years old again.
Frank is 43 years old again.
Mary is 12 years old again.
John is 89 years old again.
Lisa is 2 years old again.
---
Alan lived 23 years so far.
Frank lived 43 years so far.
Mary lived 12 years so far.
John lived 89 years so far.
Lisa lived 2 years so far.
(null) lived 0 years so far.
```

### Try rewriting the loops so they start at the end of the arrays and go to the beginning. This is harder than it looks.
```c
#include <stdio.h>

int main(int argc, char *argv[])
{
    // create two arrays we care about
    int ages[] = { 23, 43, 12, 89, 2 };
    char *names[] = {
        "Alan", "Frank",
        "Mary", "John", "Lisa"
    };
    
    // safely get the size of ages
    int count = sizeof(ages) / sizeof(int);
    int i = 0;
    
    // first way using indexing
    for (i = count - 1; i >= 0; i--) {
        printf("%s has %d years alive.\n", names[i], ages[i]);
    }
    
    printf("---\n");
    
    // setup the pointers to the start of the arrays
    int *cur_age = ages;
    char **cur_name = names;
    
    // second way using pointers
    for (i = count - 1; i >= 0; i--) {
        printf("%s is %d years old.\n", *(cur_name + i), *(cur_age + i));
    }
    
    printf("---\n");
    
    // third way, pointers are just arrays
    for (i = count - 1; i >= 0; i--) {
        printf("%s is %d years old again.\n", cur_name[i], cur_age[i]);
    }
    
    printf("---\n");
    
    // fourth way with pointers in a stuipd conplex way
    for (cur_name = names + count - 1, cur_age = ages + count - 1; (cur_age - ages) >= 0; cur_name--, cur_age--) {
        printf("%s lived %d years so far.\n", *cur_name, *cur_age);
    }
    
    return 0;
}
```
```
$ ./ex15
Lisa has 2 years alive.
John has 89 years alive.
Mary has 12 years alive.
Frank has 43 years alive.
Alan has 23 years alive.
---
Lisa is 2 years old.
John is 89 years old.
Mary is 12 years old.
Frank is 43 years old.
Alan is 23 years old.
---
Lisa is 2 years old again.
John is 89 years old again.
Mary is 12 years old again.
Frank is 43 years old again.
Alan is 23 years old again.
---
Lisa lived 2 years so far.
John lived 89 years so far.
Mary lived 12 years so far.
Frank lived 43 years so far.
Alan lived 23 years so far.
```

## Extra Credit
### Rewrite all the array usage in this program so that it's pointers.
```c
for (i = 0; i < count; i++) {
    printf("%s has %d years alive.\n", *(names + i), *(ages + i));
}
```

### Rewrite all the pointer usage so they're arrays.
I don't quite get it, it's already include in the original code.

### Go back to some of the other programs that use arrays and try to use pointers instead.
Rewrite exercise 9:
```c
#include <stdio.h>

int main(int argc, char *argv[])
{
    int numbers[4] = {0};
    char name[4] = {'a'};

    int *pointerNumbers = numbers;
    char *pointerName = name;
    
    // first, print them out raw
    printf("numbers: %d %d %d %d\n", *pointerNumbers, *(pointerNumbers + 1), *(pointerNumbers + 2), *(pointerNumbers + 3));

    printf("name each: %c %c %c %c\n", *pointerName, *(pointerName + 1), *(pointerName + 2), *(pointerName + 3));

    printf("name: %s\n", pointerName);

    // setup the numbers
    *pointerNumbers = 1;
    *(pointerNumbers + 1) = 2;
    *(pointerNumbers + 2) = 3;
    *(pointerNumbers + 3) = 4;

    // setup the name
    *pointerName = 'Z';
    *(pointerName + 1) = 'e';
    *(pointerName + 2) = 'd';
    *(pointerName + 3) = '\0';

    // then print them out initialized
    printf("numbers: %d %d %d %d\n", *pointerNumbers, *(pointerNumbers + 1), *(pointerNumbers + 2), *(pointerNumbers + 3));

    printf("name each: %c %c %c %c\n", *pointerName, *(pointerName + 1), *(pointerName + 2), *(pointerName + 3));

    // print the name like a string
    printf("name: %s\n", pointerName);

    // another way to use name
    char *another = "Zed";
   
    printf("another: %s\n", another);

    printf("another each: %c %c %c %c\n", another[0], another[1], another[2], another[3]);

    return 0;
}
```
```
$ ./ex9
numbers: 0 0 0 0
name each: a
name: a
numbers: 1 2 3 4
name each: Z e d
name: Zed
another: Zed
another each: Z e d
```

### Process command line arguments using just pointers similar to how you did names in this one.
Rewrite exercise 14:
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
        print_letters(*(argv + i));
    }
}

void print_letters(char arg[])
{
    int i = 0;

    for (i = 0; *(arg + i) != '\0'; i++) {
        char ch = *(arg + i);

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
$ ./ex14 hi this is cool
'e' == 101 'x' == 120
'h' == 104 'i' == 105
't' == 116 'h' == 104 'i' == 105 's' == 115
'i' == 105 's' == 115
'c' == 99 'o' == 111 'o' == 111 'l' == 108
```

### Play with combinations of getting the value of and the address of things.
```c
#include <stdio.h>

int main(int argc, char *argv[])
{
    char *names[] = {
        "Alan", "Frank",
        "Mary", "John", "Lisa"
    };

    int i = 0;
    for (i = 0; i < 5; i++) {
        printf("value: %s, address: %p\n", *(names + i), names + i);
    }

    return 0;
}
```
```
$ ./ex15
value: Alan, address: 0x7fff95473640
value: Frank, address: 0x7fff95473648
value: Mary, address: 0x7fff95473650
value: John, address: 0x7fff95473658
value: Lisa, address: 0x7fff95473660
```

### Add another for-loop at the end that prints out the addresses these pointers are using. You'll need the %p format for printf.
```c
#include <stdio.h>

int main(int argc, char *argv[])
{
    // create two arrays we care about
    int ages[] = { 23, 43, 12, 89, 2 };
    char *names[] = {
        "Alan", "Frank",
        "Mary", "John", "Lisa"
    };

    // safely get the size of ages
    int count = sizeof(ages) / sizeof(int);
    int i = 0;

    // first way using indexing
    for (i = 0; i < count; i++) {
        printf("%s has %d years alive.\n", names[i], ages[i]);
    }

    printf("---\n");

    // setup the pointers to the start of the arrays
    int *cur_age = ages;
    char **cur_name = names;

    // second way using pointers
    for (i = 0; i < count; i++) {
        printf("%s is %d years old.\n", *(cur_name + i), *(cur_age + i));
    }

    printf("---\n");

    // third way, pointers are just arrays
    for (i = 0; i < count; i++) {
        printf("%s is %d years old again.\n", cur_name[i], cur_age[i]);
    }

    printf("---\n");

    // fourth way with pointers in a stuipd conplex way
    for (cur_name = names, cur_age = ages; (cur_age - ages) < count; cur_name++, cur_age++) {
        printf("%s lived %d years so far.\n", *cur_name, *cur_age);
    }

    printf("---\n");

    // print address
    for (i = 0; i < count; i++) {
        printf("The address of value %d is: %p, and the address of value %s is: %p\n", ages[i], ages + i, names[i], names + i);
    }

    return 0;
}
```
```
$ ./ex15
Alan has 23 years alive.
Frank has 43 years alive.
Mary has 12 years alive.
John has 89 years alive.
Lisa has 2 years alive.
---
Alan is 23 years old.
Frank is 43 years old.
Mary is 12 years old.
John is 89 years old.
Lisa is 2 years old.
---
Alan is 23 years old again.
Frank is 43 years old again.
Mary is 12 years old again.
John is 89 years old again.
Lisa is 2 years old again.
---
Alan lived 23 years so far.
Frank lived 43 years so far.
Mary lived 12 years so far.
John lived 89 years so far.
Lisa lived 2 years so far.
---
The address of value 23 is: 0x7fff258e4ab0, and the address of value Alan is: 0x7fff258e4ad0
The address of value 43 is: 0x7fff258e4ab4, and the address of value Frank is: 0x7fff258e4ad8
The address of value 12 is: 0x7fff258e4ab8, and the address of value Mary is: 0x7fff258e4ae0
The address of value 89 is: 0x7fff258e4abc, and the address of value John is: 0x7fff258e4ae8
The address of value 2 is: 0x7fff258e4ac0, and the address of value Lisa is: 0x7fff258e4af0
```

### Rewrite this program to use a function for each of the ways you're printing out things. Try to pass pointers to these functions so they work on the data. Remember you can declare a function to accept a pointer, but just use it like an array.
```c
#include <stdio.h>

void print1(int ages[], char *names[], int count)
{
    int i = 0;
    
    for (i = 0; i < count; i++) {
        printf("%s has %d years alive.\n", names[i], ages[i]);
    }
}

void print2(int *ages, char **names, int count)
{
    int i = 0;
    
    for (i = 0; i < count; i++) {
        printf("%s is %d years old.\n", *(names + i), *(ages + i));
    }
}

void print3(int *ages, char **names, int count)
{
    int i = 0;
    
    for (i = 0; i < count; i++) {
        printf("%s is %d years old again.\n", names[i], ages[i]);
    }
}

void print4(int ages[], char *names[], int *cur_age, char **cur_name, int count)
{
    for (cur_name = names, cur_age = ages; (cur_age - ages) < count; cur_name++, cur_age++) {
        printf("%s lived %d years so far.\n", *cur_name, *cur_age);
    }
}

int main(int argc, char *argv[])
{
    // create two arrays we care about
    int ages[] = { 23, 43, 12, 89, 2 };
    char *names[] = {
        "Alan", "Frank",
        "Mary", "John", "Lisa"
    };
    
    // safely get the size of ages
    int count = sizeof(ages) / sizeof(int);
    
    // first way using indexing
    print1(ages, names, count);
    
    printf("---\n");
    
    // setup the pointers to the start of the arrays
    int *cur_age = ages;
    char **cur_name = names;
    
    // second way using pointers
    print2(cur_age, cur_name, count);
    
    printf("---\n");
    
    // third way, pointers are just arrays
    print3(cur_age, cur_name, count);
    
    printf("---\n");
    
    // fourth way with pointers in a stuipd conplex way
    print4(ages, names, cur_age, cur_name, count);
    
    return 0;
}
```
```
$ ./ex15
Alan has 23 years alive.
Frank has 43 years alive.
Mary has 12 years alive.
John has 89 years alive.
Lisa has 2 years alive.
---
Alan is 23 years old.
Frank is 43 years old.
Mary is 12 years old.
John is 89 years old.
Lisa is 2 years old.
---
Alan is 23 years old again.
Frank is 43 years old again.
Mary is 12 years old again.
John is 89 years old again.
Lisa is 2 years old again.
---
Alan lived 23 years so far.
Frank lived 43 years so far.
Mary lived 12 years so far.
John lived 89 years so far.
Lisa lived 2 years so far.
```

### Change the for-loops to while-loops and see what works better for which kind of pointer usage.
```c
#include <stdio.h>

int main(int argc, char *argv[])
{
    // create two arrays we care about
    int ages[] = { 23, 43, 12, 89, 2 };
    char *names[] = {
        "Alan", "Frank",
        "Mary", "John", "Lisa"
    };
    
    // safely get the size of ages
    int count = sizeof(ages) / sizeof(int);
    int i = 0;
    
    // first way using indexing
    while (i < count) {
        printf("%s has %d years alive.\n", names[i], ages[i]);
        i++;
    }
    
    printf("---\n");
    
    // setup the pointers to the start of the arrays
    int *cur_age = ages;
    char **cur_name = names;
    
    // second way using pointers
    i = 0;
    while (i < count) {
        printf("%s is %d years old.\n", *(cur_name + i), *(cur_age + i));
        i++;
    }
    
    printf("---\n");
    
    // third way, pointers are just arrays
    i = 0;
    while (i < count) {
        printf("%s is %d years old again.\n", cur_name[i], cur_age[i]);
        i++;
    }
    
    printf("---\n");
    
    // fourth way with pointers in a stuipd conplex way
    while (cur_age - ages < count) {
        printf("%s lived %d years so far.\n", *cur_name, *cur_age);
        cur_name++;
        cur_age++;
    }
    
    return 0;
}
```
```
$ ./ex15
Alan has 23 years alive.
Frank has 43 years alive.
Mary has 12 years alive.
John has 89 years alive.
Lisa has 2 years alive.
---
Alan is 23 years old.
Frank is 43 years old.
Mary is 12 years old.
John is 89 years old.
Lisa is 2 years old.
---
Alan is 23 years old again.
Frank is 43 years old again.
Mary is 12 years old again.
John is 89 years old again.
Lisa is 2 years old again.
---
Alan lived 23 years so far.
Frank lived 43 years so far.
Mary lived 12 years so far.
John lived 89 years so far.
Lisa lived 2 years so far.
```
