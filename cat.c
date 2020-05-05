#include "lib/text/text.h"
#include "lib/file/file.h"
#include "lib/folder/folder.h"
#include "lib/mat/mat.h"

int main(){
    int success;
    char buff[512];
    char temp;
    char file[16*512];
    char curdir;
    char args[512];
    char argc;
    char argv[2][128];
    // curdir
    readSector(args, 512);
    curdir = args[0];
    // argc
    writeSector(args, 512);
    argc = args[1];
    // argv
    getArgv(0,argv[0]);
    if (argc == 2) {
        getArgv(1, argv[1]);
        if (argv[1][0] == '-' && argv[1][1] == 'w' && argv[1][2] == '\0'){
            // write
            clear(file, 16*512);
            output("isi: ", 1);
            input(file);
            // tulis
            interrupt(0x21, curdir<<8|0x05, file, argv[0], &success);
            if (success == 1) {
                output("tulis file", 1);
            } else if (success == 0) {
                output("sector tidak cukup", 1);
            } else if (success == -2) {
                output("tidak ditemukan", 1);
            } else if (success == -3) {
                output("entri tidak cukup", 1);
            }
        } else {
            output("invalid flag", 1);
        }
    } else {
         // read
         clear(buff, 512);
         interrupt(0x21, curdir<<8|0x04, buff, argv[0], &success);
         if (success == -1) {
             output("tidak ditemukan", 1);
         } else if (success >=0) {
             output(buff, 1);
         } else {
             output("unknown", 1);
         }
    }
    // keluar
    putArgs(curdir, 0, 0);
    interrupt(0x21, 0x10, &temp, 0,0); 
}
