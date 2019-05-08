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
  int j,i = 0;
        char bg;
	//set bacgroundng if last character is ampersand
			
       	if(inputString[strlen(inputString)-1]=='&'){
	  inputString[strlen(inputString)-1]=0;
	  bg=1;
        }  
        else
	  bg=0;

	if(bg) func[defFunc+1].bg=1;
	char* stripNL=strtok(inputString,"\n"); //strip the newline character from the string
	for(char* tok = strtok(stripNL, " "); tok; tok = strtok(NULL, " ")) //tokenize input
	     func[defFunc+1].args[i++] = tok;
	return 1; 
}

void execFunc(Funcs func/*, Process** process, int *backSize, pid_t* currPID*/){
     struct rusage usage;
     printf("-- %s -- \n", func.args[0]);
      printf("background: %d\n",(int*)func.bg);
     
     if(fork()==0){
       
       
       execvp(func.args[0],func.args);
     }
     else if(!func.bg){
	  wait(NULL);
          getrusage(RUSAGE_CHILDREN, &usage); 
          printf("\n-- Statistics --\n Elapsed time: %ld millisecond(s)\nPage Faults: %ld\nPage Faults (reclaimed): %ld\n\n",
          (usage.ru_utime.tv_sec*1000+usage.ru_utime.tv_usec/1000), usage.ru_majflt, usage.ru_minflt);
     }
     /* else{
       (*backSize)+=1;
       process[*backSize]=malloc(sizeof(Process));
       strcpy(*process[*backSize-1]->name,func.args[0]);
       process[*backSize-1]->finish=0;
       process[*backSize-1]->pid=*currPID;
       }*/
}

