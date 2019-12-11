//#include "./Headers/PrimeThread.h"
#include "./Headers/PrimeThread.h"

int main()
{
	/*char* make = NULL;
	GeneratorPrime(&make);
	return 0;*/
	char buf[260] = { null, };
	char num1[PRIMELEN] = { null, };
	char num2[PRIMELEN] = { null, };
	printf("input number1 : ");
	fgets(buf, 102, stdin);

	buf[strlen(buf) - 1] = null;
	strncpy(num1, buf, 256);
	memset(buf, null, strlen(buf) + 1);

	printf("input number2 : ");
	fgets(buf, 102, stdin);

	buf[strlen(buf) - 1] = null;
	strncpy(num2, buf, 256);
	memset(buf, null, strlen(buf) + 1);

	printf("|%s|\n", num1);
	printf("|%s|\n", num2);

	printf("input operator : ");
	fgets(buf, 102, stdin);
	buf[strlen(buf) - 1] = null;
	LInt result = { null, 0, NULL };
	if (!strncmp(buf, "+", 1))
	{
		LInt bInt1 = SetLInt(num1);
		LInt bInt2 = SetLInt(num2);
		printf("==================\n");
		LIntPrint(bInt1);
		LIntPrint(bInt2);
		printf("==================\n");
		clock_t start = clock();
		//gitPlus(&result, bInt1, bInt2);
		LPlus(&bInt1, bInt1, bInt2);
		printf("LPlus Func Time : %.20lf\n", (double)(clock() - start) / CLOCKS_PER_SEC);
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
		LInt bInt1 = SetLInt(num1);
		LInt bInt2 = SetLInt(num2);
		clock_t start = clock();
		//gitMinus(&result, bInt1, bInt2);
		LMinus(&bInt1, bInt1, bInt2);
		printf("LMinus Func Time : %.20lf\n", (double)(clock() - start) / CLOCKS_PER_SEC);
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
		LInt bInt1 = SetLInt(num1);
		LInt bInt2 = SetLInt(num2);
		clock_t start = clock();
		//gitMultiple(&result, bInt1, bInt2);
		LMultiple(&bInt1, bInt1, bInt2);
		printf("LMultiple End Time : %.20lf\n", (double)(clock() - start) / CLOCKS_PER_SEC);
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
		LInt bInt1 = SetLInt(num1);
		LInt bInt2 = SetLInt(num2);
		clock_t start = clock();
		//gitDivide(&result, bInt1, bInt2, false);
		LDivide(&bInt1, bInt1, bInt2, false);
		printf("LDivide End Time : %.20lf\n", (double)(clock() - start) / CLOCKS_PER_SEC);
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
		LInt bInt1 = SetLInt(num1);
		LInt bInt2 = SetLInt(num2);
		clock_t start = clock();
		//gitDivide(&result, bInt1, bInt2, true);
		LDivide(&bInt1, bInt1, bInt2, true);
		printf("LMod End Time : %.20lf\n", (double)(clock() - start) / CLOCKS_PER_SEC);
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
		LInt bInt1 = SetLInt(num1);
		clock_t start = clock();
		LChangeBinary(&bInt1, bInt1);
		printf("LBinary End Time : %.20lf\n", (double)(clock() - start) / CLOCKS_PER_SEC);
		printf("===============\n");
		LIntPrint(bInt1);
		printf("===============\n");
		free(bInt1.num);
		return 0;
	}
	else if (!strncmp(buf, "m", 1))
	{
		LInt bInt1 = SetLInt(num1);
		LInt bInt2 = SetLInt(num2);
		clock_t start = clock();
		LParsePrime(&result, bInt1, bInt2);
		printf("LModularSquare End Time : %.20lf\n", (double)(clock() - start) / CLOCKS_PER_SEC);
		printf("===============\n");
		LIntPrint(result);
		printf("===============\n");
		free(bInt1.num);
		free(bInt2.num);
		free(result.num);
		return 0;
	}
	else if (!strncmp(buf, "r", 1))
	{
		LInt gen = { null, 0, NULL };
		LInt result = { null, 0, NULL };
		LInt con = SetLArray("65537");
		GeneratorPrime(&gen, 256, plus);
		printf("===============\n");
		LIntPrint(gen);
		LIntPrint(con);
		printf("===============\n");
		clock_t start = clock();
		LParsePrime(&result, gen, con);
		printf("Random Modular End Time : %.20lf\n", (double)(clock() - start) / CLOCKS_PER_SEC);
		printf("===============\n");
		LIntPrint(result);
		printf("===============\n");
		free(gen.num);
		free(con.num);
		free(result.num);
		return 0;
	}
	else if (!strncmp(buf, "t", 1))
	{
		clock_t start = clock();
		LInt gen[2] = { { null, 0, NULL }, { null, 0, NULL } };
		//pthread_t threads[TLEN];
		//int targs[TLEN];
		//int ret = pthread_rwlock_init(&rwLock, NULL);
		//if (ret != 0)
		//{
		//	printf("rwlock init error\n");
		//	return 0;
		//}

		//for (int l = 0; l < 2; l++)
		//{
		//	GeneratorPrime(&(gen[l]), 128, plus);

		//	InitTglobal();
		//	LIntCopySize(&primes[0], &(gen[l]), gen[l].len + 1);
		//	targs[0] = 0;

		//	for (int i = 1; i < TLEN; i++)
		//	{
		//		if (!NextGenerator(&(gen[l])))
		//		{
		//			printf("GENERATE ERROR!!!\n");
		//			return 0;
		//		}
		//		LIntCopySize(&primes[i], &(gen[l]), gen[l].len + 1);
		//		if (!check3mul(primes[i]))
		//		{
		//			if (!AddGenerator(&primes[i], TADD))
		//			{
		//				printf("GENERATE ERROR!!!\n");
		//				return 0;
		//			}
		//		}
		//		targs[i] = i;
		//	}

		//	for (int i = 0; i < TLEN; i++)
		//	{
		//		printf("primes[%d]", i);
		//		ReversePrint("", primes[i].num);
		//	}

		//	free(gen[l].num);
		//	gen[l].num = NULL;

		//	for (int i = 0; i < TLEN; i++)
		//		pthread_create(&threads[i], NULL, ThreadGenerator, (void*)&targs[i]);
		//	for (int i = 0; i < TLEN; i++)
		//	{
		//		//pthread_join(threads[i], (void*)&tresult[i]);
		//		pthread_join(threads[i], NULL);
		//	}
		//	for (int i = 0; i < TLEN; i++)
		//	{
		//		printf("%d - tresult : %c, ", i, tresult[i] ? 'T' : 'F');
		//		ReversePrint("prime num", primes[i].num);
		//	}
		//	printf("\n");

		//	for (int i = 0; i < TLEN; i++)
		//	{
		//		if (tresult[i])
		//		{
		//			LIntCopy(&(gen[l]), &(primes[i]));
		//			break;
		//		}
		//	}
		//	for (int i = 0; i < TLEN; i++)
		//		free(primes[i].num);
		//	pthread_rwlock_destroy(&rwLock);
		//}
		gen[0] = SetLArray(num1);
		gen[1] = SetLArray(num2);
		printf("===============\n");
		for (int i = 0; i < 2; i++)
		{
			LIntPrint(gen[i]);
		}
		printf("===============\n");

		LInt N = { null, 0, NULL };      //공개키
		LInt e = SetLArray("3");     //공개키
		LInt d = { null, 0, NULL };      //trapdoor
		LInt OulerN = { null, 0, NULL };
		LInt k = { null, 0, NULL };
		LInt lone = SetLArray("1");

		//공개키 N
		LMultiple(&N, gen[0], gen[1]);

		//오일러 N
		LMinus(&(gen[0]), gen[0], lone);
		LMinus(&(gen[1]), gen[1], lone);
		LMultiple(&OulerN, gen[0], gen[1]);

		//k
		LInt ktmp = { null, 0, NULL };
		LDivide(&ktmp, OulerN, e, true);
		LMinus(&k, e, ktmp);
		free(ktmp.num);

		//trapdoor d
		LMultiple(&k, k, OulerN);
		LPlus(&k, k, lone);
		LDivide(&d, k, e, false);


		free(OulerN.num);
		free(k.num);
		free(lone.num);

		printf("=======N=======\n");
		LIntPrint(N);
		printf("=======d=======\n");
		LIntPrint(d);
		printf("===============\n");

		free(N.num);
		free(e.num);
		free(d.num);

		for (int i = 0; i < 2; i++)
		{
			free(gen[i].num);
		}
		printf("Thread Operate End Time : %.20lf\n", (double)(clock() - start) / CLOCKS_PER_SEC);

		return 0;
	}
	else if (!strncmp(buf, "f", 1))
	{
		FILE* reading = fopen("original_text.txt", "r, ccs=UTF-8");
		FILE* writing = fopen("encrypted_text.txt", "w+, ccs=UTF-8");
		
		if (reading == NULL)
			return 0;


		int cnt = 0;
		while (!feof(reading))
		{
			fgets(buf, 1024, reading);
			buf[strlen(buf) - 1] = null;
			if (strlen(buf) == 0)
				break;
			printf("text : %s\n", buf);
			for (int i = 0; i < (int)strlen(buf); i++)
				printf("%d ", (int)buf[i]);
			printf("\n");

			fprintf(writing, "cnt = %d, str = %s\n integers : ", cnt, buf);
			for (int i = 0; i < (int)strlen(buf); i++)
				fprintf(writing, "%d ", (int)buf[i]);
			fprintf(writing, "\n");

			memset(buf, null, strlen(buf));
		}
		fclose(reading);
		fclose(writing);
		return 0;
	}
	else
	{
		return 0;
	}
}
/*
valgrind --leak-check=full --show-leak-kinds=all --track-origins=yes --verbose --log-file=valgrind-out.txt ./
*/