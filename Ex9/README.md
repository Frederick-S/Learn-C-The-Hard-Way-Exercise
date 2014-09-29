# Exercise 9: Arrays And Strings
## How To Break It
### Get rid of the initializers that setup name.
```
==1880== Memcheck, a memory error detector
==1880== Copyright (C) 2002-2013, and GNU GPL'd, by Julian Seward et al.
==1880== Using Valgrind-3.9.0 and LibVEX; rerun with -h for copyright info
==1880== Command: ./ex9
==1880==
numbers: 0 0 0 0
==1880== Conditional jump or move depends on uninitialised value(s)
==1880==    at 0x4EAF631: _IO_file_overflow@@GLIBC_2.2.5 (fileops.c:867)
==1880==    by 0x4E7EC7F: vfprintf (vfprintf.c:1661)
==1880==    by 0x4E88748: printf (printf.c:33)
==1880==    by 0x40061B: main (ex9.c:11)
==1880==
==1880== Conditional jump or move depends on uninitialised value(s)
==1880==    at 0x4EAF65E: _IO_file_overflow@@GLIBC_2.2.5 (fileops.c:875)
==1880==    by 0x4E7EC7F: vfprintf (vfprintf.c:1661)
==1880==    by 0x4E88748: printf (printf.c:33)
==1880==    by 0x40061B: main (ex9.c:11)
==1880==
==1880== Conditional jump or move depends on uninitialised value(s)
==1880==    at 0x4E7EC83: vfprintf (vfprintf.c:1661)
==1880==    by 0x4E88748: printf (printf.c:33)
==1880==    by 0x40061B: main (ex9.c:11)
==1880==
==1880== Syscall param write(buf) points to uninitialised byte(s)
==1880==    at 0x4F20700: __write_nocancel (syscall-template.S:81)
==1880==    by 0x4EADE42: _IO_file_write@@GLIBC_2.2.5 (fileops.c:1261)
==1880==    by 0x4EAF31B: _IO_do_write@@GLIBC_2.2.5 (fileops.c:538)
==1880==    by 0x4EAE4E0: _IO_file_xsputn@@GLIBC_2.2.5 (fileops.c:1332)
==1880==    by 0x4E7E799: vfprintf (vfprintf.c:1692)
==1880==    by 0x4E88748: printf (printf.c:33)
==1880==    by 0x40061B: main (ex9.c:11)
==1880==  Address 0x402500b is not stack'd, malloc'd or (recently) free'd
==1880==
name each: P  @
==1880== Conditional jump or move depends on uninitialised value(s)
==1880==    at 0x4E7FCB3: vfprintf (vfprintf.c:1661)
==1880==    by 0x4E88748: printf (printf.c:33)
==1880==    by 0x400631: main (ex9.c:13)
==1880==
==1880== Conditional jump or move depends on uninitialised value(s)
==1880==    at 0x4EAE551: _IO_file_xsputn@@GLIBC_2.2.5 (fileops.c:1302)
==1880==    by 0x4E7FC74: vfprintf (vfprintf.c:1661)
==1880==    by 0x4E88748: printf (printf.c:33)
==1880==    by 0x400631: main (ex9.c:13)
==1880==
==1880== Conditional jump or move depends on uninitialised value(s)
==1880==    at 0x4EAE55F: _IO_file_xsputn@@GLIBC_2.2.5 (fileops.c:1302)
==1880==    by 0x4E7FC74: vfprintf (vfprintf.c:1661)
==1880==    by 0x4E88748: printf (printf.c:33)
==1880==    by 0x400631: main (ex9.c:13)
==1880==
name: P@
numbers: 1 2 3 4
name each: Z e d
name: Zed
another: Zed
another each: Z e d
==1880==
==1880== HEAP SUMMARY:
==1880==     in use at exit: 0 bytes in 0 blocks
==1880==   total heap usage: 0 allocs, 0 frees, 0 bytes allocated
==1880==
==1880== All heap blocks were freed -- no leaks are possible
==1880==
==1880== For counts of detected and suppressed errors, rerun with: -v
==1880== Use --track-origins=yes to see where uninitialised values come from
==1880== ERROR SUMMARY: 21 errors from 7 contexts (suppressed: 1 from 1)
```
### Accidentally set name[3] = 'A'; so that there's no terminator.
```
==2072== Memcheck, a memory error detector
==2072== Copyright (C) 2002-2013, and GNU GPL'd, by Julian Seward et al.
==2072== Using Valgrind-3.9.0 and LibVEX; rerun with -h for copyright info
==2072== Command: ./ex9
==2072==
numbers: 0 0 0 0
name each: a
name: a
numbers: 1 2 3 4
name each: Z e d A
==2072== Conditional jump or move depends on uninitialised value(s)
==2072==    at 0x4E7FCB3: vfprintf (vfprintf.c:1661)
==2072==    by 0x4E88748: printf (printf.c:33)
==2072==    by 0x4006CE: main (ex9.c:33)
==2072==
name: ZedA
another: Zed
another each: Z e d
==2072==
==2072== HEAP SUMMARY:
==2072==     in use at exit: 0 bytes in 0 blocks
==2072==   total heap usage: 0 allocs, 0 frees, 0 bytes allocated
==2072==
==2072== All heap blocks were freed -- no leaks are possible
==2072==
==2072== For counts of detected and suppressed errors, rerun with: -v
==2072== Use --track-origins=yes to see where uninitialised values come from
==2072== ERROR SUMMARY: 1 errors from 1 contexts (suppressed: 1 from 1)
```
### Set the initializer to {'a','a','a','a'} so there's too many 'a' characters and no space for the '\0' terminator.
```
==2146== Memcheck, a memory error detector
==2146== Copyright (C) 2002-2013, and GNU GPL'd, by Julian Seward et al.
==2146== Using Valgrind-3.9.0 and LibVEX; rerun with -h for copyright info
==2146== Command: ./ex9
==2146==
numbers: 0 0 0 0
name each: a a a a
==2146== Conditional jump or move depends on uninitialised value(s)
==2146==    at 0x4E7FCB3: vfprintf (vfprintf.c:1661)
==2146==    by 0x4E88748: printf (printf.c:33)
==2146==    by 0x400641: main (ex9.c:13)
==2146==
name: aaaa
numbers: 1 2 3 4
name each: Z e d
name: Zed
another: Zed
another each: Z e d
==2146==
==2146== HEAP SUMMARY:
==2146==     in use at exit: 0 bytes in 0 blocks
==2146==   total heap usage: 0 allocs, 0 frees, 0 bytes allocated
==2146==
==2146== All heap blocks were freed -- no leaks are possible
==2146==
==2146== For counts of detected and suppressed errors, rerun with: -v
==2146== Use --track-origins=yes to see where uninitialised values come from
==2146== ERROR SUMMARY: 1 errors from 1 contexts (suppressed: 1 from 1)
```
### Set numbers[4] to 5.
```c
#include <stdio.h>

int main(int argc, char *argv[])
{
    int numbers[4] = {0};

    // setup the numbers
    numbers[0] = 1;
    numbers[1] = 2;
    numbers[2] = 3;
    numbers[3] = 4;
    numbers[4] = 5;

    // then print them out initialized
    printf("numbers: %d %d %d %d %d\n", numbers[0], numbers[1], numbers[2], numbers[3], numbers[4]);

    return 0;
}
```
Run with `Valgrind`:
```
==1563== Memcheck, a memory error detector
==1563== Copyright (C) 2002-2013, and GNU GPL'd, by Julian Seward et al.
==1563== Using Valgrind-3.9.0 and LibVEX; rerun with -h for copyright info
==1563== Command: ./ex9
==1563==
numbers: 1 2 3 4 5
==1563==
==1563== HEAP SUMMARY:
==1563==     in use at exit: 0 bytes in 0 blocks
==1563==   total heap usage: 0 allocs, 0 frees, 0 bytes allocated
==1563==
==1563== All heap blocks were freed -- no leaks are possible
==1563==
==1563== For counts of detected and suppressed errors, rerun with: -v
==1563== ERROR SUMMARY: 0 errors from 0 contexts (suppressed: 1 from 1)
```
I thought it will throw an index out of range exception, but it didn't. I searched on the internet and found that [C doesn't perform bounds checking](http://stackoverflow.com/questions/671703/array-index-out-of-bound-in-c).
## Extra Credit
### Assign the characters into numbers and then use printf to print them a character at a time. What kind of compiler warnings did you get?
```c
#include <stdio.h>

int main(int argc, char *argv[])
{
    int numbers[4] = {0};

    // setup the numbers
    numbers[0] = 'a';
    numbers[1] = 'b';
    numbers[2] = 'c';
    numbers[3] = 'd';

    // then print them out initialized
    printf("numbers: %c %c %c %c\n", numbers[0], numbers[1], numbers[2], numbers[3]);

    return 0;
}
```
The compiler didn't complain about it.

Run with `Valgrind`:
```
==1192== Memcheck, a memory error detector
==1192== Copyright (C) 2002-2013, and GNU GPL'd, by Julian Seward et al.
==1192== Using Valgrind-3.9.0 and LibVEX; rerun with -h for copyright info
==1192== Command: ./ex9
==1192==
numbers: a b c d
==1192==
==1192== HEAP SUMMARY:
==1192==     in use at exit: 0 bytes in 0 blocks
==1192==   total heap usage: 0 allocs, 0 frees, 0 bytes allocated
==1192==
==1192== All heap blocks were freed -- no leaks are possible
==1192==
==1192== For counts of detected and suppressed errors, rerun with: -v
==1192== ERROR SUMMARY: 0 errors from 0 contexts (suppressed: 1 from 1)
```
### Do the inverse for name, trying to treat it like an array of int and print it out one int at a time. What does Valgrind think of that?
```c
#include <stdio.h>

int main(int argc, char *argv[])
{
    char name[4] = {'a'};

    // setup the name
    name[0] = 100;
    name[1] = 101;
    name[2] = 102;
    name[3] = 103;

    // then print them out initialized
    printf("name each: %d %d %d %d\n", name[0], name[1], name[2], name[3]);

    return 0;
}
```
Run with `Valgrind`:
```
==1048== Memcheck, a memory error detector
==1048== Copyright (C) 2002-2013, and GNU GPL'd, by Julian Seward et al.
==1048== Using Valgrind-3.9.0 and LibVEX; rerun with -h for copyright info
==1048== Command: ./ex9
==1048==
name each: 100 101 102 103
==1048==
==1048== HEAP SUMMARY:
==1048==     in use at exit: 0 bytes in 0 blocks
==1048==   total heap usage: 0 allocs, 0 frees, 0 bytes allocated
==1048==
==1048== All heap blocks were freed -- no leaks are possible
==1048==
==1048== For counts of detected and suppressed errors, rerun with: -v
==1048== ERROR SUMMARY: 0 errors from 0 contexts (suppressed: 1 from 1)
```
### If an array of characters is 4 bytes long, and an integer is 4 bytes long, then can you treat the whole name array like it's just an integer? How might you accomplish this crazy hack?
Yes. Each character in the 4 bytes array can represent 8-bit in a 32-bit integer. So we use the first element in the array to represent the first 8 bits, and the second element for the second 8 bits...
And here is the simple code:
```c
#include <stdio.h>

int main(int argc, char *argv[])
{
    char name[4] = { 'a', 'b', 'c', 'd' };
    int number = (name[0] << 24) + (name[1] << 16) + (name[2] << 8) + name[3];
    
    printf("number: %d\n", number);

    return 0;
}
```
### Convert name to be in the style of another and see if the code keeps working.
It works to treat `*name` like an array of int and print it out one int at a time.
```c
#include <stdio.h>

int main(int argc, char *argv[])
{
    char *name = "abcd";
    
    printf("name each: %d %d %d %d\n", name[0], name[1], name[2], name[3]);

    return 0;
}
```

Run with `Valgrind`:
```
==1338== Memcheck, a memory error detector
==1338== Copyright (C) 2002-2013, and GNU GPL'd, by Julian Seward et al.
==1338== Using Valgrind-3.9.0 and LibVEX; rerun with -h for copyright info
==1338== Command: ./ex9
==1338==
name each: 97 98 99 100
==1338==
==1338== HEAP SUMMARY:
==1338==     in use at exit: 0 bytes in 0 blocks
==1338==   total heap usage: 0 allocs, 0 frees, 0 bytes allocated
==1338==
==1338== All heap blocks were freed -- no leaks are possible
==1338==
==1338== For counts of detected and suppressed errors, rerun with: -v
==1338== ERROR SUMMARY: 0 errors from 0 contexts (suppressed: 1 from 1)
```
But it fails to assign int to the element in `*name`:
```c
#include <stdio.h>

int main(int argc, char *argv[])
{
    char *name = "abcd";
    name[0] = 100;

    printf("name each: %d %d %d %d\n", name[0], name[1], name[2], name[3]);

    return 0;
}
```
```
==1349== Memcheck, a memory error detector
==1349== Copyright (C) 2002-2013, and GNU GPL'd, by Julian Seward et al.
==1349== Using Valgrind-3.9.0 and LibVEX; rerun with -h for copyright info
==1349== Command: ./ex9
==1349==
==1349==
==1349== Process terminating with default action of signal 11 (SIGSEGV)
==1349==  Bad permissions for mapped region at address 0x400624
==1349==    at 0x400548: main (ex9.c:6)
==1349==
==1349== HEAP SUMMARY:
==1349==     in use at exit: 0 bytes in 0 blocks
==1349==   total heap usage: 0 allocs, 0 frees, 0 bytes allocated
==1349==
==1349== All heap blocks were freed -- no leaks are possible
==1349==
==1349== For counts of detected and suppressed errors, rerun with: -v
==1349== ERROR SUMMARY: 0 errors from 0 contexts (suppressed: 1 from 1)
Segmentation fault (core dumped)
```
Under this situation, `"abcd"` is stored in read-only memory, so it's not allowed to modify it.
