/*
 * ALU.c
 *
 *  Created on: Nov 3, 2015
 *      Author: Artiom
 */
#include <string.h>
#include <stdio.h>
#include "main.h"

int ALU(int A, int B, int func)
{
	//output from the calculations
	int answer;

	//function passed into ALU
	/*
	 * We need to pass in the func, (00 for ADD, 01 for NAND, 10 for A - B, and 11 for A + 1)
	 * We need the func to be passed in because that way we know what operations we are doing
	 * Im not sure how to pass in value to this "class"
	 */

	//ADD
	if (func == 0)
	{
		//TODO
		char RegA[20];
		memset(RegA, 0, sizeof(RegA));
		strcpy(RegA, fromDecToBin(A));

		char RegB[20];
		memset(RegB, 0, sizeof(RegB));
		strcpy(RegB, fromDecToBin(B));

		char RegC[20];
		memset(RegC, 0, sizeof(RegC));
		strcpy(RegC, "");

		char carry = '0';
		int j;
//		printf("ALUA %d\n", A);
//		printf("ALUB %d\n", B);
//		printf("ALUAB %s\n", RegA);
//		printf("ALUBB %s\n", RegB);

//		printf("%lu\n", strlen(RegB));
		for (j = strlen(RegA)-1; j >= 0; j--)
		{
//			printf("%d\n", j);
			if (RegA[j] == '1' && RegB[j] == '1')
			{
				if (carry == '1')
				{
					RegC[j] = '1';
					carry = '1';
				}
				else if (carry == '0')
				{
					RegC[j] = '0';
					carry = '1';
				}
			}
			else if ((RegA[j] == '1' && RegB[j] == '0') || (RegA[j] == '0' && RegB[j] == '1'))
			{
				if (carry == '1')
				{
					RegC[j] = '0';
					carry = '1';
				}
				else if (carry == '0')
				{
					RegC[j] = '1';
					carry = '0';
				}
			}
			else if (RegA[j] == '0' && RegB[j] == '0')
			{
				if (carry == '1')
				{
					RegC[j] = '1';
					carry = '0';
				}
				else if(carry == '0')
				{
					RegC[j] = '0';
					carry = '0';
				}
			}
		}
		char buffer[20];
		memset(buffer, 0, sizeof(buffer));

//		printf("RC %s\n", RegC);
		if(RegC[0] == '1') {
			int i;
			for (i = 0; i < strlen(RegC); i++) {
				if(RegC[i] == '1') buffer[i] = '0';
				else buffer[i] = '1';
			}
//			printf("BF %s\n", buffer);
			answer = (fromBinToDec(buffer)*(-1));
		} else {
			answer = fromBinToDec(RegC);
		}
//		printf("%s\n", RegC);
//		printf("%d\n", answer);
	}
	//NAND
	else if (func == 1) {
		char RegA[20];
		memset(RegA, 0, sizeof(RegA));
		strcpy(RegA, fromDecToBin(A));

		char RegB[20];
		memset(RegB, 0, sizeof(RegB));
		strcpy(RegB, fromDecToBin(B));

		char result[20];
		memset(result, 0, sizeof(result));

		int i;
		for (i = 0; i < strlen(RegA); i++) {
			if(RegA[i] == '1') {
				if(RegB[i] == '1') strcat(result, "0");
				else if(RegB[i] == '0') strcat(result, "1");
			}
			else if(RegA[i] == '0') {
				if(RegB[i] == '1') strcat(result, "1");
				else if(RegB[i] == '0') strcat(result, "1");
			}
		}

//		int sign = 0;
		char RegC[20];
		memset(RegC, 0, sizeof(RegC));
		strcpy(RegC, "");

//		if(result[0] == '1') sign = 1;
		int j;
		for(j = 1; j < strlen(result); j++) {
			if(result[j] == '1') strcat(RegC, "0");
			else if(result[j] == '0') strcat(RegC, "1");
		}
		answer = fromBinToDec(RegC)*(-1);
	}
	//A-B
	else if (func == 10)
	{
//		char RegA[20];
//		memset(RegA, 0, sizeof(RegA));
//		strcpy(RegA, fromDecToBin(A));
//
//		char RegB[20];
//		memset(RegB, 0, sizeof(RegB));
//		strcpy(RegB, fromDecToBin(B));
//
//		char RegC[20];
//		memset(RegC, 0, sizeof(RegC));
//		strcpy(RegC, "");
//
//		char result[20];
//		memset(result, 0, sizeof(result));
//
//		int i;
//		for (i = 0; i < strlen(RegB); i++)
//		{
//			if(RegB[i] == '1')
//			{
//				strcat(result, "0");
//			}
//			else if(RegB[i] == '0')
//			{
//				strcat(result, "1");
//			}
//		}
//
//		int myNum = fromBinToDec(result);
//		myNum++;
//
//		strcpy(RegB, fromDecToBin(myNum));
//
//		char carry = '0';
//		int j;
//		for (j = 0; j < strlen(RegB); j++)
//		{
//			if (RegA[j] == '1' && RegB[j] == '1')
//			{
//				if (carry == '1') strcat(RegC, "1");
//				else if(carry == '0') strcat(RegC, "0");
//				carry = '1';
//			}
//			else if (RegA[j] == '1' && RegB[j] == '0')
//			{
//				if (carry == '1'){
//					strcat(RegC, "0");
//					carry = '1';
//				}
//				else if(carry == '0'){
//					strcat(RegC, "1");
//					carry = '0';
//				}
//			}
//			else if (RegA[j] == '0' && RegB[j] == '1')
//			{
//
//				/*
//				 * Ex: 1011 This is assuming we are carrying the first two bits at the top.
//				 *   - 0101
//				 *   _______
//				 *     0110
//				 */
//				if (carry == '1'){
//				strcat(RegC, "1");
//				carry = '0';
//				}
//				/*
//				 * Problem here:
//				 *
//				 * Ex: 0011
//				 *   - 0101
//				 *   _______
//				 *     ???? (1111 1110?)
//				 */
//				else if(carry == '0'){
//				strcat(RegC, "0");
//				carry = '0';
//				}
//			}
//			else if (RegA[j] == '0' && RegB[j] == '0')
//			{
//				if (carry == '1'){
//				strcat(RegC, "1");
//				carry = '0';
//				}
//				else if(carry == '0'){
//				strcat(RegC, "0");
//				carry = '0';
//				}
//			}
//		}
//		answer = fromBinToDec(RegC)-1;
		answer = A-B;
	}
	//A + 1 (increment)
	else if (func == 11)
	{
		char RegA[20];
		memset(RegA, 0, sizeof(RegA));
		strcpy(RegA, fromDecToBin(A));
		char RegB[20];
		memset(RegB, 0, sizeof(RegB));
		strcpy(RegB, "0000000000000000001");
		char RegC[20];
		memset(RegC, 0, sizeof(RegC));
		strcpy(RegC, "");

		char carry = '0';
		int j;
		for (j = strlen(RegA)-1; j >= 0; j--)
		{
			if (RegA[j] == '1' && RegB[j] == '1')
			{
				if (carry == '1')
				{
					RegC[j] = '1';
					carry = '1';
				}
				else if (carry == '0')
				{
					RegC[j] = '0';
					carry = '1';
				}
			}
			else if ((RegA[j] == '1' && RegB[j] == '0') || (RegA[j] == '0' && RegB[j] == '1'))
			{
				if (carry == '1')
				{
					RegC[j] = '0';
					carry = '1';
				}
				else if (carry == '0')
				{
					RegC[j] = '1';
					carry = '0';
				}
			}
			else if (RegA[j] == '0' && RegB[j] == '0')
			{
				if (carry == '1')
				{
					RegC[j] = '1';
					carry = '0';
				}
				else if(carry == '0')
				{
					RegC[j] = '0';
					carry = '0';
				}
			}
		}
		answer = fromBinToDec(RegC);
		setPC(answer);
//		printf("BEFORE %d \n", A);
//		printf("AFTER  %d \n", answer);
	}
	return answer;
}
