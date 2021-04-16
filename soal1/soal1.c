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
  
  //Jam 4 sore
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
while((wait(&status)) > 0);
  pid = fork();
  if(pid < 0)
    exit(EXIT_FAILURE);
  if(pid == 0){
    char *arg4[] = {"unzip", "Foto.zip", NULL};
    execv("/bin/unzip", arg4);
  }
 while((wait(&status)) > 0);
  pid = fork();
  if(pid < 0)
    exit(EXIT_FAILURE);
  if(pid == 0){
    char *arg5[] = {"unzip", "Musik.zip", NULL};
    execv("/bin/unzip", arg5);
  }
 while((wait(&status)) > 0);
  pid = fork();
  if(pid < 0)
    exit(EXIT_FAILURE);
  if(pid == 0){
    char *arg6[] = {"unzip", "Film.zip", NULL};
    execv("/bin/unzip", arg6);
  }
 
  while((wait(&status)) > 0);
  pid = fork();
  if(pid < 0)
    exit(EXIT_FAILURE);
  if(pid == 0){
    char *arg7[] = {"mv", "/home/dewangga99/FOTO", "/home/dewangga99/Pyoto", NULL};
    execv("/bin/mv", arg7);
  }
  while((wait(&status)) > 0);
  pid = fork();
  if(pid < 0)
    exit(EXIT_FAILURE);
  if(pid == 0){
    char *arg8[] = {"mv", "/home/dewangga99/MUSIK", "/home/dewangga99/Myusik", NULL};
    execv("/bin/mv", arg8);
  }
  while((wait(&status)) > 0);
  pid = fork();
  if(pid < 0)
    exit(EXIT_FAILURE);
  if(pid == 0){
    char *arg9[] = {"mv", "/home/dewangga99/FILM", "/home/dewangga99/Fylm", NULL};
    execv("/bin/mv", arg9);
  }
  //Akhir jam 4 sore
  
  //Jam 10
  while((wait(&status)) > 0);
  pid = fork();
  if(pid < 0)
    exit(EXIT_FAILURE);
  if(pid == 0){
    char *arg10[] = {"zip", "-r", "Lopyu_Stevany.zip", "/home/dewangga99/Pyoto", "/home/dewangga99/Myusik", "/home/dewangga99/Fylm", NULL};
    execv("/bin/zip", arg10);
  }
  while((wait(&status)) > 0);
  pid = fork();
  if(pid < 0)
    exit(EXIT_FAILURE);
  if(pid == 0){
    char *arg11[] = {"rm", "-r", "/home/dewangga99/Pyoto", "/home/dewangga99/Myusik", "/home/dewangga99/Fylm", NULL};
    execv("/bin/rm", arg11);
  }
}
