/*
 * des.c
 *
 *  Created on: Jun 17, 2013
 *      Author: MCornett
 */

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

int key[] = {0,1,2,3,4,5,6,7};

void binaryPrinter(char binaryBitString[], int bitSize, int numLines[], int size, FILE *outFile);
void generateInputKey(char sixtyFourBit[], char fiftySixBit[]);
void circularLeftShift(char fiftySixBit[], int numOfShifts);


int main(int argc,char *argv[]){

	bool endOfFile = false;
	char inputLine[8];
	char binaryBitString[64];
	char fiftySixBit[56];
	int numString[8] = {32,32,32,32,32,32,32,32};
	int eightCounter = 0;
	int x,y;

	memset(inputLine, ' ', 8);

	if (argc != 3){
		printf("Number of arguments do not match.  Exiting program\n");
	}
	else {
		FILE *inFile = fopen(argv[1], "r");
		FILE *outFile = fopen(argv[2], "w");

		if (inFile == 0){
			printf("Could not open input file.  Exiting program\n");
		} else if (outFile == 0) {
			printf("Could not open output file.  Exiting program\n");
		}else {
			while ((y = fgetc(inFile)) != EOF){
					inputLine[eightCounter] = y;
					numString[eightCounter] = y;
					eightCounter++;
					if (eightCounter == 8){
						//fprintf(outFile, "%.*s\r\n", 8, inputLine);
						eightCounter = 0;
						binaryPrinter(binaryBitString, 64, numString, 8, outFile);
						memset(inputLine, ' ', 8);
						memset(numString, 32, 8);
						fprintf(outFile, "%.*s\r\n", 64, binaryBitString);
					}
			}
			while (eightCounter < 8){
				numString[eightCounter] = 32;
				eightCounter ++;
			}
			if (eightCounter == 8){
				//fprintf(outFile, "%.*s\r\n", 8, inputLine);
				eightCounter = 0;
				binaryPrinter(binaryBitString, 64, numString, 8, outFile);
				fprintf(outFile, "%.*s\r\n", 64, binaryBitString);
			}

		}
	fprintf(outFile, "%s\r\n", key);
	binaryPrinter(binaryBitString, 64, key, 8, outFile);
	fprintf(outFile, "%.*s\r\n", 64, binaryBitString);
	generateInputKey(binaryBitString, fiftySixBit);
	fprintf(outFile, "%.*s\r\n", 56, fiftySixBit);
	return 0;
	}

}

void binaryPrinter(char binaryBitString[], int bitSize, int numLines[], int size, FILE *outFile){
	char binaryEight[8];
	int x, y, z;
	int counter = 0;

	memset(binaryEight, '0', 8);

	for (x = 0;x < size;x++){
			fprintf(outFile, "%d ", numLines[x]);
	}

	fprintf(outFile, "\r\n");

	for (x = 0;x < size;x++){
		z = numLines[x];
		for (y = 7;y >= 0;y--){
			if ((z % 2) == 1){
				 binaryEight[y] = '1';
			 }
			 z = z / 2;
		}
		for (y = 0;y < 8;y++){
			binaryBitString[counter] = binaryEight[y];
			counter++;
		}
		memset(binaryEight, '0', 8);
	}
}

void generateInputKey(char sixtyFourBit[], char fiftySixBit[]){
	int x, y = 0;
	char temp[56];
	temp[0] = sixtyFourBit[56];temp[1] = sixtyFourBit[48];temp[2] = sixtyFourBit[40];temp[3] = sixtyFourBit[32];
	temp[4] = sixtyFourBit[24];temp[5] = sixtyFourBit[16];temp[6] = sixtyFourBit[8];

	temp[7] = sixtyFourBit[0];temp[8] = sixtyFourBit[57];temp[9] = sixtyFourBit[49];temp[10] = sixtyFourBit[41];
	temp[11] = sixtyFourBit[33];temp[12] = sixtyFourBit[25];temp[13] = sixtyFourBit[17];

	temp[14] = sixtyFourBit[9];temp[15] = sixtyFourBit[1];temp[16] = sixtyFourBit[58];temp[17] = sixtyFourBit[50];
	temp[18] = sixtyFourBit[42];temp[19] = sixtyFourBit[34];temp[20] = sixtyFourBit[26];
	
	temp[21] = sixtyFourBit[18];temp[22] = sixtyFourBit[10];temp[23] = sixtyFourBit[2];temp[24] = sixtyFourBit[59];
	temp[25] = sixtyFourBit[51];temp[26] = sixtyFourBit[43];temp[27] = sixtyFourBit[35];

	temp[28] = sixtyFourBit[62];temp[29] = sixtyFourBit[54];temp[30] = sixtyFourBit[46];temp[31] = sixtyFourBit[38];
	temp[32] = sixtyFourBit[30];temp[33] = sixtyFourBit[22];temp[34] = sixtyFourBit[14];

	temp[35] = sixtyFourBit[6];temp[36] = sixtyFourBit[61];temp[37] = sixtyFourBit[53];temp[38] = sixtyFourBit[45];
	temp[39] = sixtyFourBit[37];temp[40] = sixtyFourBit[29];temp[41] = sixtyFourBit[21];

	temp[42] = sixtyFourBit[13];temp[43] = sixtyFourBit[5];temp[44] = sixtyFourBit[60];temp[45] = sixtyFourBit[52];
	temp[46] = sixtyFourBit[44];temp[47] = sixtyFourBit[36];temp[48] = sixtyFourBit[28];

	temp[49] = sixtyFourBit[20];temp[50] = sixtyFourBit[12];temp[51] = sixtyFourBit[4];temp[52] = sixtyFourBit[27];
	temp[53] = sixtyFourBit[19];temp[54] = sixtyFourBit[11];temp[55] = sixtyFourBit[3];

	memmove(fiftySixBit, temp, 56);
}

void circularLeftShift(char fiftySixBit[], int round){
	char c[28];
	char d[28];
	int x, y = 0;
	int shift;

	for (x = 0;x < 28;x++){
		c[x] = fiftySixBit[y];
		y++;
	}
	for (x = 0;x < 28;x++){
		d[x] = fiftySixBit[y];
		y++;
	}

	switch (round){

	case 1:
	case 2:
	case 9:
	case 16:
		shift = 1;
	default:
		shift = 2;
	}


