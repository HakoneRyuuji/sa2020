#include<stdio.h>

#include<unistd.h>

#include<string.h>

#include<stdbool.h>

#include<sys/wait.h>

int main(void) {
  pid_t pid;
  char cmd[99];
  while (true) {
    printf("Enter your command:");
    scanf("%s", cmd);
    if (strcmp(cmd, "quit") == 0) {
      printf("Quit the mini shell.\n");
      return 0;
    }
    pid = fork();
    if (pid == 0) {
      char * args[] = {
        cmd,
        NULL
      };
      execvp(cmd, args);

      return 0;
    } else
      wait(NULL);
  }
  return 0;
}
