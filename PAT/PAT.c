
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
*/
#define Inf INT_MAX

typedef struct Vertex* Vertex, * Vertexes;
typedef struct Adj* Adj, * Adjs;
typedef struct Graph* Graph;

struct Vertex {
    int id;         /* Unique id of a vertex */
    int known;      /* If the vertex has been traversed */
    int dist;       /* the distance along the path from start point */
    int nrescue;    /* Rescue teams in this city */
    int totrescue;  /* Total rescue teams along the path */
    int npath;      /* Length of the path */
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
        v->dist = Inf;
        v->nrescue = nrescue;
        v->totrescue = nrescue;
        v->npath = 0;
        v->adj = NULL;
    }

    int id1, id2, length;
    for (int i = 0; i < G->nadj; i++)
    {
        scanf_s("%d %d %d", &id1, &id2, &length);
        /* From id1 to id2 */
        Adj e = G->es + i;
        e->id = id2;
        e->length = length;
        e->iter = G->vs[id1].adj;
        G->vs[id1].adj = e;
        /* The other direction */
        e++, i++;
        e->id = id1;
        e->length = length;
        e->iter = G->vs[id2].adj;
        G->vs[id2].adj = e;
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
        minUnknownDist = Inf;
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
                w->npath = v->npath;
                w->totrescue = w->nrescue + v->totrescue;
                w->dist = v->dist + e->length;
            }
            /* find same shortest distance */
            else if (v->dist + e->length == w->dist)
            {
                w->npath += v->npath;
                if (w->totrescue < w->nrescue + v->totrescue)
                    w->totrescue = w->nrescue + v->totrescue;
            }
        }
    }
}

void pat_3() {
    int N, M, C1, C2;
    scanf_s("%d %d %d %d", &N, &M, &C1, &C2);

    /* Create graph */
    Vertexes vs = (Vertexes)malloc(N * sizeof(struct Vertex));
    Adjs es = (Adjs)malloc(M * 2 * sizeof(struct Adj));
    struct Graph sG = { .vs = vs, .es = es, .nvertex = N, .nadj = M * 2 };
    Graph G = &sG;

    /* Read all the data and build the graph */
    Read(G);
    G->vs[C1].dist = 0;
    G->vs[C1].npath = 1;

    /* Find the shortest path and maximum rescue teams */
    ModifiedDijkstra(G);

    printf("%d %d", G->vs[C2].npath, G->vs[C2].totrescue);

}
