#include "./Headers/PrimeThread.h"

int main()
{
	/*char* make = NULL;
	GeneratorPrime(&make);
	return 0;*/
	char buf[103] = { null, };
	char num1[102] = { null, };
	char num2[102] = { null, };
	printf("input number1 : ");
	fgets(buf, 102, stdin);
	
	buf[strlen(buf) - 1] = null;
	strncpy(num1, buf, 100);
	memset(buf, null, strlen(buf)+1);

	printf("input number2 : ");
	fgets(buf, 102, stdin);

	buf[strlen(buf) - 1] = null;
	strncpy(num2, buf, 100);
	memset(buf, null, strlen(buf)+1);

	printf("|%s|\n", num1);
	printf("|%s|\n", num2);

	printf("input operator : ");
	fgets(buf, 102, stdin);
	buf[strlen(buf) - 1] = null;
	
	LInt result = { null, 0, NULL };
	if (!strncmp(buf, "+", 1))
	{
		LInt bInt1 = SLInt(num1);
		LInt bInt2 = SLInt(num2);
		printf("==================\n");
		LIntPrint(bInt1);
		LIntPrint(bInt2);
		printf("==================\n");
		clock_t start = clock();
		//gitPlus(&result, bInt1, bInt2);
		Plus(&bInt1, bInt1, bInt2);
		printf("Plus Func Time : %.20lf\n", (double)(clock() - start) / CLOCKS_PER_SEC);
		printf("===============\n");
		//LIntPrint(result);
		LIntPrint(bInt1);
		LIntPrint(bInt2);
		printf("===============\n");
		free(bInt1.num);
		free(bInt2.num);
		//free(result.num);
		return 0;
	}
	else if (!strncmp(buf, "-", 1))
	{
		LInt bInt1 = SLInt(num1);
		LInt bInt2 = SLInt(num2);
		clock_t start = clock();
		//gitMinus(&result, bInt1, bInt2);
		Minus(&bInt1, bInt1, bInt2);
		printf("Minus Func Time : %.20lf\n", (double)(clock() - start) / CLOCKS_PER_SEC);
		printf("===============\n");
		//LIntPrint(result);
		LIntPrint(bInt1);
		LIntPrint(bInt2);
		printf("===============\n");
		free(bInt1.num);
		free(bInt2.num);
		//free(result.num);
		return 0;
	}
	else if (!strncmp(buf, "*", 1))
	{
		LInt bInt1 = SLInt(num1);
		LInt bInt2 = SLInt(num2);
		clock_t start = clock();
		//gitMultiple(&result, bInt1, bInt2);
		Multiple(&bInt1, bInt1, bInt2);
		printf("Multiple End Time : %.20lf\n", (double)(clock() - start) / CLOCKS_PER_SEC);
		printf("===============\n");
		//LIntPrint(result);
		LIntPrint(bInt1);
		LIntPrint(bInt2);
		printf("===============\n");
		free(bInt1.num);
		free(bInt2.num);
		//free(result.num);
		return 0;
	}
	else if (!strncmp(buf, "/", 1))
	{
		LInt bInt1 = SLInt(num1);
		LInt bInt2 = SLInt(num2);
		clock_t start = clock();
		//gitDivide(&result, bInt1, bInt2, false);
		Divide(&bInt1, bInt1, bInt2, false);
		printf("Divide End Time : %.20lf\n", (double)(clock() - start) / CLOCKS_PER_SEC);
		printf("===============\n");
		//LIntPrint(result);
		LIntPrint(bInt1);
		LIntPrint(bInt2);
		printf("===============\n");
		free(bInt1.num);
		free(bInt2.num);
		//free(result.num);
		return 0;
		//Operate(&result, num1, num2, "/");
	}
	else if (!strncmp(buf, ".", 1))
	{
		LInt bInt1 = SLInt(num1);
		LInt bInt2 = SLInt(num2);
		clock_t start = clock();
		//gitDivide(&result, bInt1, bInt2, true);
		Divide(&bInt1, bInt1, bInt2, true);
		printf("Mod End Time : %.20lf\n", (double)(clock() - start) / CLOCKS_PER_SEC);
		printf("===============\n");
		//LIntPrint(result);
		LIntPrint(bInt1);
		LIntPrint(bInt2);
		printf("===============\n");
		free(bInt1.num);
		free(bInt2.num);
		//free(result.num);
		return 0;
	}
	else if (!strncmp(buf, "b", 1))
	{
		LInt bInt1 = SLInt(num1);
		clock_t start = clock();
		ChangeBinary(&bInt1, bInt1);
		printf("Binary End Time : %.20lf\n", (double)(clock() - start) / CLOCKS_PER_SEC);
		printf("===============\n");
		LIntPrint(bInt1);
		printf("===============\n");
		free(bInt1.num);
		return 0;
	}
	else if (!strncmp(buf, "m", 1))
	{
		LInt bInt1 = SLInt(num1);
		LInt bInt2 = SLInt(num2);
		clock_t start = clock();
		ModularSquare(&result, bInt1, bInt2);
		printf("ModularSquare End Time : %.20lf\n", (double)(clock() - start) / CLOCKS_PER_SEC);
		printf("===============\n");
		LIntPrint(result);
		printf("===============\n");
		free(bInt1.num);
		free(bInt2.num);
		free(result.num);
		return 0;
	}
	//else if (!strncmp(buf, "p", 1))
	//{
	//	char* gen = NULL;
	//	GeneratorPrime(&gen);

	//	//printf("gen : %s\n", gen);
	//	ReversePrint("rev gen", gen);
	//	printf("strlen(gen) : %ld\n", strlen(gen));

	//	NextGenerator(&gen);

	//	//printf("next gen : %s\n", gen);
	//	ReversePrint("rev next gen", gen);
	//	printf("strlen(next gen) : %ld\n", strlen(gen));

	//}
	//else if (!strncmp(buf, "r", 1))
	//{
	//	char *N = NULL, *eulerN = NULL/*, *d = NULL, *e = "65537"*/;
	//	sem_init(&semaphore, 0, 1);
	//	clock_t start = clock();
	//	pthread_t threads[TLEN];
	//	int targs[TLEN];
	//	for (int i = 0; i < TLEN; i++)
	//		targs[i] = i;
	//	for (int i = 0; i < TLEN; i++)
	//	{
	//		pthread_create(&threads[i], NULL, ThreadGenerator, (void*)&targs[i]);
	//	}
	//	for (int i = 0; i < TLEN; i++)
	//	{
	//		pthread_join(threads[i], NULL);
	//	}
	//	sem_destroy(&semaphore);
	//	printf("Thread End Time : %.5lf\n", (double)(clock() - start) / CLOCKS_PER_SEC);

	//	ReversePrint("rev prime1", primes[0]);
	//	ReversePrint("rev prime1", primes[1]);
	//	printf("strlen(primes) : %ld\n", strlen(primes[0]));

	//	//N
	//	Multiple(&N, primes[0], primes[1]);

	//	//eulerN
	//	Minus(&primes[0], primes[0], "1");
	//	Minus(&primes[1], primes[1], "1");
	//	Multiple(&eulerN, primes[0], primes[1]);




	//	for (int i = 0; i < TLEN; i++)
	//	{
	//		free(primes[i]);
	//		primes[i] = NULL;
	//	}
	//	return 0;
	//}
	else
		return 0;
}
/*
valgrind --leak-check=full --show-leak-kinds=all --track-origins=yes --verbose --log-file=valgrind-out.txt ./
*/