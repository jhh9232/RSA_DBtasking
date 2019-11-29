#include "../Headers/CreatePrime.h"

void GeneratorPrime(char** make)
{
	clock_t start = clock();
	int i, sum = 0;
	char gen[102] = { null, };
	if (*make != NULL)
		free(*make);

	srand((unsigned int)time(NULL));
	while (true)
	{
		int ran = rand() % 10;
		if (ran == 5)
			ran += 2;
		else if (ran % 2 == 0)
			ran++;
		gen[0] = (char)(ran + zero);
		sum += ran;
		for (i = 1; i < 99; i++)
		{
			ran = rand() % 10;
			gen[i] = (char)(ran + zero);
			sum += ran;
		}
		ran = rand() % 9 + 1;
		gen[99] = (char)(ran + zero);
		sum += ran;
		//printf("sum : %d\n", sum);
		//printf("len : %d\n", strlen(gen));
		if (sum % 3 != 0)
		{
			break;
		}
		printf("시도\n");
	}
	//Reverse(gen);
	*make = (char*)calloc(strlen(gen) + 1, sizeof(char));
	strncpy(*make, gen, strlen(gen));
	printf("random gen : %s\n", *make);
	printf("Time : %.5lf\n", (double)(clock() - start) / CLOCKS_PER_SEC);
}