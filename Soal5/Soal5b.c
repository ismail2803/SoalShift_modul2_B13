#include <stdio.h>
#include <unistd.h>

int main () {

  char *argv[3] = {"killall", "Soal5", NULL};

  execv("/usr/bin/killall", argv);

  return 0;
}
