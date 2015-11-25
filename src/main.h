/*
 * main.h
 *
 *  Created on: Nov 3, 2015
 *      Author: Artiom
 */

#ifndef MAIN_H_
#define MAIN_H_

int Memory(char* memoryLine, int lines);
char* InstructionRegister(char* instruction, char* params[]);
void create_pool(int size);
char* getMemory(int i);
int ALU(int A, int B, int func);
int loadTo(int reg, int num);
int loadFrom(int reg);
void setStartingPoint(int num);
char* fromDecToBin(int num);

int getPC();
void setPC(int num);

#endif /* MAIN_H_ */
