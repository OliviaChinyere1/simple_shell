#include "shell.h"

/**
 * wordcount - counts tokens in a string for _strtok
 * @str: string to tokenize
 * @delim: delimeter between tokens
 *
 * Return: number of tokens
 *
 */

int wordcount(char *str, char delim)
{
int num = 0, i;
int flag = 0;
for (i = 0; str[i]; i++)
{
if (str[i] == delim)
flag = 0;
else if (flag == 0)
{
flag = 1;
num++;
}
}
return (num);
}

/**
 * _strtok - converts a string into an array of tokens
 * @str: string to tokenize
 * @delim: delimeter between tokens
 *
 * Return: pointer to the array of strings on success, or NULL on failure
 *
 */

char **_strtok(char *str, char delim)
{
char *cpy = NULL, **words = NULL;
int i = 0, j = 0, len = 0, total = 0;
if (str == 0 || *str == 0)
return (NULL);
total = wordcount(str, delim);
if (total == 0)
return (NULL);
words = malloc(sizeof(char *) * (total + 1));
if (words == NULL)
return (NULL);
while (*str && i < total)
{
if (*str == delim)
str++;
else
{
cpy = str;
while (*str != delim && *str)
{
len++;
str++;
}
words[i] = malloc(sizeof(char) * (len + 1));
if (!words[i])
return (NULL);
while (*cpy != delim && *cpy && *cpy != '\n')
{
words[i][j] = *cpy;
cpy++;
j++;
}
words[i][j] = '\0';
i++;
j = 0;
len = 0;
}
}
words[i] = NULL;
return (words);
}
