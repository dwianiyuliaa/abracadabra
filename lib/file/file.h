#ifndef _FILE_H_
#define _FILE_H_

#include "../mat/mat.h"

//Membaca file
void readFile(char *buffer, char *path, int *result, char parentIndex);

//Menulis isi file 
void writeFile(char *buffer, char *path, int *sectors, char parentIndex);

//menghapus file 
void deleteFile(char *path, int *result, char parentIndex);

//memngisi buffer sepanjang length dengan 0
void clear(char *buffer, int length);

//read sector
void readSector(char *buffer, int sector);

//write sector
void writeSector(char *buffer, int sector);

//cari string pada sector
void search(char *sec, char start, char remaining[15], char *idx, char *suc);

//cari index direktori file
void searchDir(char *dir, char *rel_Path, char *idx, char *suc, char parentIndex);

//cari index file
void searchFile(char *dirs, char *file, char *relPath, char *index, char *success, char parentIndex);

//menghitung panjang string
void len(char *str, int *len);

//copy string dari start sepanjang length
void copy(char *str, char *copied, int start, int length);

#endif