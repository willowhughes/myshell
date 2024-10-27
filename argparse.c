#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include "argparse.h"
#include <string.h>
#include <sys/types.h>
#include <unistd.h>
#include <sys/wait.h>
#include <errno.h>

#define FALSE (0)
#define TRUE  (1)

/*
* argCount
*
* Counts the number of arguments in a given input line.
* You may assume only whitespace is used to separate arguments.
* argCount should be able to handle multiple whitespaces between arguments.
*
* Args:
*   line: intput string containing command and arguments separated by whitespaces
*
* Returns:
*   The number of arguments in line.
*   (The command itself counts as the first argument)
*
* Example:
*   argCount("ls -l /home") returns 3
*   argCount("   ls    -l   /home  ") returns 3
*/
static int argCount(char*line)
{
 //write your code
}



/*
* argparse
*
* Parses an input line into an array of strings.
* 
*
* You may assume only whitespace is used to separate strings.
* argparse should be able to handle multiple whitespaces between strings.
* The function should dynamically allocate space for the array of strings,
* following the project requirements. 
*
* Args:
*   line: input string containing words separated by whitespace
*   argcp: stores the number of strings in the line
*
* Returns:
*   An array of strings.
*
* Example:
*   argparse("ls -l /home", &argc) --> returns ["ls", "-l", "/home", NULL] and set argc to 3
*   argparse("   ls    -l   /home  ", &argc) --> returns ["ls", "-l", "/home", NULL] and set argc to 3
*/
char** argparse(char* line, int* argcp)
{
  //write your code
}
