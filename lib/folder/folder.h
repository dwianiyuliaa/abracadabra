#ifndef _FILE_H_
#define _FILE_H_

#include "../file/file.h"
#include "../text/text.h"

//membuat folder
void create(char *path, int *result, char parentIndex);

//menghapus folder
void deleteFolder(char *path, int *success, char parentIndex);

//menampilkan daftar file dan dir ke layar
void listContent();

//menyimpan current directory, jumlah parameter program, dan isi parameter program
void putArgs(char curdir, char argc, char argv[64][128]);

//mendapatkan indeks current directory
void getCurdir(char *curdir);

//mencari isi parameter ke-idx program
void getArgv(char idx, char *argv);

//mencari jumlah parameter program
void getArgc(char *argc);

#endif