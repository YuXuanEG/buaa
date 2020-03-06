
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
#define Infinite INT_MAX

typedef struct Vertex* Vertex, * Vertexes;
typedef struct Adj* Adj, * Adjs;
typedef struct Graph* Graph;

struct Vertex {
    int id;         /* Unique id of a vertex */
    int known;      /* If the vertex has been traversed */
    int dist;       /* the distance along the path from start point */
    int num_rescue;    /* Rescue teams in this city */
    int total_rescue;  /* Total rescue teams along the path */
    int length_path;      /* Length of the path */
    Adj adj;        /* Pointer to the next vertex */
};

struct Adj {
    int id;         /* The city's id it is connected to */
    int length;     /* The length of the edge */
    Adj iter;       /* Pointer to the next adjacent city */
};

struct Graph {
    Vertexes vs;
    Adjs es;
    int nvertex;
    int nadj;
};

/* Read the graph */
void Read(Graph G)
{
    int nrescue;
    for (int i = 0; i < G->nvertex; i++)
    {
        Vertex v = G->vs + i;
        scanf_s("%d", &nrescue);
        v->id = i;
        v->known = 0;
        v->dist = Infinite;
        v->num_rescue = nrescue;
        v->total_rescue = nrescue;
        v->length_path = 0;
        v->adj = NULL;
    }

    int city1, city2, length;
    for (int i = 0; i < G->nadj; i++)
    {
        scanf_s("%d %d %d", &city1, &city2, &length);
        /* From id1 to id2 */
        Adj e = G->es + i;
        e->id = city2;
        e->length = length;
        e->iter = G->vs[city1].adj;
        G->vs[city1].adj = e;
        /* The other direction 双向图*/
        e++, i++;
        e->id = city1;
        e->length = length;
        e->iter = G->vs[city2].adj;
        G->vs[city2].adj = e;
    }
}

/* Find the shortest path length using Dijkstra alg,
 * in the same time record the number of shortest paths and max rescue teams */
void ModifiedDijkstra(Graph G)
{
    int minUnknownDist;
    Vertex v, w;
    while (1)
    {
        /* find the smallest unknown distance vertex */
        v = NULL;
        minUnknownDist = Infinite;
        for (w = G->vs; w < &G->vs[G->nvertex]; w++)
            if (!w->known && w->dist < minUnknownDist)
            {
                minUnknownDist = w->dist;
                v = w;
            }
        if (v == NULL) break;

        v->known = 1;
        for (Adj e = v->adj; e; e = e->iter) if (!G->vs[e->id].known)
        {
            w = G->vs + e->id; /* w is every adjacent vertex to v */
            /* find shorter distance */
            if (v->dist + e->length < w->dist)
            {
                w->length_path = v->length_path;
                w->total_rescue = w->num_rescue + v->total_rescue;
                w->dist = v->dist + e->length;
            }
            /* find same shortest distance */
            else if (v->dist + e->length == w->dist)
            {
                w->length_path += v->length_path;
                if (w->total_rescue < w->num_rescue + v->total_rescue)
                    w->total_rescue = w->num_rescue + v->total_rescue;
            }
        }
    }
}

void pat_3() {
    int N, M, C1, C2;//N:城市数，M：路数，C1：当前所在城市，C2：需要救援的城市
    scanf_s("%d %d %d %d", &N, &M, &C1, &C2);

    /* Create graph */
    Vertexes vs = (Vertexes)malloc(N * sizeof(struct Vertex));
    Adjs es = (Adjs)malloc(M * 2 * sizeof(struct Adj));
    struct Graph sG = { .vs = vs, .es = es, .nvertex = N, .nadj = M * 2 };
    Graph G = &sG;

    /* Read all the data and build the graph */
    Read(G);
    G->vs[C1].dist = 0;
    G->vs[C1].length_path = 1;

    /* Find the shortest path and maximum rescue teams */
    ModifiedDijkstra(G);

    printf("%d %d", G->vs[C2].length_path, G->vs[C2].total_rescue);

}
