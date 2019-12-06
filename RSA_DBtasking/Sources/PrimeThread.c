#include "../Headers/PrimeThread.h"

sem_t semaphore;
char* primes[TLEN] = { NULL, };

void* ThreadGenerator(void* arg)
{
	clock_t start = clock();
	int n = *(int*)arg;
	unsigned int* ranState = (unsigned int*)arg;
	char* gen = NULL;
	long long int rancnt = 0;
	*ranState = (unsigned int)time(NULL) ^ (unsigned int)getpid() ^ (unsigned int)pthread_self();
	ThreadGeneratorPrime(&gen, ranState);
	while (true)
	{
		ReversePrint("rev gen", gen);
		/*char scan[10] = { null, };
		fgets(scan, sizeof(scan), stdin);*/
		ModularSquare(&primes[n], gen, "2");
		printf("strlen(result) : %ld\n", strlen(primes[n]));
		if (!strncmp(primes[n], "1", strlen(primes[n])))
		{
			//printf("gen(rev) : %s\n", gen);
			ReversePrint("gen", gen);
			free(primes[n]);
			primes[n] = (char*)malloc(strlen(gen) + 1);
			strncpy(primes[n], gen, strlen(gen));
			primes[strlen(gen)] = null;
			printf("시도 횟수 : %ld\n", rancnt);
			printf("Thread[%d] 걸린 시간 : %.5lf\n", n, (double)(clock() - start) / CLOCKS_PER_SEC);
			free(gen);
			gen = NULL;
			break;
		}
		else
		{
			printf("재시도...\n");
			free(primes[n]);
			primes[n] = NULL;
			rancnt++;
			NextGenerator(&gen);
		}
	}
	return NULL;


	//printf("Thread[%d]\n", n);
	//primes[n] = (char*)malloc(2);
	//primes[n][0] = (char)(n + zero);
	//primes[n][1] = null;
	//return NULL;
}