#include <stdio.h>
#include <stdlib.h>

#define OK 1
#define ERROR 0
#define TRUE 1
#define FALSE 0
#define MAX 100

typedef int Status;
typedef int PointType;

typedef struct EdgeNode {
    int weight;
    int adjvex;
    struct EdgeNode *next;
} EdgeNode;

typedef struct {
    PointType data;
    struct EdgeNode *firstEdge;
} PointNode,AdjList[MAX];

typedef struct  {
    AdjList adjList;
    int numEdges,numNodes;
} GraphAd;

typedef struct {
	PointType vexs[MAX]; 
	int arc[MAX][MAX];
	int numNodes, numEdges; 
} MGraph;

Status visited[MAX];
//创建有向图
Status Create(GraphAd *G) {
    printf("Input NodeNum and EdgeNum\n");
	scanf("%d,%d",&G->numNodes,&G->numEdges);
    for(int i = 0;i < G->numNodes;i++) {
        G->adjList[i].firstEdge = NULL;
        G->adjList[i].data = i+1;
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
        E->weight = weight;
        E->adjvex = jj;
        E->next = G->adjList[ii].firstEdge;
        G->adjList[ii].firstEdge = E;
    }
    printf("SUCCESSFULLY\n");
    return OK;
}

void DFSPrint(GraphAd G,int i) {
    visited[i] = TRUE;
    printf("%d ",i+1);
    EdgeNode *list = G.adjList[i].firstEdge;
    while(list) {
        if(visited[list->adjvex] == FALSE) {
            DFSPrint(G,list->adjvex);
        }
        list = list->next;
    }
}

void DFS(GraphAd G) {
    for(int i = 0;i < G.numNodes;i++) {
        visited[i] = FALSE;
    }
    for(int i = 0;i < G.numNodes;i++) {
        if(visited[i] == FALSE) {
            DFSPrint(G,i);
        }
    }
}

//引入队列
typedef int ElemType;
typedef struct {
    ElemType data[MAX];
    int front;
    int rear;
} Queue;

Status Init(Queue *Q) {
    Q->front = 0;
    Q->rear = 0;
    return OK;
}

Status Add(Queue *Q,ElemType E) {
    if ((Q->rear + 1) % MAX == Q->front) {
        return ERROR;
    }	
	Q->data[Q->rear] = E;	
    Q->rear++;		
	Q->rear = Q->rear % MAX;
    return OK;
}

Status DeAdd(Queue *Q,ElemType *E) {
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

void BFS(GraphAd G) {
    Queue Q;
    Init(&Q);
    for(int i = 0;i < G.numNodes;i++) {
        visited[i] == FALSE;
    }
    for(int i = 0;i < G.numNodes;i++) {
        if(visited[i] == FALSE) {
            Add(&Q,i);
            while(Length(&Q) != 0) {
                ElemType E;
                DeAdd(&Q,&E);
                visited[E] = TRUE;
                printf("%d ",E+1);
                EdgeNode *list = G.adjList[E].firstEdge;
                while(list) {
                    Add(&Q,list->adjvex);
                    list = list->next;
                }
            }
        }
    }
}
//邻接表转换为邻接矩阵
MGraph Transfer(GraphAd G) {
    MGraph arcG;
    arcG.numEdges = G.numEdges;
    arcG.numNodes = G.numNodes;
    for(int i = 0;i < G.numNodes;i++) {
        arcG.vexs[i] = G.adjList[i].data;
    }
    //初始化邻接矩阵
    for(int i = 0;i < G.numNodes;i++) {
        for(int j = 0;j < G.numNodes;j++) {
            arcG.arc[i][j] = 0;
        }
    }
    //转换
    for(int i = 0;i < G.numNodes;i++) {
        EdgeNode *list = G.adjList[i].firstEdge;
        while(list) {
            int j = list->adjvex;
            arcG.arc[i][j] = list->weight;
            list = list->next;
        }
    }
    return arcG;
}
//邻接矩阵转化为邻接表
GraphAd Transfer2(MGraph G) {
    GraphAd adG;
    adG.numEdges = G.numEdges;
    adG.numNodes = G.numNodes;
    //初始化邻接表
    for(int i = 0;i < G.numNodes;i++) {
        adG.adjList[i].data = G.vexs[i];
        adG.adjList[i].firstEdge = NULL;
    }
    //转换
    for(int i = 0;i < G.numNodes;i++) {
        for(int j = 0;j < G.numNodes;j++) {
            if(G.arc[i][j] != 0) {
                EdgeNode *E = (EdgeNode *)malloc(sizeof(EdgeNode));
                E->weight = G.arc[i][j];
                E->adjvex = j;
                E->next = adG.adjList[i].firstEdge;
                adG.adjList[i].firstEdge = E;
            }
        }
    }
    return adG;
}

int main() {
    GraphAd G;
    Create(&G);

    //DFS(G);
    //BFS(G);
    MGraph arcG = Transfer(G);
    
}