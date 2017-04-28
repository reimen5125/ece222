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
#include <math.h>

int main(void)
{
	// Variable Definition
		FILE *file;
		char var[20];
		time_t t;
		int sub;
		int parent;
		int child1;
		int child2;
		int child3;
		int child4;
		int i;
		int found;
		int *term;
		int cont;
		int fuel;
		int dist_go;
		int dist_ret;
		int missiles;
		int ret = 0;
		struct tm* tm_info;
		char outTime[26];

	// Memory allocation
		term = (int *)calloc(4, sizeof(int));

	// Terminal number(s) find
//		system("ls -l /dev/pts");

		found = 0;
		i = 0;
		while (i < 2000 && found < 4)
		{
			sprintf(var, "/dev/pts/%d", i);
			file = fopen(var, "r");
			if (file != NULL)
			{
				term[found] = i;
				found++;
			}
			i++;
			if (file != NULL)
				fclose(file);
		}

	// Print to terminals
		for (i = 0; i < found; i++)
		{
			sprintf(var, "/dev/pts/%d", term[i]);
			file = fopen(var, "w");
//			fprintf(file, "testing, testing\n");
			if (file != NULL)
				fclose(file);
		}

	// Print start date and time of the mission
		time(&t);
		printf("Date and time:  %s\n", ctime(&t));

	// Variables for children
		srand(time(NULL));
		fuel = rand() % 4000 + 1000;	// initial diesel level (1000-5000) [gallons]
		srand(time(NULL) + 1);
		missiles = rand() % 4 + 6;	// initial missiles (5-10) [-]
		dist_go = 0;	// initial distance from base (0) [miles]
		sprintf(var, "/dev/pts/%d", term[2]);
		file = fopen(var, "w");
		cont = 1;

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

						// Calculations
							while (cont == 1)
							{
								sleep(1);
								srand(time(NULL) + 2);
								fuel = fuel - ( rand() % 100 + 100 );
								sleep(1);
								if (fuel <= 0)
								{
									cont = 0;
									fprintf(file, "mission unsuccessful\n");
									exit(0);
								}
								else if (missiles <= 0)
									ret = 1;
	
								sleep(1);
								tm_info = localtime(&t);
								strftime(outTime, 26, "Time: %H:%M:%S\n", tm_info);
								fprintf(file, "%s\n", outTime);
	
								if (ret == 0)
								{
									srand(time(NULL) + 3);
									dist_go = dist_go + ( rand() % 5 + 5);
									fprintf(file, "\tBomber %d to base, %d gallons left, %d bombs left,\n\t%d miles from base.\n", 3, fuel, missiles, dist_go);
								}
								else
								{
									srand(time(NULL) + 4);
									dist_ret = dist_ret - ( rand() % 5 + 3);
									fprintf(file, "\tBomber %d to base, %d gallons left, %d bombs left,\n\t%d miles from base.\n", 3, fuel, missiles, dist_ret);
								}
							}
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


	free(term);

	return 0;
}

