#include <sys/types.h>
#include <sys/stat.h>
#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <errno.h>
#include <unistd.h>
#include <syslog.h>
#include <string.h>
#include <time.h>

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

    int i=0;
    while(1) {
        time_t rawtime;
        struct tm *info;
        char nama[50];
        char dir[] = "/home/ismail/log/";
        char temp[50];
        char temp2[50];
        char log[] = "/log";
        char nomor[5];
        FILE *baca, *salin;
        
        time(&rawtime);
        info = localtime(&rawtime);

        if(i%30==0){
            sprintf(nama, "%02d:%02d:%d-%02d:%02d", info->tm_mday, info->tm_mon+1, info->tm_year+1900, info->tm_hour, info->tm_min);
            strcpy(temp, dir);
            strcat(temp, nama);
            mkdir(temp, 0777);
        }
        strcpy(temp2, temp);
        sprintf(nomor, "%d.log", (i%30)+1);
        strcat(log, nomor);
        strcat(temp2, log);
        
        baca = fopen("/var/log/syslog", "r");
        salin = fopen(temp2, "w+");

        char kar;

        while((kar=fgetc(baca))!=EOF)
        {
            fputc(kar,salin);
        }
        fclose(baca);
        fclose(salin);

        i++;
        sleep(60);
    }

    exit(EXIT_SUCCESS);
}
