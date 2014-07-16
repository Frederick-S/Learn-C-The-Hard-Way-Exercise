# Exercise 5: The Structure Of A C Program
## Extra Credit
### For each line, write out the symbols you don't understand and see if you can guess what they mean. Write a little chart on paper with your guess that you can use to check later and see if you get it right.
#### What does `*` mean?
> In declarations the asterisk modifier (*) specifies a pointer type. For example, where the specifier int would refer to the integer type, the specifier int* refers to the type "pointer to integer". Pointer values associate two pieces of information: a memory address and a data type.

### Go back to the source code from the previous exercises and do a similar break-down to see if you're getting it. Write down what you don't know and can't explain to yourself.
#### Why `return 0`?
> main() is expected to return zero to indicate success and non-zero to indicate failure.
> The value returned by main() is passed to the exit() function, which terminates the program.
