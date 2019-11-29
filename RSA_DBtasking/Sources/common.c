#include "../Headers/common.h"

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