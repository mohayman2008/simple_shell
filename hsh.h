#ifndef __hsh_h__
#define __hsh_h__

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <sys/types.h>
#include <sys/stat.h>

#define DELIM " \t\v\3\4\n\r\f\0"
#define PTR_BUF_SIZE_INC 10

extern char **environ;

/**
 * struct path_node - represents a single absoulute path
 * @path: String represents an absolute path
 * @next: pointer to the next node
 */
typedef struct path_node
{
	char *path;
	struct path_node *next;
} path_t;

char *_getenv(const char *key);
void duplicate_env(void);
void free_str_vector(char **str_vector);
int _setenv(const char *name, const char *value, int overwrite);
int _unsetenv(const char *name);
void print_path(void);

/*-----path.c-----*/
path_t *build_path_list(void);
void free_path_list(path_t **path_list);
char *search_path(char *name);
char *get_path(char *name);

int char_cmp(char c, char *c_set);
char **get_tokens(char *str, char *delim);
char **read_prompt(ssize_t *read_count);

int exec(char *filepath, char **av, char **env);

/*-----errors.c-----*/
void *error_null(const char *error_prefix);

void free_str_array(char **str_arr);

#endif /* __hsh_h__ */
