#include "Pat.h"
using namespace std;

void pat_1() {
	cout << "1001 A+B Format (20 score)" << endl;
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
	cout <<"1002 a+b for Polynomials (25 score)"<<endl;
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

/*
1003 Emergency
你是一个救援队长，你要救援有危险的城市，你需要尽可能快的到达有危险的城市，并且带尽可能多的人。

输入：

第1行：4个正整数： 城市数量N、 路数量M、你在的城市、你要救援的城市。

第2行：N个整数，第i个数表示第i个城市的救援队数量。

然后M行：每一行表示一条路，三个数字分别是起点、终点、距离。

保证至少有一条路让你去你要救援的城市。

输出：

最短路径条数  可带的最多人数
*/
const int MAX = 510, INF = 1 << 30;
int N, M, now, des, C1, C2, L;
int G[MAX][MAX] = { {0} };//用无向图来表示城市中有多少救援队，且是否有公路
int Teams[MAX] = { 0 }, t[MAX] = { 0 }, d[MAX], n[MAX] = { 0 };//t表示到达每个城市可以聚集的最多的救援队
bool visited[MAX] = { 0 };//d表示到达每个城市的最小距离，n表示到达每个城市的最短路径条数
void Dijkstra(int u)//Dijkstra算法
{
	fill(d, d + MAX, INF);
	d[u] = 0, t[u] = Teams[u], n[u] = 1;
	for (int i = 0; i < N; i++)
	{
		int MIN = INF, v = -1;
		for (int j = 0; j < N; j++)//找出未访问的最短路径
		{
			if (!visited[j] && d[j] < MIN)
			{
				MIN = d[j], v = j;
			}
		}
		if (v == -1) return;
		visited[v] = 1;//标记为已访问
		for (int j = 0; j < N; j++)//更新
		{
			if (!visited[j] && G[v][j])
			{
				if (d[v] + G[v][j] < d[j])//距离近则直接走近的
				{
					d[j] = d[v] + G[v][j];
					t[j] = t[v] + Teams[j];
					n[j] = n[v];
				}
				else if (d[v] + G[v][j] == d[j])//距离相等则路径条数增加，并更新救援队数量
				{
					if (t[v] + Teams[j] > t[j])
					{
						t[j] = t[v] + Teams[j];
					}
					n[j] += n[v];
				}
			}
		}
	}
}
void pat_3() {
    cout << "1003 Emergency (25 score)" << endl;
	scanf("%d %d %d %d", &N, &M, &now, &des);
	for (int i = 0; i < N; i++) scanf("%d", &Teams[i]);
	for (int i = 0; i < M; i++)
	{
		scanf("%d %d %d", &C1, &C2, &L);
		G[C1][C2] = G[C2][C1] = L;
	}
	Dijkstra(now);
	printf("%d %d", n[des], t[des]);
}

/*
题目大意
	将一个家族构成一棵树，依次输出每一层的叶节点个数；

输入：
	第一行：n：树中的节点数目；m：没有叶子的节点数目

	后m行：ID：两位数字，表示一个非叶子的节点；k：此节点孩子的数目；剩下的为子节点的编号；

输出：
	从根节点那层开始，输出每一层的叶节点数目，中间用空格隔开；

思路
建立map，每个非叶节点值为key，其孩子数组为value。

采用广度遍历的思路，将每层待遍历的非叶节点加入vector中，遍历每个非叶节点的所有孩子，按以下思路：

若该孩子出现在map的key中，即表示它是非叶节点，加入vector中；
若没出现，则是该层叶子，计数器+1；
初始化为{1}，即从根开始；当vector为空时结束。

首先输出第1层叶子数：

节点总数为1时，输出1；
节点总数大于1时，输出0；
剩下每层遍历输出计数即可。

代码实现上：

用到了unordered_map，比map效率更高；
vector可以直接互相赋值，a = b，相当于清空a，填充为b的元素。
*/
void pat_4() {
	cout << "1004 Counting Leaves(30 score)" << endl;
	int n, m;
	cin >> n >> m;
	if (n > 0) {
		if (n == 1) {
			cout << 1;
		}
		else {
			unordered_map<int, vector<int> > mmap; //建立非叶节点号及孩子数组映射
			for (int i = 0; i < m; i++) {
				int p, k;
				cin >> p >> k;
				vector<int> nodes(k);
				for (int j = 0; j < k; j++) {
					cin >> nodes[j];
				}
				mmap[p] = nodes;
			}
			vector<int> v;
			v.push_back(1);
			cout << "0";
			while (v.size() > 0) {
				int count = 0;
				vector<int> newV;
				for (int i = 0; i < v.size(); i++) {
					for (int j = 0; j < mmap[v[i]].size(); j++) {
						if (mmap.find(mmap[v[i]][j]) == mmap.end()) {  //未出现在非叶中，是叶子
							count++;
						}
						else {
							newV.push_back(mmap[v[i]][j]);
						}
					}
				}
				v = newV;
				cout << " " << count;
			}

		}
		cout << endl;
	}
}

/*
32位机：
	有符号短整型short [int] /signed short [int]		2 byte		-32768 ~ 32767							-2^15 ~ 2^15-1
	无符号短整型unsigned short [int]				2 byte			 0 ~ 65535							    0 ~ 2^16-1
													
	有符号整型int /signed [int]						4 byte		-2147483648 ~ 2147483647				-2^31 ~ 2^31-1
	无符号整型unsigned [int]						4 byte				  0 ~ 4294967295				    0 ~ 2^32-1

	有符号长整型long [int]/signed long [int]        4 byte      -2147483648 ~ 2147483647

	无符号长整型unsigned long [int]					4 byte				  0 ~ 4294967295

	long long                                       8 byte				  0 ~ 18446744073709552000

64位机：
	
*/
void pat_5() {
	cout << "1005 Spell It Right (20 score)" << endl;
	char N[110];//输入为N (≤10^100),不能用整型接收,
	cin >> N;
	int n = strlen(N), sum = 0;
	for (int i = 0; i < n; i++)
	{
		sum += (N[i]-'0');
	}
	//char numEnglish[10][6] = { "zero","one","two","three","four","five","six","seven","eight","nine" };
	string numEnglish[] = { "zero","one","two","three","four","five","six","seven","eight","nine" };
	vector<int> sumDigits;
	do {
		//如果直接是0也要放进数组中
		int digitSum = sum % 10;
		sumDigits.push_back(digitSum);
		sum /= 10;
	} while (sum);
	reverse(sumDigits.begin(), sumDigits.end());

	if(sumDigits.size()>0) cout << numEnglish[sumDigits[0]];
	
	for (int i = 1; i < sumDigits.size() ; ++i){
		cout << " " << numEnglish[sumDigits[i]] ;
	}
	
	cout << endl;
}

void pat_5_2() {
	char N[110];
	scanf("%s", &N);
	char ref[10][6] = { "zero","one","two","three","four","five","six","seven","eight","nine" };
	int n = strlen(N), sum = 0, len = 0;
	int ans[10]; //存放sum
	for (int i = 0; i < n; i++) {
		sum += (N[i] - '0');
	}
	do {
		ans[len++] = sum % 10;
		sum /= 10;
	} while (sum);
	for (int i = len - 1; i >= 0; i--) {
		printf("%s", ref[ans[i]]);
		if (i > 0) printf(" ");
	}
}
