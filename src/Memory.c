/*
 * Memory.c
 *
 *  Created on: Nov 3, 2015
 *      Author: Artiom
 */
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <stdlib.h>
#include <time.h>
#include "main.h"
#include <stdint.h>

int32_t my_32bit_int;

typedef struct instruction{
	char memoryLine[34];
} Instruction;

typedef struct memoryHeap{
	Instruction inst[5000];
} Heap;
static Heap* root;

void create_pool(int size) {
    root = malloc(sizeof(Heap));
    Heap* current = root;
    int i;
    for(i = 0; i < 5000; i++) {
    	memset(current->inst[i].memoryLine, 0, sizeof(current->inst[i].memoryLine));
    	strcpy(current->inst[i].memoryLine, fromDecToBin(abs((int)current->inst[i].memoryLine)%10000));
    }
}

void Memory(char* memoryLine, int lines) {
	strcpy(root->inst[lines].memoryLine, memoryLine);
}

char* getMemory(int i) {
	return root->inst[i].memoryLine;
}

