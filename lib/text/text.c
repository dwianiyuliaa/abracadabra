#include "text.h"

void input(char *string) {
	readString(string);
}


void output(char *string, int newLine) {
	printString(string,newLine);
}

//Mencetak string ke layar
void printString(char *string, int newLine) {
	int i = 0;
	while (string[i] != '\0') {
		interrupt(0x10, 0xE00 + string[i], 0, 0, 0);
		i = i + 1;
	}
	if (newLine) {
		interrupt(0x10, 0xE00 + '\n', 0, 0, 0);
		interrupt(0x10, 0xE00 + '\r', 0, 0, 0);
	}
}

//Membaca string input
void readString(char *string) {
	int i = 0;
	char c = 0;
	while (c != '\r') {
		c = interrupt(0x16, 0, 0, 0, 0);
		if (c == '\r') {
			string[i] = '\0';
		} else {
			if (c == '\b') {
				if (i > 0) {
					interrupt(0x10, 0xE00 + '\b', 0, 0, 0);
					interrupt(0x10, 0xE00 + '\0', 0, 0, 0);
					interrupt(0x10, 0xE00 + '\b', 0, 0, 0);
					string[i] = '\0';
					i = i - 1;
				}
			} else {
				string[i] = c;
				i = i + 1;
				interrupt(0x10, 0xE00 + c, 0, 0, 0);
			}
		}
	}
	interrupt(0x10, 0xE00 + '\n', 0, 0, 0);
	interrupt(0x10, 0xE00 + '\r', 0, 0, 0);
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
