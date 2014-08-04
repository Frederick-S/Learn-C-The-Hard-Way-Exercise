# Exercise 8: Sizes And Arrays
## How To Break It
### Get rid of the '\0' at the end of full\_name and re-run it. Run it under Valgrind too. Now, move the definition of full\_name to the top of main before areas. Try running it under Valgrind a few times and see if you get some new errors. In some cases, you might still get lucky and not catch any errors.
Run without `Valgrind`:
```
$ ./ex8
The size of an int: 4
The size of areas (int[]): 20
The number of ints in areas: 5
The first area is 10, the 2nd 12.
The size of a char: 1
The size of name (char[]): 4
The number of chars: 4
The size of full_name (char[]): 11
The number of chars: 11
name="Zed" and full_name="Zed A. Shaw"
```
Run with `Valgrind`:
```
$ valgrind ./ex8
==4438== Memcheck, a memory error detector
==4438== Copyright (C) 2002-2013, and GNU GPL'd, by Julian Seward et al.
==4438== Using Valgrind-3.9.0 and LibVEX; rerun with -h for copyright info
==4438== Command: ./ex8
==4438==
The size of an int: 4
The size of areas (int[]): 20
The number of ints in areas: 5
The first area is 10, the 2nd 12.
The size of a char: 1
The size of name (char[]): 4
The number of chars: 4
The size of full_name (char[]): 11
The number of chars: 11
==4438== Conditional jump or move depends on uninitialised value(s)
==4438==    at 0x4E7FCB3: vfprintf (vfprintf.c:1661)
==4438==    by 0x4E88748: printf (printf.c:33)
==4438==    by 0x4006E1: main (ex8.c:24)
==4438==
name="Zed" and full_name="Zed A. Shaw"
==4438==
==4438== HEAP SUMMARY:
==4438==     in use at exit: 0 bytes in 0 blocks
==4438==   total heap usage: 0 allocs, 0 frees, 0 bytes allocated
==4438==
==4438== All heap blocks were freed -- no leaks are possible
==4438==
==4438== For counts of detected and suppressed errors, rerun with: -v
==4438== Use --track-origins=yes to see where uninitialised values come from
==4438== ERROR SUMMARY: 1 errors from 1 contexts (suppressed: 1 from 1)
```
Unluckily, I didn't get new errors after I moved the definition of `full_name` to the top of main before `areas`.
### Change it so that instead of areas[0] you try to print areas[10] and see what Valgrind thinks of that.
```
$ valgrind ./ex8
==5224== Memcheck, a memory error detector
==5224== Copyright (C) 2002-2013, and GNU GPL'd, by Julian Seward et al.
==5224== Using Valgrind-3.9.0 and LibVEX; rerun with -h for copyright info
==5224== Command: ./ex8
==5224==
The size of an int: 4
The size of areas (int[]): 20
The number of ints in areas: 5
==5224== Conditional jump or move depends on uninitialised value(s)
==5224==    at 0x4E7E83E: vfprintf (vfprintf.c:1660)
==5224==    by 0x4E88748: printf (printf.c:33)
==5224==    by 0x400667: main (ex8.c:18)
==5224==
==5224== Use of uninitialised value of size 8
==5224==    at 0x4E7DCFB: _itoa_word (_itoa.c:179)
==5224==    by 0x4E819A6: vfprintf (vfprintf.c:1660)
==5224==    by 0x4E88748: printf (printf.c:33)
==5224==    by 0x400667: main (ex8.c:18)
==5224==
==5224== Conditional jump or move depends on uninitialised value(s)
==5224==    at 0x4E7DD05: _itoa_word (_itoa.c:179)
==5224==    by 0x4E819A6: vfprintf (vfprintf.c:1660)
==5224==    by 0x4E88748: printf (printf.c:33)
==5224==    by 0x400667: main (ex8.c:18)
==5224==
==5224== Conditional jump or move depends on uninitialised value(s)
==5224==    at 0x4E819F2: vfprintf (vfprintf.c:1660)
==5224==    by 0x4E88748: printf (printf.c:33)
==5224==    by 0x400667: main (ex8.c:18)
==5224==
==5224== Conditional jump or move depends on uninitialised value(s)
==5224==    at 0x4E7E909: vfprintf (vfprintf.c:1660)
==5224==    by 0x4E88748: printf (printf.c:33)
==5224==    by 0x400667: main (ex8.c:18)
==5224==
==5224== Conditional jump or move depends on uninitialised value(s)
==5224==    at 0x4E7E98C: vfprintf (vfprintf.c:1660)
==5224==    by 0x4E88748: printf (printf.c:33)
==5224==    by 0x400667: main (ex8.c:18)
==5224==
The first area is 0, the 2nd 12.
The size of a char: 1
The size of name (char[]): 4
The number of chars: 4
The size of full_name (char[]): 12
The number of chars: 12
name="Zed" and full_name="Zed A. Shaw"
==5224==
==5224== HEAP SUMMARY:
==5224==     in use at exit: 0 bytes in 0 blocks
==5224==   total heap usage: 0 allocs, 0 frees, 0 bytes allocated
==5224==
==5224== All heap blocks were freed -- no leaks are possible
==5224==
==5224== For counts of detected and suppressed errors, rerun with: -v
==5224== Use --track-origins=yes to see where uninitialised values come from
==5224== ERROR SUMMARY: 6 errors from 6 contexts (suppressed: 1 from 1)
```
### Try other versions of these, doing it to name and full_name too.
Try with `name`:
```c
printf("The first char of name is %c\n", name[5]);
```
```
$ valgrind ./ex8
==5925== Memcheck, a memory error detector
==5925== Copyright (C) 2002-2013, and GNU GPL'd, by Julian Seward et al.
==5925== Using Valgrind-3.9.0 and LibVEX; rerun with -h for copyright info
==5925== Command: ./ex8
==5925==
==5925== Conditional jump or move depends on uninitialised value(s)
==5925==    at 0x4EAF631: _IO_file_overflow@@GLIBC_2.2.5 (fileops.c:867)
==5925==    by 0x4E7EC7F: vfprintf (vfprintf.c:1661)
==5925==    by 0x4E88748: printf (printf.c:33)
==5925==    by 0x4005D9: main (ex8.c:9)
==5925==
==5925== Conditional jump or move depends on uninitialised value(s)
==5925==    at 0x4EAF65E: _IO_file_overflow@@GLIBC_2.2.5 (fileops.c:875)
==5925==    by 0x4E7EC7F: vfprintf (vfprintf.c:1661)
==5925==    by 0x4E88748: printf (printf.c:33)
==5925==    by 0x4005D9: main (ex8.c:9)
==5925==
==5925== Conditional jump or move depends on uninitialised value(s)
==5925==    at 0x4E7EC83: vfprintf (vfprintf.c:1661)
==5925==    by 0x4E88748: printf (printf.c:33)
==5925==    by 0x4005D9: main (ex8.c:9)
==5925==
==5925== Syscall param write(buf) points to uninitialised byte(s)
==5925==    at 0x4F20700: __write_nocancel (syscall-template.S:81)
==5925==    by 0x4EADE42: _IO_file_write@@GLIBC_2.2.5 (fileops.c:1261)
==5925==    by 0x4EAF31B: _IO_do_write@@GLIBC_2.2.5 (fileops.c:538)
==5925==    by 0x4EAE4E0: _IO_file_xsputn@@GLIBC_2.2.5 (fileops.c:1332)
==5925==    by 0x4E7E799: vfprintf (vfprintf.c:1692)
==5925==    by 0x4E88748: printf (printf.c:33)
==5925==    by 0x4005D9: main (ex8.c:9)
==5925==  Address 0x402501a is not stack'd, malloc'd or (recently) free'd
==5925==
The first char of name is
==5925==
==5925== HEAP SUMMARY:
==5925==     in use at exit: 0 bytes in 0 blocks
==5925==   total heap usage: 0 allocs, 0 frees, 0 bytes allocated
==5925==
==5925== All heap blocks were freed -- no leaks are possible
==5925==
==5925== For counts of detected and suppressed errors, rerun with: -v
==5925== Use --track-origins=yes to see where uninitialised values come from
==5925== ERROR SUMMARY: 4 errors from 4 contexts (suppressed: 1 from 1)
```
Try with `full_name`:
```c
printf("The first char of full_name is %c\n", full_name[20]);
```
```
$ valgrind ./ex8
==6083== Memcheck, a memory error detector
==6083== Copyright (C) 2002-2013, and GNU GPL'd, by Julian Seward et al.
==6083== Using Valgrind-3.9.0 and LibVEX; rerun with -h for copyright info
==6083== Command: ./ex8
==6083==
==6083== Conditional jump or move depends on uninitialised value(s)
==6083==    at 0x4EAF631: _IO_file_overflow@@GLIBC_2.2.5 (fileops.c:867)
==6083==    by 0x4E7EC7F: vfprintf (vfprintf.c:1661)
==6083==    by 0x4E88748: printf (printf.c:33)
==6083==    by 0x4005D9: main (ex8.c:9)
==6083==
==6083== Conditional jump or move depends on uninitialised value(s)
==6083==    at 0x4EAF65E: _IO_file_overflow@@GLIBC_2.2.5 (fileops.c:875)
==6083==    by 0x4E7EC7F: vfprintf (vfprintf.c:1661)
==6083==    by 0x4E88748: printf (printf.c:33)
==6083==    by 0x4005D9: main (ex8.c:9)
==6083==
==6083== Conditional jump or move depends on uninitialised value(s)
==6083==    at 0x4E7EC83: vfprintf (vfprintf.c:1661)
==6083==    by 0x4E88748: printf (printf.c:33)
==6083==    by 0x4005D9: main (ex8.c:9)
==6083==
==6083== Syscall param write(buf) points to uninitialised byte(s)
==6083==    at 0x4F20700: __write_nocancel (syscall-template.S:81)
==6083==    by 0x4EADE42: _IO_file_write@@GLIBC_2.2.5 (fileops.c:1261)
==6083==    by 0x4EAF31B: _IO_do_write@@GLIBC_2.2.5 (fileops.c:538)
==6083==    by 0x4EAE4E0: _IO_file_xsputn@@GLIBC_2.2.5 (fileops.c:1332)
==6083==    by 0x4E7E799: vfprintf (vfprintf.c:1692)
==6083==    by 0x4E88748: printf (printf.c:33)
==6083==    by 0x4005D9: main (ex8.c:9)
==6083==  Address 0x402501a is not stack'd, malloc'd or (recently) free'd
==6083==
The first char of name is
==6083==
==6083== HEAP SUMMARY:
==6083==     in use at exit: 0 bytes in 0 blocks
==6083==   total heap usage: 0 allocs, 0 frees, 0 bytes allocated
==6083==
==6083== All heap blocks were freed -- no leaks are possible
==6083==
==6083== For counts of detected and suppressed errors, rerun with: -v
==6083== Use --track-origins=yes to see where uninitialised values come from
==6083== ERROR SUMMARY: 4 errors from 4 contexts (suppressed: 1 from 1)
```
## Extra Credit
### Try assigning to elements in the areas array with areas[0] = 100; and similar.
```c
areas[0] = 100;
areas[1] = 200;
printf("Now the first area is %d, the 2nd %d.\n", areas[0], areas[1]);
```
```
$ ./ex8
Now the first area is 100, the 2nd 200.
```
### Try assigning to elements of name and full_name.
```c
name[0] = 'T';
full_name[0] = 'T';
printf("name=\"%s\" and full_name=\"%s\"\n", name, full_name);
```
```
$ ./ex8
name="Ted" and full_name="Ted A. Shaw"
```
### Try setting one element of areas to a character from name.
```c
areas[0] = name[0];
printf("Now the first area is %d.\n", areas[0]);
```
```
$ ./ex8
Now the first area is 90.
```
### Go search online for the different sizes used for integers on different CPUs.
I ran the following code on `Ubuntu 14.04 x32` and `Ubuntu 14.04 x64`:

`Ubuntu 14.04 x32`:
```c
#include <stdio.h>

int main(int argc, char *argv[])
{
    printf("Size of unsigned short: %u\n", sizeof(unsigned short));
    printf("Size of short: %u\n", sizeof(short));
    printf("Size of unsigned int: %u\n", sizeof(unsigned int));
    printf("Size of int: %u\n", sizeof(int));
    printf("Size of unsigned long: %u\n", sizeof(unsigned long));
    printf("Size of long: %u\n", sizeof(long));

    return 0;
}
```
Output:
```
Size of unsigned short: 2
Size of short: 2
Size of unsigned int: 4
Size of int: 4
Size of unsigned long: 4
Size of long: 4
```
`Ubuntu 14.04 x64`:
```c
#include <stdio.h>

int main(int argc, char *argv[])
{
    printf("Size of unsigned short: %lu\n", sizeof(unsigned short));
    printf("Size of short: %lu\n", sizeof(short));
    printf("Size of unsigned int: %lu\n", sizeof(unsigned int));
    printf("Size of int: %lu\n", sizeof(int));
    printf("Size of unsigned long: %lu\n", sizeof(unsigned long));
    printf("Size of long: %lu\n", sizeof(long));

    return 0;
}
```
Output:
```
Size of unsigned short: 2
Size of short: 2
Size of unsigned int: 4
Size of int: 4
Size of unsigned long: 8
Size of long: 8
```
Here are some [answers](http://stackoverflow.com/questions/2331751/does-the-size-of-an-int-depend-on-the-compiler-and-or-processor) about the integer size.

