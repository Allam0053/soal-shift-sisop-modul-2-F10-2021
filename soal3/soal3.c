#include <sys/stat.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <signal.h>
#include <time.h>
#include <unistd.h>

int signal_proccess = 1;

long get_timestamp(char time_stamp[]);
void caesar_encrypt(char str[]);
void create_kill_file(char mode);
void request_create_kill_file(char* args[]);
void stop_process();

int main(int argc, char* args[]) {
  if (argc == 2) request_create_kill_file(args);

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
  
  while (signal_proccess) {
    const int THIS_PROCESS = 0;
    const int PROCCESSING = 0;

    pid_t pid_create_dir = fork();

    char dir_timestamp[20] = "";
    get_timestamp(dir_timestamp);

    if (THIS_PROCESS == pid_create_dir) {
      char* argv[] = { "mkdir", "-p", dir_timestamp, NULL };
      execv("/bin/mkdir", argv);
    }

    while(waitpid(pid_create_dir, NULL, WNOHANG | WUNTRACED) == PROCCESSING);

    /* Pembuatan folder telah selesai */

    pid_t pid_download_pictures = fork();

    if (THIS_PROCESS != pid_download_pictures) {
      sleep(40);
      continue;
    }

    int downloaded_pictures = 0;

    while (downloaded_pictures++ < 10) {
      pid_t pid_for_download = fork();

      if (THIS_PROCESS == pid_for_download) {
        char pic_timestamp[20] = "";
        int time = (int) get_timestamp(pic_timestamp);
        int size = 50 + (time % 1000);
        char pic_path_dest[100] = "";
        char url[27];

        strcat(pic_path_dest, dir_timestamp);
        strcat(pic_path_dest, "/");
        strcat(pic_path_dest, pic_timestamp);
        strcat(pic_path_dest, ".jpg");

        sprintf(url, "https://picsum.photos/%d", size);

        // ! Path wget harus diubah
        char* argv[] = { "wget", "-q", "-O", pic_path_dest, url, NULL };
        execv("/usr/local/bin/wget", argv);
      }

      if (downloaded_pictures == 10) break;
      sleep(5);
    }

    /* Abis download => buat status.txt & zip si folder & remove folder */

    // Buat status.txt + isi pesan
    char message[20] = "Download Success";
    caesar_encrypt(message);

    char file_message_name[100] = "./";
    strcat(file_message_name, dir_timestamp);
    strcat(file_message_name, "/status.txt");

    FILE* fp = fopen(file_message_name, "w+");
    fputs(message, fp);
    fclose(fp);

    // Zip si folder
    pid_t pid_for_zip = fork();

    if (THIS_PROCESS == pid_for_zip) {
      char zip_name[50];
      strcat(zip_name, dir_timestamp);
      strcat(zip_name, ".zip");

      char* argv[] = { "zip", "-qq", "-r", zip_name, dir_timestamp, NULL };
      execv("/usr/bin/zip", argv);
    }

    while(waitpid(pid_for_zip, NULL, WNOHANG | WUNTRACED) == PROCCESSING);

    // Remove folder setelah zip
    char* argv[] = { "rm", "-r", dir_timestamp, NULL };
    execv("/bin/rm", argv);
  }
  
  return 0;
}

long get_timestamp(char time_stamp[]) {
  time_t epochtime = time(NULL);
  if (epochtime == -1) return -1;

  struct tm* ptm = localtime(&epochtime);
  if (!ptm) return -1;

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

  return epochtime;
}

void caesar_encrypt(char str[]) {
  const int SHIFT = 5;
  for (int i = 0; i < strlen(str); i++) {
    if (!isalpha(str[i])) continue;
    if (isupper(str[i])) str[i] = (str[i] + SHIFT - 65) % 26 + 65;
    else str[i] = (str[i] + SHIFT - 97) % 26 + 97;
  }
}


void create_kill_file(char mode) {
  FILE* fp = fopen("./kill-soal3.sh", "w");

  switch (mode) {
    case 'z':
      fprintf(fp, "#!/bin/bash\n");
      fprintf(fp, "for pid in $(ps -ef | awk '/soal3/ {print $2}'); do kill -9 $pid; done");
      return (void) fclose(fp);
    
    case 'x':
      fprintf(fp, "#!/bin/bash\n");
      fprintf(fp, "for pid in $(ps -ef | awk '/soal3/ {print $2}'); do kill -15 $pid; done");
      return (void) fclose(fp);
  }
}

void request_create_kill_file(char* args[]) {
  const int EQUAL = 0;
  if (strcmp(args[1], "-z") == EQUAL) return create_kill_file('z');
  if (strcmp(args[1], "-x") == EQUAL) {
    signal(SIGTERM, stop_process);
    return create_kill_file('x');
  }
}

void stop_process() {
  signal_proccess = 0;
}