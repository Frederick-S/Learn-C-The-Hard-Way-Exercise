# Exercise 2: Make Is Your Python Now
## Extra Credit
### Create an all: ex1 target that will build ex1 with just the command make.
Now the Makefile looks like this:
```
CFLAGS = -Wall -g

all: ex1

clean:
	rm -rf ex1 ex1.dSYM
```
### Read man make to find out more information on how to run it.
We can run `make` command with more options, here are some examples:

1. -d: print debugging information

    ```
    $ make ex1 -d
    GNU Make 3.81
    Copyright (C) 2006  Free Software Foundation, Inc.
    This is free software; see the source for copying conditions.
    There is NO warranty; not even for MERCHANTABILITY or FITNESS FOR A
    PARTICULAR PURPOSE.

    This program built for i386-apple-darwin11.3.0
    Reading makefiles...
    Reading makefile `Makefile'...
    Updating makefiles....
     Considering target file `Makefile'.
      Looking for an implicit rule for `Makefile'.
      Trying pattern rule with stem `Makefile'.
      Trying implicit prerequisite `Makefile.o'.
      ...
    ```
2. -f file: use a file as a makefile

    ```
    $ cp Makefile myMakefile
    $ make -f myMakefile clean
    rm -rf ex1 ex1.dSYM
    $ make -f myMakefile ex1
    cc -Wall -g    ex1.c   -o ex1
    ```
3. -I dir: specifies a directory to search for  included  makefiles

    ```
    $ mkdir dir
    $ cp Makefile dir
    $ make -I dir ex1
    cc -Wall -g    ex1.c   -o ex1
    ```
