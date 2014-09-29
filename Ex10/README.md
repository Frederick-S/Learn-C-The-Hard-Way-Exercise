# Exercise 10: Arrays Of Strings, Looping
## How To Break It
### Take your favorite other language, and use it to run this program, but with as many command line arguments as possible. See if you can bust it by giving it way too many arguments.
Here is the python code to run this program:
```py
#!/usr/bin/env python

import sys
from subprocess import call

if len(sys.argv) > 1:
    try:
        times = int(sys.argv[1])
        arguments = [str(i) for i in range(times)]
        arguments.insert(0, "./ex10")

        # Run ex10
        call(arguments)
    except Exception, e:
        print e
```
And a simple usage:
```
$ ./run_ex10.py 5
arg 1: 0
arg 2: 1
arg 3: 2
arg 4: 3
arg 5: 4
state 0: California
state 1: Oregon
state 2: Washington
state 3: Texas
```
I bust it when the length of argument list is 5000000:
```
$ ./run_ex10.py 5000000
[Errno 7] Argument list too long
```
