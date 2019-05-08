#include "helpers.h"

void printFuncs(Funcs*func,int defFunc){
     if(defFunc>2){
     	int i;
     	for(i=3;i<=defFunc; i++){
	     printf("\t%d. %s\n",i,func[i].args[0]);
     	}
     }
}
 
int addFunc(Funcs *func, int defFunc, char* inputString){
	int i = 0;
	char* stripNL=strtok(inputString,"\n"); //strip the newline character from the string
	for(char* tok = strtok(stripNL, " "); tok; tok = strtok(NULL, " ")) //tokenize input
	     func[defFunc+1].args[i++] = tok;
	if(i>32){
		printf("to many arguments \n");
		return 0;
	}
	return 1; 
}

void execFunc(Funcs func){
     struct rusage usage;
     printf("-- %s -- \n", func.args[0]);
 
     if(fork()==0){
//	printf("Jared is the best");
          execvp(func.args[0],func.args);
     }
     else{
	  wait(NULL);
          getrusage(RUSAGE_CHILDREN, &usage); 
          printf("\n-- Statistics --\n Elapsed time: %ld millisecond(s)\nPage Faults: %ld\nPage Faults (reclaimed): %ld\n\n",
          (usage.ru_utime.tv_sec*1000+usage.ru_utime.tv_usec/1000), usage.ru_majflt, usage.ru_minflt);
     }
}

