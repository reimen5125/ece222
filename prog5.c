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
#include <unistd.h>

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
		char *dictArr;
		char dictStr[40];
		int dictLen;
		int i;
		int j;
		int ousCount;
		char *notDict;
		int contains;
		char *ousArr;

	// Set initial values and allocate memory
		count = 1;
		wordCount = 0;
		charCount = 0;
		charFreq = (int*) malloc(26*sizeof(int));
		sizeFreq = (int*) malloc(40*sizeof(int));
		notDict = (char*) malloc(999*41*sizeof(char *));
		i = 0;
		j = 0;
		contains = 0;
		ousArr = (char*) malloc(999*41*sizeof(char *));
		ousCount = 0;

	// Upload dictionary.txt to an array
		file = fopen("dictionary.txt", "r");
		while (fscanf(file, "%s", dictStr) != EOF)
		{
			i++;
			memset(dictStr, 0, sizeof(dictStr));
		}
		dictArr = (char*) malloc(i*41*sizeof(char *));
		i = 0;
		rewind(file);
		while (fscanf(file, "%s", dictStr) != EOF)
		{
		//	printf("%s\n", dictStr);
			strcpy(&dictArr[i], dictStr);
		//	printf("%s\n", &dictArr[i]);
			i++;
			memset(dictStr, 0, sizeof(dictStr));
		}
		dictLen = i;
	//	fclose(file);

	// Open and analyze all novel files
		do
		{
			memset(fileName, 0, sizeof(fileName));
			sprintf(fileName, "%s_%d.txt", argv[1], count);
			printf("testing testing right before fopen\n");
			if( access( fileName, F_OK ) != -1 )
				file = fopen(fileName, "r");
			else
				file = NULL;

			while (file != NULL && fscanf(file, "%c", &temp) != EOF)
			{
				if ((temp == ' ' || temp == '-' || temp == '.' || temp == '?' || temp == '!' || temp == '\n') && strlen(str) > 0)
				{
					// Total Word Count
						wordCount++;

					// String Size Count
						sizeFreq[strlen(str)]++;
			//			printf("sizeFreq_%ld b/c of %s = %d", (strlen(str)), str, sizeFreq[strlen(str)]);

					// Dictionary Check
						for (i = 0; i <= dictLen; i++)
						{
							if (strcmp(&dictArr[i], str) == 0)
					//		if (strcmpi(&dictArr[i], str) == 0)
					//		if (&dictArr[i] == str)
								contains = 1;
						}
						if (contains == 0)
						{
							for (i = 0; i <= j; i++)
							{
					//			if (strcmpi(&dictArr[i], str) == 0)
								if (strcmp(&dictArr[i], str) == 0)
					//			if (&notDict[i] == str)
									contains = 2;
							}
							if (contains == 0)
							{
								strcpy(&notDict[j], str);
								printf("NEW STRING_%d  %s\n",j , str);
								++j;
							}
						}








					// "OUS" Check
						if (strstr(str, "ous") != NULL)
						{
							strcpy(&ousArr[ousCount], str);
					//		printf("ousArr[%d] = %s\n", ousCount, &ousArr[ousCount]);
							ousCount++;
						}

					// ACESLMTW Check
						if (strspn(str, "ACESLMTWaceslmtw") == strlen(str))	
							printf("strspn = %s\n", str);	
					
					memset(str, 0, sizeof(str));
					printf("str check 1 = %s\n", str);
				}
				else if (isalpha(temp))
				{
//***************************SEG FAULT IN NEXT TWO LINES***********
					printf("str check 2 = %s\n", str);
	//				strcat(str, temp);
					sprintf(str, "%s%c", str, temp);
					charCount++;
					printf("str check 3 = %s\n", str);

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





		//	fclose(file);
			count++;
		}
		while (file != NULL);
		
	//	memset(fileName, 0, sizeof(fileName));

	// Output Results
	//	sprintf(fileName, "%s.txt", argv[2]);
	//	file = fopen(fileName, "w");

	//	fprintf(file, "Total Novel Words = %d\n", wordCount);

	//	fclose(file);

//		free(charFreq);
//		free(sizeFreq);
//		free(notDict);
//		free(ousArr);
//		free(dictArr);	


	return 0;

}
