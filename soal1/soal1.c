#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <string.h>
#include <syslog.h>
#include <unistd.h>
#include <errno.h>
#include <fcntl.h>

int main()
{
  pid_t pid, sid;
  pid = fork();
  if(pid < 0)
    exit(EXIT_FAILURE);
  if(pid == 0){
    char *arg1[] = {"wget", "--no-check-certificate", "https://drive.google.com/uc?id=1FsrAzb9B5ixooGUs0dGiBr-rC7TS9wTD&export=download", "-O", "Foto.zip", NULL};
//https://drive.google.com/file/d/1FsrAzb9B5ixooGUs0dGiBr-rC7TS9wTD/
    execv("/bin/wget", arg1);
  }
  
  while((wait(&status)) > 0);
  pid = fork();
  if(pid < 0)
    exit(EXIT_FAILURE);
  if(pid == 0){
    char *arg2[] = {"wget", "--no-check-certificate", "https://drive.google.com/uc?id=1ZG8nRBRPquhYXq_sISdsVcXx5VdEgi-J&export=download", "-O", "Musik.zip", NULL};
//https://drive.google.com/file/d/1FsrAzb9B5ixooGUs0dGiBr-rC7TS9wTD/
    //https://drive.google.com/file/d/1ZG8nRBRPquhYXq_sISdsVcXx5VdEgi-J/view
    execv("/bin/wget", arg2);
  }
  
  while((wait(&status)) > 0);
  pid = fork();
  if(pid < 0)
    exit(EXIT_FAILURE);
  if(pid == 0){
    char *arg3[] = {"wget", "--no-check-certificate", "https://drive.google.com/uc?id=1ktjGgDkL0nNpY-vT7rT7O6ZI47Ke9xcp&export=download", "-O", "Film.zip", NULL};
//https://drive.google.com/file/d/1FsrAzb9B5ixooGUs0dGiBr-rC7TS9wTD/
    //https://drive.google.com/file/d/1ZG8nRBRPquhYXq_sISdsVcXx5VdEgi-J/view
    //https://drive.google.com/file/d/1ktjGgDkL0nNpY-vT7rT7O6ZI47Ke9xcp/view
    execv("/bin/wget", arg3);
  }

}
