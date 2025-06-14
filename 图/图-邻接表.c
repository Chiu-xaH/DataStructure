#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "Stack.h"

#define MAX 100
#define TRUE 1
#define FALSE 0
#define OK 1
#define ERROR 0

typedef int PointType;
typedef int Status;

typedef struct EdgeNode {
    struct EdgeNode *next;
    int weight;
    int adjvex;
} EdgeNode;

typedef struct PointNode {
    int inDegree;//入度，用于拓扑排序
    struct EdgeNode *firstEdge;
    PointType data;
} PointNode,AdjList[MAX];

typedef struct {
    AdjList adjList;
    int numEdges,numNodes;
} GraphAd;

/*示例图
1 —— 2
|  \ |
3 —— 4
*/
//创建有向图
Status Create(GraphAd *G) {
    printf("Input NodeNum and EdgeNum\n");
	scanf("%d,%d",&G->numNodes,&G->numEdges);
    //printf("Input Nodes\n");
    for(int i = 0;i < G->numNodes;i++) {
		G->adjList[i].data = i+1; 	
		G->adjList[i].firstEdge=NULL;
        G->adjList[i].inDegree = 0; 
	}

    for(int i = 0;i < G->numEdges;i++) {
        int ii,jj,weight;
        EdgeNode *E;
        printf("Int VexNum of Edge(i,j)xuhao and weight:\n");
		scanf("%d,%d,%d",&ii,&jj,&weight);
        ii -= 1;
        jj -= 1;
        if (ii < 0 || ii >= G->numNodes || jj < 0 || jj >= G->numNodes) {
            printf("Invalid edge (%d, %d)\n", ii+1, jj+1);
            return ERROR;
        }

        // 添加边 ii -> jj
        E = (EdgeNode *)malloc(sizeof(EdgeNode));
        if (E == NULL) return ERROR;
        E->weight = weight;
        E->adjvex = jj;
        E->next = G->adjList[ii].firstEdge;
        G->adjList[ii].firstEdge = E;
        G->adjList[jj].inDegree++; 
        //无向图，所以要再次用边另一个点反向执行一次
        // 添加边 jj -> ii
       /* E = (EdgeNode *)malloc(sizeof(EdgeNode));
        if (E == NULL) return ERROR;
        E->weight = weight;
        E->adjvex = ii;
        E->next = G->adjList[jj].firstEdge;
        G->adjList[jj].firstEdge = E;*/
    }
    printf("Create Successfully!\n");
    return OK;
}

Status visited[MAX];
//深度优先遍历
void DFS(GraphAd G,int i) {
    visited[i] = TRUE;
    printf("%d ",G.adjList[i].data);
    EdgeNode *E = G.adjList[i].firstEdge;
    while(E) {
        if(visited[E->adjvex] == FALSE) {
            DFS(G,E->adjvex);
        }
        E = E->next;
    }
}
//遍历打印点
void GetDFS(GraphAd G) {
    for(int i = 0;i < G.numNodes;i++) {
        visited[i] = FALSE;
    }
    for(int i = 0;i < G.numNodes;i++) {
        if(visited[i] == FALSE) {
            DFS(G,i);
        }
    }
}
//是否为连通图
Status isConnected(GraphAd G) {
    for(int i = 0;i < G.numNodes;i++) {
        visited[i] = FALSE;
    }
    DFS(G,0);
    for(int i = 0;i < G.numNodes;i++) {
        if(visited[i] == FALSE) {
            return FALSE;
        }
    }
    return TRUE;
}
// 图边的数量
int EdgeCounts(GraphAd G,Status isWuxiang) {
    int count = 0;
    for(int i = 0;i < G.numNodes;i++) {
        EdgeNode  *ptr = G.adjList[i].firstEdge;
        while(ptr) {
            count++;
            ptr = ptr->next;
        }
    }
    if(isWuxiang == TRUE) {
        return count / 2;
    } else {
        return count;
    }
}

//设计算法实现函数firstadj(G, v)（返回第一个与v连接的点）
PointType firstAdj(GraphAd G,PointType v) {
    v -= 1; // 规整索引
    if (v < 0 || v >= G.numNodes) return -1;

    EdgeNode *E = G.adjList[v].firstEdge;
    if (E)
        return E->adjvex + 1;// 转换回 1-based index
    else
        return -1; // 没有邻接点
}
//设计算法实现函数nextadj(G, v, w)（返回与v相邻并在w之后的下一个顶点）。
PointType nextAdj(GraphAd G,PointType v,PointType w) {
    v -= 1; // 规整索引
    w -= 1; // 规整索引
    if (v < 0 || v >= G.numNodes) return -1;

    EdgeNode *E = G.adjList[v].firstEdge;
    while (E && E->adjvex != w) {
        E = E->next;
    }
    if (E && E->next)
        return E->next->adjvex + 1;// 转换回 1-based index
    else
        return -1; // 没有后继邻接点
}
//拓扑排序
/*
   ①初始化入度数组Ind[ ]（若出现0入度顶点，则入栈s）； 
   ②若栈s为空，则跳出循环，转到⑥
   ③v=pop(s)并输出v；
   ④对v的所有后继w实现：Ind[w]-1；若Ind[w]=0；则w入栈；
   ⑤转②；
   ⑥判断是否存在回路。

*/
Status TopoSort(GraphAd G) {
    EdgeNode *E;
    Stack S;
    InitStack(&S);
    for(int i = 0;i < G.numNodes;i++) {
        if(G.adjList[i].inDegree == 0) {
            Push(&S,i);
        }
    }
    int count = 0,k;
    while(S.top != -1) {
        Elemtype EV;
        Pop(&S,&EV);
        printf("%d ",G.adjList[EV].data);
        count++;
        for(E = G.adjList[EV].firstEdge;E != NULL;E = E->next) {
            k = E->adjvex;
            //k结点的下一个点，由于由k指向的线被擦除，入度要-1
            //若擦除线后入度存在0的，进栈，进入下个循环
            if((--G.adjList[k].inDegree) == 0) {
                Push(&S,k);
            }
        }
    }
    //判断是否为AOV图
    if(count < G.numNodes) {
        return ERROR;
    } else {
        return OK;
    }
}
//得到所有的拓扑序列-回溯法
void AllTopoSort(GraphAd G, int *result,int level) {
    Status flag = FALSE;
    for (int i = 0; i < G.numNodes; i++) {
        if (G.adjList[i].inDegree == 0 && visited[i] == FALSE) {
            EdgeNode *E;
            // 选择一个入度为 0 且未访问的节点
            visited[i] = TRUE;
            result[level] = i + 1;
            // 减少所有与 i 相邻接点的入度
            for (E = G.adjList[i].firstEdge; E != NULL; E = E->next) {
                G.adjList[E->adjvex].inDegree--;
            }
            AllTopoSort(G, result, level + 1);
            // 回溯
            visited[i] = FALSE;
            for (E = G.adjList[i].firstEdge; E != NULL; E = E->next) {
                G.adjList[E->adjvex].inDegree++;
            }
            flag = TRUE;
        }
    }
    if (flag == FALSE) {
        for (int i = 0; i < level; i++) {
            printf("%d ", result[i]);
        }
        printf("\n");
    }
}
//关键路径
/*
求关键路径
根据AOE网
从源点进行拓扑排序
从汇点进行逆拓扑排序
然后列出：
		-事件最早发生时间 ve  点到源点所需经过的最大时间
每个顶点-
		-事件最迟发生时间 vl  汇点源点同上，（汇点时间-其余点为到汇点经过的时间）最小值

	    -活动最早开始时间 e  弧尾顶点事件最早开始时间
每条边-
	    -活动最晚开始时间 l  弧头顶点事件最迟开始时间-权值
		
	     时间余量 = l-e 若为0则表示关键路径
*/
//etv事件最早发生时间 ltv事件最迟发生时间
int etv[MAX];
//利用栈2，由拓扑排序得到逆向拓扑排序
Stack S2;
Status TopoSortUpdate(GraphAd G) {
    EdgeNode *E;
    Stack S;
    InitStack(&S);
    InitStack(&S2);
    //初始化时间最早发生时间数组
    for(int i = 0;i < G.numNodes;i++) {
        etv[i] = 0;
    }
    for(int i = 0;i < G.numNodes;i++) {
        if(G.adjList[i].inDegree == 0) {
            Push(&S,i);
        }
    }
    int count = 0,k;
    while(S.top != -1) {
        Elemtype EV;
        Pop(&S,&EV);
        //弹出的(拓扑序列)压入另一个栈
        Push(&S2,EV);
        count++;
        for(E = G.adjList[EV].firstEdge;E != NULL;E = E->next) {
            k = E->adjvex;
            if((--G.adjList[k].inDegree) == 0) {
                Push(&S,k);
            }
            //求各顶点的最早发生时间etv
            if((etv[EV] + E->weight) > etv[k]) {
                etv[k] = etv[EV] + E->weight;
            }
        }
    }
    if(count < G.numNodes) {
        return ERROR;
    } else {
        return OK;
    }
}

void CriticalPath(GraphAd G) {
    TopoSortUpdate(G);
    EdgeNode *E;
    //初始化ltv
    int ltv[MAX];
    for(int i = 0;i < G.numNodes;i++) {
        ltv[i] = etv[G.numNodes - 1];
    }
    //利用栈达到逆拓扑序列，计算(ltv)事件最迟发生时间
    while(S2.top != -1) {
        Elemtype EV;
        Pop(&S2,&EV);
        for(E = G.adjList[EV].firstEdge;E != NULL;E = E->next) {
            int k = E->adjvex;
            //求事件最迟发生时间ltv
            if(ltv[k] - E->weight < ltv[EV]) {
                ltv[EV] = ltv[k] - E->weight;
            }
        }
    }
    for(int j = 0;j < G.numNodes;j++) {
        for(E = G.adjList[j].firstEdge;E != NULL;E = E->next) {
            int k = E->adjvex;
            int ete = etv[j];
            int lte = ltv[k] - E->weight;
            if(ete == lte) {
                printf("<%d-%d>",G.adjList[j].data,G.adjList[k].data,E->weight);
            }
        }
    }
}
//设计算法输出其所有边或弧
//设计算法以判断顶点vi到vj之间是否存在路径
//设计算法以判断无向图是否是连通的
//设计算法产生dfs(1)的生成树，并存储到邻接矩阵中；

void Destory(GraphAd *G) {
    for(int i = 0;i < G->numNodes;i++) {
        EdgeNode *list = G->adjList[i].firstEdge;
        while(list) {
            //删除结点
            G->numEdges--;
        }
        G->numNodes--;
    }
}

//引入队列
typedef struct {
    int data[MAX];
    int front;
    int rear;
} Queue;

Status Init(Queue *Q) {
    Q->front = 0;
    Q->rear = 0;
    return OK;
}

Status Add(Queue *Q,PointType E) {
    if ((Q->rear + 1) % MAX == Q->front) {
        return ERROR;
    }	
	Q->data[Q->rear] = E;	
    Q->rear++;		
	Q->rear = Q->rear % MAX;
    return OK;
}

Status DeAdd(Queue *Q,PointType *E) {
    if(Q->front == Q->rear) {
        return ERROR;
    }
    *E = Q->data[Q->front];
    Q->front++;
    Q->front = Q->front % MAX;
    return OK;
}

int Length(Queue *Q) {
    if(Q->front == Q->rear) {
        return 0;
    }
    int count = 0;
    int i = Q->front;
    while(i != Q->rear) {
        count++;
        i++;
        i = i % MAX;
    }
    return count;
}

Status Get(Queue *Q) {
    if(Q->front == Q->rear) {
        return ERROR;
    }
    int i = Q->front;
    while(i != Q->rear) {
        printf("%d ",Q->data[i]);
        i++;
        i = i % MAX;
    }
    printf("\n");
    return OK;
}

Status BFSisLoop(GraphAd G, int start) {
    Queue Q;
    Init(&Q);

    int parent[MAX]; // 用于记录每个节点的父节点
    for (int i = 0; i < G.numNodes; i++) parent[i] = -1;

    visited[start] = TRUE;
    Add(&Q, start);

    while (Length(&Q)) {
        int u;
        DeAdd(&Q, &u);
        for (EdgeNode *p = G.adjList[u].firstEdge; p; p = p->next) {
            int v = p->adjvex;
            if (!visited[v]) {
                visited[v] = TRUE;
                parent[v] = u;
                Add(&Q, v);
            } else if (v != parent[u]) {
                return FALSE; // 非父节点已访问，说明有环
            }
        }
    }
    return TRUE;
}

// 设计算法以判断G是否是一棵以v0为根的有向树，
Status isRootTreeBFS(GraphAd G,PointType root) {
    for (int i = 0; i < G.numNodes; i++) visited[i] = FALSE;

    if (!BFSisLoop(G,root-1)) { // 规整索引
        printf("Has Loop!\n");
        return FALSE;
    }

    // 检查连通性
    for (int i = 0; i < G.numNodes; i++) {
        if (!visited[i]) return FALSE;
    }

    return TRUE;
}
void DFS5(GraphAd G, int arc[][MAX], int u) {
    visited[u] = TRUE;

    EdgeNode *E = G.adjList[u].firstEdge;
    while (E) {
        int v = E->adjvex;
        if (!visited[v]) {
            arc[u][v] = E->weight;
            // 无向图，矩阵对称,如果不是无向图需要注释掉
            arc[v][u] = E->weight; 

            DFS5(G, arc, v);
        }
        E = E->next;
    }
}

// 	设连通图G用邻接表A表示，设计算法以产生dfs（1）的dfs生成树，并存储到邻接矩阵B[][]中。
void Question5(GraphAd G,int arc[][MAX]) {
    // 初始化邻接矩阵
    for (int i = 0; i < G.numNodes; i++) {
        visited[i] = FALSE;
        for (int j = 0; j < G.numNodes; j++) {
            arc[i][j] = 0; 
        }
    }
    int rootIndex = 1-1;
    DFS5(G, arc, rootIndex);
}

int main() {
    Status i;
    GraphAd G; 
    memset(visited, FALSE, sizeof(visited));  
    i = Create(&G);
//    GetDFS(G);
//    printf("\n*******\n");
//    if(isConnected(G) == OK) {
//        printf("IS CONNECTED");
//    } else {
//        printf("NOT CONNECTED");
//    }
   // printf("\n*******\n");
    //i = TopoSort(G);
    //printf("\n*******\n");
    int result[MAX];
    AllTopoSort(G,result,0);
    //printf("\n*******\n");
    //CriticalPath(G);
   // printf("\n*******\n");
    //printf("Edge count is %d",EdgeCounts(G));
}