#ifndef PRIME_THREAD_H
#define PRIME_THREAD_H


#include "./CreatePrime.h"
#include <sys/types.h>
#include <pthread.h>
#define TLEN 8
#define TADD "20"
#define TERR -1

extern pthread_rwlock_t rwLock;
extern LInt primes[TLEN];
extern int tresult[TLEN];

void InitTglobal();
void* ThreadGenerator(void*);

#endif