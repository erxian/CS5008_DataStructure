// Modify this file for your assignment
// gcc readline.c -o readline
// 
// This example program demonstrates
// how to read a line in C and
// use the string compare function.
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/wait.h>
#include <sys/types.h>
#include <signal.h>

#define MAX_BUFFER_SIZE 80

char* historyCommands[MAX_BUFFER_SIZE];
int count = 0;
char* add_to_history(char* str) {
	char* tempStr = malloc((strlen(str))*sizeof(char));
	strcpy(tempStr, str);	
	if (strcmp(tempStr, "history") != 0) { 
		historyCommands[count] = tempStr;
		count++;
	}
	return tempStr;
}

int builtin_history(char **args);
int builtin_cd(char **args);
int builtin_help(char **args);
int builtin_exit(char **args);

char *builtin_str[] = {"history", "cd", "help", "exit"};

int (*builtin_func[]) (char **) = {&builtin_history, &builtin_cd, &builtin_help, &builtin_exit};

int count_builtins() {
  return sizeof(builtin_str) / sizeof(char *);
}

int builtin_history(char **args) {
	char **ptr = historyCommands;
	for (ptr = historyCommands; *ptr != NULL; ptr++) {
		printf("%s\n", *ptr);
	}
	return 1;
}

int builtin_cd(char **args)
{
  if (args[1] == NULL) {
    fprintf(stderr, "lsh: expected argument to \"cd\"\n");
  } else {
    if (chdir(args[1]) != 0) {
      perror("lsh cd");
    }
  }
  return 1;
}

int builtin_help(char **args)
{
  int i;
  printf("\n***Welcome To Zengping's Shell***\n");
  printf("List of Commands are built in:\n");

  for (i = 0; i < count_builtins(); i++) {
      printf("  %s\n", builtin_str[i]);
  }

  printf("All other general commands are available too!\n");
  printf("Use 'man [command]' to get more usage :)\n");
  printf("\n");
  return 1;
}

int builtin_exit(char **args)
{
  printf("\nBye Bye\n"); 
  return 0;
}

int execute_builtin(char** args) {
  int i;

  if (args[0] == NULL) {
    // An empty command was entered.
    return 1;
  }

  for (i = 0; i < count_builtins(); i++) {
    if (strcmp(args[0], builtin_str[i]) == 0) {
      return (*builtin_func[i])(args);
    }
  }
  return 1;
}

void sigint_handler(int signo) {
	printf("mini-shell terminated\n");
	exit(0);
}

// function for finding pipe 
int isPipe(char* str, char** strpiped) 
{ 
    int i; 
    for (i = 0; i < 2; i++) { 
        strpiped[i] = strsep(&str, "|"); 
        if (strpiped[i] == NULL) 
            break; 
    } 
    if (strpiped[1] == NULL) 
        return 0; // returns zero if no pipe is found. 
    else { 
        return 1; 
    } 
} 

// function for spliting commands by space 
void splitCommand(char* str, char** parsed) 
{ 
    int i; 
    for (i = 0; i < MAX_BUFFER_SIZE; i++) { 
        parsed[i] = strsep(&str, " "); 
        if (parsed[i] == NULL) 
            break; 
        if (strlen(parsed[i]) == 0) 
            i--; 
    } 
} 


// Function where the system command is executed 
void executeCommand(char** parsed) 
{ 
    // Forking a child 
    pid_t pid = fork();  
  
    if (pid == -1) { 
        printf("\nFailed forking child.."); 
        return; 
    } else if (pid == 0) { 
	signal(SIGINT, SIG_DFL);
        if (execvp(parsed[0], parsed) < 0) { 
            printf("\nCommand not found--Did you mean something else?.\n"); 
        }
	//printf("Child: Should never get here\n"); 
        exit(0); 
    } else { 
        // waiting for child to terminate 
        wait(NULL);  
        return; 
    } 
}


void executePipeCommand(char** parsed, char** parsedpipe) {
    int pipefd[2];  
    pid_t p1, p2; 
  
    if (pipe(pipefd) < 0) { 
        printf("\nPipe could not be initialized"); 
        return; 
    } 
    p1 = fork(); 
    if (p1 < 0) { 
        printf("\nCould not fork"); 
        return; 
    } 
  
    if (p1 == 0) { 
	signal(SIGINT, SIG_DFL);
        // Child 1 executing.. 
        // It only needs to write at the write end 
        dup2(pipefd[1], STDOUT_FILENO); 
        close(pipefd[0]); 
        close(pipefd[1]); 
  
        if (execvp(parsed[0], parsed) < 0) { 
            printf("\nCommand not found--Did you mean something else?"); 
        } 
        exit(0); 
    } else { 
        // Parent executing 
        p2 = fork(); 
  
        if (p2 < 0) { 
            printf("\nCould not fork"); 
            return; 
        } 
        // Child 2 executing.. 
        if (p2 == 0) {
	    signal(SIGINT, SIG_DFL); 
            dup2(pipefd[0], STDIN_FILENO); 
            close(pipefd[1]); 
            close(pipefd[0]); 
            if (execvp(parsedpipe[0], parsedpipe) < 0) { 
                printf("\nCommand not found--Did you mean something else?"); 
            } 
            exit(0); 
        } else { 
            // parent executing, waiting for two children 
            close(pipefd[0]);
	    close(pipefd[1]);
            wait(NULL); 
            wait(NULL); 
        } 
    }
}

int input_handler(char* str, char** parsed, char** parsedpipe) 
{ 
    char* strpiped[2]; 
    int piped = 0; 

    piped = isPipe(str, strpiped); 
  
    if (piped) { 
        splitCommand(strpiped[0], parsed); 
        splitCommand(strpiped[1], parsedpipe); 
    } else { 
        splitCommand(str, parsed); 
    } 
     
    int i; 
    for (i = 0; i < count_builtins(); i++) {
	if (strcmp(parsed[0], builtin_str[i]) == 0) {
            // return 0 means exit, 1 means cd or help 
            return (*builtin_func[i])(parsed); 
        } 
    }
    // return 2 means no pipe, 3 means having pipe.
    return piped + 2; 
} 

int main() {	
	// A buffer to hold 80 characters at most
	char inputString[MAX_BUFFER_SIZE];
	char* parsedArgs[MAX_BUFFER_SIZE];
	char* parsedArgsPiped[MAX_BUFFER_SIZE];
	int status;
	char* tempstring;
        
	signal(SIGINT, sigint_handler);
	 // A loop that runs forever.
	do {
    		printf("mini-shell> ");
    		fflush(stdout);
	    	// Read in 1 line of text
	    	// The line is coming from 'stdin' standard input
		fgets(inputString, MAX_BUFFER_SIZE, stdin);
		if (inputString[strlen(inputString)-1] == '\n')
			inputString[strlen(inputString)-1] = '\0'; 
		if (inputString[0] == '\0') {
		        status = 1;	
			continue;
                } else {
			tempstring = add_to_history(inputString);
                }
		int input_status = input_handler(inputString,
					parsedArgs, parsedArgsPiped);	
		if (input_status == 2) {
			executeCommand(parsedArgs);
		}
		if (input_status == 3) {
			executePipeCommand(parsedArgs, parsedArgsPiped);	
		}	
		status = input_status;
	} while (status);

	free(tempstring);
	return 0;
}
