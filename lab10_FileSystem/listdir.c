#include <stdio.h>
#include <dirent.h>

int main (int argc,char *argv[]) {
    int total = 0;
        DIR *pDir;
        struct dirent *pDirent;

        if (argc < 2) {
            printf ("Missing out directory!\n");
            return -1;
        }
        pDir = opendir (argv[1]);
        if (pDir == NULL) {
            printf ("Cannot open directory '%s'\n", argv[1]);
            return 1;
        }

        while ((pDirent = readdir(pDir)) != NULL) {
            printf ("[%s]\n", pDirent->d_name);
        }
        closedir (pDir);
        return 0;
    }
