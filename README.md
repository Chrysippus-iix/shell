# Unix Shell in C

A minimal Unix shell built from scratch in C, implementing core OS concepts.

# Foreword

In these times where such a big field as computing has become riddled with surface level doctrine or web development, and confusion as to where to start or what to learn... i developed curiosity for the underlying workings of a computer itself. I created this github on short notice (which i hadnt done so before). I created this during university because recruiters, employers, or others wanted an eye into what ive been doing. And ive become very curious about low level computing, kernels, systems, but also and not limited to machine learning and deep learning, and other stuff as well that ill cover in time (maybe).

It is currently june 25th 2026, im using AI to assist me in learning as i ask it questions and try to reason about what i want to accomplish, i also use man pages, youtube, and books if necessary. 

⚠️SMALL DISCLAIMER
Im very forgetful, i have terrible memory, so throughout the process i documented a lot in my own words using analogies as well. So you'll see a LOT of comments in the code, its just part of my process, kinda.

# Where i got really lost
Not just syntax, yeah i kinda get lost, but you can ask around about that. However, reasoning about architecture, infrastructure, or what youre trying to accomplish and asking the computer to do is a different topic, its very important, you dont just type away at syntax, at least i cant do that without thinking of structures. For libraries or function usage, you can also lookup man pages, look for help and whatnot. None of that was the issue, where i REALLY got stuck was the usage of strtok, the string tokenizer. I just couldnt reason about strings that way, it was so weird to me (for some reason). I understand the idea, but in practice? The whole ordeal of strtok and tokens for strings was so bizarre. I often forget the gist of it and find it difficult to reason about it in my mind.

## Features
- Interactive prompt
- Command parsing and tokenization
- Process creation via fork/exec
- Parent process waits for child to complete
- Built-in `exit` command

## How it works
1. Shell prints a prompt and reads user input
2. Input is tokenized using `strtok` (split by spaces)
3. `fork()` creates a child process
4. Child calls `execvp()` to replace itself with the requested command
5. Parent calls `waitpid()` to wait for child to finish

## Build
```bash
gcc -Wall -Wextra -o shell shell.c
./shell
```

## Lessons Learned
- `strtok` uses a static internal buffer, subsequent calls take `NULL` to continue parsing the same string
- `fork()` returns the child's PID to the parent and 0, to the child that's how one process becomes two different behaviors
- `execvp()` completely replaces the child process image with the target program

## Status
Work in progress planned additions: piping, redirection, environment variables
