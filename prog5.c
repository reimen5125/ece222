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
		char **dictArr;
		char dictStr[40];
		int dictLen;
		int *dictNum;
		int i;
		int j;
		int k;
		int ousCount;
		char **notDict;
		int contains;
		char **ousArr;
		char ousStr[4];
		char **letArr;
		int letCount;
		int notCount;

	// Set initial values and allocate memory
		count = 1;
		wordCount = 0;
		charCount = 0;
		charFreq = (int*) malloc(26*sizeof(int));
		sizeFreq = (int*) malloc(46*sizeof(int));
		i = 0;
		j = 0;
		contains = 0;
		ousCount = 0;
		letCount = 0;

	// Upload dictionary.txt to an array
		file = fopen("dictionary.txt", "r");

		while (fgets(dictStr, 46, file) != NULL)
		{
//			printf("dictStr = %s", dictStr);
			i++;
			memset(dictStr, 0, sizeof(dictStr));
		}

		dictLen = i - 1;

		dictArr = (char **)malloc(dictLen*sizeof(char *));
		dictNum = (int *)calloc(dictLen, sizeof(int));
		notDict = (char**) malloc(dictLen*46*sizeof(char *));
		ousArr = (char**) malloc(999*46*sizeof(char *));
		letArr = (char **) malloc(dictLen*46*sizeof(char *));

		rewind(file);

		for (i = 0; i < dictLen; i++)
		{
			fgets(dictStr, 46, file);

			for (k = 0; k < 46; k++)
			{
				dictStr[k] = toupper(dictStr[k]);
			}
	//		printf("%s\n", dictStr);
			dictArr[i] = (char *)malloc(46*sizeof(char));
			strcpy(dictArr[i], dictStr);
			memset(dictStr, 0, sizeof(dictStr));
//			printf("%s\n", &dictArr[i]);
		}
		fclose(file);

//		for (i = 0; i < dictLen; i++)
//			printf("%s\n", dictArr[i]);

	// Open and analyze all novel files
		do
		{
			memset(fileName, 0, sizeof(fileName));
			sprintf(fileName, "%s_%d.txt", argv[1], count);
			if( access( fileName, F_OK ) != -1 )
				file = fopen(fileName, "r");
			else
				file = NULL;

			while (file != NULL && fscanf(file, "%c", &temp) != EOF)
			{
	//			printf("temp = %c\tstr = %s\tstrlen = %d\n", temp, str, (int)(strlen(str)));
				if ((temp == ' ' || temp == '-' || temp == '.' || temp == '?' || temp == '!' || temp == '\n') && strlen(str) > 0)
				{
					// Total Word Count
						wordCount++;

					// String Size Count
						sizeFreq[strlen(str)]++;
			//			printf("sizeFreq_%ld b/c of %s = %d", (strlen(str)), str, sizeFreq[strlen(str)]);

					// Dictionary Check
						contains = 0;
						str[strlen(str) + 1] = '\0';
						for (i = 0; i < dictLen; i++)
						{
							if (strstr(dictArr[i], str) != NULL)
					//		if (strcmp(dictArr[i], str) == 0)
								contains = 1;
						}

						if (contains == 0)
						{
							for (i = 0; i < j; i++)
							{
								if (strstr(notDict[i], str) != NULL)
						//		if (strcmp(notDict[i], str) == 0)
								{
									dictNum[i]++;
									contains = 2;
						//			printf("dictNum[%d] = %s [%d])", i, notDict[i], dictNum[i]);
								}
							}
							if (contains == 0)
							{
								notDict[j] = (char *)malloc(46*sizeof(char));
								strcpy(notDict[j], str);
						//		printf("NEW STRING_%d  %s\n",j , notDict[j]);
								dictNum[i]++;
								j++;
							}
						}
						notCount = j;

					// "OUS" Check
						contains = 0;
				//		strcpy(ousStr, "ous");
				//		str[strlen(str) + 1] = '\0';
				//		if (strstr(str, ousStr) != NULL)
				//		printf("%s", str);
				/*		for (i = 0; i < sizeof(str) - 2; i++)
						{
							if (str[i] == 'o' && str[i + 1] == 'u' && str[i + 2] == 's')
								contains = 2;
						}
				*/
						if (strstr(str, "OUS") != NULL)
				//		if (contains == 2)
						{
						//	printf("testing testing");
						//	printf("ousArr[%d] = %s\n", ousCount, ousArr[ousCount]);
							for (i = 0; i < ousCount; i++)
							{
								if (strstr(ousArr[i], str) != NULL)
									contains = 1;
							}
							if (contains == 0)
							{
								ousArr[ousCount] = (char *)malloc(46*sizeof(char));
								strcpy(ousArr[ousCount], str);
						//		printf("ousArr[%d] = %s\n", ousCount, ousArr[ousCount]);
								ousCount++;
							}
						}

					// ACESLMTW Check
						if (strspn(str, "ACESLMTW") == strlen(str))
						{
							letArr[letCount] = (char *)malloc(46*sizeof(char));
							strcpy(letArr[letCount], str);
					//		printf("strspn = %s %s\n", str, letArr[letCount]);
							letCount++;	
						}
					
					memset(str, 0, sizeof(str));
				}
				else if (isalpha(temp))
				{
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
					for (k = 0; k < 46; k++)
					{
						str[k] = toupper(str[k]);
					}
				}
			}

			count++;
		}
		while (file != NULL);
		
		
		memset(fileName, 0, sizeof(fileName));


	// Output Results
		sprintf(fileName, "%s.txt", argv[2]);
		file = fopen(fileName, "w");

		fprintf(file, "Total Novel Words = %d\n\n", wordCount);
	//	printf("Total Novel Words = %d\n\n", wordCount);
		fprintf(file, "Total Novel Letters = %d\n\n", charCount);
	//	printf("Total Novel Letters = %d\n\n", charCount);
		for (i = 0; i < 26; i++)
		{
			fprintf(file, "Total Letters %c = %d = %4.2f%%\n", (char)(i + 65), charFreq[i], (float)charFreq[i]/charCount*100);
	//		printf("Total Letters %c = %d = %4.2f%%\n", (char)(i + 65), charFreq[i], (float)charFreq[i]/charCount*100);
		}
		fprintf(file, "\n");
	//	printf("\n");
		for (i = 1; i < 46; i++)
		{
			if (sizeFreq[i] > 0)
			{
				fprintf(file, "Total Words of Length %d = %d\n", i, sizeFreq[i]);
	//			printf("Total Words of Length %d = %d\n", i, sizeFreq[i]);
			}
		}
		fprintf(file, "\nAddendum Words:\n");
		printf("\nAppendum Words:\n");
		for (i = 0; i < notCount; i++)
		{
			fprintf(file, "Word[%d] = %s [%d]\n", i, notDict[i], dictNum[i]);
			printf("Word[%d] = %s [%d]\n", i, notDict[i], dictNum[i]);
		}
		fprintf(file, "\nWords containing the string \"OUS\"\n");
	//	printf("\nWords containing the string \"OUS\"\n");
		for (i = 0; i < ousCount; i++)
		{
			fprintf(file, "SubStringWord[%d] = %s\n", i, ousArr[i]);
	//		printf("SubStringWord[%d] = %s\n", i, ousArr[i]);
		}
		fprintf(file, "\nWords only made up of the letters \"ACESLMTW\"\n");
	//	printf("\nWords only made up of the letters \"ACESLMTW\"\n");
		for (i = 0; i < letCount; i++)
		{
			fprintf(file, "SpecialWord[%d] = %s\n", i, letArr[i]);
	//		printf("SpecialWord[%d] = %s\n", i, letArr[i]);
		}

		fclose(file);


	// Free Memory
		free(charFreq);
		free(sizeFreq);
		for (i = 0; i < j; i++)
			free(notDict[i]);
		free(notDict);
		for (i = 0; i < ousCount; i++)
			free(ousArr[i]);
		free(ousArr);
		for (i = 0; i < dictLen; i++)
		{
			free(dictArr[i]);
		}
		free(dictArr);

	return 0;

}
