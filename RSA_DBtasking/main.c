//#include "./Headers/PrimeThread.h"
#include "./Headers/PrimeThread.h"
#include "./Headers/RSAlib.h"
#include "./Headers/ReadConfig.h"

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
	
	if (!strncmp(buf, "o", 1))
	{
		memset(buf, null, strlen(buf) + 1);
		printf("input operator2 : ");
		fgets(buf, 102, stdin);
		buf[strlen(buf) - 1] = null;
		OperTmp(buf, num1, num2);
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
		WriteKey(gen[0], gen[1]);

		for (int i = 0; i < 2; i++)
			free(gen[i].num);
		printf("Thread Operate End Time : %.20lf\n", (double)(clock() - start) / CLOCKS_PER_SEC);

		return 0;
	}
	else if (!strncmp(buf, "e", 1))
	{
		LInt publicN = CfgGetData("KEYS", "PUBN");
		if (!(publicN.num)) return 0;
		LInt publicE = CfgGetData("KEYS", "PUBE");
		if (!(publicE.num))
		{
			free(publicN.num);
			return 0;
		}
		LInt trapdoor = CfgGetData("KEYS", "TRAPD");
		if (!(trapdoor.num))
		{
			free(publicN.num);
			free(publicE.num);
			return 0;
		}
		FILE* reading = fopen("original_text.txt", "r, ccs=UTF-8");
		if (!reading) return 0;
		FILE* writing = fopen("encrypted_text.txt", "w+, ccs=UTF-8");

		printf("===============\n");
		LIntPrint(publicN);
		printf("===============\n");
		LIntPrint(publicE);
		printf("===============\n");
		LIntPrint(trapdoor);
		printf("===============\n");

		char buffer[LARGELEN];
		//read and encrypted file
		while (!feof(reading))
		{
			fgets(buffer, 4096, reading);
			buffer[strlen(buffer) - 1] = null;
			if (strlen(buffer) == 0)
				break;
			printf("text : %s\n", buffer);
			/*
			for (int i = 0; i < (int)strlen(buffer); i++)
				printf("%d ", (int)buffer[i]);
			printf("\n");

			fprintf(writing, "text = %s\nintegers : ", buffer);
			for (int i = 0; i < (int)strlen(buffer); i++)
				fprintf(writing, "%d ", (int)buffer[i]);
			fprintf(writing, "\n");
			*/
			memset(buffer, null, strlen(buffer));
		}

		//Free
		fclose(reading);
		fclose(writing);
		free(publicN.num);
		free(publicE.num);
		free(trapdoor.num);
		
		return 0;
	}
	else if (!strncmp(buf, "g", 1))
	{
		
	}
	else
	{
		return 0;
	}
}
/*
valgrind --leak-check=full --show-leak-kinds=all --track-origins=yes --verbose --log-file=valgrind-out.txt ./
*/