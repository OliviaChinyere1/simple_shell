#include "shell.h"

/**
<<<<<<< HEAD
 * exec - handles execution of commands
 * @input: array of arguments from standard input
 * @s: name of the program
 * @i: index of error
 * @head: linked list containing environment
 *
 * Return: return to main loop with 1 on success, or 0 on failure
 *
 */

int exec(char **input, char *s, int *i, env_t **head)
{
struct stat filestat;
int status = 0;
char *exe = NULL, **env = NULL;
pid_t child_pid;
child_pid = fork();
if (child_pid == -1)
{
print_error(i, s, input);
free_everything(input);
exit(EXIT_SUCCESS);
}
if (child_pid == 0)
{
env = list_to_arr(*head);
if (get_env_val("PATH=", env)[0] != '/')
execve(input[0], input, env);
exe = path_finder(input, env);
if (!exe && !stat(input[0], &filestat))
{
if (execve(input[0], input, env) == -1)
{
print_error(i, s, input);
free_everything(input), free_everything(env);
return (0);
}
free_everything(input);
free_everything(env);
}
if (execve(exe, input, env) == -1)
{
print_error(i, s, input);
free(exe), free_everything(input), free_everything(env);
exit(EXIT_SUCCESS);
}
}
else
wait(&status);
free_everything(input), free_everything(env);
return (1);
}

/**
 * main - simple command-line argument interpreter
 * prints a prompt and waits for the user to input a command,
 * then creates a child process in which it exececutes the command
 *
 * @ac: number of arguments
 * @av: array of arguments
 *
 * Return: always 0, for success
 *
 */

int main(int ac, char *av[])
{
size_t len = 0;
int cmd_count = 0, get;
char **input = NULL, *line = NULL, *prog_name = av[0];
env_t *head = NULL;
if (ac != 1)
{
print_error_main(av);
exit(127);
}
signal(SIGINT, sigint_handler);
arr_to_list(&head, environ);
while (1)
{
if (isatty(STDIN_FILENO) != 0 && isatty(STDOUT_FILENO) != 0)
print_prompt();
get = getline(&line, &len, stdin);
if (get < 0)
{
if (isatty(STDIN_FILENO) != 0 && isatty(STDOUT_FILENO) != 0)
_putchar('\n');
break;
}
cmd_count++;
if (_strcmp(line, "\n") == 0)
continue;
input = parse_line(line, get);
if (!input)
continue;
if (is_builtin(line, input, prog_name, &cmd_count, &head))
{
free_everything(input);
continue;
}
if (!exec(input, prog_name, &cmd_count, &head))
break;
}
free_list(&head), free(line);
return (0);
=======
* main - entry point
* @ac: arg count
* @av: arg vector
*
* Return: 0 on success, 1 on error
*/
int main(int ac, char **av)
{
info_t info[] = { INFO_INIT };
int fd = 2;
asm ("mov %1, %0\n\t"
"add $3, %0"
: "=r" (fd)
: "r" (fd));
if (ac == 2)
{
fd = open(av[1], O_RDONLY);
if (fd == -1)
{
if (errno == EACCES)
exit(126);
if (errno == ENOENT)
{
_eputs(av[0]);
_eputs(": 0: Can't open ");
_eputs(av[1]);
_eputchar('\n');
_eputchar(BUF_FLUSH);
exit(127);
}
return (EXIT_FAILURE);
}
info->readfd = fd;
}
populate_env_list(info);
read_history(info);
hsh(info, av);
return (EXIT_SUCCESS);
>>>>>>> c20d4032d9927a186d8df7d43e671084238098de
}
