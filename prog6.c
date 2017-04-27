/*
	Rachel Eimen
	C14796950
	ECE 222-001
	Program 6 - Signals: "Base to Submarines"
	Description:  Create a program with a "base process" that is linked to child processes, or "submarines".  Use this system to perform various tasks relating to a mission.
*/

#include <stdio.h>
#include <unistd.h>
#include <time.h>
// #include <io.h>
// #include <signal.h>
#include <sys/types.h>
#include <stdlib.h>
#include <string.h>

//FILE *popen(const char *command, const char *mode);
//int pclose(FILE *stream);

int main(void)
{
	// Variable Definition
		FILE *file;
		char var[20];
//		int num = 0;
//		char temp[46];
		time_t t;
		int sub;
		int parent;
		int child1;
		int child2;
		int child3;
		int child4;
		int i;
		int found = 0;
		char loc1[20];
		char loc2[20];
		char loc3[20];
		char loc4[20];

	// Terminal number(s) find
		system("ls -l /dev/pts");

		i = 0;
		while (i < 200 && found < 4);
		{
			// num = system("ls -l /dev/pts");
//			system("ls -l /dev/pts");
	//		if(fileno(stdin))
	//			printf("terminal = %d", fileno(stdin));
	
	//		sprintf(output, "grep bar %d", num);
	//		sprintf(output, "%d%d", num, i);
			sprintf(var, "/dev/pts/%d", i);
	//		file = popen(output, "r");
			file = fopen(var, "r");
			if (file != NULL)
			{
				switch (found)
				{
					case 0:
						strcpy(loc1, var);
						found++;
						printf("loc1 = %s", loc1);
						break;
					case 1:
						strcpy(loc2, var);
						found++;
						printf("loc2 = %s", loc2);
						break;
					case 2:
						strcpy(loc3, var);
						found++;
						printf("loc3 = %s", loc3);
						break;
					case 3:
						strcpy(loc4, var);
						found++;
						printf("loc4 = %s", loc4);
						break;
				}
			}
//			while (file != NULL && fscanf(file, "%c", &temp) != EOF)
//			{
//				fgets(temp, 46, file);
//				printf("testing testing %s ", temp);
//			}
			i++;
		}

	// Print start date and time of the mission
		time(&t);
		printf("Date and time:  %s\n", ctime(&t));

	// Fork children and assign pid's
		sub = fork();
		if (sub != 0)	// parent
		{
			parent = sub;
			printf("parent = %d\n", parent);
		}
		else	// children
		{
			sub = fork();
			if (sub == 0)
			{
				sub = fork();
				if (sub == 0)
				{
					sub = fork();
					if (sub == 0)	// child4 (separate function)
					{
						child4 = sub;
						printf("child4 = %d\n", child4);
					}
					else	// child3
					{
						child3 = sub;
						printf("child3 = %d\n", child3);
					}
				}
				else	// child2
				{
					child2 = sub;
					printf("child2 = %d\n", child2);
				}					
			}
			else	// child1
			{
				child1 = sub;
				printf("child1 = %d\n", child1);
			}
			sleep(2);
		}
		sleep(1);

	return 0;
}
