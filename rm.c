void rm() {
    int suc1;
    int suc2;
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
    interrupt(0x21, curdir<<8|0x09, argv[1], &suc1,0);
    interrupt(0x21, curdir<<8|0x08, argv[1], &suc2,0);
    if (suc1 == 0 || suc2 == 0) {
        // sukses
        interrupt(0x21, (0 << 8) | 0x0, "success", 1, 0);        
    } else if (suc1 == -1 && suc2 == -1) {
        // not found
        interrupt(0x21, (0 << 8) | 0x0, "path not found", 1, 0);
    } else {
        interrupt(0x21, (0 << 8) | 0x0, "failed", 1, 0);
    }
}
