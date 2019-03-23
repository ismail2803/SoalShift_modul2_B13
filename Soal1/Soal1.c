#include <sys/types.h>
#include <sys/stat.h>
#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <errno.h>
#include <unistd.h>
#include <syslog.h>
#include <string.h>
#include <dirent.h>

static void StripFileName(char *FileName, char *NewFileName)
{
    int PLocation;
    int i;
    int x;

    i = strlen(FileName) - 1;
    
    while (i && FileName[i] != '.')
    {
        i--;
    }

    if (i)
    {
        PLocation = i;
    }
    else
    {
        PLocation = strlen(FileName);
        i = strlen(FileName) - 1;
    }

    while (i && FileName[i] != '\\')
    {
        if (FileName[i] != '\\')
        i--;
    }

    if (FileName[i] == '\\')
        i++;
        x = 0;

    while (i < PLocation)
    {
        NewFileName[x] = FileName[i];
        x++;
        i++;
    }
    NewFileName[x] = '\0';
}

static void StripEksName(char *FileName, char *NewFileName)
{
    int PLocation;
    int i;
    int x=0;
    int j;

    i = strlen(FileName) - 1;
    j = strlen(FileName) - 1;
    
    while (i && FileName[i] != '.')
    {
        i--;
    }
    PLocation = i;

    while (i <= j)
    {
        NewFileName[x] = FileName[i];
        x++;
        i++;
    }
    NewFileName[x] = '\0';
}

int main() {
    pid_t pid, sid;
    pid = fork();

    if (pid < 0) {
        exit(EXIT_FAILURE);
    }

    if (pid > 0) {
        exit(EXIT_SUCCESS);
    }

    umask(0);

    sid = setsid();

    if (sid < 0) {
        exit(EXIT_FAILURE);
    }

    if ((chdir("/")) < 0) {
        exit(EXIT_FAILURE);
    }

    close(STDIN_FILENO);
    close(STDOUT_FILENO);
    close(STDERR_FILENO);

    while(1) {
        DIR *d;
        struct dirent *dir;
        char folder[100] = "/home/ismail/modul2/gambar/";
        char folderl[100] = "/home/ismail/Pictures/";
        d = opendir("/home/ismail/Pictures/");
        if (d) {
            while ((dir = readdir(d)) != NULL) 
            {
                if(dir->d_type != 4){
                    char fullname[50];
                    char newname[50];
                    char eksname[10];
                    char grey[10] = "_grey";
                    strcpy(fullname, dir->d_name);
                    StripEksName(fullname, eksname);
                    char ekstensi[50];
                    strcpy(ekstensi, eksname);
                    if(strcmp(ekstensi, ".png") == 0)
                    {
                        StripFileName(fullname, newname);
                        strcat(newname, grey);
                        strcat(newname, ekstensi);

                        char foldertemp[100];
                        
                        strcpy(foldertemp, folder);
                        strcat(foldertemp, newname);
                        strcpy(newname, foldertemp);

                        strcpy(foldertemp, folderl);
                        strcat(foldertemp, fullname);
                        strcpy(fullname, foldertemp);

                        rename(fullname, newname);
                    }
                }
            }
            closedir(d);
        }
        sleep(5);
    } 
    exit(EXIT_SUCCESS);
}

