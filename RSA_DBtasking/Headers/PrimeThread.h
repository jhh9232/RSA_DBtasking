#ifndef PRIME_THREAD_H
#define PRIME_THREAD_H

#include "./CreatePrime.h"
#include <pthread.h>
#include <semaphore.h>
#define TLEN 2

extern sem_t semaphore;
extern char* primes[2];

void* ThreadGenerator(void*);

#endif