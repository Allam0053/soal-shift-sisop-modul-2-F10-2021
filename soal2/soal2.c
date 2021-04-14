#include <stdlib.h>
#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>
#include <wait.h>
#include <string.h>
#include <time.h>
#include <dirent.h>

void listFilesRecursively(char *path);
char makedir[100][100];
int list_dir=0;

int main(){

    char zip_dir[]="/home/allam/";
    char zip_file[]="/home/allam/pets.zip";
    char target_loc[100];
    char folder_name[50]="/modul2/petshop";
    sprintf(target_loc, "%s%s", "/home/allam", folder_name); // = "/home/allam/modul2/petshop";

    int status;

    pid_t cpid1,cpid2,cpid3,cpid4,cpid5,cpid6;
    //2a====================cpid1,cpid2
    cpid1 = fork();
    if (cpid1 < 0)
        exit(EXIT_FAILURE); // Jika gagal membuat proses baru, program akan berhenti

    if (cpid1 == 0) {
        char *arg2a[] = {"mkdir", "-p", target_loc, NULL};
        execv("/bin/mkdir", arg2a);
        exit(EXIT_SUCCESS);
    }


    while ((wait(&status)) > 0);
    cpid2 = fork();
    if (cpid2 < 0)
        exit(EXIT_FAILURE);
    
    if (cpid2 == 0){
        char *argv[] = {"unzip", zip_file, "-d", target_loc, "-x", "*/*", NULL};
        execv("/bin/unzip", argv);
        exit(EXIT_SUCCESS);
    }

    //2b====================cpid3,cpid4,cpid5
    while ((wait(&status)) > 0);
    cpid3 = fork();
    if (cpid3 < 0)
        exit(EXIT_FAILURE);
    
    if (cpid3 == 0){
        listFilesRecursively("/home/allam/modul2/petshop");
        for (int i=0; i<list_dir; i++){
            cpid4 = fork();
            if (cpid4 < 0)
                exit(1);
            if ( cpid4 == 0){
                char *argv[] = {"mkdir", "-p", makedir[i], NULL};
                execv("/bin/mkdir", argv);
                exit(0);
            }
        }
        exit(EXIT_SUCCESS);
    }
    
}

void listFilesRecursively(char *basePath)
{
    char path[1000];
    struct dirent *dp;
    DIR *dir = opendir(basePath);

    if (!dir)
        return;

    while ((dp = readdir(dir)) != NULL)
    {
        if (strcmp(dp->d_name, ".") != 0 && strcmp(dp->d_name, "..") != 0)
        {
            // printf("%s\n", dp->d_name);
            // strcpy(makedir[list_dir++], strtok(dp->d_name, ";") );
            sprintf(makedir[list_dir++], "%s/%s", basePath, strtok(dp->d_name, ";"));
            
            // Construct new path from our base path
            strcpy(path, basePath);
            strcat(path, "/");
            strcat(path, dp->d_name);

            listFilesRecursively(path);
        }
    }

    closedir(dir);
}