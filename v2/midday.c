#include "helpers.h"

int main(){
  int childPID;
  pid_t currPID;
  pid_t pid;
  struct rusage usage;
  struct rusage *waitusage;
  char *inCh;
  char *npath;
  char cwd[1024];
  char *ncommand;
  int numUserCmd = 2;
  Funcs funcs[35];
  Process** process;
  int i,j,l,k;
  int backSize=0;
  
  process =(Process**) calloc (50, sizeof(Process*));
  l=0;
  while(l <50){
    process[l] = malloc(sizeof(Process));
    l++;
  }
  while(1){
    
    //pid=wait3(NULL,WNOHANG,NULL);
    if(wait3(NULL,WNOHANG,NULL)>0){
      pusage();
      i=0;
      while(i<50){
	if(process[i]->pid != pid){ 
	  process[i]->finish = 0;
	 }
	i++;
      }
    }
    //print menu items
    printf("G’day, Commander! What command would you like to run?\n");
    printf("\t0. whoami\t\t: Prints out the result of the whoami command\n");
    printf("\t1. last\t\t\t: Prints out the result of the last command\n");
    printf("\t2. ls\t\t\t: Prints out the result of a listing on a user-specified path\n");
    printFuncs(funcs, numUserCmd);
    printf("\ta. add command\t\t: Adds a new command to the menu\n");
    printf("\tc. change directory\t: Changes process working directory\n");
    printf("\tp. pwd\t\t\t: Prints working directory\n");
    printf("\tr. running processes \t: Prints list of running processes\n");
    printf("\te. exit\t\t\t: Leave Mid-Day Commander\n");
    
    inCh = readline("Option?: ");
    
    
    if (feof(stdin)) {
      inCh[0] = 'e';
    }
    
    switch(inCh[0]){
    case 'a':
      printf("\n-- Add a command --\n");
      ncommand = readline("Command to add?: ");
      numUserCmd += addFunc(funcs,numUserCmd, strdup( ncommand )); //increment stored number of functions after adding
      printf("Added command %s\n",ncommand);
      break;
    case 'c':
      
      printf("\n-- Change Directory --\n");
      
      npath = readline("New Directory: ");
      chdir(npath); //changes directory to path entered, if not real no change is made
      //pontentially add error handle
      break;
    case 'p':
      printf("\n-- Current Directory --\n");
      getcwd(cwd, sizeof(cwd));  //fills string cwd with the current working directory
      printf("Directory %s\n\n", cwd);
      break;
    case 'r':
      printf("\n --Current Processes --\n");
      k=0;
      while(k<50){
	if (process[k]->finish == 1){
	  printprocess(process[k]);
	}
	k++;
      }
      break;
    case 'e':
      wait(NULL);
      printf("Logging you out, Commander.");
      exit(0);  //exits 
    default: //if option is not valid, restart program loop
      if(atoi(inCh)==0 && inCh[0]!='0')
	printf("That is not a valid option. Please try again\n\n");
      else
	switch(atoi(inCh)){
	case 0:
	  if(fork()==0){ //fork process and start whoami if the input was '0'
	    printf("\n-- Who Am I? --\n");
	    char* args[2] = {"whoami", NULL};
	    execvp(args[0],args);	
	  }	
	  else{ //parent case
	    wait(NULL); //waits for child to die and presents statistics about child
	    pusage();
	  }
	  
	  break;
	case 1:
	  if(fork()==0){ //fork process and start last if the input was '1'
	    printf("\n-- Last Logins --\n");
	    char* args[2] = {"last", NULL};
	    execvp(args[0],args);
	  }
	  else{
	    wait(NULL);
	    pusage();
	  }
	  
	  break;
	case 2:
	  if(fork()==0){ //fork process and start ls if the input was '2'
	    printf("\n-- Directory Listings --\n");
	    char *path;
	    char *argIn;
	    char *args[34];
	    int i=1;
	    args[0] = "ls";
	    argIn = readline("Arguments?: ");
	    char *token = strtok(argIn, " ");
	    while (token != NULL){
	      args[i] = malloc(strlen(token) + 1);
	      strcpy(args[i], token);
	      token = strtok(NULL, " "); //get tokenized arguments
	      i++;
	    }
	    path = readline("Path?: ");
	    args[i] = path;
	    i++;
	    args[i] = NULL;
	    execvp(args[0],args); //execute ls
	  }
	  else{
	    wait(NULL);
	    pusage();
	  }
						  
	  break;
	default:
	  backSize = execFunc(funcs[atoi(inCh)],process[backSize],backSize,currPID);
	  break;
	}
      break;
    }
    
  }
}

