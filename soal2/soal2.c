#include <stdlib.h>
#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>
#include <wait.h>
#include <string.h>
#include <time.h>
#include <dirent.h>

void listFilesRecursively(char *path);
void listFiles(char *basePath);
void listFolder(char *basePath);
char makedir[100][100];
int list_dir=0;
char files[100][100];
int list_files=0;
char folders[100][100];
int list_folders=0;

int main(){

    char zip_dir[]="/home/allam/";
    char zip_file[]="/home/allam/pets.zip";
    char target_loc[100];
    char folder_name[50]="/modul2/petshop";
    sprintf(target_loc, "%s%s", "/home/allam", folder_name); // = "/home/allam/modul2/petshop";

    int status;

    pid_t cpid1,cpid2,cpid3,cpid4,cpid5,cpid6,cpid7;
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

    //2b====================cpid3,cpid4
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

    //2c
    while ((wait(&status)) > 0);
    cpid5 = fork();
    if (cpid5 < 0)
        exit(EXIT_FAILURE);
    
    if (cpid5 == 0){
        listFiles("/home/allam/modul2/petshop");
        char kind[100][100];
        char name[100][100];
        char age[100][100];
        char temp[100];
        char source[200], dest[200];
        char under[]="_";
        char jpg[]=".jpg";
        for(int i=0; i<list_files; i++){
            // printf("%s\n", files[i]);
            strcpy(temp, files[i]);
            strcpy(kind[i], strtok(temp,";"));
            strcpy(name[i], strtok(NULL,";"));
            strcpy(age[i], strtok(NULL,";"));

            sprintf(source, "%s/%s", target_loc, files[i]);
            if(strstr(files[i], jpg)==NULL){ //if 1 poto ada 2 hewan: duplicate, namai poto dg 1 hewan
                while ((wait(&status)) > 0);
                cpid6 = fork();
                if (cpid6 < 0)
                    exit(1);
                if ( cpid6 == 0){
                    sprintf(source, "%s/%s%s%s", target_loc, files[i], under, files[i+1]);
                    sprintf(dest, "%s/%s.jpg", target_loc, files[i]);
                    char *argv[] = {"cp", source, dest, NULL};
                    execv("/bin/cp", argv);
                    exit(0);
                }

                while ((wait(&status)) > 0);
                cpid6 = fork();
                if (cpid6 < 0)
                    exit(1);
                if ( cpid6 == 0){
                    sprintf(source, "%s/%s%s%s", target_loc, files[i], under, files[i+1]);
                    sprintf(dest, "%s/%s", target_loc, files[i+1]);
                    char *argv[] = {"mv", source, dest, NULL};
                    execv("/bin/mv", argv);
                    exit(0);
                }

                strcat(files[i],".jpg");            
            }
            while ((wait(&status)) > 0);
            cpid6 = fork();
            if (cpid6 < 0)
                exit(1);
            if ( cpid6 == 0){
                sprintf(source, "%s/%s", target_loc, files[i]);
                sprintf(dest, "%s/%s/%s.jpg", target_loc, kind[i], name[i]);
                char *argv[] = {"mv", source, dest, NULL};
                execv("/bin/mv", argv);
                exit(0);
            }
        }
        exit(EXIT_SUCCESS);
    }
    
    //2e
    while ((wait(&status)) > 0);
    cpid7 = fork();
    if (cpid7 < 0)
        exit(EXIT_FAILURE);

    if(cpid7 == 0){
        
        FILE *output;
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

void listFiles(char *basePath)
{
    char path[1000];
    struct dirent *dp;
    DIR *dir = opendir(basePath);
    char *token;

    if (!dir)
        return;

    while ((dp = readdir(dir)) != NULL)
    {
        if (strcmp(dp->d_name, ".") != 0 && strcmp(dp->d_name, "..") != 0 && (strstr(dp->d_name, ".") != NULL))//check if it's not folder
        {
            const char s[2] = "_";
            token = strtok(dp->d_name, s);
            strcpy(files[list_files++],token);
            // printf("%s\n", files[list_files-1]);
            token = strtok(NULL, s);
            
            while( token != NULL ) {
                strcpy(files[list_files++],token);
                // printf("%s\n", files[list_files-1]);
                token = strtok(NULL, s);
            }
        }
    }

    closedir(dir);
}

void listFolder(char *basePath)
{
    char path[1000];
    struct dirent *dp;
    DIR *dir = opendir(basePath);
    char *token;

    if (!dir)
        return;

    while ((dp = readdir(dir)) != NULL)
    {
        if (strcmp(dp->d_name, ".") != 0 && strcmp(dp->d_name, "..") != 0){//check if it's folder
            strcpy(folders[list_folders++],dp->d_name);
        }
    }

    closedir(dir);
}