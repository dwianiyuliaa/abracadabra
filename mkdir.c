#include "lib/text/text.h"
#include "lib/file/file.h"
#include "lib/folder/folder.h"
#include "lib/mat/mat.h"

void mkdir() {
    char argv[1][128];
    char curdir;
    char argc;
    int success;
    char temp;
   
    // interrupt(0x21, 0x21, &curdir, 0, 0);
    getCurdir(&curdir);
    // interrupt(0x21, 0x22, &argc, 0, 0);
    getArgc(&argc);
    // interrupt(0x21, 0x23, 0, argv[0], 0);
    getArgv(0, argv[0]);
    interrupt(0x21, curdir<<8|0x07, argv[0], &success,0);
    if (success == 0) {
        output("sukses", 1);
    } else if (success == -1) {
        output("not found", 1);
    } else if (success == -2) {
        output("folder already exists", 1);
    } else if (success == -3) {
        output("entri tidak cukup", 1);
    }
    output(curdir,1);
    output(&temp,1);
}
