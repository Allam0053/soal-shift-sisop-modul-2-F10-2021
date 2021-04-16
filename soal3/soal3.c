#include <stdio.h>
#include <time.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <ctype.h>

long get_timestamp(char time_stamp[]);
void caesar_encrypt(char str[]);

int main() {
  pid_t pid = fork();

  if (pid < 0) exit(EXIT_FAILURE);
  if (pid > 0) exit(EXIT_SUCCESS);

  /* Below here is child (daemon) process */

  umask(0);
  pid_t sid = setsid();

  // ! chdir() harus dihapus
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
      // ? Apakah perlu copy timestamp ?
      int downloaded_pictures = 0;
      char this_timestamp[20];
      strcpy(this_timestamp, dir_timestamp);

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

          // ! Path wget harus diubah
          char* argv[] = { "wget", "-O", pic_path_dest, url, NULL };
          execv("/usr/local/bin/wget", argv);
        }

        sleep(5);
      }

      /* Abis download => buat status.txt & zip si folder & hapus folder */

      // Buat status.txt + isi pesan
      char message[20] = "Download Success";
      caesar_encrypt(message);

      char file_message_name[100] = "./";
      strcat(file_message_name, dir_timestamp);
      strcat(file_message_name, "/status.txt");

      FILE* fp = fopen(file_message_name, "w+");
      fputs(message, fp);
      fclose(fp);

      // zip si folder
      pid_t pid_for_zip = fork();

      if (pid_for_zip == 0) {
        char zip_name[50];
        strcat(zip_name, dir_timestamp);
        strcat(zip_name, ".zip");

        char* argv[] = { "zip", "-r", zip_name, dir_timestamp, NULL };
        execv("/usr/bin/zip", argv);
      }

      // ? Apakah perlu wait untuk zip folder ?
      while(wait(NULL) > 0);

      // remove folder
      char* argv[] = { "rm", "-r", dir_timestamp, NULL };
      execv("/bin/rm", argv);
      // exit(EXIT_SUCCESS);
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

void caesar_encrypt(char str[]) {
  const int SHIFT = 5;
  for (int i = 0; i < strlen(str); i++) {
    if (!isalpha(str[i])) continue;
    if (isupper(str[i])) str[i] = (str[i] + SHIFT - 65) % 26 + 65;
    else str[i] = (str[i] + SHIFT - 97) % 26 + 97;
  }
}