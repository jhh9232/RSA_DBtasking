#include "../Headers/common.h"

int Wait(int millisec)
{
	millisec--;
	int result;
	struct timeval timeout;
	//timeout 설정
	timeout.tv_sec = millisec / 1000;              //second
	timeout.tv_usec = (millisec % 1000) * 1000;    //microsecond -> millisecond
	result = select(0, NULL, NULL, NULL, &timeout);
	if (result == -1)	        //오류
	{
		puts("select(): error");
	}
	else if (result == 0)	    //시간초과
	{
		return true;
	}
	return false;
}

int IsNumber(char* n)
{
	int i;
	for (i = 0; i < strlen(n); i++)
	{
		//숫자가 아니면
		if ((n[i] < zero) || n[i] > nine)
		{
			return false;
		}
	}
	return true;
}
void Eliminate(char* n)
{
	for (; *n != null; n++)
	{
		if (*n < zero || *n > nine)
		{
			//만약 복사, 이동중 메모리블록이 겹쳐지게 되는 상황이 발생한다면 strncpy, memcpy 사용하지 말 것
			memmove(n, n + 1, strlen(n+1));
			n[strlen(n) - 1] = null;
			n--;
		}
	}
}
void Reverse(char* n)
{
	int i, size = (int)strlen(n);
	char* tmp = NULL;
	if (size < 2)
		return;
	tmp = (char*)malloc(strlen(n));
	strncpy(tmp, n, (size_t)size);
	for (i = 1; i <= size; i++)
	{
		n[size - i] = tmp[i - 1];
	}
	free(tmp);
}

void ReverseMalloc(char** n)
{
	int i, size = (int)strlen(*n);
	char* tmp = NULL;
	if (size < 2)
		return;
	tmp = (char*)malloc((size_t)size + 1);
	strncpy(tmp, *n, (size_t)+size);
	for (i = 1; i <= size; i++)
	{
		(*n)[size - i] = tmp[i - 1];
	}
	free(tmp);
}

void ReversePrint(const char *explain, char* n)
{
	if (explain)
		printf("%s : ", explain);
	if (n == NULL)
	{
		printf("EMPTY\n");
		return;
	}
	int i = 0;
	size_t size = strlen(n);
	size--;
	
	for (i = (int)size; i >= 1; i--)
	{
		printf("%c", n[i]);
		//if (i % 3 == 0)
		//	printf(",");
	}
	printf("%c\n", n[0]);
}
void ReverseMinusPrint(const char* explain, char* n)
{
	if (explain)
		printf("%s : -", explain);
	if (n == NULL)
	{
		printf("EMPTY\n");
		return;
	}
	int i = 0;
	size_t size = strlen(n);
	size--;

	for (i = (int)size; i >= 1; i--)
	{
		printf("%c", n[i]);
		//if (i % 3 == 0)
		//	printf(",");
	}
	printf("%c\n", n[0]);
}


void SetLInit(LInt* bInt)
{
	bInt->sign = null;
	bInt->len = 0;
	if (bInt->num)
		free(bInt->num);
	bInt->num = NULL;
}

LInt SetLArray(char* str)
{
	LInt bInt;
	size_t sLen = 0;
	char* number = NULL;
	if (!str || !strncmp(str, "", strlen(str)))
		str = "0";
	if (str[0] >= zero && str[0] <= nine)
	{
		bInt.sign = plus;
		sLen = strlen(str);
		number = (char*)malloc(sLen + 1);
		strncpy(number, str, sLen);
		number[sLen] = null;
	}
	else
	{
		bInt.sign = minus;
		sLen = strlen(str + 1);
		number = (char*)malloc(sLen + 1);
		strncpy(number, str + 1, sLen);
		number[sLen] = null;
	}

	ReverseMalloc(&number);
	bInt.len = sLen;
	bInt.num = number;
	return bInt;
}

LInt SetLInt(char* str)
{
	if (!str || !strncmp(str, "", strlen(str)))
		str = "0";
	size_t sLen = 0;
	char* number = NULL;
	char sign = null;
	if (str[0] >= zero && str[0] <= nine)
		sign = plus;
	else
		sign = minus;
	Eliminate(str);
	Reverse(str);
	sLen = strlen(str);
	number = (char*)malloc(sLen + 1);
	strncpy(number, str, sLen);
	number[sLen] = null;
	LInt bInt = { .sign = sign, .len = sLen, .num = number };
	return bInt;
}

void LIntPrint(LInt bInt)
{
	printf(".sign = %c\n", bInt.sign);
	printf(".len  = %ld\n", bInt.len);
	printf(".num  = %s", bInt.num);
	if (bInt.sign == minus)
	{
		printf("-\n");
		ReverseMinusPrint(".rev ", bInt.num);
	}
	else
	{
		printf("\n");
		ReversePrint(".rev ", bInt.num);
	}
}

void LIntSetMalloc(char** result, size_t size)
{
	if (*result)
		free(*result);

	*result = (char*)malloc(size + 1);
}

void LIntSetCalloc(char** result, size_t size)
{
	if (*result)
		free(*result);

	*result = (char*)calloc(size + 1, sizeof(char));
}

void LIntCopy(LInt* dest, LInt* source)
{
	dest->sign = source->sign;
	dest->len = source->len;
	LIntSetMalloc(&(dest->num), source->len);
	strncpy(dest->num, source->num, source->len);
	dest->num[source->len] = null;
}

void LIntCopySize(LInt* dest, LInt* source, size_t size)
{
	dest->sign = source->sign;
	dest->len = source->len;
	LIntSetMalloc(&(dest->num), size);
	strncpy(dest->num, source->num, source->len);
	dest->num[source->len] = null;
}