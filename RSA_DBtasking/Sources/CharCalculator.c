#include "../Headers/CharCalculator.h"
#include <malloc.h>
#include <stdarg.h>
#define CALLEN 405

int Plus(LInt*, LInt, LInt);
int Minus(LInt*, LInt, LInt);
int Multiple(LInt*, LInt, LInt);
int Divide(LInt*, LInt, LInt, int);

void Modular(char** result, char* num1, char* num2, char* n, char oper)
{
	clock_t start = clock();
	switch (oper)
	{
	case plus:
		//(a mod(n) + b mod(n)) mod(n) = (a + b) mod(n)
		printf("Modular plus\n");
		//Plus(result, num1, num2);
		//Divide(result, *result, n, true);
		break;
	case minus:
		//(a mod(n) - b mod(n)) mod(n) = (a - b) mod(n)
		printf("Modular minus\n");
		//Minus(result, num1, num2);
		//Divide(result, *result, n, true);
		break;
	case multiple:
		//(a mod(n) * b mod(n)) mod(n) = (a * b) mod(n)
		printf("Modular multiple\n");
		break;
	case square:
		//100 ^ 50 = 정확히 100자리 1e+100
		//((a mod(n))^ b) mod(n) = a ^ b mod(n)
		//2^90 mod 13 = (2^50 * 2^40) mod 13
		printf("Modular square\n");
		break;
	default:
		return;
	}
	printf("Time : %.5lf\n", (double)(clock() - start) / CLOCKS_PER_SEC);
}

int LIntCompare(LInt* left, LInt* right, int absolute)
{
	if (absolute)
	{
		if (left->len < right->len) return -1;
		else if (left->len > right->len) return 1;

		for (int i = (int)left->len - 1; i >= 0; i--)
		{
			if (left->num[i] < right->num[i]) return -1;
			else if (left->num[i] > right->num[i]) return 1;
		}
		return 0;
	}
	else
	{
		if (left->sign == plus && right->sign == plus)
			return LIntCompare(left, right, true);
		else if (left->sign == minus && right->sign == minus)
			return LIntCompare(right, left, true);
		else
			return left->sign;
	}
}

void LIntSwap(LInt* left, LInt* right)
{
	size_t lLen = left->len, rLen = right->len;
	char lSign = left->sign, rSign = right->sign;

	char* temp = left->num;

	left->num = right->num;
	left->len = rLen;
	left->sign = rSign;

	right->num = temp;
	right->len = lLen;
	right->sign = lSign;
}

//void LIntPSwap(LInt** left, LInt** right)
//{
//	if (!(*left) || !(*right))
//		return;
//
//	size_t lLen = (*left)->len, rLen = (*right)->len;
//	char lSign = (*left)->sign, rSign = (*right)->sign;
//
//	char* temp = (*left)->num;
//
//	(*left)->num = (*right)->num;
//	(*left)->len = rLen;
//	(*left)->sign = rSign;
//
//	(*right)->num = temp;
//	(*right)->len = lLen;
//	(*right)->sign = lSign;
//}

void SetZeroMalloc(char** result)
{
	if ((*result) != NULL)
		free(*result);
	*result = (char*)malloc(2);
	(*result)[0] = zero;
	(*result)[1] = null;
}

void SetZero(LInt* result)
{
	SetZeroMalloc(&(result->num));
	result->sign = plus;
	result->len = 1;
}
void SetMalloc(char** result, size_t size)
{
	if (*result)
		free(*result);

	*result = (char*)malloc(size + 1);
}
void SetCalloc(char** result, size_t size)
{
	if (*result)
		free(*result);

	*result = (char*)calloc(size + 1, sizeof(char));
}

void LIntCopy(LInt* dest, LInt* source)
{
	if (!dest)
		return;
	dest->sign = source->sign;
	dest->len = source->len;
	SetMalloc(&(dest->num), source->len);
	strncpy(dest->num, source->num, source->len);
	dest->num[source->len] = null;
}
void LIntCopySize(LInt* dest, LInt* source, size_t size)
{
	if (!dest)
		return;
	dest->sign = source->sign;
	dest->len = source->len;
	SetMalloc(&(dest->num), size);
	strncpy(dest->num, source->num, source->len);
	dest->num[source->len] = null;
}

int IsZero(LInt* bInt)
{
	if (bInt && bInt->len == 1 && bInt->num[0] == zero && bInt->num[1] == null) return true;
	return false;
}

void EraseHeadZero(LInt* bInt)
{
	for (size_t i = bInt->len - 1; i >= 1; i--)
	{
		if (bInt->num[i] == zero)
		{
			bInt->num[i] = null;
			bInt->len--;
		}
		else break;
	}
}


//https://github.com/njw1204/calculator-in-c
int Plus(LInt* result, LInt num1, LInt num2)
{
	LInt n1 = { null, 0, NULL }, n2 = { null, 0, NULL };
	LIntCopy(&n1, &num1);
	LIntCopy(&n2, &num2);
	if (LIntCompare(&n1, &n2, true) == -1)
		LIntSwap(&n1, &n2);

	if (IsZero(&n2)) {
		LIntCopy(result, &n1);
		free(n1.num);
		free(n2.num);
		return SUCCESS;
	}
	//부호가 같은 덧셈
	if (n1.sign == n2.sign) {
		SetMalloc(&(result->num), n1.len + 1);
		int carry = 0;
		for (int i = 0; i < n1.len; i++) {
			int sum = n1.num[i] - zero + carry;
			if (i < n2.len) sum += n2.num[i] - zero;
			if (sum >= 10) {
				sum -= 10;
				carry = 1;
			}
			else carry = 0;
			result->num[i] = (char)(sum + zero);
		}

		if (carry) {
			if (n1.len >= LARGELEN) {
				SetZero(result);
				free(n1.num);
				free(n2.num);
				return ERROR;
			}
			else {
				result->num[n1.len] = one;
				result->num[n1.len + 1] = null;
				result->len = n1.len + 1;
			}
		}
		else
		{
			result->num[n1.len] = null;
			result->len = n1.len;
		}

		if (IsZero(result)) result->sign = plus;
		result->sign = n1.sign;
		free(n1.num);
		free(n2.num);
		return SUCCESS;
	}
	//부호가 다른 덧셈
	else {
		n2.sign = n1.sign;
		int RESULT = Minus(result, n1, n2);
		free(n1.num);
		free(n2.num);
		return RESULT;
	}
}

int Minus(LInt* result, LInt num1, LInt num2)
{
	LInt n1 = { null, 0, NULL }, n2 = { null, 0, NULL };
	LIntCopy(&n1, &num1);
	LIntCopy(&n2, &num2);
	if (n1.sign != n2.sign)
	{
		n2.sign = n1.sign;
		int RESULT = Plus(result, n1, n2);
		free(n1.num);
		free(n2.num);
		return RESULT;
	}
	else if (n1.sign == minus && n2.sign == minus)
	{
		LIntSwap(&n1, &n2);
		n1.sign = plus;
		n2.sign = plus;
	}

	char signFlag = 0;
	int cmp = LIntCompare(&n1, &n2, true);
	if (cmp == -1)
	{
		LIntSwap(&n1, &n2);
		signFlag = minus;
	}
	else if (cmp == 1)
	{
		signFlag = plus;
	}
	else
	{
		SetZero(result);
		free(n1.num);
		free(n2.num);
		return SUCCESS;
	}
	if (IsZero(&n2))
	{
		LIntCopy(result, &n1);
		free(n1.num);
		free(n2.num);
		return SUCCESS;
	}

	int carry = 0;
	SetMalloc(&(result->num), n1.len);
	for (int i = 0; i < n1.len; i++)
	{
		int sum = n1.num[i] - zero + carry;
		if (i < n2.len) sum -= n2.num[i] - zero;
		if (sum < 0)
		{
			sum += 10;
			carry = -1;
		}
		else carry = 0;
		result->num[i] = (char)(sum + zero);
	}
	result->len = n1.len;
	result->num[result->len] = null;

	result->sign = signFlag;
	EraseHeadZero(result);
	if (IsZero(result)) result->sign = plus;
	free(n1.num);
	free(n2.num);
	return SUCCESS;
}

int gitMultiple10(LInt* bInt, size_t count)
{
	if (IsZero(bInt)) return SUCCESS;
	if (bInt->len + count > LARGELEN)
	{
		SetZero(bInt);
		return ERROR;
	}
	memmove(bInt->num + count, bInt->num, bInt->len);
	for (size_t i = 0; i < count; i++) bInt->num[i] = zero;
	bInt->len += count;
	bInt->num[bInt->len] = null;
	return SUCCESS;
}
void GetMulOneDigit(LInt* mulOne, LInt num)
{
	SetZero(mulOne);
	for (int i = 1; i <= 9; i++)
		Plus(&mulOne[i], mulOne[i-1], num);
}

int Multiple(LInt* result, LInt num1, LInt num2)
{
	LInt n1 = { null, 0, NULL };
	LInt n2 = { null, 0, NULL };
	LIntCopy(&n1, &num1);
	LIntCopy(&n2, &num2);
	char signFlag = null;
	if (n1.sign == n2.sign) signFlag = plus;
	else signFlag = minus;
	//잉여?
	n1.sign = plus;
	n2.sign = plus;

	if (IsZero(&n1) || IsZero(&n2))
	{
		SetZero(result);
		free(n1.num);
		free(n2.num);
		return SUCCESS;
	}

	LInt mulOne[10];
	for (int i = 0; i < 10; i++)
	{
		mulOne[i].len = 0;
		mulOne[i].sign = null;
		mulOne[i].num = NULL;
	}
	GetMulOneDigit(mulOne, n1);
	SetMalloc(&(result->num), n1.len + n2.len);
	result->len = 1;
	result->num[0] = zero;
	result->num[1] = null;
	for (size_t i = 0; i < n2.len; i++)
	{
		LInt temp = { null, 0, NULL };
		if (n2.num[i] == zero) continue;
		size_t onelen = (size_t)(n2.num[i] - zero);
		LIntCopySize(&temp, &mulOne[onelen], mulOne[onelen].len + i);
		if (gitMultiple10(&temp, i) == ERROR)
		{
			for (int j = 0; j < 10; j++)
				free(mulOne[j].num);
			free(temp.num);
			SetZero(result);
			free(n1.num);
			free(n2.num);
			return ERROR;
		}
		LInt plusT = { null, 0, NULL };
		LIntCopy(&plusT, result);
		if (Plus(result, plusT, temp) == ERROR)
		{
			for (int j = 0; j < 10; j++)
				free(mulOne[j].num);
			free(plusT.num);
			free(temp.num);
			SetZero(result);
			free(n1.num);
			free(n2.num);
			return ERROR;
		}
		free(plusT.num);
		free(temp.num);
	}
	result->sign = signFlag;
	if (IsZero(result)) result->sign = 1;
	for (int j = 0; j < 10; j++)
		free(mulOne[j].num);

	free(n1.num);
	free(n2.num);
	return SUCCESS;
}
int Divide(LInt* result, LInt num1, LInt num2, int isMod)
{
	LInt n1 = { null, 0, NULL };
	LInt n2 = { null, 0, NULL };
	LIntCopy(&n1, &num1);
	LIntCopy(&n2, &num2);
	char signFlag = null;
	if (n1.sign == n2.sign) signFlag = plus;
	else signFlag = minus;
	n1.sign = plus;
	n2.sign = plus;

	if (IsZero(&n2))
	{
		SetZero(result);
		free(n1.num);
		free(n2.num);
		return ERROR;
	}

	int cmp = LIntCompare(&n1, &n2, true);
	if (cmp == -1)
	{
		if (isMod)
		{
			LIntCopy(result, &n1);
			free(n1.num);
			free(n2.num);
		}
		else
		{
			SetZero(result);
			free(n1.num);
			free(n2.num);
		}
		return SUCCESS;
	}
	else if (cmp == 0)
	{
		SetZero(result);
		if(!isMod)
			result->num[0] = one;
		free(n1.num);
		free(n2.num);
		return SUCCESS;
	}
	LInt mulOne[10];
	LInt div = { null, 0, NULL };
	LIntCopy(&div, &n1);
	for (int i = 0; i < 10; i++)
	{
		mulOne[i].len = 0;
		mulOne[i].sign = null;
		mulOne[i].num = NULL;
	}
	GetMulOneDigit(mulOne, n2);
	SetCalloc(&(result->num), n1.len);
	result->len = 0;

	for (int i = (int)(div.len) - (int)(n2.len); i >= 0; i--)
	{
		LInt temp = { null, 0, NULL };
		LInt plusT = { null, 0, NULL };
		int match = 0;
		if (i >= div.len)
		{
			for (int j = i; j >= div.len; j--) result->num[j] = zero;
			i = (int)(div.len - 1);
		}
		SetMalloc(&(temp.num), (div.len - (size_t)i));
		strncpy(temp.num, (div.num + i), div.len - (size_t)i);
		temp.num[div.len - (size_t)i] = null;
		temp.len = div.len - (size_t)i;

		for (int j = 1; j <= 9; j++)
		{
			if (LIntCompare(&mulOne[j], &temp, TRUE) == 1)
			{
				match = j - 1;
				result->num[i] = (char)(match + zero);
				break;
			}
			else if (j == 9)
			{
				match = 9;
				result->num[i] = nine;
			}
		}
		LIntCopySize(&temp, &mulOne[match], mulOne[match].len + (size_t)i + 1);
		gitMultiple10(&temp, (size_t)i);
		LIntCopy(&plusT, &div);
		Minus(&div, plusT, temp);
		free(plusT.num);
		free(temp.num);

		if (IsZero(&div))
		{
			for (int t = 0; t < i; t++)
				result->num[t] = zero;
			break;
		}
	}
	result->len = strlen(result->num);
	for (int i = 0; i < 10; i++)
		free(mulOne[i].num);

	result->sign = signFlag;
	//printf("quo : %s\n", result->num);
	//printf("mod : %s\n", div.num);
	if (isMod)
	{
		LIntCopy(result, &div);
		EraseHeadZero(result);
		free(div.num);
		free(n1.num);
		free(n2.num);
		return SUCCESS;
	}
	else
	{
		free(div.num);
		EraseHeadZero(result);
		free(n1.num);
		free(n2.num);
		return SUCCESS;
	}
}

int ChangeBinary(LInt* bin, LInt num)
{
	//clock_t start = clock();
	int i = 0;
	char res[LARGELEN] = { null, };
	LInt binT = { null, 0, NULL };
	LIntCopy(&binT, &num);
	while(binT.num[0] != zero || binT.num[1] != null)
	{
		if ((binT.num[0] - zero) % 2 == 0)
			res[i] = zero;
		else
			res[i] = one;

		Divide(&binT, binT, SLConst("2"), false);
		i++;
		if (i >= LARGELEN)
		{
			free(binT.num);
			SetZero(bin);
			return ERROR;
		}
	}
	size_t resLen = strlen(res);
	SetMalloc(&(bin->num), resLen);
	strncpy(bin->num, res, resLen);
	bin->num[resLen] = null;
	bin->len = resLen;
	//LIntPrint(*bin);
	free(binT.num);
	return SUCCESS;
}

int ModularSquare(LInt* result, LInt P, LInt a)
{
	LInt binP = { null, 0, NULL };
	LInt temp = { null, 0, NULL };
	LInt sqrmod = { null, 0, NULL };
	LIntCopy(&sqrmod, &a);
	Minus(&binP, P, SLConst("1"));
	ChangeBinary(&binP, binP);
	ReversePrint("rev bin", binP.num);
	printf("len(bin) : %d\n", strlen(binP.num));
	
	Divide(&sqrmod, sqrmod, P, true);
	if (binP.num[0] == one)
	{
		SetMalloc(&(result->num), sqrmod.len);
		strncpy(result->num, sqrmod.num, sqrmod.len);
		result->num[sqrmod.len] = null;
	}
	else
	{
		SetZero(result);
		result->num[0] = one;
	}
	for (int i = 1; i < binP.len; i++)
	{
		Multiple(&sqrmod, sqrmod, sqrmod);
		Divide(&sqrmod, sqrmod, P, true);
		if (binP.num[i] == one)
		{
			Multiple(result, *result, sqrmod);
			Divide(result, *result, P, true);
		}
	}
	
	free(temp.num);
	free(binP.num);
	free(sqrmod.num);
	printf("====================\n");
	LIntPrint(*result);
	printf("====================\n");
	return SUCCESS;
}