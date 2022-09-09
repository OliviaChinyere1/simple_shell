#include "shell.h"

/**
 * is_builtin - checks if the command is a builti
 * @line: line from input, passed in to free properly
 * @prog_name: name of the program
 * @argv: parsed command line
 * @i: pointer to the increment variable of main
 * @head: double pointer to the environ linked list
 *
 * Return: 0 to main
 *
 */

int is_builtin(char *line, char **argv, char *prog_name, int *i, env_t **head)
{
int n, l;
long int m;
if (!_strcmp(argv[0], "exit"))
{
m = exit_handler(argv);
if (m == -1)
print_error_exit(i, prog_name, argv);
else
{
free_everything(argv);
free(line);
free_list(head);
exit(m);
}
return (1);
}
if (!_strcmp(argv[0], "env"))
{
n = env_handler(argv, head);
if (n == -1)
print_error_env(argv);
return (1);
}
if (!_strcmp(argv[0], "setenv") || !_strcmp(argv[0], "unsetenv"))
{
setenv_handler(argv, head, i, prog_name);
return (1);
}
if (!_strcmp(argv[0], "cd"))
{
l = cd_handler(argv, head);
if (l == -1)
{
print_error_cd(i, prog_name, argv);
write(2, "\n", 1);
}
return (1);
}
return (0);
}

/**
 * exit_handler - handles the builtin exit with arguments
 * @tokens: array of strings from the command line
 *
 * Return: 0 if there are no arguments,
 * -1 on failure, or the value of the argument
 *
 */

long int exit_handler(char **tokens)
{
int flag = 0, i;
long int num = 0;
if (tokens[1] == NULL)
return (num);
for (i = 0; tokens[1][i]; i++)
{
if ((tokens[1][i] >= '0' && tokens[1][i] <= '9') || tokens[1][0] == '+')
{
flag = 1;
if (tokens[1][i + 1] < '0' || tokens[1][i + 1] > '9')
break;
}
else
break;
flag = 0;
}
if (flag == 1)
{
num = _atoi(tokens[1]);
return (num);
}
return (-1);
}

/**
 * env_handler - replicates the bash env built
 * @av: array of arguments from the command line
 * @head: double pointer to the env_t linked list
 *
 * Return: 0 on success, -1 on error
 */

int env_handler(char **av, env_t **head)
{
if (av[1] == NULL)
{
print_list(*head);
return (0);
}
return (-1);
}

/**
 * cd_handler - replicates the bash cd builtin
 * @argv: array of arguments from the command line
 * @head: double pointer to the env_t linked list
 *
 * Return: 0 if none of the other cases succeeded
 */

int cd_handler(char **argv, env_t **head)
{
char *home = NULL, *old = NULL, **env = NULL;
env = list_to_arr(*head);
if (!argv[1])
{
home = get_env_val("HOME=", env);
chdir(home);
change_pwd(home, env, head);
free_everything(env);
return (1);
}
if (_strcmp(argv[1], "-") == 0)
{
old = get_env_val("OLDPWD=", env);
_puts(old);
change_pwd(old, env, head);
chdir(old);
free_everything(env);
return (1);
}
if (chdir(argv[1]) < 0)
{
free_everything(env);
return (-1);
}
else
{
change_pwd(argv[1], env, head);
free_everything(env);
return (1);
}
return (0);
}

/**
 * change_pwd - helper function for c
 * @path: path of the working directories we want to change t
 * @head: double pointer to the env_t linked list
 * @env: double array containing the environment
 *
 */

void change_pwd(char *path, char **env, env_t **head)
{
char **old = NULL, **current = NULL;
int nodes = 0, set = 0;
old = malloc(sizeof(char *) * 4);
old[0] = _strdup("old");
old[1] = _strdup("OLDPWD");
old[2] = _strdup(get_env_val("PWD=", env));
old[3] = NULL;
current = malloc(sizeof(char *) * 4);
current[0] = _strdup("current");
current[1] = _strdup("PWD");
current[2] = _strdup(path);
current[3] = NULL;
nodes = arr_to_list(head, env);
if (!nodes)
return;
set = _setenv(head, old, 2);
if (set < 0)
{
free_everything(old);
free_everything(current);
return;
}
free_everything(old);
set = _setenv(head, current, 2);
if (set < 0)
{
free_everything(current);
return;
}
free_everything(current);
}

