# Simple Shell (hsh)

A minimal UNIX command interpreter written in C.

## Features
- Interactive and non-interactive modes
- Command execution with arguments
- PATH handling
- Builtins: exit, env
- Correct exit status handling
- No fork when command does not exist
- EOF (Ctrl+D) support

## Compilation
```bash
gcc -Wall -Werror -Wextra -pedantic -std=gnu89 *.c -o hsh
