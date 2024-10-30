#include <assert.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <errno.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/stat.h>
#include <pwd.h>
#include <grp.h>
#include <time.h>
#include <fcntl.h>
#include <ctype.h>
#include "builtin.h"
#include <string.h>
#include <dirent.h>

#define MAX_PATH_LENGTH 128

//Prototypes
static void exitProgram(char** args, int argcp);
static void cd(char** args, int argpcp);
static void pwd(char** args, int argcp);

//Group A
static void cmdA_ls(char** args, int argc);
static void cmdA_cp(char** args, int argc);
static void cmdA_env(char** args, int argc);

//Group B
static void cmdB_stat(char** args, int argc);
static void cmdB_tail(char** args, int argc);
static void cmdB_touch(char** args, int argc);


/*
* builtIn
*
* Checks if a command is a built-in shell command and executes it if so.
*
* Args:
*   args: array of strings containing command and arguments
*   argcp: number of elements in args array
*
* Returns:
*   1 if the command was a built-in, 0 otherwise.
*
* Built-in commands are executed directly by the shell process rather than
* being forked to a new process. This function compares the given command
* to each of the built-ins (exit, pwd, cd, and ls/cp/env or stat/tail/touch
* depending on group). If a match is found, the corresponding function is called.
*
* Hint: Refer to checklist for group specific examples
*/
int builtIn(char** args, int argcp)
{
  pwd(args, argcp);
  //cd(args, argcp);
  pwd(args, argcp);

  cmdB_stat(args, argcp);

  exitProgram(args, argcp);

  return 1;
}

static void cmdB_stat(char** args, int argc)
{
  struct stat file_info;
  char *filepath = "argparse.c";
  
  if (stat(filepath, &file_info) == -1) {
    perror("stat");
    return;
  }

  // Print the file's metadata
  printf("\nFile Name: %s\n", filepath);
  printf("Size: %lld\t", (long long)file_info.st_size);
  printf("Blocks: %lld\t", (long long)file_info.st_blocks);
  printf("IO Block: %ld ", (long)file_info.st_blksize);

  if (S_ISREG(file_info.st_mode)) {
    printf("regular file\n");
  } else if (S_ISDIR(file_info.st_mode)) {
    printf("directory\n");
  } else if (S_ISLNK(file_info.st_mode)) {
    printf("symbolic link\n");
  } else {
    printf("other\n");
  }

  printf("Device: %lx\tInode: %lu\t", (unsigned long)file_info.st_dev, (unsigned long)file_info.st_ino);
  printf("Links: %ld\n", (long)file_info.st_nlink);

  int mode = file_info.st_mode & 0777; // Mask to get the permission bits
  printf("Permissions: (%03o/", mode); // Print numeric permissions
    
  printf("%c", (file_info.st_mode & S_IFDIR) ? 'd' : '-');
  printf("%c", (file_info.st_mode & S_IRUSR) ? 'r' : '-');
  printf("%c", (file_info.st_mode & S_IWUSR) ? 'w' : '-');
  printf("%c", (file_info.st_mode & S_IXUSR) ? 'x' : '-');
  printf("%c", (file_info.st_mode & S_IRGRP) ? 'r' : '-');
  printf("%c", (file_info.st_mode & S_IWGRP) ? 'w' : '-');
  printf("%c", (file_info.st_mode & S_IXGRP) ? 'x' : '-');
  printf("%c", (file_info.st_mode & S_IROTH) ? 'r' : '-');
  printf("%c", (file_info.st_mode & S_IWOTH) ? 'w' : '-');
  printf("%c", (file_info.st_mode & S_IXOTH) ? 'x' : '-');
  printf(")\t");

  struct passwd *pw = getpwuid(file_info.st_uid); // Get the passwd struct for the UID
  if (pw != NULL) {
    printf("UID: (%d, %s)\t", file_info.st_uid, pw->pw_name); // Print UID and username
  }

  struct group *gr = getgrgid(file_info.st_gid); // Get the group struct for the GID
  // Print GID in the desired format
  if (gr != NULL) {
    printf("GID: (%d, %s)\n", file_info.st_gid, gr->gr_name); // Print GID and group name
  }


  // Print timestamps
  // char atime[20], mtime[20], ctime[20];
  // strftime(atime, sizeof(atime), "%Y-%m-%d %H:%M:%S", localtime(&file_info.st_atime));
  // strftime(mtime, sizeof(mtime), "%Y-%m-%d %H:%M:%S", localtime(&file_info.st_mtime));
  // strftime(ctime, sizeof(ctime), "%Y-%m-%d %H:%M:%S", localtime(&file_info.st_ctime));
  
  // printf("Access: %s\n", atime);
  // printf("Modify: %s\n", mtime);
  // printf("Change: %s\n", ctime);
}

/*
* exitProgram
*
* Terminates the shell with a given exit status.
* If no exit status is provided, exits with status 0.
* This function should use the exit(3) library call.
*
* Args:
*   args: array of strings containing "exit" and optionally an exit status
*   argcp: number of elements in args array
*/
static void exitProgram(char** args, int argcp)
{
  int code = 0;
  printf("Goodbye\n");
  exit(code);
}

/*
* pwd
*
* Prints the current working directory.
*
* Args:
*   args: array of strings containing "pwd"
*   argcp: number of elements in args array, should be 1
*
* Example Usage:
*   Command: $ pwd
*   Output: /some/path/to/directory
*/
static void pwd(char** args, int argpc)
{
  char cwd[MAX_PATH_LENGTH];

    if (getcwd(cwd, sizeof(cwd)) == NULL) {
        perror("getcwd() error");
        return;
    }

    printf("%s\n", cwd);
}

/*
* cd
*
* Changes the current working directory.
* When no parameters are provided, changes to the home directory.
* Supports . (current directory) and .. (parent directory).
*
* Args:
*   args: array of strings containing "cd" and optionally a directory path
*   argcp: number of elements in args array
*
* Example Usage:
*   Command: $ pwd
*   Output: /some/path/to/directory
*   Command: $ cd ..
*   Command: $ pwd
*   Output: /some/path/to
*
* Hint: Read the man page for chdir(2)
*/
static void cd(char** args, int argcp)
{
  char *path = "..";

  if (chdir(path) != 0) {
    perror("chdir() error");
    return;
  }
}
