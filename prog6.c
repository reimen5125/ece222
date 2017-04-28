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
#include <sys/types.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

#include <signal.h>
#include <errno.h>
#include <sys/wait.h>

typedef void (*ptr);

int missiles;
int fuel;
int currentChild;

void sigkill (int signum)
{
	kill(currentChild, SIGFPE);
}

void launchMissile (int signum)
{
	missiles = missiles - 1;
	if (missiles <= 0)
		printf("Sub %d has no ordinance left.  Returning to base.\n", currentChild);
	else
		printf("Missile was launched.  %d missiles remaining for sub %d.\n", missiles, currentChild);
}

void addFuel (int signum)
{
	fuel = 5000;
	printf("Sub %d has fuel level of %d gallons.\n", currentChild, fuel);
}

int kill(pid_t pid, int sig);

int main(void)
{
	// Variable Definition
		FILE *file;
		char var[20];
		time_t t;
		int parent;
		int child1;
		int child2;
		int child3;
		int child4;
		int i;
		int found;
		int *term;
		int cont;
		int dist_go;
		int dist_ret;
		int ret = 0;
		struct tm* tm_info;
		char outTime[26];
		char command[20];
		char var1[20];
		char var2[20];
		char var3[20];
		char varPar[20];

	// Memory allocation
		term = (int *)calloc(4, sizeof(int));

	// Install signals
		signal(SIGUSR1, (ptr)launchMissile);
		signal(SIGUSR2, (ptr)addFuel);
		signal(SIGFPE, (ptr)sigkill);
		

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
		cont = 1;
	// Fork children and analyze information for each
	if (!(child1 = fork()))
	{
		// Calculations
			sprintf(var, "/dev/pts/%d", term[0]);
			file = fopen(var, "w");

			while (cont == 1)
			{
				sleep(1);
				srand(time(NULL) + 2);
				fuel = fuel - ( rand() % 100 + 100 );
				sleep(1);
				if (dist_ret <= 0 && ret == 1 && missiles <= 0)
					fprintf(file, "successful mission\n");
				else if (fuel <= 0)
				{
					cont = 0;
					fprintf(file, "unsuccessful mission\n");
					exit(0);
				}
				else if (missiles <= 0)
				{
					ret = 1;
					dist_ret = dist_go;
				}
				sleep(1);
				t = 0;
				time(&t);
				tm_info = localtime(&t);
				strftime(outTime, 26, "Time: %H:%M:%S\n", tm_info);
				fprintf(file, "%s\n", outTime);
				if (ret == 0)
				{
					srand(time(NULL) + 3);
					dist_go = dist_go + ( rand() % 5 + 5);
					fprintf(file, "\tBomber %d to base, %d gallons left, %d bombs left,\n\t%d miles from base.\n", 1, fuel, missiles, dist_go);
				}
				else
				{
					srand(time(NULL) + 4);
					dist_ret = dist_ret - ( rand() % 5 + 3);
					fprintf(file, "\tBomber %d to base, %d gallons left, %d bombs left,\n\t%d miles from base.\n", 1, fuel, missiles, dist_ret);
				}
			}
	}
	else if (!(child2 = fork()))
	{
		// Calculations
			sprintf(var, "/dev/pts/%d", term[1]);
			file = fopen(var, "w");

			while (cont == 1)
			{
				sleep(1);
				srand(time(NULL) + 2);
				fuel = fuel - ( rand() % 100 + 100 );
				sleep(1);
				if (dist_ret <= 0 && ret == 1 && missiles <= 0)
					fprintf(file, "successful mission\n");
				else if (fuel <= 0)
				{
					cont = 0;
					fprintf(file, "unsuccessful mission\n");
					exit(0);
				}
				else if (missiles <= 0)
				{
					ret = 1;
					dist_ret = dist_go;
				}
				sleep(1);
				t = 0;
				time(&t);
				tm_info = localtime(&t);
				strftime(outTime, 26, "Time: %H:%M:%S\n", tm_info);
				fprintf(file, "%s\n", outTime);
				if (ret == 0)
				{
					srand(time(NULL) + 3);
					dist_go = dist_go + ( rand() % 5 + 5);
					fprintf(file, "\tBomber %d to base, %d gallons left, %d bombs left,\n\t%d miles from base.\n", 2, fuel, missiles, dist_go);
				}
				else
				{
					srand(time(NULL) + 4);
					dist_ret = dist_ret - ( rand() % 5 + 3);
					fprintf(file, "\tBomber %d to base, %d gallons left, %d bombs left,\n\t%d miles from base.\n", 2, fuel, missiles, dist_ret);
				}
			}
	}
	else if (!(child3 = fork()))
	{
		// Calculations
			sprintf(var, "/dev/pts/%d", term[2]);
			file = fopen(var, "w");

			while (cont == 1)
			{
				sleep(1);
				srand(time(NULL) + 2);
				fuel = fuel - ( rand() % 100 + 100 );
				sleep(1);
				if (dist_ret <= 0 && ret == 1 && missiles <= 0)
					fprintf(file, "successful mission\n");
				else if (fuel <= 0)
				{
					cont = 0;
					fprintf(file, "unsuccessful mission\n");
					exit(0);
				}
				else if (missiles <= 0)
				{
					ret = 1;
					dist_ret = dist_go;
				}

				sleep(1);
				t = 0;
				time(&t);
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
	else if (!(child4 = fork()))
	{
		
	}
	else
	{
		parent = getpid();
		printf("parent = %d\nchild1 = %d\nchild2 = %d\nchild3 = %d\nchild4 = %d\n", parent, child1, child2, child3, child4);

		sprintf(var1, "/dev/pts/%d", child1);
		sprintf(var2, "/dev/pts/%d", child2);
		sprintf(var3, "/dev/pts/%d", child3);
		sprintf(varPar, "/dev/pts/%d", parent);
		while (kill(var1, 0) && kill(var2, 0) && kill(var3, 0) && kill(varPar, 0))
		{
//			fgets(dictStr, 46, file) != NULL
			if ( fgets(command, 20, stdin) != NULL )
			{
				if (strcmp(command, "l1"))
				{
					kill(child1, SIGUSR1);
					currentChild = 1;
				}
				else if (strcmp(command, "l2"))
				{
					kill(child2, SIGUSR1);
					currentChild = 2;
				}
				else if (strcmp(command, "l3"))
				{
					kill(child3, SIGUSR1);
					currentChild = 3;
				}
				else if (strcmp(command, "r1"))
				{
					kill(child1, SIGUSR2);
					currentChild = 1;
				}
				else if (strcmp(command, "r2"))
				{
					kill(child2, SIGUSR2);
					currentChild = 2;
				}
				else if (strcmp(command, "r3"))
				{
					kill(child3, SIGUSR2);
					currentChild = 3;
				}
				else if (strcmp(command, "q"))
					exit(0);
				else if (strcmp(command, "s1"))
					sigkill(child1);
/*				else if (strmp(command, "s2"))
					kill(child2);
				else if (strcmp(command, "s3"))
					kill(child3);
*/				kill(child3, SIGUSR2);
				printf("testing, testing");
			}
				printf("testing, testing");
		}
	}
	sleep(2);

	free(term);


	return 0;
}

