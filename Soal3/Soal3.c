#include <stdio.h>
#include <string.h>
#include <sys/types.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/wait.h>

int main(int argc, char* argv[])
{
    int status;
    int p1[4];
    pipe(p1);
    pipe(p1+2);
    pid_t pID;

    pID = fork();
    //genap = terima
    //ganjil = kirim
    //1 = stdout
    //0 = stdin

    if (pID == 0)
    {
        pID = fork();

        if (pID == 0)
        {
            char *argv[3] = {"unzip", "/home/ismail/sisop/SoalShift_modul2_B13/Soal3/campur2.zip", NULL};
       	    execv("/usr/bin/unzip", argv);
        }
        else
        {
            while ((wait(&status)) > 0);
            close(p1[0]);
            close(p1[2]);
	        close(p1[3]);
            dup2(p1[1],1);
            char *argv[3] = {"ls", "/home/ismail/sisop/SoalShift_modul2_B13/Soal3/campur2", NULL};
            execv("/bin/ls", argv);
        }
    }
    else
    {
        while ((wait(&status)) > 0);
        pID = fork();

        if (pID == 0)
        {
            close(p1[1]);
            close(p1[2]);
            dup2(p1[0],0);
            dup2(p1[3],1);
            char *argv[3] = {"grep", ".txt$", NULL};
            execv("/bin/grep", argv);
        }
        else
        {
            close(p1[0]);
            close(p1[1]);
            close(p1[3]);
            FILE *mfile;
            char data[1000];
            mfile = fopen ("/home/ismail/sisop/SoalShift_modul2_B13/Soal3/daftar.txt", "w");
            read(p1[2], data, 1000);
            fputs(data, mfile);
	        fclose(mfile);
        }
    }
}
