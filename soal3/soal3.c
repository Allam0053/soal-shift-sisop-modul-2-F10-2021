#include <stdio.h>
#include <time.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <stdlib.h>
#include <unistd.h>
#include <curl/curl.h>
#include <string.h>

void get_timestamp(char time_stamp[]);

int main() {
  pid_t pid = fork();

  if (pid < 0) exit(EXIT_FAILURE);
  if (pid > 0) exit(EXIT_SUCCESS);

  /* Below here is child process */

  umask(0);
  pid_t sid = setsid();

  if (sid < 0) exit(EXIT_FAILURE);
  if (chdir("/Users/riza/Documents/A-Kuliah/6-Sistem-Operasi/Praktikum/soal-shift-sisop-modul-2-F10-2021/soal3") < 0) exit(EXIT_FAILURE);

  close(STDIN_FILENO);
  close(STDOUT_FILENO);
  close(STDERR_FILENO);
  
  while (1) {
    pid_t pid_in_daemon = fork();

    if (pid_in_daemon != 0) {
      char time_stamp[20] = "";
      get_timestamp(time_stamp);
      char* argv[] = { "mkdir", "-p", time_stamp };
      execv("/bin/mkdir", argv);
    }

    sleep(40);
  }
  
  return 0;
}

void get_timestamp(char time_stamp[]) {
  time_t rawtime = time(NULL);
  if (rawtime == -1) return;

  struct tm* ptm = localtime(&rawtime);
  if (!ptm) return;

  char temp[5];

  sprintf(temp, "%4d", 1900 + ptm->tm_year);
  strcat(time_stamp, temp);
  strcat(time_stamp, "-");


  sprintf(temp, "%02d", 1 + ptm->tm_mon);
  strcat(time_stamp, temp);
  strcat(time_stamp, "-");

  sprintf(temp, "%02d", ptm->tm_mday);
  strcat(time_stamp, temp);
  strcat(time_stamp, "_");


  sprintf(temp, "%02d", ptm->tm_hour);
  strcat(time_stamp, temp);
  strcat(time_stamp, ":");

  sprintf(temp, "%02d", ptm->tm_min);
  strcat(time_stamp, temp);
  strcat(time_stamp, ":");

  sprintf(temp, "%02d", ptm->tm_sec);
  strcat(time_stamp, temp);
}