/*
 * PC.c
 *
 *  Created on: Nov 3, 2015
 *      Author: Artiom
 */
#include <stdio.h>
#include <string.h>
int counter = 0;
void setPC(int num) {
	counter = num;
}
int getPC() {
	return counter;
}

