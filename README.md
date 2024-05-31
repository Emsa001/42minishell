
# 42 MiniShell

This project is about creating a simple shell. Yes, your own little bash 🙂
![App Screenshot](https://imgur.com/aOVi1Zp.png)
 

## Challenges
#### Process Management
Handle process creation and management using `fork()`, `execve()`, and `wait()` functions. This involves correctly forking new processes to execute commands, managing process IDs, and ensuring effective communication between parent and child processes.

#### File Descriptors and Redirections
Implement input/output redirections, which requires a solid grasp of how file descriptors work in Unix-like systems. Handle input (`<`), output (`>`), append (`>>`), and heredoc (`<<`).

#### Signal Handling
Gracefully handle signals like `ctrl-C`, `ctrl-D`, and `ctrl-\`, ensuring they interact correctly with the shell's state and processes. Implementing signal handlers to manage interrupts without disrupting the shell's functionality.

#### Memory Management
Allocate and free memory properly to avoid leaks, especially when dealing with dynamic inputs and environment variables. This involves understanding and correctly using functions like `malloc()` and `free()`.
We created [ft_destructor](https://github.com/Emsa001/ft_destructor/) that helped use to secure each allocation and free everything in case of error.

#### Parsing and Execution
Correctly parse user inputs to interpret and execute commands. Handle different types of quotes, and special symbols required by subject while maintaining the correct execution order.

#### Built-in Commands
Implement built-in commands such as `cd`, `echo`, `pwd`, `export`, `unset`, `env`, and `exit` with their expected behaviors. Each command has its own set of rules and nuances that need to be replicated accurately.

#### User Interaction
Create a user-friendly shell experience by managing the display of prompts, maintaining command history, and ensuring responsive handling of user inputs. Implement features like `readline` for input and history management.

#### Compliance with Standards
Adhere to coding standards (the Norm) while implementing all features. Ensuring your code is clean, maintainable, and free of norm errors

#### cat | cat | cat | cat | cat | cat | ls
Yes, this was painfull (btw dogs don't have this problem)
## Installation

Clone the repository and build
```bash
git clone https://github.com/Emsa001/42minishell
cd ./42minishell
make
```

Run the program
```bash
./minishell
```
## Demo


Example Commands:
```bash
echo Hello $USER
export x1="two words"
printf "%s\n" $x1
ls *s*
cat | cat | cat | ls
false && echo 123
true && echo 123
```

![App Screenshot](https://imgur.com/YYWxTzA.png)


## Authors

- [@emsa001](https://www.github.com/emsa001)
- [@triedel42](https://www.github.com/triedel42)

