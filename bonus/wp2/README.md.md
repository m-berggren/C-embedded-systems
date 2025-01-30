Write a calendar program using enums.

Your task is to write a program that will use separate enums for days of the week (Mon, Tue, etc) and Weeks (week 1, week 2, ..., week 5). The program should increment the day every second. After Sunday, the week should increment as well and the counting should start from the beginning. Once it gets to week 5, it should stop.

The program should ask the user to provide the start day and week. Every time the program increments the day, it should write the week and day on the console.

For example the interaction should be:

Provide starting week:

```
1
```

Provide starting day:

```
Mon
```
Output:

```
Week 1, Monday
Week 1, Tuesday
...
```

You are NOT allowed to use strings to store the days and weeks. Your program should also check for the correct input from the user.