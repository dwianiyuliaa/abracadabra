// menampilkan isi sebuah direktori
void ps(char* buff, int nl);
void pi(int i, int nl);
void pc(char c, int nl);
void clear(char *buff, int len);

int main() {
    int i;
    int j;
    char current_dir;
    char dir[512];
    char file[512];
    char nameFile[15];
    char temp;
    interrupt(0x21, 0x21, &current_dir, 0, 0);
    interrupt(0x21, 0x02, dir, 0x101, 0); // interup sektor dir
    interrupt(0x21, 0x02, file, 0x102, 0); // interup sektor file
    ps("isi: ", 1); // menampilkan string isi dengan new line
    clear(nameFile, 15); // membersihkan buffer dari name of file
    ps("folder: ", 0);
    for (i=0; i<512; i+=16) {
        if (dir[i] == current_dir && dir[i+1] != '\0') {
            clear(nameFile, 15);
            for (j=0; j<15; j++) {
                nameFile[j] = dir[i+j+1]; // mengisi nama folder dari direktori
            }
            ps(nameFile, 1); // meampilkan nama folder
        }
    }
    ps("file: ", 1);
    for (i=0; i<512; i+=16) {
        if (file[i] == current_dir && file[i+1] != '\0') {
            clear(nameFile, 15);
            for (j=0; j<15; j++) {
                nameFile[j] = file[i+j+1]; // mengisi nama folder dari direktori
            }
            ps(nameFile, 1); // meampilkan nama folder
        }
    }
    interrupt(0x21, 0x20, 0, 0);
    interrupt(0x21, 0x7, &temp, 0,0);
}



void ps(char* buff, int nl) {
    interrupt(0x21, (0 << 8) | 0x0, buff, nl, 0);
}

void pi(int i, int nl){
    interrupt(0x21, (0 << 8) | 0x24, i, nl, 0);
}

void pc(char c, int nl){
    interrupt(0x21, (0 << 8) | 0x25, c, nl, 0);
}

void clear(char *buff, int len) {
    int i;
    for (i=9; i<len; i++) {
        buff[i] = 0x00; // mengosongkan
    }
}