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
### Read man cc to find out more information on what the flags -Wall and -g do.
#### -Wall
```
This enables all the warnings about constructions that some users
consider questionable, and that are easy to avoid (or modify to
prevent the warning), even in conjunction with macros.  This also
enables some language-specific warnings described in C++ Dialect
Options and Objective-C and Objective-C++ Dialect Options.

-Wall turns on the following warning flags:

-Waddress -Warray-bounds (only with -O2) -Wc++0x-compat
-Wchar-subscripts -Wimplicit-int -Wimplicit-function-declaration
-Wcomment -Wformat -Wmain (only for C/ObjC and unless
-ffreestanding) -Wmissing-braces -Wnonnull -Wparentheses
-Wpointer-sign -Wreorder -Wreturn-type -Wsequence-point
-Wsign-compare (only in C++) -Wstrict-aliasing -Wstrict-overflow=1
-Wswitch -Wtrigraphs -Wuninitialized -Wunknown-pragmas
-Wunused-function -Wunused-label -Wunused-value -Wunused-variable
-Wvolatile-register-var

Note that some warning flags are not implied by -Wall.  Some of
them warn about constructions that users generally do not consider
questionable, but which occasionally you might wish to check for;
others warn about constructions that are necessary or hard to avoid
in some cases, and there is no simple way to modify the code to
suppress the warning. Some of them are enabled by -Wextra but many
of them must be enabled individually.
```
#### -g
```
Produce debugging information in the operating system's native
format (stabs, COFF, XCOFF, or DWARF 2).  GDB can work with this
debugging information.

On most systems that use stabs format, -g enables use of extra
debugging information that only GDB can use; this extra information
makes debugging work better in GDB but will probably make other
debuggers crash or refuse to read the program.  If you want to
control for certain whether to generate the extra information, use
-gstabs+, -gstabs, -gxcoff+, -gxcoff, or -gvms (see below).

GCC allows you to use -g with -O.  The shortcuts taken by optimized
code may occasionally produce surprising results: some variables
you declared may not exist at all; flow of control may briefly move
where you did not expect it; some statements may not be executed
because they compute constant results or their values were already
at hand; some statements may execute in different places because
they were moved out of loops.

Nevertheless it proves possible to debug optimized output.  This
makes it reasonable to use the optimizer for programs that might
have bugs.

The following options are useful when GCC is generated with the
capability for more than one debugging format.
```
### Research Makefiles online and see if you can improve this one even more.
