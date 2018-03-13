# [Concurrency](https://talks.golang.org/2015/simplicity-is-complicated.slide#21)

Concurrency is the ability to write your program as independently executing
pieces. In Go, concurrency has three elements:

- goroutines (execution)
- channels (communication)
- select (coordination)

Concurrency is a way to design a program by decomposing it into independently
executing pieces. The result can be clean, efficient, and very adaptable.
