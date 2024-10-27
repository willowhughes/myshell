/* CS 347 -- Mini Shell!
 * Original author Phil Nelson 2000
 */
#include <assert.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <errno.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <ctype.h>
#include "argparse.h"
#include "builtin.h"


/* PROTOTYPES */

void processline (char *line);
ssize_t getinput(char** line, size_t* size);


/*
* main
*
* Main entry point of the myshell program.
* This is essentially the primary read-eval-print loop of the command interpreter.
*
* Runs the shell in an endless loop until an exit command is issued.
*
* Hint: Use getinput and processline as appropriate.
*/
int main () {

 //write your code

  return EXIT_SUCCESS;
}


/*
* getinput
*
* Prompts the user for a line of input (e.g. %myshell%) and stores it in a dynamically
* allocated buffer (pointed to by *line).
* If input fits in the buffer, it is stored in *line.
* If the buffer is too small, *line is freed and a larger buffer is allocated.
* The size of the buffer is stored in *size.
*
* Args:
*   line: pointer to a char* that will be set to the address of the input buffer
*   size: pointer to a size_t that will be set to the size of the buffer *line or 0 if *line is NULL.
*
* Returns:
*   The length of the the string stored in *line.
*
* Hint: There is a standard i/o function that can make getinput easier than it sounds.
*/
ssize_t getinput(char** line, size_t* size) {

  ssize_t len = 0;


  //write your code

  return len;
}


/*
* processline
*
* Interprets the input line as a command and either executes it as a built-in
* or forks a child process to execute an external program.
* Built-in commands are executed immediately.
* External commands are parsed then forked to be executed.
*
* Args:
*   line: string containing a shell command and arguments
*
* Note: There are three cases to consider when forking a child process:
*   1. Fork fails
*   2. Fork succeeds and this is the child process
*   3. Fork succeeds and this is the parent process
*
* Hint: See the man page for fork(2) for more information.
* Hint: The process should only fork when the line is not empty and not trying to
*       run a built-in command.
*/
void processline (char *line)
{
 /*check whether line is empty*/
  //write your code

  pid_t cpid;
  int   status;
  int argCount;
  char** arguments = argparse(line, &argCount);

  /*check whether arguments are builtin commands
   *if not builtin, fork to execute the command.
   */
    //write your code
}
