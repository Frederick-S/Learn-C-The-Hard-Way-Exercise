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
