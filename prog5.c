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

	// Open all novel files
		count = 1;
		wordCount = 0;

		do
		{
			memset(fileName, 0, sizeof(fileName));
			sprintf(fileName, "%s_%d.txt", argv[1], count);
			file = fopen(fileName, "r");
			while (file != NULL && fscanf(file, "%c", &temp) != EOF)
		//	while (file != NULL && fscanf(file, "%s", str) != EOF)
			{
		//		if (sizeof(str) < 15)
		//			printf("%s", str);
		//		memset(str, 0, sizeof(str));
				if (temp == ' ' || temp == '-')
				{
					wordCount++;
					memset(str, 0, sizeof(str));
				}
				else if (temp == '.' || temp == '?' || temp == '!' || temp == '\n')
					memset(str, 0, sizeof(str));
				else if (isalpha(temp))
				{
					sprintf(str, "%s%c", str, temp);
		//			printf("%s\n", str);
				}
			}
			count++;	
		}
		while (file != NULL);


	return 0;

}
