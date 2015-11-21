/*
 * ALU.c
 *
 *  Created on: Nov 3, 2015
 *      Author: Artiom
 */

int ALU()
{
	//A and B are values passed into the ALU
	int A = 0;
	int B = 0;
	//opcode passed into the ALU (probably will not need it, not sure)
	int opcode = 0000;
	//the output from the ALU
	int aluOut = 0;
	//output from the calculations
	int answer;
	//function passed into ALU
	/*
	 * We need to pass in the func, (00 for ADD, 01 for NAND, 10 for A - B, and 11 for A + 1)
	 * We need the func to be passed in because that way we know what operations we are doing
	 * Im not sure how to pass in value to this "class"
	 */
	int func;

	//ADD
	if (func == 0)
	{
		answer = A + B;
	}
	//NAND
	else if (func == 1)
	{
		//not sure how to do
	}
	//A-B
	else if (func == 10)
	{
		answer = A - B;
	}
	//A + 1 (increment?)
	else if (func == 11)
	{
		//might need to be switched to A = A + 1;
		answer = A + 1;
	}

	return aluOut;
}
