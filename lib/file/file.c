#include "file.h"

void readFile(char *buffer, char *path, int *result, char parentIndex) {
    char dir_buffer[1024], sec_buffer[512];
	int i, exist, baris_sec, itr;

	// copy ke dir
	i = 0;
	readSector(sec_buffer, 0x101);
	while (i < 512) {
		dir_buffer[i] = sec_buffer[i];
		i++;
	}
	i = 0;
	readSector(sec_buffer, 0x102);
	while (i < 512) {
		dir_buffer[512+i] = sec_buffer[i];
		i++;
	}

	// cari nama file dalam dir
	exist = 0;
	i = 0;
	while (exist == 0 && i < 64) {
		
		if (dir_buffer[i*16] == parentIndex){
			if (dir_buffer[16*i+1] != 0xFF && dir_buffer[16*i+2] != 0x00) {
				int j = i*16+2;
				// bila ada file cek nama
				int k = 0;
				int sama = 1;
				while (k < 14 && sama == 1) {
					if (dir_buffer[j+k] != path[k]){
						sama = 0;
					} else if (path[k] == '\0' && dir_buffer[j+k] == '\0') {
						k = 13;
					}
					k++;
				}
				if (sama) {
					exist = 1;
					baris_sec = dir_buffer[i*16+1];
				}
			}
		}
		i++;
	}
	if (exist) {
		readSector(sec_buffer, 0x103);
		itr = 0;
		while (sec_buffer[baris_sec*16 + itr] != '\0' && itr < 16) {
			char tmp[512];
			readSector(tmp, sec_buffer[baris_sec*16 + itr]);
			i = 0;
			while (i < 512) {
				buffer[512*itr + i] = tmp[i];
				i++;
			}
            itr++;
		}
		*result = 1; //Success
	} else {
		*result = -1;
	}
}

void writeFile(char *buffer, char *path, int *sectors, char parentIndex) {
	char map[512], dir[1024], sector[512];
	int dir_idx2, dir_idx, tersedia, find, exist, sama, curr;
	readSector(map, 0x100);
	readSector(dir, 0x101);
    readSector(dir+512, 0x102);
    readSector(sector, 0x103);

	dir_idx = 0;
	find = 0;
	//cari folder
    while(!find && (dir_idx < 1024)){
        if ((dir[dir_idx] == 0x0) && (dir[dir_idx+1] == 0x0) && (dir[dir_idx+2] == 0x0)){
            find = 1;
        }
        else{
			dir_idx+=16;
        }
    }

	//cari nama file dalam folder
    exist = 0;
    dir_idx2 = 0;
    while((exist == 0) && (dir_idx2 < 64)){
        if (dir[16*dir_idx2] == parentIndex){
            if ((dir[16*dir_idx2+2] != 0x0) && (dir[16*dir_idx2+1] != 0xFF)){
                curr = dir_idx2*16+2;
                dir_idx = 0;
                sama = 1;

                while(sama == 1 && dir_idx < 14){
                    if (dir[dir_idx+curr] == "\0" && path[dir_idx] == "\0"){
                        dir_idx = 13;
                    }
                    else if (dir[dir_idx+curr] != path[dir_idx]){
                        sama = 0;
                    }
                    dir_idx++;
                }
                if (sama){
                    exist = 1;
                    *sectors = -1;
                    return;
                }
            }
        }
        dir_idx2++;
    }

    if (find && !exist){
        int stop = 0;
		int k = 0;
        while (k < 256 && !stop){
            if (map[k] != 0x0){
                k++;
            }
            else{
                stop = 1;
            }
        }
        if ((256-k) >= 16){
            char temp[512];
            int a, b, c;
			int sector_count;
            for (c=0; c<32; c++){
                if (sector[c*16] == 0x0){
                    break;
				}
            // }
                for (a=0; a<16; a++){
                    dir[dir_idx+a] = 0x0;
                }
                for (a=2; a<16; a++){
                    dir[dir_idx+a] = path[a-2];
                }

                //mark dir
                dir[dir_idx] = parentIndex;
                dir[dir_idx+1] = c;

                a = 0;
                b = 0;
                sector_count = 0;
                while (buffer[b] != 0x0){
                    int m = 0;
                    clear(temp, 512);
                    while (m < 512 && buffer[b] != 0x0){
                        temp[m] = buffer[b];
                        b++;
                        m++;
                    }
                    map[k] = 0xFF;
                    sector[c*16+sector_count] = k;
                    writeSector(temp,k);
                    k++;
                    sector_count++;
                }
            }
			writeSector(map, 0x100);
			writeSector(dir, 0x101);
			writeSector(dir+512, 0x102);
			writeSector(sector, 0x103);
			*sectors = 1;
		}
		else{
			*sectors = -3;
			return;
		}
	}
	else{
		*sectors = -2;
		return;
	}
}

void deleteFile(char *path, int *result, char parentIndex){
	int itr;
	char file_index, suc;
	char map[512];
	char dir[512];
	char file[512];
	char sector[512];
    
	readSector(map, 0x100);
	readSector(dir, 0x101);
	readSector(file, 0x102);
	readSector(sector, 0x103);
	
	searchFile(dir,file,path,&file_index,&suc,parentIndex);
	if(suc){
		file[file_index * 16] = 0x00;
		file[file_index * 16 + 1] = 0x00;
		
		for (itr = 0; itr < 16 && sector[file_index*16+itr]!=0x00; itr++){
			sector[(int)file_index*16+itr] = 0x00;
			map[(int)sector[file_index*16+itr]] = 0x00;
		}

		writeSector(map, 0x100);
		writeSector(dir, 0x101);
		writeSector(file, 0x102);
		writeSector(sector, 0x103);
		*result = 0;
	} else {
		*result = -1;
	}
}

void clear(char *buffer, int length) {
	int i;
	for (i = 0; i < length; ++i) {
		buffer[i] = 0x00;
	}
}

void readSector(char *buffer, int sector) {
	interrupt(0x13, 0x201, buffer, 
	div(sector, 36) * 0x100 + mod(sector, 18) + 1, 
	mod(div(sector, 18), 2) * 0x100);
}

void writeSector(char *buffer, int sector) {
	interrupt(0x13, 0x301, buffer, 
	div(sector, 36) * 0x100 + mod(sector, 18) + 1, 
	mod(div(sector, 18), 2) * 0x100);
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

void searchFile(char *dir, char *file, char *path, char *idx, char *suc, char parentIndex){
	char splited_path[32 * 16];
	char fileName[15];
	char dir_index;
	int length, len_cpy;

	//memisahkan fileName dari path
	len(path,&length);
	length = length - 1;

	len_cpy = 0;
	while(path[length] != '/' && length >= 0){
		len_cpy += 1;
		length -= 1;
	}
	length += 1;
	copy(path,splited_path,0,length-1);
	copy(path,fileName,length,len_cpy);

	//search dir file
	searchDir(dir,splited_path,&dir_index,suc,parentIndex);
	if(*suc){
		search(file,dir_index,fileName,idx,suc);
	}

}

void len(char *str, int *len){
    *len = 0;
    while (str[*len] != "\0"){
        *len++;
    }
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
