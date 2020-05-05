//Function Declaration
int mod(int a, int b);
int div(int a, int b);
void printString(char *str, int nL);
void printInt(int i, int nL);
void printChar(char c, int nL);
void len(char *str, int *len);
void count(char *str, char c, int *much);
int isSame(char *sc, char *c2);
void copy(char *str, char *copied, int start, int len);
int find(char *c, char c1);
int getCommandType(char *str);
void concat(char *s1, char *s2, char isiNull, int len1);
void replace(char find, char change, char *s);
void split(char *string, char separator, char splitted[64][128]);
void clear(char *buffer, int length);
void searchDir(char *dirs, char *relPath, char *index, char *success, char parentIndex);
void search(char *sector, char awal, char sisanya[15], char *index, char *success);

int main() {
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
    //     //Get input user
    //     interrupt(0x21, (0 << 8) | 0x0, "$ ", 0, 0);
    //     interrupt(0x21, (0 << 8) | 0x1, &input, 0, 0);
        
    //     len(input, &inputLen);
    //     count(input, 0x20, &splitLen);
        
    //     //Get current_dir
    //     interrupt(0x21, 0x21, &current_dir, 0, 0);
    //     // printString("current_dir : ", 0);
    //     // if (current_dir == 0xFF) {
    //     //     printString("di Root", 1);
    //     // } else {
    //     //     printInt(current_dir, 1);
    //     // }

    //     //Get command berdasarkan input user
    //     type = getCommandType(input);
        
    //     argc = splitLen;
    //     split(input, 0x20, argv); // <- get argumen vektor
    //     if (type == 1) {
    //         // printString("Command echo", 1);
    //         interrupt(0x21, 0x20, current_dir, argc, argv + 1);
    //         interrupt(0x21, current_dir << 8 | 0x6, "echoUtil", 0x2000, &succ); //invoke executeProgram()
    //     } else if (type == 2) {
    //         // printString("Command cd", 1);
    //         if (argc > 1) {
    //             printString("Jumlah parameter cd harus 1 atau tidak sama sekali", 1);
    //         } else if (argc == 0) {
    //             current_dir = 0xFF;
    //             interrupt(0x21, 0x20, current_dir, 0, 0);
    //         } else if (argc == 1) {
    //             if (isSame(argv[1], "..")) {
    //                 if (current_dir != 0xFF) { 
    //                     printString("Go up 1 level", 1);
    //                     interrupt(0x21, (0 << 8) | 0x02, dirs, 0x101, 0);
    //                     current_dir = dirs[current_dir * 16]; //parent dari current_dir
    //                     interrupt(0x21, 0x20, current_dir, 0, 0);
    //                 }
    //             } else {
    //                 printString("Go to : ", 0);
    //                 printString(argv[1], 1);
    //                 interrupt(0x21, (0 << 8) | 0x02, dirs, 0x101, 0);
    //                 searchDir(dirs, argv[1], &idx, &succ, current_dir);
    //                 if (succ)
    //                 {
    //                     // printString("Masuk ke tujuan bosque", 1);
    //                     current_dir = idx;
    //                     interrupt(0x21, 0x20, current_dir, 0, 0);
    //                 }else{
    //                     printString(argv[1], 0);
    //                     printString(" not found", 1);
    //                 }
    //             }
    //         }
    //     } else if (type == 3) {
    //         // printString("Command ls", 1);
    //         if (argc != 0) {
    //             printString("ls tidak menerima parameter apapun", 1);
    //         } else {
    //             interrupt(0x21, 0x20, current_dir, argc, argv + 1);
    //             interrupt(0x21, 0xFF << 8 | 0x6, "ls", 0x2000, &succ);
    //         }
    //     } else if (type == 4) {
    //         // printString("Command mkdir", 1);
    //         if (argc != 1)
    //         {
    //             printString("Jumlah parameter mkdir harus 1", 1);
    //         }
    //         else
    //         {
    //             interrupt(0x21, 0x20, current_dir, argc, argv + 1);
    //             interrupt(0x21, 0xFF << 8 | 0x6, "mkdir", 0x2000, &succ);
    //         }
    //     }
    //     else if (type == 5)
    //     {
    //         // printString("Command rm", 1);
    //         if (argc != 1)
    //         {
    //             printString("Jumlah parameter rm harus 1", 1);
    //         }
    //         else
    //         {
    //             // KODE RM DI SHELL AGAR TIDAK BISA DIHAPUS MENGGUNAKKAN RM
    //             interrupt(0x21, current_dir << 8 | 0x0A, argv[1], &b1, 0);
    //             interrupt(0x21, current_dir << 8 | 0x09, argv[1], &b2, 0);
    //             if (b1 == -1 && b2 == -1)
    //             {
    //                 printString("PATH NOT_FOUND", 1);
    //             }
    //             else if (b1 == 0 || b2 == 0)
    //             {
    //                 printString("SUCCESS", 1);
    //             }
    //             else
    //             {
    //                 printString("FAILED, UNKNOWN REASON", 1);
    //             }
    //         }
    //     }
    //     else if (type == 6)
    //     {
    //         // printString("Command cat", 1);
    //         if (argc != 1 && argc != 2)
    //         {
    //             printString("cat menerima 1 / 2 parameter", 1);
    //         }
    //         else
    //         {
    //             interrupt(0x21, 0x20, current_dir, argc, argv + 1);
    //             interrupt(0x21, 0xFF << 8 | 0x6, "cat", 0x2000, &succ);
    //         }
    //     }
    //     else if (type == 7 || type == 8)
    //     {
    //         if (type == 7)
    //         {
    //             // printString("Command runLocal", 1);
    //             konstantaRun = 2;
    //             globalPIdx = current_dir;
    //         }
    //         else
    //         {
    //             // printString("Command runGlobal", 1);
    //             konstantaRun = 0;
    //             globalPIdx = 0xFF;
    //         }
    //         interrupt(0x21, 0x02, file, 0x102, 0);
    //         //Cek dulu apakah filenya ada
    //         search(file, globalPIdx, argv[0]+konstantaRun,&i, &ada);
    //         if (ada)
    //         {
    //             //argv[0] adalah nama file yang akan dirun dibaca mulai dari index yang ke 2
    //             //sisanya = parameternya

    //             //persiapan args
    //             interrupt(0x21, 0x20, current_dir, argc, argv + 1);
    //             //run programnya
    //             interrupt(0x21, globalPIdx << 8 | 0x6, argv[0] + konstantaRun, 0x2000, &succ);
    //         }
    //         else
    //         {
    //             printString(argv[0] + konstantaRun, 0);
    //             printString(" not found", 1);
    //         }
    //     }
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
void clear(char *isi, int panjang){
    int i;
    for (i=0; i<panjang; i++) {
        isi[i] = 0x00;
    }
}


void searchDir(char *dir, char *rel_Path, char *idx, char *suc, char parentIndex){
    if (rel_Path [0] == '\0') {
        *suc = 1;
        *idx = parentIndex;
    } else {
        // cari panjang rel_Path
        int lenPath,hitungSlash,i;
        char splitPath[64][128];
        char find[15];
        len(rel_Path, &lenPath);
        // hitung slash
        count(rel_Path, '/',&hitungSlash);
        // split path;
        
        split(rel_Path, '/', splitPath);
        *suc = 1;
        
        for (i=0; (i < (hitungSlash + 1)) && *suc; i++) {
            // bila berhasil bersihkan find sepanjang 15
            clear(find, 15);
            // copy splitpath ke i ke dalam find
            copy(splitPath[i], find, 0, 15);
            // cari dir mulai dari parent
            search(dir, parentIndex, find, idx, suc);
            parentIndex = *idx;
        }
    }
}
void search(char *sec, char start, char remaining[15], char *idx, char *suc){
    char salin[15];
    int i, j;
    // kosongkan salin sepanjang 15
    clear(salin,15);
    *suc = 0;
    *idx = 0;
    
    i = 0;
    while ((i<32) && !(*suc)){
        if (sec[i*16] == start) {
            // kosongkan salin
            clear(salin,15);
            j = 0;
            // isi salin dengan sector
            while (j < 15) {
                salin[j] = sec[i*16+j+1];
                j++;
            }
            *suc = isSame(salin, remaining);
        }
        i++;
    }
    *idx = i-1;
}

int mod(int a, int b){
	while (a >= b){
		a = a - b;
	}
	return a;
}

int div(int a, int b){
	int q = 0;
	while (q * b <= a){
		q = q + 1;
	}
	return q - 1;
}

void printString(char *str, int nL){
     interrupt(0x21, (0<<8) | 0x0, str, nL, 0);
}

void printInt(int i, int nL){
    int j;
    char num[10];
    num[0] = "0";
    num[1] = "0";
    num[2] = "0";
    num[3] = "0";
    num[4] = "0";
    num[5] = "0";
    num[6] = "0";
    num[7] = "0";
    num[8] = "0";
    num[9] = "\0";
    j = 8;
    while (i!=0 && j>=0){
        num[j] = "0" + mod(i, 10);
        i = div(i, 10);
        j--;
    }
    printString(num, nL);
}

void printChar(char c, int nL){
    interrupt(0x10, 0xE00+c, 0, 0, 0);
    if (nL){
        interrupt(0x10, 0xE00 + "\n", 0, 0, 0);
        interrupt(0x10, 0xE00 + "\r", 0, 0, 0);
    }
}

void len(char *str, int *len){
    *len = 0;
    while (str[*len] != "\0"){
        *len++;
    }
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

void copy(char *str, char *copied, int start, int length){
    int i, lenStr;
    len(str, &lenStr);
    copied[0] = "\0";
    if (start < lenStr){
        if (len > 0){
            i = start;
            while (str[i] != "\0" && len > 0){
                copied[i-start] = str[i];
                i++;
                length--;
            } while (length <= 0 && str[i] == "\0");
        }
    }
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