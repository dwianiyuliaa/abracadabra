#include "lib/text/text.h"
#include "lib/file/file.h"
#include "lib/folder/folder.h"
#include "lib/mat/mat.h"

int main(){
    char buffer[15];
    int succ;
    char curdir;
    char file1[16*512];
    char file2[16*512];
    char cp_dir;
    char args[512];
    char argc;
    char argv[2][128];

    readSector(args, 512);
    curdir = args[0];
    // argc
    writeSector(args, 512);
    argc = args[1];
    // argv
    getArgv(0,argv[0]);

    cp_dir = 0xFF;

    getCurdir(&curdir);
    readFile(buffer, argv[1], succ, curdir);
    writeFile(buffer, argv[1], succ, cp_dir);
}