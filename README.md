# 🐚 Minishell

> A minimalist recreation of a Unix shell — inspired by **bash**, built from scratch in C as part of the 42 School curriculum.

## 🧠 About

Minishell is a full-blown project that ties together everything you've learned in C so far: parsing, process management, signals, environment variables, and file descriptors. The goal is to build a functional shell that can execute commands, handle redirections and pipes, expand variables, and behave like bash for a well-defined subset of features.

This project reinforces:
- Process creation and management (`fork`, `execve`, `wait`, `waitpid`)
- File descriptors and redirections (`dup2`, `pipe`, `open`, `close`)
- Signal handling (`SIGINT`, `SIGQUIT`) with `signal` / `sigaction`
- Lexing and parsing (tokenizing input, building an AST or command list)
- Environment variable management and expansion

## ⚙️ Features

### Prompt & input
- Interactive prompt with history (via `readline`)
- Handles `ctrl-C`, `ctrl-D`, and `ctrl-\` like bash

### Command execution
- Executes binaries via absolute path (`/bin/ls`), relative path (`./a.out`), or `$PATH` lookup
- Handles quotes: single `'` (no expansion), double `"` (variable expansion allowed)

### Redirections
| Symbol | Behavior |
|---|---|
| `<` | Input redirection |
| `>` | Output redirection (truncate) |
| `>>` | Output redirection (append) |
| `<<` | Heredoc |

### Pipes
- Supports pipelines of arbitrary length: `ls | grep .c | wc -l`

### Built-ins
| Built-in | Description |
|---|---|
| `echo` (with `-n`) | Print arguments |
| `cd` | Change directory |
| `pwd` | Print working directory |
| `export` | Set environment variables |
| `unset` | Remove environment variables |
| `env` | Print environment |
| `exit` | Exit the shell |

### Variable expansion
- `$VAR` expands to the corresponding environment variable
- `$?` expands to the exit status of the last command

## 🚀 Usage

Clone the repo and compile:

```bash
git clone <your-repo-url>
cd minishell
make
```

Run the shell:

```bash
./minishell
```

Example session:

```bash
minishell$ echo "hello $USER" > out.txt
minishell$ cat out.txt | grep hello
hello eddy
minishell$ exit
```

## 🧪 Testing

*(Optional — mention here if you used a tester like [mini-hell](https://github.com/Chelsea486MHz/mini-hell) or [minishell_tester](https://github.com/zstenger93/42_minishell_tester), and how you compared behavior against bash)*

```bash
bash tester.sh
```

## 🗂️ Project Structure

```
minishell/
├── includes/
│   └── minishell.h        # Structs, prototypes, macros
├── src/
│   ├── main.c              # Main loop, prompt, readline
│   ├── lexer/              # Tokenization
│   ├── parser/             # Building command structures
│   ├── executor/           # Fork, exec, pipes, redirections
│   ├── builtins/           # cd, echo, export, unset, env, pwd, exit
│   ├── env/                # Environment management
│   ├── signals/            # Signal handling
│   └── utils/
├── libft/                  # Libft used internally
├── Makefile
└── README.md
```

## 📌 Notes

- Built with `readline` for input handling and history.
- No memory leaks (checked with `valgrind`, ignoring `readline`'s known leaks).
- Behavior matches `bash` for the required feature set.
- Norm-compliant for the 42 curriculum.

## 👥 Authors

**Eddy** & *(teammate name)* — students at [42 Paris](https://42.fr)
[GitHub](https://github.com/your-username) · [42 Intra](https://profile.intra.42.fr/users/your-login)
