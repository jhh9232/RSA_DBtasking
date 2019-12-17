#include "../Headers/CreatePrime.h"

void GeneratorPrime(LInt* make, int size, char sign, int arrlen)
{
	clock_t start = clock();
	srand((unsigned int)time(NULL));

	for (int l = 0; l < arrlen; l++)
	{
		int i, sum = 0;
		char gen[LARGELEN] = { null, };
		if ((make+l)->num != NULL)
			free((make+l)->num);

		while (true)
		{
			int ran = rand() % 10;
			if (ran == 5)
				ran += 2;
			else if (ran % 2 == 0)
				ran++;
			gen[0] = (char)(ran + zero);
			sum += ran;
			for (i = 1; i < size - 1; i++)
			{
				ran = rand() % 10;
				gen[i] = (char)(ran + zero);
				sum += ran;
			}
			ran = rand() % 9 + 1;
			gen[size - 1] = (char)(ran + zero);
			sum += ran;
			//printf("sum : %d\n", sum);
			//printf("len : %d\n", strlen(gen));
			if (sum % 3 != 0)
			{
				break;
			}
			//printf("retry...\n");
		}
		//Reverse(gen);
		size_t genlen = strlen(gen);
		(make + l)->num = (char*)malloc(genlen + 1);
		strncpy((make + l)->num, gen, genlen);
		((make + l)->num)[genlen] = null;
		(make + l)->len = genlen;
		(make + l)->sign = sign;
		//printf("random gen : %s\n", *make[l]);
		printf("Gen Time : %.5lf\n", (double)(clock() - start) / CLOCKS_PER_SEC);
	}
	
}

void ThreadGeneratorPrime(LInt* make, int size, char sign, unsigned int* ranSeed)
{
	int i, sum = 0;
	char gen[LARGELEN] = { null, };
	if (make->num != NULL)
		free(make->num);

	srand(*ranSeed);
	while (true)
	{
		int ran = rand() % 10;
		if (ran == 5)
			ran += 2;
		else if (ran % 2 == 0)
			ran++;
		gen[0] = (char)(ran + zero);
		sum += ran;
		for (i = 1; i < size - 1; i++)
		{
			ran = rand() % 10;
			gen[i] = (char)(ran + zero);
			sum += ran;
		}
		ran = rand() % 9 + 1;
		gen[size - 1] = (char)(ran + zero);
		sum += ran;
		//printf("sum : %d\n", sum);
		//printf("len : %d\n", strlen(gen));
		if (sum % 3 != 0)
			break;
		//printf("retry...\n");
	}
	size_t genlen = strlen(gen);
	make->num = (char*)malloc(genlen + 1);
	strncpy(make->num, gen, genlen);
	(make->num)[genlen] = null;
	make->len = genlen;
	make->sign = sign;
}

int NextGenerator(LInt* make)
{
	LInt add = { null, 0, NULL };
	size_t originLen = make->len;
	if ((make->num)[0] == three)
		add = SetLArray("4");
	else
		add = SetLArray("2");
	LPlus(make, *make, add);
	if (strlen(make->num) != originLen)
		return ERROR;
	free(add.num);
	return SUCCESS;
}

int check3mul(LInt bInt)
{
	int sum = 0;
	for (int i = 0; i < bInt.len; i++)
		sum = sum + (int)(bInt.num[i] - zero);
	if (sum % 3 != 0) return true;
	return false;
}

int AddGenerator(LInt* make, char* adder)
{
	LInt add = SetLArray(adder);
	while (true)
	{
		size_t originLen = make->len;
		LPlus(make, *make, add);
		if (strlen(make->num) != originLen)
			return ERROR;
		int isPrime = (int)(make->num[0] - zero);
		if (isPrime % 2 == 0 || isPrime == 5)
			continue;

		if (check3mul(*make))
			break;

		//printf("retry...\n");
	}
	free(add.num);
	return SUCCESS;
}

//void NextGenerator(char** make)
//{
	//clock_t start = clock();
	//while (true)
	//{
	//	if ((*make)[0] == '3')
	//		Plus(make, *make, "4");
	//	else
	//		Plus(make, *make, "2");

	//	int sum = 0;
	//	for (int i = 0; i < strlen(*make); i++)
	//		sum = sum + (int)((*make)[i] - zero);

	//	if (sum % 3 != 0)
	//		break;
	//	printf("next 시도\n");

	//	if (strlen(*make) > 100)
	//		GeneratorPrime(make);
	//}
	////printf("Plus gen : %s\n", *make);
	//printf("Next Time : %.5lf\n", (double)(clock() - start) / CLOCKS_PER_SEC);
//}