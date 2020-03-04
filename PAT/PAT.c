
#include "Pat.h"
void pat_1() {
	int a, b, sum;
	printf("input 2 integers a and b where −10^6< a,b <10^6 \n");
	scanf_s("%d %d", &a, &b);
	sum = a + b;
	printf("%d\n", sum);

	if (sum < 0)
	{
		printf("-");
		sum = -sum;
	}
	int c[7], len = 0;
	if (sum == 0)
	{
		printf("0");
	}
	else {
		while (sum > 0)
		{
			c[len++] = sum % 10;
			sum /= 10;
		}
		for (int i = len - 1; i >= 0; i--)
		{
			printf("%d", c[i]);
			if (i % 3 == 0 && i != 0)printf(",");
		}
	}
}

typedef struct Poly{
	double coefficients;//系数
	int exponents;//指数
}Poly[20];//一个结构体数组最多存储20个poly对象
void pat_2() {
	printf("1002 a+b for Polynomials (25分)\n");
	int kA,kB,kSumCount=0;
	Poly a, b, sum;

	scanf_s("%d", &kA);
	for (int i = 0; i < kA; i++)
		scanf_s("%d %lf", &a[i].exponents, &a[i].coefficients);

	scanf_s("%d", &kB);
	for (int i = 0; i < kB; i++)
		scanf_s("%d %lf", &b[i].exponents, &b[i].coefficients);

	int i = 0, j = 0;
	while (i < kA || j < kB)
	{
		if (i == kA || (j < kB && a[i].exponents < b[j].exponents))
		{
			sum[kSumCount].exponents = b[j].exponents;
			sum[kSumCount].coefficients = b[j++].coefficients;
		}
		else if (j == kB || (i < kA && a[i].exponents > b[j].exponents))
		{
			sum[kSumCount].exponents = a[i].exponents;
			sum[kSumCount].coefficients = a[i++].coefficients;
		}
		else
		{
			sum[kSumCount].exponents = a[i].exponents;
			sum[kSumCount].coefficients = a[i++].coefficients + b[j++].coefficients;
		}
		if (fabs(sum[kSumCount].coefficients) >= 0.05) kSumCount++;
	}

	printf("%d", kSumCount);

	for (int i = 0; i < kSumCount; i++)
		printf(" %d %.1lf", sum[i].exponents, sum[i].coefficients);

	
}