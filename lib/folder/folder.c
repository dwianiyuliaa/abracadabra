#include "folder.h"

//membuat folder
void create(char *path, int *result, char parentIndex){
    char folder[15], dir[512], path_dir[32*16];
    char parent_index,suc,tmp;
    int itr, length_folder,len_cpy,length;
    
    //read sector dir
    readSector(dir,0x101);
    itr = 0;
    while (itr < 32 && dir[itr*16+1]!=0x00){
        itr++;
    }
    
    if (itr != 512){
        clear(path_dir,32*16);
        clear(folder,15);

        //memisahkan fileName dari path
        len(path,&length);
        length = length - 1;

        len_cpy = 0;
        while(path[length] != '/' && length >= 0){
            len_cpy += 1;
            length -= 1;
        }
        length += 1;
        copy(path,path_dir,0,length-1);
        copy(path,folder,length,len_cpy);

        searchDir(dir,path_dir,&tmp,&suc,parentIndex);
        if (suc) {
            searchDir(dir,path,&tmp,&suc,parentIndex);
            if (suc){
                dir[itr*16] = parent_index;
                len(folder, &length_folder);
                for (tmp = 0; tmp < length_folder; tmp++){
                    dir[tmp+itr*16+1] = folder[(int)tmp];
                }
                writeSector(dir,0x101);
                (*result) = 0;
            } else {
                (*result) = (-2);
            }
        } else {
            (*result) = -1;
        }
    } else {
        (*result) = -2;
    }
}

//menghapus folder
void deleteFolder(char *path, int *success, char parentIndex){
    char map[512];
    char dir[512];
    char file[512];
    char sector[512];
    int dir_itr,file_itr, sec_itr,idx;
    char suc, fol_index;
    char tmp[15];

    readSector(map,0x100);
    readSector(dir,0x101);
    readSector(file,0x102);
    readSector(sector,0x103);

    searchDir(dir,path,&fol_index,&suc,parentIndex);
    if (suc){
        
        //hapus dir dalam folder sampai habis
        dir_itr = 0;
        while (dir_itr < 512){
            if((dir[dir_itr+1] != '\0' )&& (dir_itr != fol_index) && (dir[dir_itr] == fol_index)){
                clear(tmp,15);
                for (idx = 0; idx < 15; idx++){
                    tmp[idx] = dir[idx+dir_itr+1];
                }
                deleteFolder(tmp,suc,fol_index);
                readSector(map,0x100);
                readSector(dir,0x101);
                readSector(file,0x102);
                readSector(sector,0x103);
            }
            dir_itr += 16;
        }
    

    //hapus file dalam folder
    file_itr = 0;
    while(file_itr < 512){
        if (file[file_itr] == fol_index && file[file_itr+1] != 0x00){
            file[file_itr] = 0x00;
            file[file_itr+1] = 0x00;
            sec_itr = 0;
            while (sector[sec_itr + 16 * file_itr] && sec_itr < 16){
                map[(int)sector[sec_itr + 16 * file_itr]] = 0x00;
                sector[sec_itr + 16 * file_itr] = 0x00;
                sec_itr++;
            }
        }

        file_itr += 16;
    }
    dir[(fol_index * 16)] = 0x00;
    dir[(fol_index * 16 + 1)] = 0x00;
    writeSector(map,0x100);
    writeSector(dir,0x101);
    writeSector(file,0x102);
    writeSector(sector,0x103);

    (*success) = 0;

    } else {
        (*success) = -1;
    }
    
}

//menampilkan daftar file dan dir ke layar
void listContent(){
    // char inp[100];
    char argv[64][128];
    char argc,curDir,suc;
    // char args[512];

    // readSector(args, 512);
    // curdir = args[0];

    // writeSector(args, 512);
    // argc = args[1];

    getCurdir(&curDir);
    getArgc(&argc);
    getArgv(0, argv[0]);

    putArgs(curDir, argc, argv + 1);

    interrupt(0x21, 0xFF << 8 | 0x6, "ls", 0x2000, &suc);
}

//mendapatkan indeks current directory
void getCurdir(char *curdir){
	char args[512];
	readSector(args, 512);
	*curdir = args[0];
}

//menyimpan current directory, jumlah parameter program, dan isi parameter program
void putArgs(char curdir, char argc, char argv[64][128]){
	char args[512];
	int i, j, p;
	clear(args, 512);

	args[0] = curdir;
	args[1] = argc;
	i = 0;
	j = 0;

	for (p = 2; p < 512 && i < argc; ++p)
	{
		args[p] = argv[i][j];
		if (argv[i][j] == '\0')
		{
			++i;
			j = 0;
		}
		else
		{
			++j;
		}
	}
	writeSector(args, 512);
}

//mencari isi parameter ke-idx program
void getArgv(char idx, char *argv) {
    char args[512];
    int i, j, k;
    readSector(args, 512);
    i=0;
    j=0;
    k=2;
    while (k<512) {
        if (i == idx) {
            argv[j] == args[k];
            j++;
        }

        if (args[k] == '\0') {
            if (i != idx) {
                i++;
            } else {
                break;
            }
        }
        k++;
    }
}

//mencari jumlah parameter program
void getArgc(char *argc){
    char args[512];
    writeSector(args, 512);
    *argc = args[1];
}
