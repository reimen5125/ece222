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
//		char *dictArr;
		char **dictArr;
		char dictStr[40];
		int dictLen;
		int i;
		int j;
		int k;
		int ousCount;
		char *notDict;
		int contains;
		char *ousArr;
//		int c;
//		int stop = 0;

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
//		fscanf(file, "%s", dictStr);
/*		stop = 0;
		while (stop == 0)
		{
		if ((c = getc(dictStr)) == EOF)
		{
			stop = 1;
			break;
		}
*/
//		while (fscanf(file, "%s", dictStr) != EOF)
//		while (strchr( fscanf(file, "%s", dictStr), EOF ) < 1)
//		while (!feof(file))
//		while (stop == 0)
//		while (strcmp(dictStr, "zurich"))
		while (fgets(dictStr, 41, file) != NULL)
		{
			// fscanf(file, "%s", &dictStr[0]);
//			fscanf(file, "%s", dictStr);
//			printf("dictStr = %s", dictStr);
/*			for (j = 0; j < sizeof(dictStr); j++)
			{
				if ((int)(dictStr[j]) == "Zurich")
				{
					stop = 1;
					break;
				}
*/
			i++;
			memset(dictStr, 0, sizeof(dictStr));
//			if (stop == 1)
//				break;
//			}
		}
//		}

		dictLen = i - 1;

//		dictArr = (char*) malloc(i*41*sizeof(char *));
//		dictArr = malloc(i*41*sizeof(char)); // *));
		dictArr = (char **)malloc(dictLen*sizeof(char *));
//		i = 0;
//		stop = 0;
		rewind(file);
//		while (fscanf(file, "%s", dictStr) != EOF)
//		while (strchr( fscanf(file, "%s", dictStr), EOF ) < 1)
//		while (!feof(file))
//		fscanf(file, "%s", dictStr);
//		while (stop == 0)
		for (i = 0; i < dictLen; i++)
		{
//		if ((c = getchar(dictStr)) == EOF)
//		{
//			stop = 1;
//			break;
//		}
//			fscanf(file, "%s", dictStr);
			fgets(dictStr, 41, file);

			for (k = 0; k < 41; k++)
			{
				dictStr[k] = toupper(dictStr[k]);
		//		putchar(toupper(dictStr[k]));
			}
	//		printf("%s\n", dictStr);
			dictArr[i] = (char *)malloc(41*sizeof(char));
//			strcpy(&dictArr[i], dictStr);
			strncpy(dictArr[i], dictStr, strlen(dictStr));
			puts(dictArr[i]);
//			&dictArr[i] = dictStr;
			memset(dictStr, 0, sizeof(dictStr));
//			printf("%s\n", &dictArr[i]);
//			i++;
		}
		fclose(file);

		for (i = 0; i < dictLen; i++)
			printf("%s\n", dictArr[i]);

	// Open and analyze all novel files
		do
		{
			memset(fileName, 0, sizeof(fileName));
			sprintf(fileName, "%s_%d.txt", argv[1], count);
	//		printf("testing testing right before fopen\n");
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
						for (i = 0; i < dictLen; i++)
						{
							if (strcmp(dictArr[i], str) == 0)
					//		printf("%s\n", &dictArr[3]);
					//		if (strcmpi(&dictArr[i], str) == 0)
								contains = 1;
					//		if (&dictArr[i] == 
						}
						if (contains == 0)
						{
							for (i = 0; i <= j; i++)
							{
					//			if (strcmpi(&dictArr[i], str) == 0)
								if (strcmp(&notDict[i], str) == 0)
									contains = 2;
					//			if (&notDict[i] == str)
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
						{
						//	printf("strspn = %s\n", str);	
						}
					
					memset(str, 0, sizeof(str));
	//				printf("str check 1 = %s\n", str);
				}
				else if (isalpha(temp))
				{
			//		printf("str check 2 = %s\n", str);
	//				strcat(str, temp);
					sprintf(str, "%s%c", str, temp);
					charCount++;
			//		printf("str check 3 = %s\n", str);

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
					for (k = 0; k < 41; k++)
					{
						str[k] = toupper(str[k]);
					}
				}
			}





//			fclose(file);
			count++;
		}
		while (file != NULL);
		
		
		memset(fileName, 0, sizeof(fileName));

	// Output Results
	//	sprintf(fileName, "%s.txt", argv[2]);
	//	file = fopen(fileName, "w");

	//	fprintf(file, "Total Novel Words = %d\n", wordCount);

	//	fclose(file);

		free(charFreq);
		free(sizeFreq);
		free(notDict);
		free(ousArr);
		for (i = 0; i < dictLen; i++)
		{
			free(dictArr[i]);	
		}
		free(dictArr);

	return 0;

}
