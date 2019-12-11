#include "../Headers/PrimeThread.h"

pthread_rwlock_t rwLock;
LInt primes[TLEN];
int tresult[TLEN];

void WriteTres(int);
int ReadTres();

void WriteTres(int n)
{
	pthread_rwlock_wrlock(&rwLock);

	tresult[n] = true;

	pthread_rwlock_unlock(&rwLock);
}
int ReadTres()
{
	pthread_rwlock_rdlock(&rwLock);
	for (int i = 0; i < TLEN; i++)
	{
		if (tresult[i])
		{
			pthread_rwlock_unlock(&rwLock);
			return true;
		}
	}
	pthread_rwlock_unlock(&rwLock);
	return false;
}

void InitTglobal()
{
	for (int i = 0; i < TLEN; i++)
	{
		primes[i].sign = null;
		primes[i].len = 0;
		primes[i].num = NULL;

		tresult[i] = false;
	}
}

void LIntThreadCopy(LInt* bInt, int len)
{
	primes[len].sign = bInt->sign;
	primes[len].len = bInt->len;
	if (primes[len].num)
		free(primes[len].num);
	primes[len].num = bInt->num;
}

void* ThreadGenerator(void* arg)
{
	int n = *(int*)arg;
	int cnt = 0;
	//long long int rancnt = 0;
	LInt result = { null, 0, NULL };
	LInt con = SetLArray("2");
	LParsePrime(&result, primes[n], con);
	if (result.len == 1 && !(strncmp(result.num, "1", result.len)))
	{
		printf("success...\n");
		WriteTres(n);
		free(con.num);
		free(result.num);
		return NULL;
	}
	
	while (true)
	{
		clock_t tstart = clock();
		SetLInit(&result);
		AddGenerator(&(primes[n]), TADD);
		LParsePrime(&result, primes[n], con);
		if (result.len == 1 && !(strncmp(result.num, "1", result.len)))
		{
			printf("success...\n");
			WriteTres(n);
			free(con.num);
			free(result.num);
			return NULL;
		}
		if (ReadTres())
		{
			printf("another thread success...\n");
			free(con.num);
			free(result.num);
			return NULL;
		}
		cnt++;
		printf("%d retry in %d Thread... time : %.20lf \n", cnt, n, (double)(clock() - tstart) / CLOCKS_PER_SEC);
	}
	
}
