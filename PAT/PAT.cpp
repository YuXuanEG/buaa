#include "Pat.h"
using namespace std;

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


void pat_2() {
	cout <<"1002 a+b for Polynomials (25分)"<<endl;
	map<int, float> coefMap;
	for (int i = 0; i < 2; i++) {
		int k;
		cin >> k;
		for (int j = 0; j < k; j++) {
			int exp;
			float coef;
			cin >> exp >> coef;
			coefMap[exp] += coef;
			if (coefMap[exp] == 0) {
				coefMap.erase(exp);
			}
		}
	}
	cout << coefMap.size();
	for (auto it = coefMap.rbegin(); it != coefMap.rend(); ++it) {
		cout << " " << it->first << " " << fixed << setprecision(1) << it->second;
	}
	cout << endl;
	
}


void pat_3() {
    int N, M, C1, C2;//N:城市数，M：路数，C1：当前所在城市，C2：需要救援的城市
    
}
