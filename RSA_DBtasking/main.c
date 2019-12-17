//#include "./Headers/PrimeThread.h"
#include "./Headers/PrimeThread.h"
#include "./Headers/RSAlib.h"
#include "./Headers/ReadConfig.h"

int ReadingCheck();

int main()
{
	/*char* make = NULL;
	GeneratorPrime(&make);
	return 0;*/
	char buf[260] = { null, };
	char num1[PRIMELEN] = { null, };
	char num2[PRIMELEN] = { null, };
	printf("input number1 : ");
	fgets(buf, 256, stdin);

	buf[strlen(buf) - 1] = null;
	strncpy(num1, buf, 256);
	memset(buf, null, strlen(buf) + 1);

	printf("input number2 : ");
	fgets(buf, 256, stdin);

	buf[strlen(buf) - 1] = null;
	strncpy(num2, buf, 256);
	memset(buf, null, strlen(buf) + 1);

	printf("|%s|\n", num1);
	printf("|%s|\n", num2);

	printf("input operator : ");
	fgets(buf, 256, stdin);
	buf[strlen(buf) - 1] = null;
	
	if (!strncmp(buf, "o", 1))
	{
		memset(buf, null, strlen(buf) + 1);
		printf("input operator2 : ");
		fgets(buf, 102, stdin);
		buf[strlen(buf) - 1] = null;
		OperTmp(buf, num1, num2);
		return 0;
	}
	else if (!strncmp(buf, "r", 1))
	{
		LInt gen = { null, 0, NULL };
		LInt result = { null, 0, NULL };
		LInt con = SetLArray("65537");
		GeneratorPrime(&gen, 256, plus, 1);
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
	else if (!strncmp(buf, "g", 1))
	{
		clock_t start = clock();
		LInt gen[2] = { { null, 0, NULL }, { null, 0, NULL } };
		pthread_t threads[TLEN];
		int targs[TLEN];
		int ret = pthread_rwlock_init(&rwLock, NULL);
		if (ret != 0)
		{
			printf("rwlock init error\n");
			return 0;
		}

		GeneratorPrime(gen, 128, plus, 2);

		for (int l = 0; l < 2; l++)
		{
			//GeneratorPrime(&(gen[l]), 16, plus);

			InitTglobal();
			LIntCopySize(&primes[0], &(gen[l]), gen[l].len + 1);
			targs[0] = 0;

			for (int i = 1; i < TLEN; i++)
			{
				if (!NextGenerator(&(gen[l])))
				{
					printf("GENERATE ERROR!!!\n");
					return 0;
				}
				LIntCopySize(&primes[i], &(gen[l]), gen[l].len + 1);
				if (!check3mul(primes[i]))
				{
					if (!AddGenerator(&primes[i], TADD))
					{
						printf("GENERATE ERROR!!!\n");
						return 0;
					}
				}
				targs[i] = i;
			}

			for (int i = 0; i < TLEN; i++)
			{
				printf("primes[%d]", i);
				ReversePrint("", primes[i].num);
			}

			free(gen[l].num);
			gen[l].num = NULL;

			for (int i = 0; i < TLEN; i++)
				pthread_create(&threads[i], NULL, ThreadGenerator, (void*)&targs[i]);
			for (int i = 0; i < TLEN; i++)
			{
				//pthread_join(threads[i], (void*)&tresult[i]);
				pthread_join(threads[i], NULL);
			}
			for (int i = 0; i < TLEN; i++)
			{
				printf("%d - tresult : %c, ", i, tresult[i] ? 'T' : 'F');
				ReversePrint("prime num", primes[i].num);
			}
			printf("\n");

			for (int i = 0; i < TLEN; i++)
			{
				if (tresult[i])
				{
					LIntCopy(&(gen[l]), &(primes[i]));
					break;
				}
			}
			for (int i = 0; i < TLEN; i++)
				free(primes[i].num);
			pthread_rwlock_destroy(&rwLock);
		}
		printf("===============\n");
		for (int i = 0; i < 2; i++)
		{
			printf("%d\n", i);
			LIntPrint(gen[i]);
		}
		printf("===============\n");
		WriteKey(gen[0], gen[1]);

		for (int i = 0; i < 2; i++)
			free(gen[i].num);
		printf("Thread Operate End Time : %.20lf\n", (double)(clock() - start) / CLOCKS_PER_SEC);

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
		FILE* reading = fopen("original_text.txt", "r, ccs=UTF-8");
		if (!reading)
			return 0;
		
		if (!ReadingCheck())
		{
			fclose(reading);
			return 0;
		}

		FILE* writing = fopen("encrypted_text.txt", "w+, ccs=UTF-8");

		printf("===============\n");
		LIntPrint(GetPubN());
		printf("===============\n");
		LIntPrint(GetPubE());
		printf("===============\n");
		LIntPrint(GetPrvD());
		printf("===============\n");

		char buffer[LARGELEN] = { null };
		//read and encrypted file
		while (!feof(reading))
		{
			fgets(buffer, 4096, reading);
			if (strlen(buffer) == 0)
				break;
			printf("text : %s", buffer);
			EncryptText(writing, buffer);
			memset(buffer, null, strlen(buffer));
		}

		//Free
		fclose(reading);
		fclose(writing);
		DestroyAll();
		
		return 0;
	}
	else if (!strncmp(buf, "d", 1))
	{
		FILE* reading = fopen("encrypted_text.txt", "r, ccs=UTF-8");
		if (!reading)
			return 0;

		if (!ReadingCheck())
		{
			fclose(reading);
			return 0;
		}

		FILE* writing = fopen("decrypted_text.txt", "w+, ccs=UTF-8");

		char buffer[LARGELEN] = { null };
		char origin[LARGELEN] = { null };
		//read and decrypted file
		int i = 0;
		while (!feof(reading))
		{
			fscanf(reading, "%s ", buffer);
			if (strlen(buffer) == 0)
				break;
			printf("text : \"%s\"\n", buffer);
			DecryptText(buffer, origin, i);
			memset(buffer, null, strlen(buffer));
			i++;
			if (origin[i] > 0)
			{
				fprintf(writing, "%s", origin);
				memset(origin, null, strlen(origin));
				i = 0;
			}
		}
		if (origin[0] != null)
		{
			fprintf(writing, "%s", origin);
			memset(origin, null, strlen(origin));
		}

		fclose(reading);
		fclose(writing);
		DestroyAll();
	}
	else
	{
		return 0;
	}
	return 0;
}

int ReadingCheck()
{
	LInt publicN = CfgGetData("KEYS", "PUBN");
	if (!(publicN.num)) return ERROR;
	LInt publicE = CfgGetData("KEYS", "PUBE");
	if (!(publicE.num))
	{
		free(publicN.num);
		return ERROR;
	}
	LInt trapdoor = CfgGetData("KEYS", "TRAPD");
	if (!(trapdoor.num))
	{
		free(publicN.num);
		free(publicE.num);
		return ERROR;
	}

	SetPubN(publicN, false);
	SetPubE(publicE, false);
	SetPrvD(trapdoor, false);

	return SUCCESS;
}

/*
valgrind --leak-check=full --show-leak-kinds=all --track-origins=yes --verbose --log-file=valgrind-out.txt ./
*/