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

char makedir[100][100];
int list_dir=0;
char files[100][100];
int list_files=0;
char folders[100][100];
int list_folders=0;

char kind[100][100];
char name[100][100];
char age[100][100];

int main(){

    char zip_dir[]="/home/allam/";
    char zip_file[]="/home/allam/pets.zip";
    char target_loc[100];
    char folder_name[50]="/modul2/petshop";
    sprintf(target_loc, "%s%s", "/home/allam", folder_name); // = "/home/allam/modul2/petshop";

    int status;

    pid_t cpid,cpid1,cpid2,cpid3,cpid4,cpid5,cpid6,cpid7,cpid8;

    cpid = fork();
    if (cpid < 0) exit(EXIT_FAILURE);
    if (cpid == 0) {
        char *arg2a[] = {"wget", "https://drive.google.com/uc?id=1g5rehatLEkqvuuK_eooHJXB57EfdnxVD&export=download", "-O", "/home/allam/Downloads/pets.zip", NULL};
        execv("/bin/wget", arg2a);
        exit(EXIT_SUCCESS);
    }

    tunggu

    cpid = fork();
    if (cpid < 0) exit(EXIT_FAILURE);
    if (cpid == 0) {
        char source[] = "/home/allam/Downloads/pets.zip";
        char dest__[] = "/home/allam/pets.zip";
        char *arg2a[] = {"mv", source, dest__, NULL};
        execv("/bin/mv", arg2a);
        exit(EXIT_SUCCESS);
    }

    tunggu

    //2a====================cpid1,cpid2
    cpid1 = fork();
    if (cpid1 < 0) exit(EXIT_FAILURE);
    if (cpid1 == 0) {
        char *arg2a[] = {"mkdir", "-p", target_loc, NULL};
        execv("/bin/mkdir", arg2a);
        exit(EXIT_SUCCESS);
    }

    tunggu

    cpid2 = fork();
    if (cpid2 < 0) exit(EXIT_FAILURE);
    if (cpid2 == 0){
        char *argv[] = {"unzip", zip_file, "-d", target_loc, "-x", "*/*", NULL};
        execv("/bin/unzip", argv);
        tunggu
        printf("2a selesai\n");
        exit(EXIT_SUCCESS);
    }

    tunggu

    //2b====================cpid3,cpid4
    cpid3 = fork();
    if (cpid3 < 0) exit(EXIT_FAILURE);
    
    if (cpid3 == 0) {
        listFilesRecursively("/home/allam/modul2/petshop");
        for (int i=0; i<list_dir; i++) {
            cpid4 = fork();
            if (cpid4 < 0) exit(1);
            if ( cpid4 == 0) {
                char *argv[] = {"mkdir", "-p", makedir[i], NULL};
                execv("/bin/mkdir", argv);
                exit(0);
            }
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

                cpid6 = fork();
                if (cpid6 < 0) exit(1);
                if (cpid6 == 0) {
                    sprintf(source, "%s/%s%s%s", target_loc, files[i], under, files[i+1]);
                    sprintf(dest__, "%s/%s.jpg", target_loc, files[i]);
                    char *argv[] = {"cp", source, dest__, NULL};
                    execv("/bin/cp", argv);
                    exit(0);
                }

                tunggu

                cpid6 = fork();
                if (cpid6 < 0) exit(1);
                if (cpid6 == 0) {
                    sprintf(source, "%s/%s%s%s", target_loc, files[i], under, files[i+1]);
                    sprintf(dest__, "%s/%s", target_loc, files[i+1]);
                    char *argv[] = {"mv", source, dest__, NULL};
                    execv("/bin/mv", argv);
                    exit(0);
                }

                strcat(files[i],".jpg");            
            }

            tunggu

            cpid6 = fork();
            if (cpid6 < 0) exit(1);
            if (cpid6 == 0) {
                sprintf(source, "%s/%s", target_loc, files[i]);
                sprintf(dest__, "%s/%s/%s.jpg", target_loc, kind[i], name[i]);
                char *argv[] = {"mv", source, dest__, NULL};
                execv("/bin/mv", argv);
                exit(0);
            }
        }

        tunggu
        printf("2c 2d selesai\n");
        //breakpoint 2c 2d================================

        FILE *output;
        listFolder(target_loc);

        for(int i=0; i<list_folders; i++) {
            tunggu
            cpid8 = fork();
            if (cpid8 < 0) exit(1);
            if (cpid8 == 0) {
                sprintf(dest__, "%s/%s/keterangan.txt", target_loc, folders[i]);
                char *argv[] = {"touch", dest__, NULL};
                execv("/bin/touch", argv);
                exit(0);
            }

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

void listFilesRecursively(char *basePath) {
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

void listFiles(char *basePath) {
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

void listFolder(char *basePath) {
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