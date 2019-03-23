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

	int i=1;
	while(1) {
		char dir[50] = "/home/ismail/Documents/makanan/";
		char nama[15]="makan_sehat";
		char eks[5]=".txt";
		char namafile[30];
		char temp[60];
		char angka[10];
		struct stat filestat;
		stat("/home/ismail/Documents/makanan/makan_enak.txt",&filestat);
		time_t timenow;
		time(&timenow);
		int waktu = difftime(timenow, filestat.st_atime);

		if(waktu <= 30 && waktu != 0)
		{
			sprintf(angka, "%d", i);
			strcpy(namafile, nama);
			strcat(namafile, angka);
			strcat(namafile, eks);
			strcpy(temp, dir);
			strcat(temp, namafile);

			FILE* fo;

			fo = fopen (temp, "w+");
			fclose(fo);
			i++;
		}
		sleep(5);
	}
	exit(EXIT_SUCCESS);
}