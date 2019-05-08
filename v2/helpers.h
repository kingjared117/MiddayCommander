#include <sys/time.h>
#include <sys/resource.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <string.h>
#include <readline/readline.h>
#include <readline/history.h>	

typedef struct Funcs {
	char* args[33];
	char bg;
} Funcs;

typedef struct Process {
	int task;
	char name[128];
	pid_t pid;
	int finish;	
} Process;

void printFuncs(Funcs* func, int defFunc);

int addFunc(Funcs *func, int defFunc, char* inputString);

int execFunc(Funcs func, Process* process, int backSize, pid_t currPID);

void pusage();

void printprocess(Process* process);