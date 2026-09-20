# Lab 2 (Part 1): Intro to Processes

CSCI Operating Systems — Processes and Signals

Programs demonstrating process creation with `fork()`, and a three-process
program in which a parent forks two children, each child sleeps for a random
interval, and the parent waits for both to finish.

## Files

| File | Description |
| --- | --- |
| `main.c` | Single `fork()`; parent and child both loop and `write()` their pid and counter to stdout. |
| `main2.c` | `fork()` with the return value used to split into `ChildProcess()` and `ParentProcess()`. |
| `main3.c` | The lab exercise: parent forks **two** children (3 processes total). Each child loops a random number of times (up to 30), sleeping a random number of seconds (up to 10) each pass and printing its pid and its parent pid. The parent `wait()`s for both children and reports each completion. |
| `Makefile` | Build rules for all three programs. |

## Build

```sh
make prog1      # builds main.c   -> prog1
make prog2      # builds main2.c  -> prog2
make my3proc    # builds main3.c  -> my3proc
```

## Run

```sh
./my3proc
```

Sample output:

```
Child Pid: 1234 is going to sleep!
Child Pid: 1235 is going to sleep!
Child Pid: 1234 is awake!
Where is my Parent: 1233?
Child Pid: 1234 has completed
Child Pid: 1235 has completed
```

## Notes

`main3.c` seeds `srandom()` with the current time in microseconds XORed with
the process id, so the two children produce different random sequences instead
of identical ones (both children otherwise inherit the same seed state from the
parent). `fflush(stdout)` is called after each print so output appears in real
time rather than sitting in the buffer while the child sleeps.

Calls used: `fork()`, `wait()`, `sleep()`, `getpid()`, `getppid()`,
`srandom()`, `random()`, `exit()`.
