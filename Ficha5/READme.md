# Sistemas de Operação
## Q1

O `número de processos é igual a 2^n`, onde **n corresponde ao número de fork()** usados no programa
- O primeiro fork() (dentro do processo main) vai criar um novo processo

- Este novo processo vai sendo executado concurrentemente ao processo pai, depois, ambos vão criar um novo processo (passando a haver 4 no total)

- Agora, cada processo vai criar um novo processo ficando um total de 8 processos

## Q2

Vão ser criados 2^4 (n = 4 fork()) processos, isto é, 16 processos

## Q3

The `fork()` call is made in line 10 creating a new process. This new process will run before its parent and, since it's a child process, making a new `fork()` call will return the value 0, setting `value` to 1 and printing `CHILD: value = 1, addr = 0x...`.

Afterwards, the main process will have its thread unlocked and will continue running. However, since the return value of this call will be its child pid, it will go to the `else` branch and print `PARENT: value = 0, addr = 0x...`.

The memory addresses of both `value` variables will be the same since the variable `value` was created before the fork was created.

## Q4

Since the function `execlp` doesn't change the pid of the child process, if it executes successfully, `waitpid` in the parent will return a value of the process (usually a child) whose status information has been obtained.

That is different from -1, so we will get the message `child exited` printed.

## Q5

You can't execute commands with arguments, because in the function call `execlp(command, command, (char *)0)`, `command` is the string that the user inputs to the buffer, so if you input a command with arguments, following the documentation of `execlp`, you should pass firstly the file, and then one argument per parameter in the call. 

However, in this case, we have 2 problems:
```
For example, let's assume command is "touch a" (we have 2 problems)

    - The file "touch a" will not be found;

    - All the arguments are passed to the 2nd parameter, instead of being divided in the 2nd and 3rd arguments.
```