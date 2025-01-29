Write a program that counts the number of 0s and 1s in the binary representation of a decimal number.

Your program should take a decimal number as argument. Then it should print the decimal number, it's binary representation and then count the number of 0s and 1s.

For example, for the following command:

```
main.exe 3
```
The output should be:

```
Number: 3
Binary: 0b11
Number of 0s: 0
Number of 1s: 2
```

In this task, you must use bit operations. You are not allowed to convert the number to strings or arrays of any sort. Leading 0s should not be counted (e.g., 0b0011 should return "Number of 0s: 0; Number of 1s: 2").

Please remember that the program should handle errors:

When the argument is empty
When the argument is not a number (e.g., 0x11)