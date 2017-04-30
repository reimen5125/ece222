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
void sigkill1(int);

int missiles;
int fuel;
int currentChild;
int done = 0;

void sigkill1 (int signum)
{
}

void launchMissile (int signum)
{
	missiles = missiles - 1;
	if (missiles <= 0)
		printf("Sub has no ordinance left.  Returning to base.\n");
	else
		printf("Missile was launched.  %d missiles remaining for sub.\n", missiles);
}

void addFuel (int signum)
{
	fuel = 5000;
	printf("Sub has fuel level of %d gallons.\n", fuel);
}

int main(void)
{
	// Variable Definition
		FILE *file;
		FILE *parentFile;
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
		int returnStatus1 = 1;
		int returnStatus2 = 1;
		int returnStatus3 = 1;
		int returnStatus4;
		int turn = 0;

	// Memory allocation
		term = (int *)calloc(4, sizeof(int));

	// Install signals
		signal(SIGUSR1, (ptr)launchMissile);
		signal(SIGUSR2, (ptr)addFuel);
		signal(SIGKILL, sigkill1);
		

	// Terminal number(s) find
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

	sprintf(var, "/dev/pts/%d", term[0]);
	parentFile = fopen(var, "w");

	// Fork children and analyze information for each
	if (!(child1 = fork()))
	{
		// Calculations
			sprintf(var, "/dev/pts/%d", term[1]);
			file = fopen(var, "w");

			while (cont == 1)
			{
				sleep(1);
				srand(time(NULL) + 2);
				fuel = fuel - ( (rand() + 1) % 100 + 100 );
				sleep(1);
				if (dist_ret <= 0 && ret == 1 && missiles <= 0)
				{

					cont = 0;
					fprintf(file, "successful mission\n");
					done++;
					fprintf(parentFile, "done child1 = %d\n", done);
					break;
				}
				else if (fuel <= 0)
				{
					cont = 0;
					fprintf(file, "unsuccessful mission\n");
					fprintf(parentFile, "Sub 1 dead in the water.\n");
					fprintf(file, "Rescue is on the way, sub 1.\n");
					done++;
					fprintf(parentFile, "done child1 = %d\n", done);
					break;
				}
				else if (missiles <= 0 && turn == 0)
				{
					ret = 1;
					dist_ret = dist_go;
					done++;
					turn = 1;
				}
				else if (missiles <= 0 && turn == 1)
				{
					dist_ret--;
				}
				else if (fuel <= 500)
					fprintf(parentFile, "Sub 1 running out of fuel!\n");

				// Print time
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
			returnStatus1 = 0;
			return(returnStatus1);
	}
	else if (!(child2 = fork()))
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
				{
					cont = 0;
					fprintf(file, "successful mission\n");
					done++;
					fprintf(parentFile, "done child2 = %d\n", done);
					break;
				}
				else if (fuel <= 0)
				{
					cont = 0;
					fprintf(file, "unsuccessful mission\n");
					fprintf(parentFile, "Sub 2 dead in the water.\n");
					fprintf(file, "Rescue is on the way, sub 2.\n");
					done++;
					fprintf(parentFile, "done child2 = %d\n", done);
					break;
				}
				else if (missiles <= 0 && turn == 0)
				{
					ret = 1;
					dist_ret = dist_go;
					done++;
					turn = 1;
				}
				else if (missiles <= 0 && turn == 1)
				{
					dist_ret--;
				}
				else if (fuel <= 500)
					fprintf(parentFile, "Sub 2 running out of fuel!\n");

				// Print time
					sleep(1);
					t = 0;
					time(&t);
					tm_info = localtime(&t);
					strftime(outTime, 26, "Time: %H:%M:%S\n", tm_info);
					fprintf(file, "%s\n", outTime);

				if (ret == 0)
				{
					srand(time(NULL) + 3);
					dist_go = dist_go + ( rand() % 5 + 3);
					fprintf(file, "\tBomber %d to base, %d gallons left, %d bombs left,\n\t%d miles from base.\n", 2, fuel, missiles, dist_go);
				}
				else
				{
					srand(time(NULL) + 4);
					dist_ret = dist_ret - ( rand() % 5 + 3);
					fprintf(file, "\tBomber %d to base, %d gallons left, %d bombs left,\n\t%d miles from base.\n", 2, fuel, missiles, dist_ret);
				}
			}
			returnStatus2 = 0;
			return(returnStatus2);
	}
	else if (!(child3 = fork()))
	{
		// Calculations
			sprintf(var, "/dev/pts/%d", term[3]);
			file = fopen(var, "w");

			while (cont == 1)
			{
				sleep(1);
				srand(time(NULL) + 2);
				fuel = fuel - ( rand() % 100 + 100 );
				sleep(1);
				if (dist_ret <= 0 && ret == 1 && missiles <= 0)
				{
					cont = 0;
					fprintf(file, "successful mission\n");
					done++;
					fprintf(parentFile, "done child3 = %d\n", done);
					break;
				}
				else if (fuel <= 0)
				{
					cont = 0;
					fprintf(file, "unsuccessful mission\n");
					done++;
					fprintf(parentFile, "done child3 = %d\n", done);
					fprintf(parentFile, "Sub 3 dead in the water.\n");
					fprintf(file, "Rescue is on the way, sub 3.\n");
					break;
				}
				else if (missiles <= 0 && turn == 0)
				{
					ret = 1;
					dist_ret = dist_go;
					done++;
					turn = 1;
				}
				else if (missiles <= 0 && turn == 1)
				{
					dist_ret--;
				}
				else if (fuel <= 500)
					fprintf(parentFile, "Sub 3 running out of fuel!\n");

				// Print time
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
		returnStatus3 = 0;
		return(returnStatus3);
	}
	else if (!(child4 = fork()))
	{
		while (1)
		{
			if ( fgets(command, 20, stdin) != NULL )
			{
				if (strstr(command, "l1"))
				{
					kill(child1, SIGUSR1);
					currentChild = 1;
				}
				else if (strstr(command, "l2"))
				{
					kill(child2, SIGUSR1);
					currentChild = 2;
				}
				else if (strstr(command, "l3"))
				{
					kill(child3, SIGUSR1);
					currentChild = 3;
				}
				else if (strstr(command, "r1"))
				{
					kill(child1, SIGUSR2);
					currentChild = 1;
				}
				else if (strstr(command, "r2"))
				{
					kill(child2, SIGUSR2);
					currentChild = 2;
				}
				else if (strstr(command, "r3"))
				{
					kill(child3, SIGUSR2);
					currentChild = 3;
				}
				else if (strstr(command, "q"))
				{
					kill(child1, SIGKILL);
					kill(child2, SIGKILL);
					kill(child3, SIGKILL);
					kill(child4, SIGKILL);
					done = 3;
					break;
				}
				else if (strstr(command, "s1"))
				{
					fprintf(parentFile, "Sub 1 terminated.\n");
					kill(child1, SIGKILL);
				}
				else if (strstr(command, "s2"))
				{
					fprintf(parentFile, "Sub 2 terminated.\n");
					kill(child2, SIGKILL);
				}
				else if (strstr(command, "s3"))
				{
					fprintf(parentFile, "Sub 3 terminated.\n");
					kill(child3, SIGKILL);
				}
				else
					fprintf(parentFile, "Invalid input.\n");
			}
		}
		returnStatus4 = 0;
		return(returnStatus4);
	}
	else
	{
		parent = getpid();
		printf("parent = %d\nchild1 = %d\nchild2 = %d\nchild3 = %d\n", parent, child1, child2, child3);

		sprintf(var1, "/dev/pts/%d", child1);
		sprintf(var2, "/dev/pts/%d", child2);
		sprintf(var3, "/dev/pts/%d", child3);
		sprintf(varPar, "/dev/pts/%d", parent);
	}
	
	// Terminate any subs that are finished running
		if (returnStatus1 == 0)
			kill(child1, SIGKILL);
		if (returnStatus2 == 0)
			kill(child2, SIGKILL);
		if (returnStatus3 == 0)
			kill(child3, SIGKILL);

	// Wait for the 0 return status of the subs so the parent will not finish running until they are finished
		waitpid(-1, &returnStatus1, 0);
		waitpid(-1, &returnStatus2, 0);
		waitpid(-1, &returnStatus3, 0);

	// Print final date and time
		t = 0;
		time(&t);
		tm_info = localtime(&t);
		printf("Date and time:  %s\n", ctime(&t));

	free(term);


	return 0;
}

