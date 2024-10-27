#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>

#define MAXVEX 10000
//核心思想：有向图邻接表的改造 Edmond-Karp算法
typedef struct EdgeNode {
    int weight;//容量
    int adjvex;
    int flow;//流量
    struct EdgeNode *next;
    struct EdgeNode *prv; //指向反向边
} EdgeNode;

typedef struct {
    int data;
    struct EdgeNode *firstEdge;
} PointNode,AdjList[MAXVEX];

typedef struct  {
    AdjList adjList;
    int numEdges,numNodes;
} GraphAd;

bool Create(GraphAd *G) {
    printf("Input NodeNum and EdgeNum\n");
	scanf("%d %d",&G->numNodes,&G->numEdges);
    for(int i = 0;i < G->numNodes;i++) {
        G->adjList[i].firstEdge = NULL;
        G->adjList[i].data = i+1;
    }
    printf("Int VexNum of Edge(i,j)xuhao and weight:\n");
    for(int i = 0;i < G->numEdges;i++) {
        int ii,jj,weight;
		scanf("%d %d %d",&ii,&jj,&weight);
        ii -= 1;
        jj -= 1;
        if (ii < 0 || ii >= G->numNodes || jj < 0 || jj >= G->numNodes) {
            printf("Invalid edge (%d, %d)\n", ii+1, jj+1);
            return false;
        }
        EdgeNode* E = (EdgeNode*)malloc(sizeof(EdgeNode));
        EdgeNode* backE = (EdgeNode*)malloc(sizeof(EdgeNode));
        // 添加边 ii -> jj 正常边
        E->weight = weight;
        E->adjvex = jj;
        E->flow = 0;
        E->next = G->adjList[ii].firstEdge;
        G->adjList[ii].firstEdge = E;
        //反向边
        backE->adjvex = ii;
        backE->weight = 0;
        backE->flow = 0;
        backE->next = G->adjList[jj].firstEdge;
        G->adjList[jj].firstEdge = backE;
        //连接反向边与边
        E->prv = backE;
        backE->prv = E; 
    }
    return true;
}
// BFS查找增广路径
bool bfs(GraphAd* G,int start,int end,EdgeNode* parent[]) {
    bool visited[MAXVEX] = { false };
    //模拟个队列 用来BFS
    int queue[MAXVEX], front = 0, rear = 0;
    //入队
    queue[rear++] = start;
    visited[start] = true;
    parent[start] = NULL;
    //队不为空
    while (front < rear) {
        //出队
        int u = queue[front++];
        for (EdgeNode* e = G->adjList[u].firstEdge; e != NULL; e = e->next) {
            int v = e->adjvex;
            //没访问过 并且 流量<容量
            if (!visited[v] && e->weight > e->flow) {
                parent[v] = e;
                visited[v] = true;
                if (v == end) return true;
                queue[rear++] = v;
            }
        }
    }
    return false;
}

int min(int a,int b) {
    return a < b ? a : b;
}
//Edmond-Karp算法计算最大流 start为源点 end为汇点
int EdmondsKarp(GraphAd* G,int start,int end) {
    int maxFlow = 0;
    EdgeNode* parent[MAXVEX];

    while (bfs(G,start,end,parent)) {
        int pathFlow = INT_MAX;
        //找最小剩余容量weight
        for (int v = end;v != start;v = parent[v]->prv->adjvex) {
            pathFlow = min(parent[v]->weight - parent[v]->flow,pathFlow);
        }
        //更新流量flow值
        for (int v = end;v != start;v = parent[v]->prv->adjvex) {
            parent[v]->flow += pathFlow;
            parent[v]->prv->flow -= pathFlow;
        }
        maxFlow += pathFlow;
    }
    return maxFlow;
}

int main() {
    GraphAd G;
    Create(&G);
    int maxFlow = EdmondsKarp(&G,0,G.numNodes-1);
    printf("The maximum flow is: %d\n",maxFlow);
    return 0;
}