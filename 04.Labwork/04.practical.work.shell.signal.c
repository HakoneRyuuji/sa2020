#include<stdio.h>

#include<stdlib.h>

#include<unistd.h>

#include<string.h>

#include<stdbool.h>

#include<sys/wait.h>

void handler(int signal_num) {
  printf("Signal %d => ", signal_num);
  switch (signal_num) {
  case SIGTSTP:
    printf("pause\n");
    break;
  case SIGINT:
  case SIGTERM:
    printf("Terminated\n");
    exit(0);
    break;
  }
}

int main(int argc, char const *argv[]) {
	char input[100];
	char *args[10];
    pid_t pid;
    char cmd[99];
  // ctrl z
    signal(SIGTSTP, handler);
  // ctrl c or killed
    signal(SIGINT, handler);
    signal(SIGTERM, handler);

	while (1) {
		// ask for command
		printf("Enter your command:");
		fgets(input, sizeof(input), stdin);

		// initialization of args everytime
		memset(args, 0, sizeof(args));
		
		// transform the input string
		// to array of args
		// so that execvp can use
		int argc = 0;
		int len = strlen(input);
		char *prevArg = input;
		for (int i = 0; i < len; i++) {
			if (input[i] == ' ') {
				args[argc++] = prevArg;
				prevArg = &input[i+1];
				input[i] = '\0';
			}
			if (input[i] == '\n') {
				input[i] = '\0';
			}
		}
		args[argc++] = prevArg;

		// dump the info for debugging purpose
		printf("Input : %s\n", input);
		if (strcmp(input, "quit") == 0) {
			break;
		}

		printf("- argc : %d\n", argc);
		printf("- args : \n");
		for (int i = 0; i <= argc; i++) {
			printf("  + args[%d]=%s\n", i, args[i]);
		}

		// fork() + exec() combo
		int pid = fork();
		if (pid == 0) {
			execvp(args[0], args);
		}
		else {
			waitpid(pid, NULL, 0);
		}
	}
	printf("Terminating.\n");
	return 0;
}

