/*
 * =====================================================================================
 *
 *       Filename:  shell.cc
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  2017년 07월 01일 23시 02분 30초
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  Hobum (Vincent) Kwon (mn), hobum.kwon@gmail.com
 *        Company:  Samsung Electornics
 *
 * =====================================================================================
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>

typedef struct _COMMAND {
  char *name;
  char *desc;
  bool (*func)(int argc, char *argv[]);
} Command;

bool cmd_cd(int argc,   char *argv[]);
bool cmd_exit(int argc, char *argv[]);
bool cmd_help(int argc, char *argv[]);

Command builtin_cmds[] = {
  {"cd", "change directory",  cmd_cd },
  {"exit", "exit this shell", cmd_exit },
  {"quit", "quit this shell", cmd_exit },
  {"help", "show this help", cmd_help },
  {"?", "show this help", cmd_help }
};

bool cmd_cd(int argc, char *argv[]) {
  if (argc == 1) chdir(getenv("HOME"));
  else if (argc == 2) {
    if (chdir(argv[1])) printf("No directory"); 
  }
  else {
    printf("Usage: cd [dir]\n");
  }
  return true;
}

bool cmd_exit(int argc, char *argv[]) {
  return false;
}

bool cmd_help(int argc, char *argv[]) {
  int i;
  for (i = 0; i < sizeof(builtin_cmds) / sizeof(Command); i++) {
    if (argc == 1 || strcmp(builtin_cmds[i].name, argv[1]) == 0) 
      printf("%-10s: %s\n", builtin_cmds[i].name, builtin_cmds[i].desc);
  }
}

int tokenize(char *buf, char *delims, char* tokens[], int maxTokens) {
  int token_count = 0;
  char *token;
  token = strtok(buf,delims);
  while (token != NULL & token_count < maxTokens) {
    tokens[token_count] = token;
    token_count++;
    token = strtok(NULL, delims);
  }
  tokens[token_count] = NULL;
  return token_count;
}

bool run(char *line) {
  char delims[] = "\r\n\t";
  char *tokens[128];
  int token_count;
  int i;
  int status;
  pid_t child;
  token_count = tokenize(line, delims, tokens, sizeof(tokens) / sizeof(char*));
  if (token_count == 0) return true;
  for (i = 0; i < sizeof(builtin_cmds) / sizeof(Command); i++) {
    if (strcmp(builtin_cmds[i].name, tokens[0]) == 0) {
      return builtin_cmds[i].func(token_count, tokens);
    }
  }
  child = fork();
  if (child == 0) {
    execvp(tokens[0], tokens);
    printf("No such file\n");
    _exit(0);
  } 
  else if (child < 0) {
    printf("Failed to fork()");
    _exit(0);
  }
  else {
    wait(&status);
  }
  return true;
}

int main() {
  char line[1024];
  while (true) {
    printf("%s  $ ", get_current_dir_name());
    fgets(line, sizeof(line)-1, stdin);
    if (run(line) == false) break;
  }
  return 0;
}
