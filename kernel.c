#include "lib/text/text.h"
#include "lib/file/file.h"
#include "lib/folder/folder.h"
#include "lib/mat/mat.h"

void handleInterrupt21 (int AX, int BX, int CX, int DX);
void executeProgram(char *path, int segment, int *result, char parentIndex);
void count(char *str, char c, int *much);
int isSame(char *sc, char *c2);
int find(char *c, char c1);
int getCommandType(char *str);
void concat(char *s1, char *s2, char isiNull, int len1);
void replace(char find, char change, char *s);
void split(char *string, char separator, char splitted[64][128]);
void terminate(int out);

int main() {
    /*
    char buffer[512*16];
    char input[16];
    char input2[10];
	int suc,i;
	makeInterrupt21();
    
    // create("apa",&suc,0xFF);


    for (i = 0; i < 16 ; i ++){
        input[i] = 0x0;
    }
    for (i = 0; i < 10 ; i ++){
        input2[i] = 0x0;
    }
    for (i = 0; i < 512*16 ; i ++){
        buffer[i] = 0x0;
    }
    interrupt(0x21,0x0,"input: \0",0,0);
    interrupt(0x21,0x1,input,0,0);
    interrupt(0x21,0x0,"\r\nreceived \0",0,0);
    interrupt(0x21,0x0,input,0,0);
    interrupt(0x21,0x0,"input2: \0",0,0);
    interrupt(0x21,0x01,input2,0,0);
    interrupt(0x21,0x0,"\r\nreceived 2 \0",0,0);
    interrupt(0x21,0x0,input2,0,0);
    
    interrupt(0x21,0x0,"is it work",0,0);
    readFile(buffer, input, &suc, 0xFF);
    interrupt(0x21, 0x4, buffer, "key.txt", &suc,0xFF);
    interrupt(0x21, 0x4, &buffer, &input, &suc,0xFF);
    interrupt(0x21,0x0,"\nworked!",0,0);
    interrupt(0x21, 0x5, buffer, input2, &suc,0xFF);
    interrupt(0x21,0x0,"worked22222!",0,0);
    if (suc==1)
	{
		interrupt(0x21,0x0, "Key : \r\n\0", 0, 0);
        interrupt(0x21,0x0,"\r\nwriting file \r\n\0",0,0);
	 	interrupt(0x21,0x0, buffer, 0, 0);
	}
	else if(suc == -1)
	{
        interrupt(0x21,0x0, "\r\nnot succ\r\n\0 ", 0, 0);
		interrupt(0x21, 0x6, "keyproc", 0x2000, &suc);
	}
    interrupt(0x21, 0x5, buffer, input, &suc,0xFF);
*/
	// while (1){}
    int b1, b2, i, j, idx, num;
    char exit, current_dir, argc, succ, ada, globalPIdx;
    char inputSeparator[1];
    char input[100], temp[100], fileName[15];
    int inputLen, splitLen;
    int type, copyStart, copyEnd;
    char argv[64][128];
    char dirs[512];
    char file[512];
    int konstantaRun;
    char same;

    exit = 0;
    while (!exit) {
        //input
        interrupt(0x21, (0 << 8) | 0x0, "$ ", 0, 0);
        interrupt(0x21, (0 << 8) | 0x1, &input, 0, 0);

        len(input, &inputLen);

		count(input, 0x20, &splitLen);

        //cari current_dir
		getCurdir(&current_dir);
        // interrupt(0x21, 0x21, &current_dir, 0, 0);
        printString("current_dir : ", 0);
        if (current_dir == 0xFF) {
            printString("di Root", 1);
        } else {
            printInt(current_dir, 1);
        }

        //isi type  dengan jenis command (echo, cd, dll)
        type = getCommandType(input);
        
        argc = splitLen;
        split(input, 0x20, argv); //get argumen vektor

        if (type == 1) {
            printString("echo", 1);
			putArgs(current_dir, argc, argv + 1);
            // interrupt(0x21, 0x20, current_dir, argc, argv + 1);
            interrupt(0x21, current_dir << 8 | 0x6, "echoUtil", 0x2000, &succ); //invoke executeProgram()
        } else if (type == 2) {
            // printString("cd", 1);
            if (argc > 1) {
                printString("cd harus 1 atau tidak sama sekali", 1);
            } else if (argc == 0) {
                current_dir = 0xFF;
				putArgs(current_dir, 0,0);
                // interrupt(0x21, 0x20, current_dir, 0, 0);
            } else if (argc == 1) {
                if (isSame(argv[1], "..")) {
                    if (current_dir != 0xFF) { 
                        printString("success 1", 1);
                        interrupt(0x21, (0 << 8) | 0x02, dirs, 0x101, 0);
                        current_dir = dirs[current_dir * 16]; //parent current_dir
						putArgs(current_dir,0,0);
                        // interrupt(0x21, 0x20, current_dir, 0, 0);
                    }
                } else {
                    printString("Go : ", 0);
                    printString(argv[1], 1);
                    interrupt(0x21, (0 << 8) | 0x02, dirs, 0x101, 0);
                    searchDir(dirs, argv[1], &idx, &succ, current_dir);
                    if (succ)
                    {
                        // printString("get in", 1);
                        current_dir = idx;
						putArgs(current_dir, 0,0);
                        // interrupt(0x21, 0x20, current_dir, 0, 0);
                    }else{
                        printString(argv[1], 0);
                        printString(" not found", 1);
                    }
                }
            }
        } else if (type == 3) {
            // printString("ls", 1);
            if (argc != 0) {
                printString("no get input", 1);
            } else {
				putArgs(current_dir, argc, argv + 1);
                // interrupt(0x21, 0x20, current_dir, argc, argv + 1);
                interrupt(0x21, 0xFF << 8 | 0x6, "ls", 0x2000, &succ);
            }
        } else if (type == 4) {
            // printString("mkdir", 1);
            if (argc != 1)
            {
                printString("Mkdir harus 1", 1);
            }
            else
            {
				putArgs(current_dir, argc, argv + 1);
                // interrupt(0x21, 0x20, current_dir, argc, argv + 1);
                interrupt(0x21, 0xFF << 8 | 0x6, "mkdir", 0x2000, &succ);
            }
        }
        else if (type == 5)
        {
            // printString("rm", 1);
            if (argc != 1)
            {
                printString("Rm harus 1", 1);
            }
            else
            {
                interrupt(0x21, current_dir << 8 | 0x0A, argv[1], &b1, 0);
                interrupt(0x21, current_dir << 8 | 0x09, argv[1], &b2, 0);
                if (b1 == -1 && b2 == -1)
                {
                    printString("Path not found", 1);
                }
                else if (b1 == 0 || b2 == 0)
                {
                    printString("success!", 1);
                }
                else
                {
                    printString("Failed", 1);
                }
            }
        }
        else if (type == 6)
        {
            // printString("Command cat", 1);
            if (argc != 1 && argc != 2)
            {
                printString("cat", 1);
            }
            else
            {
                interrupt(0x21, 0x20, current_dir, argc, argv + 1);
                interrupt(0x21, 0xFF << 8 | 0x6, "cat", 0x2000, &succ);
            }
        }
        else if (type == 7 || type == 8)
        {
            if (type == 7)
            {
                // printString("Command runLocal", 1);
                konstantaRun = 2;
                globalPIdx = current_dir;
            }
            else
            {
                // printString("Command runGlobal", 1);
                konstantaRun = 0;
                globalPIdx = 0xFF;
            }
            interrupt(0x21, 0x02, file, 0x102, 0);
            //Cek dulu apakah filenya ada
            search(file, globalPIdx, argv[0]+konstantaRun,&i, &ada);
            if (ada)
            {
                //argv[0] adalah nama file yang akan dirun dibaca mulai dari index yang ke 2
                //sisanya = parameternya

                //persiapan args
                interrupt(0x21, 0x20, current_dir, argc, argv + 1);
                //run programnya
                interrupt(0x21, globalPIdx << 8 | 0x6, argv[0] + konstantaRun, 0x2000, &succ);
            }
            else
            {
                printString(argv[0] + konstantaRun, 0);
                printString("not found", 1);
            }
        }
    }
    putArgs(0xFF,0,0);
    executeProgram("shell",0x2000,&succ,0xFF);
    while(1){}	
}

void handleInterrupt21(int AX, int BX, int CX, int DX) {
	char AL, AH;
	AL = (char)(AX);
	AH = (char)(AX >> 8);

	switch (AL) {
		case 0x00:
			printString(&BX, CX);
			break;
		case 0x01:
			readString(&BX);
			break;
		case 0x02:
			readSector(&BX, CX);
			break;
		case 0x03:
			writeSector(&BX, CX);
			break;
		case 0x04:
			readFile(BX, CX, DX, AH);
			break;
		case 0x05:
			writeFile(BX, CX, DX, AH);
			break;
		case 0x06:
			executeProgram(BX, CX, DX, AH);
			break;
        case 0x07:
			create(BX, CX, AH);
			break;
        case 0x08:
			deleteFile(BX, CX, AH);
			break;
        case 0x09:
			deleteFolder(BX, CX, AH);
			break;
        case 0x10:
            terminate(BX);
            break;
		default:
			printString("Invalid interrupt", 1);
	}
}


//Execute program
void executeProgram(char *path, int segment, int *result, char parentIndex) {
	char buffer[16*512];
	int succ,i;
	readFile(&buffer, path, &succ, 0xFF);
	if (succ)
	{
		for (i = 0; i < 16*512; i++)
		{
			putInMemory(segment, i, buffer[i]);
		}
		launchProgram(segment);
	}
	else
	{
		interrupt(0x21,0,"File not found",0,0);
	}
	
}

// Menggabungkan dua string
void concat(char *s_1, char *s_2, char i_null, int length1){
    int i = 0;
    while (s_2[i] != '\0'){
        s_1[i + length1 + i_null] = s_2[i];
        i++;
    }
    s_1[i + length1 + i_null] = '\0';
}

void replace(char find, char change, char *s){
    int length,i;
    //cari panjang string s
    len(s, &length);
    i = 0;
    while (i < length) {
        if (s[i] == find){
            s[i] = change;
        }
        i++;
    }
    s[length] = '\0';
}

void split(char *s, char sprt, char split[64][128]){
    // mengosongkan baris ke-0 split sebanyak 128 kolom
    int i, j, k;
    i = 0;
    j = 0;
    k = 0;
    clear(split[0], 128);
    while (s[i] != '\0') {
        // bila s ke i sama dg pemisah maka isi split dg \0
        if (s[i] == sprt) {
            split[j][k] = '\0';
            k = 0; // diset 0
            j++;
            clear(split[j], 128);
        } else {
            split[j][k] = s[i];
            k++;
        }
        i++;
    }
    split[j][k] = '\0';
}

void count(char *str, char c, int *much){
    char temp[2];
    int i;
    *much = 0;
    i = 0;
    while (str[i] != "\0"){
        if (str[i] == c){
            *much++;
        }
        i++;
    }
}

int isSame(char *string1, char *string2){
    int i, len1, len2;
    char result;
    len(string1, &len1);
    len(string2, &len2);
    if (len1 != len2){
        return 0;
    }
    else{
        for (i = 0; i < len1; i++ ){
            if (string1[i] != string2[i]){
                return 0;
            }
        }
    }
    return 1;
}

int find(char *c, char c1){
    int i;
    i = 0;
    while (c[i] != "\0"){
        if (c[i] == c1){
            return i;
        }
        i++;
    }
    return -1;
}

void terminate(int out){
    char shell[6];
    shell[0] = 's';
    shell[1] = 'h';
    shell[2] = 'e';
    shell[3] = 'l';
    shell[4] = 'l';
    shell[5] = '\0';
}

int getCommandType(char *str){
    char command[20];
    int command_idx, spasi_idx, lenStr;
    spasi_idx = find(str, 0x20);
    len(str, &lenStr);
    if (spasi_idx == -1){
        spasi_idx = lenStr;
    }
    copy(str, command, 0, spasi_idx);
    if (isSame(command, "cd")){
        return 1;
    }
    if (isSame(command, "echo")){
        return 2;
    }
    if (isSame(command, "ls")){
        return 3;
    }
    if (isSame(command, "mkdir")){
        return 4;
    }
    if (isSame(command, "rm")){
        return 5;
    }
    if (isSame(command, "cat")){
        return 6;
    }

    if (command[0] != "." && command[1] != "/"){
        return 7;
    }
    else{
        return 8;
    }
}

void cat(char* filename){
    char buffer[15];
    int succ;
    char curdir;
    getCurdir(&curdir);
    readFile(buffer, filename, succ, curdir);
    printString(buffer,1);
}

void cp(char* file1,char* file2, char* cp_dir){
    char buffer[15];
    int succ;
    char curdir;
    getCurdir(&curdir);
    readFile(buffer, file1, succ, curdir);
    writeFile(buffer, file2, succ, cp_dir);
}

void mv(char* filename, char* mv_dir){
    char buffer[15];
    char curdir;
    int succ;
   
   getCurdir(&curdir);
    readFile(buffer, filename, succ, curdir);
    writeFile(buffer, filename, succ, mv_dir);
    deleteFile(filename,succ,curdir);

}

void mkdir(char* foldername) {
    char buffer[15];
    char curdir;
    int succ;
   
   getCurdir(&curdir);
   create(foldername, succ, curdir);
    if (succ == 0) {
        output("sukses", 1);
    } else if (success == -1) {
        output("not found", 1);
    } else if (success == -2) {
        output("folder already exists", 1);
    } else if (success == -3) {
        output("entri tidak cukup", 1);
    }
    output(curdir,1);
}

void rm(char* filename) {
    int suc1;
    int suc2;
    char curdir;
    getCurdir(&curdir);
    // curdir
    interrupt(0x21, curdir<<8|0x09, filename, &suc1,0);
    interrupt(0x21, curdir<<8|0x08, filename, &suc2,0);
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
