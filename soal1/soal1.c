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
  if(chdir("/home/allam") < 0)
    exit(EXIT_FAILURE);
  
  close(STDIN_FILENO);
  close(STDOUT_FILENO);
  close(STDERR_FILENO);
  
  char foto1[] = "https://drive.google.com/uc?id=1FsrAzb9B5ixooGUs0dGiBr-rC7TS9wTD&export=download";
  char musik1[] = "https://drive.google.com/uc?id=1ZG8nRBRPquhYXq_sISdsVcXx5VdEgi-J&export=download";
  char film1[] = "https://drive.google.com/uc?id=1ktjGgDkL0nNpY-vT7rT7O6ZI47Ke9xcp&export=download";
  
  char fotozip[] = "Foto.zip";
  char musikzip[] = "Musik.zip";
  char filmzip[] = "Film.zip";
  
  while(1){
    //fill the rest here
    //Jam 4 sore
    time_t rawtime = time(NULL);
    struct tm timeinfo = *localtime(&rawtime);
    
    if(timeinfo.tm_mday == 17 && timeinfo.tm_mon + 1 == 4 && timeinfo.tm_hour == 20 && timeinfo.tm_min == 47)
    {
      pid_t pid = fork();
      if (pid < 0) exit(EXIT_FAILURE);
      if (pid == 0) {
          char *arg1[] = {"wget", "--no-check-certificate", foto1, "-O", fotozip, NULL};
          //https://drive.google.com/file/d/1FsrAzb9B5ixooGUs0dGiBr-rC7TS9wTD/
          execv("/bin/wget", arg1);
      }

      while(wait(NULL) > 0);
      pid = fork();
      if (pid < 0) exit(EXIT_FAILURE);
      if (pid == 0) {
      char *arg2[] = {"wget", "--no-check-certificate", musik1, "-O", musikzip, NULL};
          //https://drive.google.com/file/d/1FsrAzb9B5ixooGUs0dGiBr-rC7TS9wTD/
          //https://drive.google.com/file/d/1ZG8nRBRPquhYXq_sISdsVcXx5VdEgi-J/view
          execv("/bin/wget", arg2);
      }

      while(wait(NULL) > 0);
      pid = fork();
      if (pid < 0) exit(EXIT_FAILURE);
      if (pid == 0) {
          char *arg3[] = {"wget", "--no-check-certificate", film1, "-O", filmzip, NULL};
          //https://drive.google.com/file/d/1FsrAzb9B5ixooGUs0dGiBr-rC7TS9wTD/
          //https://drive.google.com/file/d/1ZG8nRBRPquhYXq_sISdsVcXx5VdEgi-J/view
          //https://drive.google.com/file/d/1ktjGgDkL0nNpY-vT7rT7O6ZI47Ke9xcp/view
          execv("/bin/wget", arg3);
      }

      while(wait(NULL) > 0);
      pid = fork();
      if (pid < 0) exit(EXIT_FAILURE);
      if (pid == 0) {
          char *arg4[] = {"unzip", fotozip, NULL};
          execv("/bin/unzip", arg4);
      }

      while(wait(NULL) > 0);
      pid = fork();
      if (pid < 0) exit(EXIT_FAILURE);
      if (pid == 0) {
          char *arg5[] = {"unzip", musikzip, NULL};
          execv("/bin/unzip", arg5);
      }

      while(wait(NULL) > 0);
      pid = fork();
      if (pid < 0) exit(EXIT_FAILURE);
      if (pid == 0) {
          char *arg6[] = {"unzip", filmzip, NULL};
          execv("/bin/unzip", arg6);
      }

      while(wait(NULL) > 0);
      pid = fork();
      if(pid < 0) exit(EXIT_FAILURE);
      if(pid == 0){
          char *arg7[] = {"mv", "FOTO", "Pyoto", NULL};
          execv("/bin/mv", arg7);
      }

      while(wait(NULL) > 0);
      pid = fork();
      if (pid < 0) exit(EXIT_FAILURE);
      if (pid == 0) {
          char *arg8[] = {"mv", "MUSIK", "Myusik", NULL};
          execv("/bin/mv", arg8);
      }

      while(wait(NULL) > 0);
      pid = fork();
      if (pid < 0) exit(EXIT_FAILURE);
      if (pid == 0) {
          char *arg9[] = {"mv", "FILM", "Fylm", NULL};
          execv("/bin/mv", arg9);
      }

      //Akhir jam 4 sore
    }
    
  
    
    else if(timeinfo.tm_mday == 17 && timeinfo.tm_mon + 1 == 4 && timeinfo.tm_hour == 20 && timeinfo.tm_min == 48)
    {
      //Buat jam 10
      //Jam 10
      while(wait(NULL) > 0);
      pid_t pid = fork();
      if (pid < 0) exit(EXIT_FAILURE);
      if (pid == 0) {
          char *arg10[] = {"zip", "-r", "Lopyu_Stevany.zip", "Pyoto", "Myusik", "Fylm", NULL};
          execv("/bin/zip", arg10);
      }

      while(wait(NULL) > 0);
      pid = fork();
      if (pid < 0) exit(EXIT_FAILURE);
      if (pid == 0) {
          char *arg11[] = {"rm", "-r", "Pyoto", "Myusik", "Fylm", NULL};
          execv("/bin/rm", arg11);
      }
    }
    
  
    sleep(1);
  }
  
  
}
