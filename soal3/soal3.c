#include <stdio.h>
#include <time.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

long get_timestamp(char time_stamp[]);

int main() {
  pid_t pid = fork();

  if (pid < 0) exit(EXIT_FAILURE);
  if (pid > 0) exit(EXIT_SUCCESS);

  /* Below here is child (daemon) process */

  umask(0);
  pid_t sid = setsid();

  if (sid < 0) exit(EXIT_FAILURE);
  if (chdir("/Users/riza/Documents/A-Kuliah/6-Sistem-Operasi/Praktikum/soal-shift-sisop-modul-2-F10-2021/soal3") < 0) exit(EXIT_FAILURE);

  close(STDIN_FILENO);
  close(STDOUT_FILENO);
  close(STDERR_FILENO);
  
  while (1) {
    pid_t pid_create_dir = fork();
    char dir_timestamp[20];
    get_timestamp(dir_timestamp);

    if (pid_create_dir == 0) {
      char* argv[] = { "mkdir", "-p", dir_timestamp, NULL };
      execv("/bin/mkdir", argv);
    }

    while (wait(NULL) > 0);

    /* Pembuatan folder telah selesai */

    pid_t pid_download_pictures = fork();

    if (pid_download_pictures == 0) {
      int downloaded_pictures = 0;

      while (downloaded_pictures++ < 10) {
        pid_t pid_for_download = fork();

        if (pid_for_download == 0) {
          char pic_timestamp[20];
          int time = (int) get_timestamp(pic_timestamp);
          int size = 50 + (time % 1000);
          char pic_path_dest[100];
          char url[27];

          strcat(pic_path_dest, dir_timestamp);
          strcat(pic_path_dest, "/");
          strcat(pic_path_dest, pic_timestamp);
          strcat(pic_path_dest, ".jpg");

          sprintf(url, "https://picsum.photos/%d", size);

          char* argv[] = { "wget", "-O", pic_path_dest, url };
          // ! Path wget harus diubah
          execv("/usr/local/bin/wget", argv);
        }

        sleep(5);
      }

    }

    /* Dibawah sini gak boleh ada wait (kalo ada wait, berarti dia nunggu si download. jadinya 90 detik) */

    sleep(40);
  }
  
  return 0;
}

long get_timestamp(char time_stamp[]) {
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

  return rawtime;
}