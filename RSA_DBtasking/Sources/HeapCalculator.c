#include "../Headers/HeapCalculator.h"
#include <malloc.h>
#include <stdarg.h>
#define CALLEN 405

int LIntCompare(LInt*, LInt*, int);
void LIntSwap(LInt*, LInt*);
void LIntSetZeroMalloc(char**);
void LIntSetZero(LInt*);
int LIntIsZero(LInt*);
void LIntEraseHeadZero(LInt*);

//https://github.com/njw1204/calculator-in-c
int LPlus(LInt* result, LInt num1, LInt num2)
{
	LInt n1 = { null, 0, NULL }, n2 = { null, 0, NULL };
	LIntCopy(&n1, &num1);
	LIntCopy(&n2, &num2);
	if (LIntCompare(&n1, &n2, true) == -1)
		LIntSwap(&n1, &n2);

	if (LIntIsZero(&n2)) {
		LIntCopy(result, &n1);
		free(n1.num);
		free(n2.num);
		return SUCCESS;
	}
	//부호가 같은 덧셈
	if (n1.sign == n2.sign)
	{
		LIntSetMalloc(&(result->num), n1.len + 1);
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
				LIntSetZero(result);
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

		if (LIntIsZero(result)) result->sign = plus;
		result->sign = n1.sign;
		free(n1.num);
		free(n2.num);
		return SUCCESS;
	}
	//부호가 다른 덧셈
	else {
		n2.sign = n1.sign;
		int RESULT = LMinus(result, n1, n2);
		free(n1.num);
		free(n2.num);
		return RESULT;
	}
}

int LMinus(LInt* result, LInt num1, LInt num2)
{
	LInt n1 = { null, 0, NULL }, n2 = { null, 0, NULL };
	LIntCopy(&n1, &num1);
	LIntCopy(&n2, &num2);
	if (n1.sign != n2.sign)
	{
		n2.sign = n1.sign;
		int RESULT = LPlus(result, n1, n2);
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
		LIntSetZero(result);
		free(n1.num);
		free(n2.num);
		return SUCCESS;
	}
	if (LIntIsZero(&n2))
	{
		LIntCopy(result, &n1);
		free(n1.num);
		free(n2.num);
		return SUCCESS;
	}

	int carry = 0;
	LIntSetMalloc(&(result->num), n1.len);
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
	LIntEraseHeadZero(result);
	if (LIntIsZero(result)) result->sign = plus;
	free(n1.num);
	free(n2.num);
	return SUCCESS;
}

// ==== help multiple, divide ====
int LMultiple10(LInt* bInt, size_t count)
{
	if (LIntIsZero(bInt)) return SUCCESS;
	if (bInt->len + count > LARGELEN)
	{
		LIntSetZero(bInt);
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
	LIntSetZero(mulOne);
	for (int i = 1; i <= 9; i++)
		LPlus(&mulOne[i], mulOne[i-1], num);
}
// ===============================

int LMultiple(LInt* result, LInt num1, LInt num2)
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

	if (LIntIsZero(&n1) || LIntIsZero(&n2))
	{
		LIntSetZero(result);
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
	LIntSetMalloc(&(result->num), n1.len + n2.len);
	result->len = 1;
	result->num[0] = zero;
	result->num[1] = null;
	for (size_t i = 0; i < n2.len; i++)
	{
		LInt temp = { null, 0, NULL };
		if (n2.num[i] == zero) continue;
		size_t onelen = (size_t)(n2.num[i] - zero);
		LIntCopySize(&temp, &mulOne[onelen], mulOne[onelen].len + i);
		if (LMultiple10(&temp, i) == ERROR)
		{
			for (int j = 0; j < 10; j++)
				free(mulOne[j].num);
			free(temp.num);
			LIntSetZero(result);
			free(n1.num);
			free(n2.num);
			return ERROR;
		}
		LInt plusT = { null, 0, NULL };
		LIntCopy(&plusT, result);
		if (LPlus(result, plusT, temp) == ERROR)
		{
			for (int j = 0; j < 10; j++)
				free(mulOne[j].num);
			free(plusT.num);
			free(temp.num);
			LIntSetZero(result);
			free(n1.num);
			free(n2.num);
			return ERROR;
		}
		free(plusT.num);
		free(temp.num);
	}
	result->sign = signFlag;
	if (LIntIsZero(result)) result->sign = 1;
	for (int j = 0; j < 10; j++)
		free(mulOne[j].num);

	free(n1.num);
	free(n2.num);
	return SUCCESS;
}
int LDivide(LInt* result, LInt num1, LInt num2, int isMod)
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

	if (LIntIsZero(&n2))
	{
		LIntSetZero(result);
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
			LIntSetZero(result);
			free(n1.num);
			free(n2.num);
		}
		return SUCCESS;
	}
	else if (cmp == 0)
	{
		LIntSetZero(result);
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
	LIntSetCalloc(&(result->num), n1.len);
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
		LIntSetMalloc(&(temp.num), (div.len - (size_t)i));
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
		LMultiple10(&temp, (size_t)i);
		LIntCopy(&plusT, &div);
		LMinus(&div, plusT, temp);
		free(plusT.num);
		free(temp.num);

		if (LIntIsZero(&div))
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
		LIntEraseHeadZero(result);
		free(div.num);
		free(n1.num);
		free(n2.num);
		return SUCCESS;
	}
	else
	{
		free(div.num);
		LIntEraseHeadZero(result);
		free(n1.num);
		free(n2.num);
		return SUCCESS;
	}
}

int LChangeBinary(LInt* bin, LInt num)
{
	//clock_t start = clock();
	int i = 0;
	char res[LARGELEN] = { null, };
	LInt binT = { null, 0, NULL };
	LInt mtwo = SetLArray("2");
	LIntCopy(&binT, &num);
	while(binT.num[0] != zero || binT.num[1] != null)
	{
		if ((binT.num[0] - zero) % 2 == 0)
			res[i] = zero;
		else
			res[i] = one;

		LDivide(&binT, binT, mtwo, false);
		i++;
		if (i >= LARGELEN)
		{
			free(binT.num);
			LIntSetZero(bin);
			return ERROR;
		}
	}
	size_t resLen = strlen(res);
	LIntSetMalloc(&(bin->num), resLen);
	strncpy(bin->num, res, resLen);
	bin->num[resLen] = null;
	bin->len = resLen;
	//LIntPrint(*bin);
	free(binT.num);
	free(mtwo.num);
	return SUCCESS;
}

int LParsePrime(LInt* result, LInt P, LInt a)
{
	LInt binP = { null, 0, NULL };
	LInt sqrmod = { null, 0, NULL };
	LInt mone = SetLArray("1");
	LIntCopy(&sqrmod, &a);
	LMinus(&binP, P, mone);
	free(mone.num);
	LChangeBinary(&binP, binP);
	//ReversePrint("rev bin", binP.num);
	//printf("len(bin) : %ld\n", strlen(binP.num));
	
	LDivide(&sqrmod, sqrmod, P, true);
	if (binP.num[0] == one)
	{
		result->len = sqrmod.len;
		LIntSetMalloc(&(result->num), sqrmod.len);
		strncpy(result->num, sqrmod.num, sqrmod.len);
		result->num[sqrmod.len] = null;
	}
	else
	{
		LIntSetZero(result);
		result->num[0] = one;
	}
	for (int i = 1; i < binP.len; i++)
	{
		LMultiple(&sqrmod, sqrmod, sqrmod);
		LDivide(&sqrmod, sqrmod, P, true);
		if (binP.num[i] == one)
		{
			LMultiple(result, *result, sqrmod);
			LDivide(result, *result, P, true);
		}
	}
	free(binP.num);
	free(sqrmod.num);
	//printf("====================\n");
	//LIntPrint(*result);
	//printf("====================\n");
	return SUCCESS;
}

int LModularSquare(LInt* result, LInt P, LInt a, LInt modn)
{
	LInt binP = { null, 0, NULL };
	LInt sqrmod = { null, 0, NULL };
	LIntCopy(&sqrmod, &a);
	LChangeBinary(&binP, P);

	LDivide(&sqrmod, sqrmod, modn, true);
	if (binP.num[0] == one)
	{
		result->len = sqrmod.len;
		LIntSetMalloc(&(result->num), sqrmod.len);
		strncpy(result->num, sqrmod.num, sqrmod.len);
		result->num[sqrmod.len] = null;
	}
	else
	{
		LIntSetZero(result);
		result->num[0] = one;
	}
	for (int i = 1; i < binP.len; i++)
	{
		LMultiple(&sqrmod, sqrmod, sqrmod);
		LDivide(&sqrmod, sqrmod, modn, true);
		if (binP.num[i] == one)
		{
			LMultiple(result, *result, sqrmod);
			LDivide(result, *result, modn, true);
		}
	}
	free(modn.num);
	free(binP.num);
	free(sqrmod.num);
	//printf("====================\n");
	//LIntPrint(*result);
	//printf("====================\n");
	return SUCCESS;
}


//Non Include Header Function
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

void LIntSetZeroMalloc(char** result)
{
	if ((*result) != NULL)
		free(*result);
	*result = (char*)malloc(2);
	(*result)[0] = zero;
	(*result)[1] = null;
}

void LIntSetZero(LInt* result)
{
	LIntSetZeroMalloc(&(result->num));
	result->sign = plus;
	result->len = 1;
}

int LIntIsZero(LInt* bInt)
{
	if (bInt && bInt->len == 1 && bInt->num[0] == zero && bInt->num[1] == null) return true;
	return false;
}

void LIntEraseHeadZero(LInt* bInt)
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



/*
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
*/