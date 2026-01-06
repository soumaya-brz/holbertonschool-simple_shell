# Simple Shell (hsh)

A minimal UNIX command line interpreter written in C.

## Features
- Interactive mode (prompt)
- Non-interactive mode (piped input)
- Commands with arguments
- PATH handling (type `ls` instead of `/bin/ls`)
- Builtins: `exit`, `env`
- Handles EOF (Ctrl+D)
- Does NOT call `fork()` when the command does not exist

## Compilation
```bash
gcc -Wall -Werror -Wextra -pedantic -std=gnu89 *.c -o hsh
