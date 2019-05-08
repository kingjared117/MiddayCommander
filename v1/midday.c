#include "helpers.h"

int main(){
  int childPID;
  struct rusage usage;
  char *inCh;
  char *npath;
  char cwd[1024];
  char *ncommand;
  int numUserCmd = 2;
  Funcs funcs[35];
  
  
  while(1){
    //print menu items
    printf("G’day, Commander! What command would you like to run?\n");
    printf("\t0. whoami\t\t: Prints out the result of the whoami command\n");
    printf("\t1. last\t\t\t: Prints out the result of the last command\n");
    printf("\t2. ls\t\t\t: Prints out the result of a listing on a user-specified path\n");
    printFuncs(funcs, numUserCmd);
    printf("\ta. add command\t\t: Adds a new command to the menu\n");
    printf("\tc. change directory\t: Changes process working directory\n");
    printf("\tp. pwd\t\t\t: Prints working directory\n");
    printf("\te. exit\t\t\t: Leave Mid-Day Commander\n");
    //take in option input
    inCh = readline("Option?: ");
    if (feof(stdin)) {
      inCh[0] = 'e';
    }
    switch(inCh[0]){
    case 'a':
      printf("\n-- Add a command --\n");
      ncommand = readline("Command to add?: "); //read in command with arguments to add
      if (strlen(ncommand) > 128){
	printf("Only accepts 128 characters, try again \n");
	break;
      }
      numUserCmd += addFunc(funcs,numUserCmd, strdup( ncommand )); //increment stored number of functions after adding
      printf("Added command %s\n",ncommand);
      break;
    case 'c':
      
      printf("\n-- Change Directory --\n");
      npath = readline("New Directory: ");  //takes in the new directory location
      if (strlen(npath) > 128){
	printf("Only accepts 128 characters, try again");
	break;
      }
      chdir(npath); //changes directory to path entered, if not real no change is made
      break;
    case 'p':
      printf("\n-- Current Directory --\n");
      getcwd(cwd, sizeof(cwd));  //fills string cwd with the current working directory
      printf("Directory %s\n\n", cwd);
      break;
    case 'e':
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
	    //Runs whoami
	    execvp(args[0],args);	
	  }	
	  else{ //parent case
	    wait(NULL); //waits for child to die and presents statistics about child
	    getrusage(RUSAGE_CHILDREN, &usage);
	    printf("\n-- Statistics --\n Elapsed time: %ld millisecond(s)\nPage Faults: %ld\nPage Faults (reclaimed): %ld\n\n",
		   (usage.ru_utime.tv_sec*1000+usage.ru_utime.tv_usec/1000), usage.ru_majflt, usage.ru_minflt);
	  }
	  break;
	case 1:
	  if(fork()==0){ //fork process and start last if the input was '1'
	    printf("\n-- Last Logins --\n");
	    char* args[2] = {"last", NULL};
	    //Runs Last
	    execvp(args[0],args);
	  }
	  else{
	    wait(NULL);
	    getrusage(RUSAGE_CHILDREN, &usage); //get child statistics
	    printf("\n-- Statistics --\n Elapsed time: %ld millisecond(s)\nPage Faults: %ld\nPage Faults (reclaimed): %ld\n\n",
		   (usage.ru_utime.tv_sec*1000+usage.ru_utime.tv_usec/1000), usage.ru_majflt, usage.ru_minflt);
	  }
	  break;
	case 2:
	  if(fork()==0){ //fork process and start ls if the input was '2'
	    printf("\n-- Directory Listings --\n");
	    char *path;     //store user inputed path
	    char *argIn; 	//store arguments
	    char *args[34]; //fill to use as arguments for function
	    int i=1;	//counter for loop
	    args[0] = "ls";
	    argIn = readline("Arguments?: ");//get arguments
	    if (strlen(argIn) > 128){
	      printf("Only accepts 128 characters, try again\n");
	      break;
	    }
	    
	    char *token = strtok(argIn, " ");//tokenize arguments and get first argument
	    while (token != NULL){
	      args[i] = malloc(strlen(token) + 1);//malloc out space
	      strcpy(args[i], token);		    //copy token into array
	      token = strtok(NULL, " "); //get tokenized arguments
	      i++;
	    }
	    
	    if (i > 32){  //error to many arguments
	      printf("Only accept 32 arguments, try agaian \n");
	      break;
	    }
	    
	    path = readline("Path?: "); //get path
	    if (strlen(path) > 128){
	      printf("Only accepts 128 characters, try again \n");
	      break;
	    }
	    
	    args[i] = path; //add path to array
	    i++;			    //increment array
	    args[i] = NULL;		    //add NULL at end 
	    execvp(args[0],args); //execute ls
	  }
	  else{
	    wait(NULL);
	    getrusage(RUSAGE_CHILDREN, &usage); 
	    printf("\n-- Statistics --\n Elapsed time: %ld millisecond(s)\nPage Faults: %ld\nPage Faults (reclaimed): %ld\n\n",
		   (usage.ru_utime.tv_sec*1000+usage.ru_utime.tv_usec/1000), usage.ru_majflt, usage.ru_minflt);
	  }	
	  break;
	default:
	  execFunc(funcs[atoi(inCh)]);
	  break;
	}
      break;
    }
    
  }
}
