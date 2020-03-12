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

void pat_6() {
	int n;
	cin >> n;
	string minId = "";
	string maxId = "";
	string minTime = "23:59:59";
	string maxTime = "00:00:00";
	for (int i = 0; i < n; i++) {
		string id, t1, t2;
		cin >> id >> t1 >> t2;
		if (t1 < minTime) {
			minTime = t1;
			minId = id;
		}
		if (t2 > maxTime) {
			maxTime = t2;
			maxId = id;
		}
	}
	cout << minId << " " << maxId << endl;
}

void pat_7() {
	int n;
	scanf("%d", &n);
	vector<int> v(n);
	int leftindex = 0, rightindex = n - 1, sum = -1, temp = 0, tempindex = 0;
	//动态规划 
	for (int i = 0; i < n; i++) {
		scanf("%d", &v[i]);
		temp = temp + v[i]; //临时和 
		if (temp < 0) { //小于0则从下一个数重新开始计算 
			temp = 0;
			tempindex = i + 1;
		}
		else if (temp > sum) { //临时和大于当前的sum，则更新sum ,最左边的值的位置为上一次tempindex,最右边的值的位置为当前的i 
			sum = temp;
			leftindex = tempindex;
			rightindex = i;
		}
	}
	if (sum < 0) sum = 0;
	printf("%d %d %d", sum, v[leftindex], v[rightindex]);
}
void pat_8() {
	int n;
	cin >> n;
	int up = 0;
	int down = 0;
	int last = 0;
	for (int i = 0; i < n; i++) {
		int k;
		cin >> k;
		if (k > last) {
			up += (k - last);
		}
		else {
			down += (last - k);
		}
		last = k;
	}

	int sum = n * 5 + up * 6 + down * 4;
	cout << sum << endl;
}
void pat_9() {
	map<int, double> mmap;

	int k1, k2;
	cin >> k1;
	vector<int> exp(k1);
	vector<double> coef(k1);
	for (int i = 0; i < k1; i++) {
		cin >> exp[i] >> coef[i];
	}

	cin >> k2;
	for (int i = 0; i < k2; i++) {
		int tempExp;
		double tempCoef;
		cin >> tempExp >> tempCoef;
		for (int j = 0; j < k1; j++) {
			int newExp = tempExp + exp[j];
			mmap[newExp] += (tempCoef * coef[j]);
			if (mmap[newExp] == 0) {
				mmap.erase(newExp);
			}
		}
	}

	cout << mmap.size();
	for (auto it = mmap.rbegin(); it != mmap.rend(); ++it) {
		cout << " " << it->first << " " << setprecision(1) << fixed << it->second;
	}
	cout << endl;
}


long long convert(string s, long long radix) {
	long long sum = 0;
	int index = 0, temp = 0;
	for (int i = s.size() - 1; i >= 0; i--) {
		if (isdigit(s[i])) {
			//sum += (s[i] - '0') * int(pow(radix, index++))强制类型转换后 会有两个测试点无法通过
			sum += (s[i] - '0') * pow(radix, index++);
		}
		else {
			sum += (s[i] - 'a' + 10) * pow(radix, index++);
		}
	}
	return sum;

	//    //效果相同
	//    long long result = 0;
	//    for(int i = 0; i < s.size(); i++){
	//        if(s[i] >= '0' && s[i] <= '9') result += (s[i] - '0') * pow(radix, s.size()-i-1);
	//        else if(s[i] >= 'a' && s[i] <= 'z') result += (s[i] - 'a' + 10) * pow(radix, s.size()-i-1);
	//    }
	//    return result;

}
long long find_radix(string n, long long num) {

	char it = *max_element(n.begin(), n.end()); //*max_element这个函数学到了
	long long low = (isdigit(it) ? it - '0' : it - 'a' + 10) + 1;//计算最小进制

	long long high = max(num, low);//若num太小 则取未确定进制的数的最小进制为最大值 比如当输入为1 1 1 2
	while (low <= high) {
		long long mid = (low + high) / 2;
		long long t = convert(n, mid);
		if (t < 0 || t > num) high = mid - 1;   //t<0：数太大了 导致溢出 故也算作取值过大
		else if (t == num) return mid;
		else low = mid + 1;

	}
	return -1;
}

void pat_10() {
	cout << "1010 Radix (25 score)" << endl;
	string n1, n2;
	long long tag = 0, radix = 0, result_radix;
	cin >> n1 >> n2 >> tag >> radix;
	result_radix = tag == 1 ? find_radix(n2, convert(n1, radix)) : find_radix(n1, convert(n2, radix));
	if (result_radix != -1) {
		printf("%lld", result_radix);
	}
	else {
		printf("Impossible");
	}

}

void pat_11(){}
void pat_12(){}
void pat_13(){}
void pat_14(){}
void pat_15(){}
void pat_16(){}
void pat_17(){}
void pat_18(){}
void pat_19(){}
void pat_20(){}
void pat_21(){}
void pat_22(){}
void pat_23(){}
void pat_24(){}
void pat_25(){}
void pat_26(){}
void pat_27(){}
void pat_28(){}
void pat_29(){}
void pat_30(){}
void pat_31(){}
void pat_32(){}
void pat_33(){}
void pat_34(){}
void pat_35(){}
void pat_36(){}
void pat_37(){}
void pat_38(){}
void pat_39(){}
void pat_40(){}
void pat_41(){}
void pat_42(){}
void pat_43(){}
void pat_44(){}
void pat_45(){}
void pat_46(){}
void pat_47(){}
void pat_48(){}
void pat_49(){}
void pat_50(){}
void pat_51(){}
void pat_52(){}
void pat_53(){}
void pat_54(){}
void pat_55(){}
void pat_56(){}
void pat_57(){}
void pat_58(){}
void pat_59(){}
void pat_60(){}
void pat_61(){}
void pat_62(){}
void pat_63(){}
void pat_64(){}
void pat_65(){}
void pat_66(){}
void pat_67(){}
void pat_68(){}
void pat_69(){}
void pat_70(){}
void pat_71(){}
void pat_72(){}
void pat_73(){}
void pat_74(){}
void pat_75(){}
void pat_76(){}
void pat_77(){}
void pat_78(){}
void pat_79(){}
void pat_80(){}
void pat_81(){}
void pat_82(){}
void pat_83(){}
void pat_84(){}
void pat_85(){}
void pat_86(){}
void pat_87(){}
void pat_88(){}
void pat_89(){}
void pat_90(){}
void pat_91(){}
void pat_92(){}
void pat_93(){}
void pat_94(){}
void pat_95(){}
void pat_96(){}
void pat_97(){}
void pat_98(){}
void pat_99(){}
void pat_100(){}
void pat_101(){}
void pat_102(){}
void pat_103(){}
void pat_104(){}
void pat_105(){}
void pat_106(){}
void pat_107(){}
void pat_108(){}
void pat_109(){}
void pat_110(){}
void pat_111(){}
void pat_112(){}
void pat_113(){}
void pat_114(){}
void pat_115(){}
void pat_116(){}
void pat_117(){}
void pat_118(){}
void pat_119(){}
void pat_120(){}
void pat_121(){}
void pat_122(){}
void pat_123(){}
void pat_124(){}
void pat_125(){}
void pat_126(){}
void pat_127(){}
void pat_128(){}
void pat_129(){}
void pat_130(){}
void pat_131(){}
void pat_132(){}
void pat_133(){}
void pat_134(){}
void pat_135(){}
void pat_136(){}
void pat_137(){}
void pat_138(){}
void pat_139(){}
void pat_140(){}
void pat_141(){}
void pat_142(){}
void pat_143(){}
void pat_144(){}
void pat_145(){}
void pat_146(){}
void pat_147(){}
void pat_148(){}
void pat_149(){}
void pat_150(){}
void pat_151(){}
void pat_152(){}
void pat_153(){}
void pat_154(){}
void pat_155(){}
