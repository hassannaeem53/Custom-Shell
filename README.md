# Custom-Shell
This shell is developed on Ubuntu OS using basic OS concepts like System Calls(Fork, execvp, etc) , Inter-process Communication, Multi-threading and Input Output Redirection.

The shell was assigned as multiple assignments in semester 4 of BS-CS Program(FAST-NUCES LHR) for Operating System Course.The evaluation was done by Sir Saad Farooq.

### CodeFile 1 involves the following functionalities

1. User types a command, such as “cp ./OS ../newOS”. The command will be stored in a character
array or a string object.
2. Shell will perform tokenization and separate the command and its arguments.
3. Shell will create a child process and use execvp system call to execute the command.
4. Shell will wait for the command to finish execution.
5. After the command has been executed, shell will ask the user to enter the command again.
6. Shell will exit when the command given by the user is “exit”.

### CodeFile 2 extends ..
add support for input/output redirection. So, the commands in which |, < and > symbols are used should be supported by the shell.

Example:
ls > file.txt
man fork | grep child > file.txt
The command can have any number of | symbols, such as
command1 | command 2 | command3 > file.txt


