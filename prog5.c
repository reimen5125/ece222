/*
	Rachel Eimen
	C14796950
	4/12/17
	ECE 2220-001
	Dr. Bill Reid
	Program 5: Strings - Analyzing a Novel

	Purpose: Analyzes a novel specified by the reader by running through multiple files.  Creates an output file, also specified by the reader, and prints out the results.
*/

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>

int main ( int argc, char **argv )
{

	// Variable Declaration
		FILE *file;
		int count;
		char fileName[30];
		char str[40];
		char temp;
		int wordCount;
		int charCount;
		int *charFreq;
		int *sizeFreq;
//		char **dictArr;
		char *dictArr;
		char dictStr[40];
		int i;

	// Set initial values and allocate memory
		count = 1;
		wordCount = 0;
		charCount = 0;
		charFreq = (int*) malloc(26*sizeof(int));
		sizeFreq = (int*) malloc(40*sizeof(int));
		i = 0;

	// Upload dictionary.txt to an array
		file = fopen("dictionary.txt", "r");
		while (fscanf(file, "%s", dictStr) != EOF)
		{
			i++;
			memset(dictStr, 0, sizeof(dictStr));
		//	printf("%s", dictStr);
		}
	//	char dictArr[i][40];
//(char**) 
//		dictArr = (char**) calloc(i, 40*sizeof(char *));
//		dictArr = (char*) calloc(i, 41*sizeof(char *));
		dictArr = (char*) malloc(i*41*sizeof(char *));
		i = 0;
		rewind(file);
		while (fscanf(file, "%s", dictStr) != EOF)
		{
			printf("%s\n", dictStr);
//			memset(dictArr[i], '\0', sizeof(dictArr[i]));
//			dictArr[i] = (char) calloc(sizeof(dictStr)+1, sizeof(char));
			strcpy(&dictArr[i], dictStr);
//			&dictArr[i] = dictStr;
			printf("%s\n", &dictArr[i]);
			i++;
			memset(dictStr, 0, sizeof(dictStr));
		}


	// Open all novel files
		do
		{
			memset(fileName, 0, sizeof(fileName));
			sprintf(fileName, "%s_%d.txt", argv[1], count);
			file = fopen(fileName, "r");
			while (file != NULL && fscanf(file, "%c", &temp) != EOF)
			{
				if (temp == ' ' || temp == '-')
				{
					// Total Word Count
						wordCount++;

					// String Size Count
						sizeFreq[strlen(str)]++;
			//			printf("sizeFreq_%ld b/c of %s = %d", (strlen(str)), str, sizeFreq[strlen(str)]);
						
					
					memset(str, 0, sizeof(str));
				}
				else if (temp == '.' || temp == '?' || temp == '!' || temp == '\n')
					memset(str, 0, sizeof(str));
				else if (isalpha(temp))
				{
					sprintf(str, "%s%c", str, temp);
					charCount++;

					// Letter Count
						if (isupper(temp))
						{
							charFreq[temp - 65]++;
			//				printf("charFreq_%c = %d\n", temp, charFreq[temp - 65]);
						}
						else
						{
							charFreq[temp - 97]++;
			//				printf("charFreq_%c = %d\n", temp, charFreq[temp - 97]);
						}
				}
			}
			count++;	
		}
		while (file != NULL);


	return 0;

}
