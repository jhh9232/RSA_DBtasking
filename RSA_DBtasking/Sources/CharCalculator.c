#include "../Headers/CharCalculator.h"
#include <malloc.h>
#include <stdarg.h>
#define CALLEN 405

int gitPlus(LInt*, LInt, LInt);
int gitMinus(LInt*, LInt, LInt);
int gitMultiple(LInt*, LInt, LInt);
int gitDivide(LInt*, LInt, LInt, int);

void Plus(char** result, char* num1, char* num2)
{
	char res[CALLEN] = { null, };
	int i = 0, carry = 0;
	while (true)
	{
		if (*num1 == null)
		{
			if (*num2 == null)
			{
				if (carry > 0)
					res[i] = (char)(carry + zero);
				break;
			}
			else
			{
				res[i] = (char)((*num2 - 48) + carry);
				num2++;
			}
		}
		else if (*num2 == null)
		{
			res[i] = (char)((*num1 - zero) + carry);
			num1++;
		}
		else
		{
			res[i] = (char)((*num1 - zero) + (*num2 - zero) + carry);
			num1++;
			num2++;
		}

		if (res[i] > 9)
		{
			res[i] = (char)(res[i] - 10);
			carry = 1;
		}
		else
		{
			carry = 0;
		}
		res[i] = (char)(res[i] + zero);
		i++;
	}
	if (*result != NULL)
		free(*result);
	*result = (char*)malloc(strlen(res) + 1);
	strncpy(*result, res, strlen(res) + 1);
	(*result)[strlen(res)] = null;
}

void Minus(char** result, char* num1, char* num2)
{
	char res[CALLEN] = { null, };
	int i = 0, carry = 0;
	while (true)
	{
		if (*num1 == null)
		{
			if (*num2 == null)
			{
				//음수일 경우 0을 리턴
				if (carry == 1)
				{
					res[0] = minus;
					res[1] = null;
					break;
				}
				break;
			}
			else
			{
				res[i] = (char)(0 - (*num2 - 48) - carry);
				num2++;
			}
		}
		else if (*num2 == null)
		{
			res[i] = (char)((*num1 - zero) - carry);
			num1++;
		}
		else
		{
			res[i] = (char)((*num1 - zero) - (*num2 - zero) - carry);
			num1++;
			num2++;
		}

		if (res[i] < 0)
		{
			res[i] = (char)(res[i] + 10);
			carry = 1;
		}
		else
		{
			carry = 0;
		}
		res[i] = (char)(res[i] + zero);
		i++;
	}
	while (strlen(res) > 0 && res[strlen(res) - 1] == zero)
		res[strlen(res) - 1] = null;
	if (res[0] == null)
		res[0] = zero;

	if (*result != NULL)
		free(*result);
	*result = (char*)malloc(strlen(res) + 1);
	strncpy(*result, res, strlen(res) + 1);
	(*result)[strlen(res)] = null;
}

void Multiple(char** result, char* num1, char* num2)
{
	//2자리*2자리 = 4자리 (99*99 = 9801), 3자리*3자리 = 6자리 (999*999 = 998001)
	char* res = (char*)malloc(2);
	res[0] = zero;
	res[1] = null;

	if (num2[0] == zero && num2[1] == null)
		return;

	int i = 0, cipher = 0;
	while (*num2 != null)
	{
		char save[CALLEN] = { null, };
		int carry = 0, num1Size = (int)strlen(num1);
		for (i = 0; i < cipher; i++)
			save[i] = zero;
		for (i = cipher; i < num1Size + cipher; i++)
		{
			save[i] = (char)((num1[i - cipher] - zero) * (*num2 - zero) + carry);
			if (save[i] > 9)
			{
				carry = (int)(save[i] / 10);
				save[i] = (char)(save[i] % 10 + zero);
			}
			else
			{
				carry = 0;
				save[i] = (char)(save[i] + zero);
			}
		}
		if (carry > 0)
			save[(int)strlen(num1) + cipher] = (char)(carry + zero);

		Plus(&res, save, res);
		cipher++;
		num2++;
	}

	if (*result != NULL)
	{
		free(*result);
	}
	*result = (char*)malloc(strlen(res) + 1);
	strncpy(*result, res, strlen(res) + 1);
	(*result)[strlen(res)] = null;
	free(res);
}

void Divide(char** result, char* num1, char* num2, int isMod)
{
	//clock_t start = clock();
	char res[CALLEN] = { null, };

	int i;
	char quotient[CALLEN] = { null, };     //역순저장이 안 될 예정
	if ((num2[0] == zero && num2[1] == null))
	{
		if (*result)
			free(*result);
		*result = (char*)malloc(2);
		(*result)[0] = divide;
		(*result)[1] = null;
		return;
	}
	else if (strlen(num1) < strlen(num2))
	{
		if (isMod)
		{
			char* memory = (char*)malloc(strlen(num1) + 1);
			strncpy(memory, num1, strlen(num1));
			memory[strlen(num1)] = null;
			if (*result)
				free(*result);
			*result = (char*)malloc(strlen(memory) + 1);
			strncpy(*result, memory, strlen(memory));
			(*result)[strlen(memory)] = null;
			free(memory);
			return;
		}
		else
		{
			if (*result)
				free(*result);
			*result = (char*)malloc(2);
			(*result)[0] = zero;
			(*result)[1] = null;
			return;
		}
	}

	for (i = (int)strlen(num1) - 1; i >= 0; i--)
	{
		size_t size = strlen(res);
		res[size] = num1[i];
		if (strlen(res) >= strlen(num2))
		{
			char* tmpRes = (char*)malloc(strlen(res) + 1);
			strncpy(tmpRes, res, strlen(res) + 1);
			tmpRes[strlen(res)] = null;
			ReverseMalloc(&tmpRes);

			int minusCnt = -1;
			while (tmpRes[0] != minus)
			{
				strncpy(res, tmpRes, strlen(tmpRes));
				memset(res + strlen(tmpRes), null, CALLEN - strlen(tmpRes));
				Minus(&tmpRes, tmpRes, num2);
				minusCnt++;
			}

			while (strlen(res) > 0 && res[strlen(res) - 1] == zero)
				res[strlen(res) - 1] = null;

			quotient[strlen(quotient)] = (char)(minusCnt + zero);
			Reverse(res);
			free(tmpRes);
		}
		else
		{
			quotient[strlen(quotient)] = zero;
		}
	}
	if (*result != NULL)
		free(*result);

	if (isMod == true)
	{
		Reverse(res);
		while (strlen(res) > 0 && res[strlen(res) - 1] == zero)
			res[strlen(res) - 1] = null;
		if (res[0] == null)
			res[0] = zero;
		*result = (char*)malloc(strlen(res) + 1);
		strncpy(*result, res, strlen(res) + 1);
		(*result)[strlen(res)] = null;
		//printf("mod : %s\n", *result);
	}
	else
	{
		Reverse(quotient);
		while (strlen(quotient) > 0 && quotient[strlen(quotient) - 1] == zero)
			quotient[strlen(quotient) - 1] = null;
		if (quotient[0] == null)
			quotient[0] = zero;
		*result = (char*)malloc(strlen(quotient) + 1);
		strncpy(*result, quotient, strlen(quotient) + 1);
		(*result)[strlen(quotient)] = null;
		//printf("quo : %s\n", *result);
	}
	//clock_t end = clock();
	//printf("Div Time : %d\n", (end - start));
	//printf("Div Time : %.20lf\n", (double)(end - start) / CLOCKS_PER_SEC);
}

void ChangeBinary(char** bin, char* dec)
{
	//clock_t start = clock();
	int i = 0;
	char res[CALLEN] = { null, };
	char* cal = (char*)calloc(strlen(dec) + 1, sizeof(char));
	strncpy(cal, dec, strlen(dec));

	while (cal[0] != zero || cal[1] != null)
	{
		if ((cal[0] - zero) % 2 == 0)
			res[i] = zero;
		else
			res[i] = one;
		Divide(&cal, cal, "2", false);
		//printf("cal : %s\n", cal);
		i++;
	}
	free(cal);
	if (*bin != NULL)
		free(*bin);

	*bin = (char*)calloc(strlen(res) + 1, sizeof(char));
	strncpy(*bin, res, strlen(res));

	//printf("origin : %s\nreverse : ", *bin);
	//printf("\n");
	//printf("strlen(bin) : %ld\n", strlen(*bin));
	//printf("Change Bin Time : %.5lf\n", (double)(clock() - start) / CLOCKS_PER_SEC);
}

void Operate(char** result, char* num1, char* num2, char oper)
{
	clock_t start = clock();
	switch (oper)
	{
	case plus:
		printf("plus\n");
		Plus(result, num1, num2);
		break;
	case minus:
		printf("minus\n");
		Minus(result, num1, num2);
		if (*result[0] == minus)
			*result[0] = zero;
		break;
	case multiple:
		printf("multiple\n");
		Multiple(result, num1, num2);
		printf("multiple result : %s\n", *result);
		break;
	case divide:
		printf("divide\n");
		Divide(result, num1, num2, false);
		if (*result[0] == divide)
			*result[0] = zero;
		break;
	case mod:
		printf("Mod\n");
		Divide(result, num1, num2, true);
		if (*result[0] == divide)
			*result[0] = zero;
		break;
	default:
		return;
	}
	printf("Time : %.5lf\n", (double)(clock() - start) / CLOCKS_PER_SEC);
}
void Modular(char** result, char* num1, char* num2, char* n, char oper)
{
	clock_t start = clock();
	switch (oper)
	{
	case plus:
		//(a mod(n) + b mod(n)) mod(n) = (a + b) mod(n)
		printf("Modular plus\n");
		Plus(result, num1, num2);
		Divide(result, *result, n, true);
		break;
	case minus:
		//(a mod(n) - b mod(n)) mod(n) = (a - b) mod(n)
		printf("Modular minus\n");
		Minus(result, num1, num2);
		Divide(result, *result, n, true);
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

void ModularSquare(char** result, char* P, char* a)
{
	//printf("P : %s\n", P);
	clock_t start = clock();
	char* sqr_1 = NULL, * bin = NULL;
	char* sqrmod = (char*)calloc(strlen(a) + 1, sizeof(char));
	strncpy(sqrmod, a, strlen(a));
	char* resmod = NULL;

	Minus(&sqr_1, P, "1");
	//printf("Minus 1 : %s\n", sqr_1);
	ChangeBinary(&bin, sqr_1);
	printf("SQUARE MODULAR Time : %.20lf\n", (double)(clock() - start) / CLOCKS_PER_SEC);
	printf("divide %ld start\n", strlen(bin));
	start = clock();
	//printf("bin : %s\n", bin);
	//mod 구하기
	Divide(&sqrmod, sqrmod, P, true);
	if (bin[0] == one)
	{
		resmod = (char*)calloc(strlen(sqrmod) + 1, sizeof(char));
		strncpy(resmod, sqrmod, strlen(sqrmod));
	}
	else
	{
		resmod = (char*)calloc(2, sizeof(char));
		resmod[0] = one;
	}
	//printf("first sqrmod : %s\n", sqrmod);
	//printf("first resmod : %s\n", resmod);
	for (int i = 1; i < strlen(bin); i++)
	{
		Multiple(&sqrmod, sqrmod, sqrmod);
		Divide(&sqrmod, sqrmod, P, true);
		//printf("[%d] sqrmod : %s\n",i , sqrmod);

		if (bin[i] == one)
		{
			Multiple(&resmod, resmod, sqrmod);
			//printf("mul res : %s\n", resmod);
			Divide(&resmod, resmod, P, true);
			//printf("resmod : %s\n", resmod);
		}
	}

	*result = (char*)malloc(strlen(resmod) + 1);
	strncpy(*result, resmod, strlen(resmod) + 1);
	(*result)[strlen(resmod)] = null;

	free(sqr_1);
	free(bin);
	free(sqrmod);
	free(resmod);
	printf("SQUARE MODULAR Time : %.20lf\n", (double)(clock() - start) / CLOCKS_PER_SEC);
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
int gitPlus(LInt* result, LInt num1, LInt num2)
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
		int RESULT = gitMinus(result, n1, n2);
		free(n1.num);
		free(n2.num);
		return RESULT;
	}
}

int gitMinus(LInt* result, LInt num1, LInt num2)
{
	LInt n1 = { null, 0, NULL }, n2 = { null, 0, NULL };
	LIntCopy(&n1, &num1);
	LIntCopy(&n2, &num2);
	if (n1.sign != n2.sign)
	{
		n2.sign = n1.sign;
		int RESULT = gitPlus(result, n1, n2);
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
		gitPlus(&mulOne[i], mulOne[i-1], num);
}

int gitMultiple(LInt* result, LInt num1, LInt num2)
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
		if (gitPlus(result, plusT, temp) == ERROR)
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
int gitDivide(LInt* result, LInt num1, LInt num2, int isMod)
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
		gitMinus(&div, plusT, temp);
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

int gitChangeBinary(LInt* bin, LInt num)
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

		gitDivide(&binT, binT, SLConst("2"), false);
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

int gitModularSquare(LInt* result, LInt P, LInt a)
{
	LInt binP = { null, 0, NULL };
	LInt temp = { null, 0, NULL };
	LInt sqrmod = { null, 0, NULL };
	LIntCopy(&sqrmod, &a);
	gitMinus(&binP, P, SLConst("1"));
	gitChangeBinary(&binP, binP);
	ReversePrint("rev bin", binP.num);
	printf("len(bin) : %d\n", strlen(binP.num));
	
	gitDivide(&sqrmod, sqrmod, P, true);
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
		gitMultiple(&sqrmod, sqrmod, sqrmod);
		gitDivide(&sqrmod, sqrmod, P, true);
		if (binP.num[i] == one)
		{
			gitMultiple(result, *result, sqrmod);
			gitDivide(result, *result, P, true);
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