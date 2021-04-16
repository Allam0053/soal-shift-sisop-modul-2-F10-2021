#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <string.h>
#include <syslog.h>
#include <unistd.h>
#include <errno.h>
#include <fcntl.h>
#include <time.h>
#include <wait.h>

int main()
{
  
  /*time_t rawtime = time(NULL);
  struct tm timeinfo = *localtime(&rawtime);
  int i = 0;
  while(i < 100)
  {
  	timeinfo = *localtime(&rawtime);
  	printf ( "%d\n", timeinfo.tm_sec);
  	i++;
  }*/
  
  pid_t sid, sid1;
  int status;
  
  sid = fork();
  if(sid < 0)
    exit(EXIT_FAILURE);
  if(sid > 0)
    exit(EXIT_SUCCESS);
  
  umask(0);
  sid1 = setsid();
  if(sid1 < 0)
    exit(EXIT_FAILURE);
  if(chdir("/home/dewanggad99") < 0)
    exit(EXIT_FAILURE);
  
  close(STDIN_FILENO);
  close(STDOUT_FILENO);
  close(STDERR_FILENO);
  
  while(1){
    //fill the rest here
    //Jam 4 sore
    time_t rawtime = time(NULL);
  struct tm timeinfo = *localtime(&rawtime);
    
    if(timeinfo.tm_mday == 9 && timeinfo.tm_mon + 1 == 4 && timeinfo.tm_hour == 16 && timeinfo.tm_min == 22)
    {
      //Buat jam 4
      //Mungkin dikomen bagian EXIT_FAILURE-nya
  pid_t pid = fork();
  if(pid < 0)
    exit(EXIT_FAILURE);
  if(pid == 0){
    char *arg1[] = {"wget", "--no-check-certificate", "https://drive.google.com/uc?id=1FsrAzb9B5ixooGUs0dGiBr-rC7TS9wTD&export=download", "-O", "Foto.zip", NULL};
//https://drive.google.com/file/d/1FsrAzb9B5ixooGUs0dGiBr-rC7TS9wTD/
    execv("/bin/wget", arg1);
  }
  
  while(wait(NULL) > 0);
  pid = fork();
  if(pid < 0)
    exit(EXIT_FAILURE);
  if(pid == 0){
    char *arg2[] = {"wget", "--no-check-certificate", "https://drive.google.com/uc?id=1ZG8nRBRPquhYXq_sISdsVcXx5VdEgi-J&export=download", "-O", "Musik.zip", NULL};
//https://drive.google.com/file/d/1FsrAzb9B5ixooGUs0dGiBr-rC7TS9wTD/
    //https://drive.google.com/file/d/1ZG8nRBRPquhYXq_sISdsVcXx5VdEgi-J/view
    execv("/bin/wget", arg2);
  }
  
  while(wait(NULL) > 0);
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
while(wait(NULL) > 0);
  pid = fork();
  if(pid < 0)
    exit(EXIT_FAILURE);
  if(pid == 0){
    char *arg4[] = {"unzip", "Foto.zip", NULL};
    execv("/bin/unzip", arg4);
  }
 while(wait(NULL) > 0);
  pid = fork();
  if(pid < 0)
    exit(EXIT_FAILURE);
  if(pid == 0){
    char *arg5[] = {"unzip", "Musik.zip", NULL};
    execv("/bin/unzip", arg5);
  }
 while(wait(NULL) > 0);
  pid = fork();
  if(pid < 0)
    exit(EXIT_FAILURE);
  if(pid == 0){
    char *arg6[] = {"unzip", "Film.zip", NULL};
    execv("/bin/unzip", arg6);
  }
 
  while(wait(NULL) > 0);
  pid = fork();
  if(pid < 0)
    exit(EXIT_FAILURE);
  if(pid == 0){
    char *arg7[] = {"mv", "/home/dewanggad99/FOTO", "/home/dewanggad99/Pyoto", NULL};
    execv("/bin/mv", arg7);
  }
  while(wait(NULL) > 0);
  pid = fork();
  if(pid < 0)
    exit(EXIT_FAILURE);
  if(pid == 0){
    char *arg8[] = {"mv", "/home/dewanggad99/MUSIK", "/home/dewanggad99/Myusik", NULL};
    execv("/bin/mv", arg8);
  }
  while(wait(NULL) > 0);
  pid = fork();
  if(pid < 0)
    exit(EXIT_FAILURE);
  if(pid == 0){
    char *arg9[] = {"mv", "/home/dewanggad99/FILM", "/home/dewanggad99/Fylm", NULL};
    execv("/bin/mv", arg9);
  }
  //Akhir jam 4 sore
    }
    
  
    
    else if(timeinfo.tm_mday == 9 && timeinfo.tm_mon + 1 == 4 && timeinfo.tm_hour == 22 && timeinfo.tm_min == 22)
    {
      //Buat jam 10
      //Jam 10
  pid_t pid = fork();
  if(pid < 0)
    exit(EXIT_FAILURE);
  if(pid == 0){
    char *arg10[] = {"zip", "-r", "Lopyu_Stevany.zip", "/home/dewanggad99/Pyoto", "/home/dewanggad99/Myusik", "/home/dewanggad99/Fylm", NULL};
    execv("/bin/zip", arg10);
  }
  while(wait(NULL) > 0);
  pid = fork();
  if(pid < 0)
    exit(EXIT_FAILURE);
  if(pid == 0){
    char *arg11[] = {"rm", "-r", "/home/dewanggad99/Pyoto", "/home/dewanggad99/Myusik", "/home/dewanggad99/Fylm", NULL};
    execv("/bin/rm", arg11);
  }
    }
    
  
    sleep(1);
  }
  
  
}
