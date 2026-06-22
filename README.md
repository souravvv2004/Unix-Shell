# C_Shell — Unix Shell in C

A Unix shell built from scratch in C using system calls like `fork()`, `exec()`, `pipe()`, and `wait()` — supporting command execution, piping, I/O redirection, background processes, and signal handling.

---

## Features

- Command execution via `fork()` + `execvp()`
- Piping between commands (`|`)
- I/O Redirection (`>`, `>>`, `<`)
- Background process execution (`&`)
- Built-in commands (`cd`, `exit`, `help`, `history`)
- Signal handling (`SIGINT`, `SIGCHLD`)
- Arrow key navigation and command history via `readline`

---
## Architecture

```
                        +------------------+
                        |   User Input     |
                        |  (keyboard)      |
                        +--------+---------+
                                 |
                                 v
                        +------------------+
                        |     main.c       |
                        |  readline loop   |
                        |  + history       |
                        +--------+---------+
                                 |
                                 v
                        +------------------+
                        |    parser.c      |
                        |  tokenize input  |
                        |  tokens[]        |
                        +--------+---------+
                                 |
                                 v
                        +------------------+
                        |   executor.c     |
                        |  route command   |
                        +--+--+--+--+------+
                           |  |  |  |
           +---------------+  |  |  +------------------+
           |                  |  |                     |
           v                  v  v                     v
   +-----------+      +-------+  +--------+   +---------------+
   | builtins  |      | pipe.c|  |redirect|   | fork+execvp   |
   |   .c      |      |pipe() |  |  .c    |   | child process |
   | cd,exit   |      |dup2() |  |open()  |   |               |
   | help      |      |       |  |dup2()  |   |               |
   | history   |      +---+---+  +---+----+   +-------+-------+
   +-----------+          |          |                 |
                          +----+-----+                 |
                               |                       |
                               +-----------+-----------+
                                           |
                                           v
                                  +------------------+
                                  |   OS / kernel    |
                                  |  executes cmd    |
                                  +--------+---------+
                                           |
                                           v
                                  +------------------+
                                  | Terminal output  |
                                  +------------------+

   signals.c (async)
   +-----------------+
   | SIGINT  --> new |
   |   prompt        |
   | SIGCHLD --> no  |
   |   zombies       |
   +-----------------+
```

---

## Project Structure

```
shell/
│
├── src/
│   ├── main.c          # REPL loop, signal setup
│   ├── executor.c      # fork, execvp, wait logic
│   ├── parser.c        # tokenize input
│   ├── builtins.c      # cd, exit, help, history
│   ├── redirection.c   # >, <, >> handling
│   ├── pipe.c          # pipe chaining
│   └── signals.c       # SIGINT, SIGCHLD handlers
│
├── include/
│   ├── executor.h
│   ├── parser.h
│   ├── builtins.h
│   ├── redirection.h
│   ├── pipe.h
│   └── signals.h
│
├── Makefile
└── README.md
```

---

## Build

### Prerequisites
```bash
sudo apt install gcc libreadline-de
```

### Compile
```bash
make
```

### Run
```bash
./myshell
```

### Clean
```bash
make clean
```

---

## Usage

### Basic command
```
C_Shell > ls -la
C_Shell > pwd
C_Shell > echo hello
```

### Piping
```
C_Shell > ls src | grep .c
```

### Output redirection
```
C_Shell > ls > out.txt
```

### Append
```
C_Shell > echo hello >> out.txt
```

### Input redirection
```
C_Shell > wc -l < out.txt
```

### Background process
```
C_Shell > sleep 5 &
[background] pid: 1234
```

### Built-ins
```
C_Shell > cd /home
C_Shell > history
C_Shell > help
C_Shell > exit
```

### Signals
| Signal | Key | Behavior |
|---|---|---|
| `SIGINT` | Ctrl+C | Cancels current input, shows new prompt |
| `SIGCHLD` | automatic | Cleans up background child processes |

---
