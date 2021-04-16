#include <stdlib.h>
#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <wait.h>
#include <string.h>
#include <time.h>
#include <dirent.h>
#include <stdbool.h>
#include <fcntl.h>

#define tunggu while ((wait(&status)) > 0);

void listFilesRecursively(char *path);
void listFiles(char *basePath);
void listFolder(char *basePath);
void util(pid_t *cpid, char *arg, char **argv);

char makedir[100][100]; //berisi folder yang harus dibuat ex.: cat, dog. NOTE: not distinct value
int list_dir=0;
char files[100][100];   //berisi files / foto. per hewan disimpan di string yg berbeda
int list_files=0;
char folders[100][100]; //berisi folder yang harus dibuat ex.: cat, dog. NOTE: distinct value
int list_folders=0;

char kind[100][100];    //keterangan jenis, nama, umur hewan tersimpan di sini.
char name[100][100];
char age[100][100];

int main(){

    char zip_dir[]="/home/allam/";
    char zip_file[]="/home/allam/pets.zip";
    char target_loc[100];
    char folder_name[50]="/modul2/petshop";
    sprintf(target_loc, "%s%s", "/home/allam", folder_name); // = "/home/allam/modul2/petshop";

    char *mkdir[] = {"/bin/mkdir", "mkdir"};
    char *wget_[] = {"/bin/wget", "wget"};
    char *mv___[] = {"/bin/mv", "mv"};
    char *cp___[] = {"/bin/cp", "cp"};
    char *unzip[] = {"/bin/unzip", "unzip"};
    char *touch[] = {"/bin/touch", "touch"};

    int status;

    pid_t cpid,cpid1,cpid2,cpid3,cpid4,cpid5,cpid6,cpid7,cpid8;

    char link[] = "https://drive.google.com/uc?id=1g5rehatLEkqvuuK_eooHJXB57EfdnxVD&export=download";
    char dir_[] = "/home/allam/Downloads/pets.zip";
    char *arg_init0[] = {wget_[1], link, "-O", dir_, NULL};
    util (&cpid, wget_[0], arg_init0);

    tunggu

    char source[] = "/home/allam/Downloads/pets.zip";
    char dest__[] = "/home/allam/pets.zip";
    char *arg_init1[] = {mv___[1], source, dest__, NULL};
    util (&cpid, mv___[0], arg_init1);

    tunggu

    //2a====================cpid1,cpid2
    char *arg_2a[] = {mkdir[1], "-p", target_loc, NULL};
    util (&cpid1, mkdir[0], arg_2a);

    tunggu

    char *arg_2a1[] = {unzip[1], zip_file, "-d", target_loc, "-x", "*/*", NULL};
    util (&cpid2, unzip[0], arg_2a1);

    tunggu

    //2b====================cpid3,cpid4
    cpid3 = fork();
    if (cpid3 < 0) exit(EXIT_FAILURE);
    
    if (cpid3 == 0) {
        listFilesRecursively("/home/allam/modul2/petshop");
        for (int i=0; i<list_dir; i++) {
            char *arg_2b[] = {mkdir[1], "-p", makedir[i], NULL};
            util (&cpid4, mkdir[0], arg_2b);
        }
        tunggu
        printf("2b selesai\n");
        exit(EXIT_SUCCESS);
    }

    tunggu

    //2c
    cpid5 = fork();
    if (cpid5 < 0) exit(EXIT_FAILURE);
    if (cpid5 == 0){
        listFiles("/home/allam/modul2/petshop");
        char temp[100];
        char source[200], dest__[200];
        char under[]="_";
        char jpg[]=".jpg";

        for (int i=0; i<list_files; i++) {
            sprintf(source, "%s/%s", target_loc, files[i]);
            strcpy(temp, files[i]);
            strcpy(kind[i], strtok(temp,";"));
            strcpy(name[i], strtok(NULL,";"));
            strcpy(age[i], strtok(NULL,"j"));
            age[i][strlen(age[i])-1] = '\0';

            if(strstr(files[i], jpg)==NULL){ //if 1 poto ada 2 hewan: duplicate, namai poto dg 1 hewan
                tunggu

                sprintf(source, "%s/%s%s%s", target_loc, files[i], under, files[i+1]);
                sprintf(dest__, "%s/%s.jpg", target_loc, files[i]);
                char *arg_2c[] = {cp___[1], source, dest__, NULL};
                util (&cpid6, cp___[0], arg_2c);

                tunggu

                sprintf(source, "%s/%s%s%s", target_loc, files[i], under, files[i+1]);
                sprintf(dest__, "%s/%s", target_loc, files[i+1]);
                char *arg_2c1[] = {mv___[1], source, dest__, NULL};
                util (&cpid6, mv___[0], arg_2c1);

                strcat(files[i],".jpg");            
            }
            tunggu

            sprintf(source, "%s/%s", target_loc, files[i]);
            sprintf(dest__, "%s/%s/%s.jpg", target_loc, kind[i], name[i]);
            char *arg_2c2[] = {mv___[1], source, dest__, NULL};
            util (&cpid6, mv___[0], arg_2c2);
        }

        tunggu
        printf("2c 2d selesai\n");
        //breakpoint 2c 2d================================

        FILE *output;
        listFolder(target_loc);

        for(int i=0; i<list_folders; i++) {
            tunggu
            sprintf(dest__, "%s/%s/keterangan.txt", target_loc, folders[i]);
            char *arg_2e[] = {touch[1], dest__, NULL};
            util (&cpid8, touch[0], arg_2e);

            tunggu

            cpid8 = fork();
            if (cpid8 < 0) exit(1);
            if (cpid8 == 0) {
                pid_t pid, sid;

                pid = fork();
                if (pid < 0) exit(EXIT_FAILURE);
                if (pid > 0) exit(EXIT_SUCCESS);
                umask(0);
                sid = setsid();
                if (sid < 0) exit(EXIT_FAILURE);
                if ((chdir("/")) < 0) exit(EXIT_FAILURE);

                sprintf(dest__, "%s/%s/keterangan.txt", target_loc, folders[i]);
                output = fopen(dest__, "w+");
                umask(0);
                for(int j=0; j<list_files; j++) {
                    if( strcmp(folders[i], kind[j])==0 ) {
                        fprintf(output, "nama : %s\n", name[j]);
                        fprintf(output, "umur : %s tahun\n\n", age[j]);
                    }
                }
                fclose(output);

                exit(0);
            }
        }
        tunggu
        printf("2e selesai\n");
        exit(EXIT_SUCCESS);
    }
}

void listFilesRecursively (char *basePath) {
    char path[1000];
    struct dirent *dp;
    DIR *dir = opendir(basePath);

    if (!dir) return;

    while ((dp = readdir(dir)) != NULL) {
        if (strcmp(dp->d_name, ".") != 0 && strcmp(dp->d_name, "..") != 0) {
            sprintf(makedir[list_dir++], "%s/%s", basePath, strtok(dp->d_name, ";"));
            
            strcpy(path, basePath);
            strcat(path, "/");
            strcat(path, dp->d_name);

            listFilesRecursively(path);
        }
    }
    closedir(dir);
}

void listFiles (char *basePath) {
    char path[1000];
    struct dirent *dp;
    DIR *dir = opendir(basePath);
    char *token;

    if (!dir) return;

    while ((dp = readdir(dir)) != NULL) {
        if (strcmp(dp->d_name, ".") != 0 && strcmp(dp->d_name, "..") != 0 && (strstr(dp->d_name, ".") != NULL)){ //check if it's not folder 

            const char s[2] = "_";
            token = strtok(dp->d_name, s);
            strcpy(files[list_files++],token);
            token = strtok(NULL, s);
            
            while( token != NULL ) {
                strcpy(files[list_files++],token);
                token = strtok(NULL, s);
            }
        }
    }
    closedir(dir);
}

void listFolder (char *basePath) {
    char path[1000];
    struct dirent *dp;
    DIR *dir = opendir(basePath);
    char *token;

    if (!dir) return;

    while ((dp = readdir(dir)) != NULL) {
        if (strcmp(dp->d_name, ".") != 0 && strcmp(dp->d_name, "..") != 0) {//check folder
            strcpy(folders[list_folders++],dp->d_name);
        }
    }
    closedir(dir);
}

void util (pid_t *cpid, char *arg, char **argv) {
  *cpid = fork();
  if (*cpid < 0) exit(1);
  if (*cpid == 0) {
      execv(arg, argv);
      exit(0);
  }
  return;
}