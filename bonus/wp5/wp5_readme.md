The elevator controller uses one byte (8 bits) to store the status of the elevator.

The values/meaning of the bits of the byte are:

```
Name           Bits       Info
-------------------------------
engine_on      1          Is engine on or off (the elevator moves or not). This is bit no 7 (MSB)
floor_pos      3          Which floor number the elevator should go to (0-7)  
door_pos       2          If the door is open or closed  
brake1         1          Normal brakes
brake2         1          Emergency brakes
```

We should store them in a byte like this:
```
[engine_on]  [floor_pos]   [door_pos]    [brake1]   [brake2]          

 1 bit       3 bits         2 bits        1 bit      1 bit
```

(8 bits in total)

Write a program which takes 5 arguments (different number of arguments should result in an error message). The arguments should correspond to the values/variables above. The program should also be able to print error message if the bit combination is invalid. 

Example for a start of the program from command line:
```
main   1 7 1 1 0          
```
The above should be treated as:

```
Name                Value  
----------------------------
engine_on            1      
floor_pos            7
door_pos             1
brake1               1
brake2               0
```

and the output should be
```
0xF6
```