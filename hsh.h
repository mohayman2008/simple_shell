#ifndef __hsh_h__
#define __hsh_h__

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>

#define DELIM " \t\v\3\4\n\r\f\0"
#define PTR_BUF_SIZE_INC 10

extern char **environ;

int char_cmp(char c, char *c_set);
char **get_tokens(char *str, char *delim);
char **read_prompt(ssize_t *read_count);

int exec(char *filepath, char **av, char **env);

void free_str_array(char **str_arr);

#endif /* __hsh_h__ */
