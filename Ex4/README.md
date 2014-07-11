# Exercise 4: Introducing Valgrind
## Installing Valgrind
I ran into some errors in this step:

1. Linux kernel version is not supported

  ```
  checking for the kernel version... unsupported (3.13.0-24-generic)
  configure: error: Valgrind works on kernels 2.4, 2.6
  ```

2. Unsupported glibc version

I downloaded `valgrind-3.9.0` to re-configure, then I met another error:

  ```
  checking the GLIBC_VERSION version... unsupported version 2.19
  configure: error: Valgrind requires glibc version 2.2 - 2.17
  ```
  
After Google, I found a solution [here](http://stackoverflow.com/questions/10518734/valgrind-doesnt-accept-newest-version-of-glibc), add the following code in `configure` file (before the line with `darwin)`):

  ```
   2.19)
  { $as_echo "$as_me:${as_lineno-$LINENO}: result: 2.19 family" >&5
$as_echo "2.19 family" >&6; }

$as_echo "#define GLIBC_2_19 1" >>confdefs.h

  DEFAULT_SUPP="glibc-2.X.supp ${DEFAULT_SUPP}"
  DEFAULT_SUPP="glibc-2.34567-NPTL-helgrind.supp ${DEFAULT_SUPP}"
  DEFAULT_SUPP="glibc-2.X-drd.supp ${DEFAULT_SUPP}"
  ;;
  ```

## Using Valgrind
I met an error again when I ran `valgrind ./ex4`:

  ```
  valgrind:  Fatal error at startup: a function redirection
  valgrind:  which is mandatory for this platform-tool combination
  valgrind:  cannot be set up.  Details of the redirection are:
  valgrind:
  valgrind:  A must-be-redirected function
  valgrind:  whose name matches the pattern:      strlen
  valgrind:  in an object with soname matching:   ld-linux-x86-64.so.2
  valgrind:  was not found whilst processing
  valgrind:  symbols from the object with soname: ld-linux-x86-64.so.2
  valgrind:
  valgrind:  Possible fixes: (1, short term): install glibc's debuginfo
  valgrind:  package on this machine.  (2, longer term): ask the packagers
  valgrind:  for your Linux distribution to please in future ship a non-
  valgrind:  stripped ld.so (or whatever the dynamic linker .so is called)
  valgrind:  that exports the above-named function using the standard
  valgrind:  calling conventions for this platform.  The package you need
  valgrind:  to install for fix (1) is called
  valgrind:
  valgrind:    On Debian, Ubuntu:                 libc6-dbg
  valgrind:    On SuSE, openSuSE, Fedora, RHEL:   glibc-debuginfo
  valgrind:
  valgrind:  Cannot continue -- exiting now.  Sorry.
  ```

Luckily, it gives us 2 possible fixes, so I ran `sudo apt-get install libc6-dbg` to install the package, and it worked.

## Extra Credit
### Fix this program using Valgrind and the compiler as your guide.
