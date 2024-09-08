#include <stdio.h>
#include <stdlib.h>
#include "Stack.h"

#define OK 1
#define ERROR 0
#define TRUE 1
#define FALSE 0
#define MAXVEX 100
#define INFINITY 65535

typedef int Status;	
typedef int VertexType; /* 顶点  */
typedef int EdgeType; /* 边上的权值 */

typedef struct {
	VertexType vexs[MAXVEX]; 
	EdgeType arc[MAXVEX][MAXVEX];/* 邻接矩阵 */
	int numNodes, numEdges; /* 图中顶点数和边数  */
} MGraph;

Status Create(MGraph *G) {
    printf("Input NodeNums ang EdgeNums\n");
	scanf("%d,%d",&G->numNodes,&G->numEdges);
    for(int i = 0;i < G->numNodes;i++) {
        G->vexs[i] = i + 1;
    }
    for(int i = 0;i < G->numNodes;i++) {
        for(int j = 0;j < G->numEdges;j++) {
            G->arc[i][j] = INFINITY;
        }
    }
    for(int i = 0;i < G->numEdges;i++) {
        int ii,jj,weight;
        printf("Input Edge Nums and weight\n");
		scanf("%d,%d,%d",&ii,&jj,&weight);
        ii -= 1;
        jj -= 1;
		G->arc[ii][jj] = weight; 
        //注释掉以创建有向图
		G->arc[jj][ii]= G->arc[ii][jj]; /* 无向图，矩阵对称 */
    }
    printf("Create Successfully!\n");
    return OK;
}

Status visited[MAXVEX];
//深度优先搜索遍历-DFS
//采用visited数组记录是否被访问过，未访问则递归，并循环每个点进行
void DFS(MGraph G,int i) {
    visited[i] = TRUE;
    for(int j = 0;j < G.numNodes;j++) {
        if(G.arc[i][j] == INFINITY && visited[j] == FALSE) {
            DFS(G,j);
        }
    }
}
//遍历所有点
void DFSPrint(MGraph G,int i) {
    visited[i] = TRUE;
    printf("%d ",G.vexs[i]);
    for(int j = 0;j < G.numNodes;j++) {
        if(G.arc[i][j] == 1 && visited[j] == FALSE) {
            DFSPrint(G,j);
        }
    }
}

void GetDFS(MGraph G) {
    for(int i = 0;i < G.numNodes;i++) {
        visited[i] = FALSE;
    }
    for(int i = 0;i < G.numNodes;i++) {
        if(visited[i] == FALSE) {
            DFSPrint(G,i);
        }
    }
}
//设计算法以判断给定的无向图是否是连通的
Status isConnected(MGraph G) {
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
//设计算法以求解给定的无向图中的边数
int EdgeCounts(MGraph G) {
    int count = 0;
    for(int i = 0;i < G.numNodes;i++) {
        for(int j = 0;j < i;j++) {
            if(G.arc[i][j] == 1) {
                count++;
            }
        }
    }
    return count;
}
//设计算法以判断给定的无向图是树 (没有环路的连通图)(判断给定的无向图是否包含环）
Status DFSisLoop(MGraph G, int i, int parent) {
    visited[i] = TRUE;
    for (int j = 0; j < G.numNodes; j++) {
        if (G.arc[i][j] == 1) {
            if (visited[j] == FALSE) {
                //子节点中发现环
                if (DFSisLoop(G, j, i) == FALSE) {
                    return FALSE;
                }
                //已访问过(else)且不是父节点(j != parent(上一次的i))
            } else if (j != parent) {
                return FALSE;
            }
        }
    }
    return TRUE;
}

Status isTreeDFS(MGraph G) {
    for (int i = 0; i < G.numNodes; i++) {
        visited[i] = FALSE;
    }

    //检查有没有环
    if (DFSisLoop(G, 0, -1) == FALSE) {
        printf("IS LOOP\n");
        return FALSE;
    }

    // 检查连通，同上面
    for(int i = 0;i < G.numNodes;i++) {
        if(visited[i] == FALSE) {
            return FALSE;
        }
    }

    return TRUE;
}
//设计算法以求解无向图G的连通分量的个数
int ConectedCount(MGraph G) {
    int count = 0;
    for(int i = 0;i < G.numNodes;i++) {
        visited[i] = FALSE;
    }
    for(int i = 0;i < G.numNodes;i++) {
        if(visited[i] == FALSE) {
            count++;
            DFS(G,i);
        }
    }
    return count;
}
//设计算法，将1-n(=20,或其他数)放在一个环上，使环上任意两个相邻元素的和为质数
//若两个数的和为质数，则用线连接起来
Status Huzhi(int num) {
    if(num <= 3) {
        return TRUE;
    } else {
        for(int i = 2;i < num;i++) {
            if(num % i == 0) {
                return FALSE;
            }
        }
        return TRUE;
    }
}

Status CreateHuzhi(MGraph *G) {
    printf("Input NodeNums n\n");
	scanf("%d",&G->numNodes);
    for(int i = 0;i < G->numNodes;i++) {
        G->vexs[i] = i + 1;
    }
    for(int i = 0;i < G->numNodes;i++) {
        for(int j = 0;j < G->numEdges;j++) {
            G->arc[i][j] = INFINITY;
        }
    }
    for(int i = 0;i < G->numNodes;i++) {
        for(int j = 0;j < G->numNodes;j++) {
            if(i != j) {
                if(Huzhi(G->vexs[i] + G->vexs[j]) == TRUE) {
                    //建立连线
                    G->arc[i][j] = 1;
                }
            }
        }
    }
    printf("Create Successfully!\n");
    return OK;
}
//设计算法以判断给定的有向图是以v0为根的有向树。

//设计算法以判断图中的一个顶点是否为关节点。
//关节点：若一个顶点被删除后，其原先所在的连通分量变成两个及以上的连通分量
void DeleteVex(MGraph *G,int Vertex) {
    int ptr = Vertex-1;
    //删除点
    for(int i = ptr+1;i < G->numNodes;i++) {
        G->vexs[i-1] = G->vexs[i];
    }
    //找边数(无向图遍历一次即可)
    for(int i = 0;i < G->numNodes;i++) {
        if(G->arc[i][ptr] != INFINITY && G->arc[i][ptr] != 0) {
            G->numEdges--;
        }
    }
    /*有向图则启用
    for(int i = 0;i < G->numNodes;i++) {
        G->arc[ptr][i];
    }*/
    //行
    for(int i = 0;i < G->numNodes;i++) {
        for(int j = ptr+1;j < G->numNodes;j++) {
            G->arc[i][j-1] = G->arc[i][j];
        }
    }
    //列
    for(int i = 0;i < G->numNodes - 1;i++) {
        for(int j = ptr+1;j < G->numNodes;j++) {
            G->arc[j-1][i] = G->arc[j][i];
        }
    }
    G->numNodes--;
}

Status isJoint(MGraph *G,int Vertex) {
    DeleteVex(G,Vertex);
    int count = ConectedCount(*G);
    if(count >= 2) {
        return OK;
    } else {
        return ERROR;
    }
}
//引入队列
typedef int ElemType;
typedef struct {
    ElemType data[MAXVEX];
    int front;
    int rear;
} Queue;

Status Init(Queue *Q) {
    Q->front = 0;
    Q->rear = 0;
    return OK;
}

Status Add(Queue *Q,ElemType E) {
    if ((Q->rear + 1) % MAXVEX == Q->front) {
        return ERROR;
    }	
	Q->data[Q->rear] = E;	
    Q->rear++;		
	Q->rear = Q->rear % MAXVEX;
    return OK;
}

Status DeAdd(Queue *Q,ElemType *E) {
    if(Q->front == Q->rear) {
        return ERROR;
    }
    *E = Q->data[Q->front];
    Q->front++;
    Q->front = Q->front % MAXVEX;
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
        i = i % MAXVEX;
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
        i = i % MAXVEX;
    }
    printf("\n");
    return OK;
}

//广度优先搜索遍历-BFS
//采用队列，访问过后入队尾并标记visited数组，
//然后出队头并打印，再根据出队的元素搜寻接下来没被访问过的点，再次入队，直到队空
void BFS(MGraph G,Queue *Q,int i) {
    visited[i] = TRUE;
    Add(Q,i);
    while(Length(Q) != 0) {
        int node;
        DeAdd(Q,&node);
        for(int j = 0;j < G.numNodes;j++) {
            if(G.arc[i][j] == 1 && visited[j] == FALSE) {
                visited[j] = TRUE;
                Add(Q,j);
            }
        }
    }
}

void BFSPrint(MGraph G,Queue *Q,int i) {
    visited[i] = TRUE;
    Add(Q,i);
    while(Length(Q) != 0) {
        int node;
        DeAdd(Q,&node);
        printf("%d ",G.vexs[node]);
        for(int j = 0;j < G.numNodes;j++) {
            if(G.arc[node][j] == 1 && visited[j] == FALSE) {
                visited[j] = TRUE;
                Add(Q,j);
            }
        }
    }
}

void GetBFS(MGraph G) {
    Queue Q;
    Init(&Q);
    for(int i = 0;i < G.numNodes;i++) {
        visited[i] = FALSE;
    }
    for(int i = 0;i < G.numNodes;i++) {
        if(visited[i] == FALSE) {
            BFSPrint(G,&Q,i);
        }
    }
}

//设计算法以判断无向图G是否是一棵树
Status BFSisLoop(MGraph G,Queue *Q,int i,int parent) {
    visited[i] = TRUE;
    Add(Q,i);
    while(Length(Q) != 0) {
        int node;
        DeAdd(Q,&node);
        for(int j = 0;j < G.numNodes;j++) {
            if(G.arc[node][j] == 1) {
                if (visited[j] == FALSE) {
                    visited[j] = TRUE;
                    Add(Q, j);
                    parent = node;
                } else if (j != parent) {
                    return FALSE; // 检测到环
                }
            }
        }
    }
    return TRUE;
}

Status isTreeBFS(MGraph G) {
    Queue Q;
    Init(&Q);
    for (int i = 0; i < G.numNodes; i++) {
        visited[i] = FALSE;
    }
    //检查有没有环
    if (BFSisLoop(G,&Q, 0, -1) == FALSE) {
        printf("IS LOOP\n");
        return FALSE;
    }
    // 检查连通，同上面
    for(int i = 0;i < G.numNodes;i++) {
        if(visited[i] == FALSE) {
            return FALSE;
        }
    }
    return TRUE;
}

//设计算法, 按照广度遍历算法的基本方法判断有向图G是否是一棵以v0为根的有向树
Status isRootTreeBFS(MGraph G,int root) {
    if(!isTreeBFS(G)) {
        return ERROR;
    }
    for(int i = 0;i < G.numNodes;i++) {
        if(G.arc[i][root-1] != INFINITY && G.arc[i][root-1] != 0) {
            return ERROR;
        }
    }
    return OK;
}

//设计算法以求出距离顶点v0的最短路径长度（以弧数为单位）为最长的顶点, 并要求时间尽可能地少。
//(1) 若要求输出满足条件的所有结点, 是否可通过在本算法中简单加些操作来实现？如何设计？
//(2) 设计算法求出一棵树中层次数最大（小）的叶子结点。
int Farest(MGraph G) {
    Queue Q;
    Init(&Q);
    int co = 0;
    for(int i = 0;i < G.numNodes;i++) {
        visited[i] = FALSE;
    }
    for(int i = 0;i < G.numNodes;i++) {
        if(visited[i] == FALSE) {
            visited[i] = TRUE;
            Add(&Q,i);
            while(Length(&Q) != 0) {
                int node;
                DeAdd(&Q,&node);
                co = G.vexs[node];
                for(int j = 0;j < G.numNodes;j++) {
                    if(G.arc[node][j] == 1 && visited[j] == FALSE) {
                        visited[j] = TRUE;
                        Add(&Q,j);
                    }
                }
            }
        }
    }
    return co;
}

Status MaxLeaf(MGraph G) {
    if(isTreeBFS(G) == FALSE) {
        return -1;
    } else {
        Queue Q;
        Init(&Q);
        int maxDepth = 0;
        int maxDepthLeaf = -1;
        for(int i = 0;i < G.numNodes;i++) {
            visited[i] = FALSE;
        }
        Add(&Q, 0);  // 假设从节点0开始遍历
        visited[0] = TRUE;
        
        int depth = 0;
        while(Length(&Q) != 0) {
            int levelSize = Length(&Q);  // 当前层节点数
            
            for(int i = 0; i < levelSize; i++) {
                int node;
                DeAdd(&Q, &node);
                
                // 叶子节点判断：若某节点没有未访问的子节点
                int isLeaf = TRUE;
                for(int j = 0; j < G.numNodes; j++) {
                    if(G.arc[node][j] == 1 && visited[j] == FALSE) {
                        visited[j] = TRUE;
                        Add(&Q, j);
                        isLeaf = FALSE;
                    }
                }
                
                if(isLeaf) {
                    if(depth > maxDepth) {
                        maxDepth = depth;
                        maxDepthLeaf = node;
                    }
                }
            }
            depth++;
        }
        
        return G.vexs[maxDepthLeaf]; 
    }
}
//设计算法在图G的顶点子集U中找出距离顶点v0最近的顶点（以弧数为单位）, 并要求时间尽可能地少。
int Nearest(MGraph G) {}
//设计算法求距离顶点v0的最短路径长度（以弧数为单位）为k的所有顶点，并要求时间尽可能地少。
Status FindPoint(MGraph G,int length) {}
//设计算法求顶点v0到每个顶点的最短路径（以弧数为单位）, 要求时间尽可能地少。

//设计算法求出以顶点v0为根的广度遍历生成树。

//设计算法以对给定的两点，寻找出最短路径。

//最小生成树-普里姆（Prim）算法
//从初点开始找，选择最小权值的路
//然后比较每次已到达点的相连的路的权值，选择小的，最后直到已到达所有的点
void Prim(MGraph G) {
    int adjvex[MAXVEX],lowcost[MAXVEX];
    //从v0点开始，所以索引为0（从哪里开始都行）
    adjvex[0] = 0;
    lowcost[0] = 0;
    //当lowcost[i] = 0时，代表纳入最小生成树中
    for(int i = 1;i < G.numNodes;i++) {
        //arc[0][i]代表所有与0相连的边的权值(weight)
        //lowcost储存与0连接的边的权值
        lowcost[i] = G.arc[0][i];
        adjvex[i] = 0;
    }
    //初始化完成，开始构建树
    for(int i = 1;i < G.numNodes;i++) {
        int min = INFINITY;
        //k存储最小权值的下标
        //j做顶点下标循环变量
        //从顶点0的下一个1开始
        int j = 1,k = 0;
        while(j < G.numNodes) {
            if(
                lowcost[j] != 0 && 
                lowcost[j] < min) {
                    min = lowcost[j];
                    k = j;
                }
            j++;
        }
        //循环结束后，与顶点0相连的边中最小权值与下标已更新
        //adjvex[k]时与顶点k连接的顶点
        printf("(%d,%d)\n",adjvex[k]+1,k+1);
        //当lowcost[i] = 0时，代表纳入最小生成树中
        lowcost[k] = 0;
        //lowcost储存与0连接的边的权值
        //再次遍历
        for(int j = 1;j < G.numNodes;j++) {
            //对于未纳入生成树的顶点j
            //且点j到k的边权值小于0到j的权值时
            if(
                lowcost[j] != 0 && 
                G.arc[k][j] < lowcost[j]) {
                    //重复类似最开始初始化顶点0的操作
                    //但此时初始化顶点k
                    lowcost[j] = G.arc[k][j];
                    adjvex[j] = k;
                }
        }
    }
}
//最小生成树-克鲁斯卡尔（Kruskal）算法
//建立新的数组保存每一条边的两点与权值
//从权值最小的边开始，直到所有的点都到达
typedef struct {
    int begin,end,weight;
} Edge;

void MappaoSort(Edge edge[],int length) {
    for(int i = 0;i < length-1;i++) {
        for(int j = 0;j < length-i-1;j++) {
            if(edge[j].weight > edge[j+1].weight) {
                Edge temp = edge[j];
                edge[j] = edge[j+1];
                edge[j+1] = temp;
            }   
        }
    }
}

Edge TransferEdgeArr(MGraph G,Edge edge[]) {
    int count = 0;
    for(int i = 0;i < G.numEdges;i++) {
        for(int j = i+1;j < G.numNodes;j++) {
            if(G.arc[i][j] != INFINITY) {
                edge[count].begin = i;
                edge[count].end = j;
                edge[count].weight = G.arc[i][j];
                count++;
            }
        }
    }
    MappaoSort(edge,G.numEdges);
}
//返回某个顶点vex所属连通分量的根节点
int Find(int parent[],int vex) {
    //当vex点有父节点时，继续向上追溯
    while(parent[vex] > 0) {
        vex = parent[vex];
    }
    //找到根节点
    return vex;
}

void Kruskal(MGraph G,Edge edge[]) {
    //parent[i]的值代表顶点i的父节点
    int parent[MAXVEX];
    //初始状态0，表示父节点就是自己
    for(int i = 0;i < G.numNodes;i++) {
        parent[i] = 0;
    }
    for(int i = 0;i < G.numEdges;i++) {
        //查找边的左右顶点的父节点
        int n = Find(parent,edge[i].begin);
        int m = Find(parent,edge[i].end);
        //如果父节点相同，则构成环，跳过构建
        //如果不同，将n的父节点定义为m
        if(n != m) {
            parent[n] = m;
            //parent[m] = n;
            printf("(%d,%d) Weight %d\n",edge[i].begin+1,edge[i].end+1,edge[i].weight);
        }
    }
}
//最短路径-迪杰斯特拉（Dijkstra）算法
//选择初点，然后将剩余的点列表格横行，纵列为循环次数（1~NodeNums-1）
//表格之填入权值（初始化第一次循环一列为无穷），
//然后找初点能通过一条边就到达的点们，比较权值与现有表格中的大小，若更小则更新，否则不动，
//完成一次循环后，选出一列最小数对应的顶点，纳入最短路径的点（纳入后不再参与下面循环），
//如此反复最后得到纳入最短路径的点按顺序走就是最短路径
int pathArc[MAXVEX];
int shortPath[MAXVEX];
void printPath(int v0,int v) {
    if(pathArc[v] == -1) {
        printf("%d ",v0);
        return;
    }
    printPath(v0,pathArc[v]);
    printf("%d ",v);
}
//PathArc为最短路径 ShortPathTable为带权长度
void Dijkstra(MGraph G,int v0) {
    int final[MAXVEX];
    for(int v = 0;v < G.numNodes;v++) {
        // FALSE标记为未访问,TRUE已访问
        final[v] = FALSE;
        // 当前顶点到其他顶点的边权值
        // 初始化最短路径值
        shortPath[v] = G.arc[v0][v];
        // 初始化路径数组
        pathArc[v] = -1;
    }
    // 源节点到自身的距离为0
    shortPath[v0] = 0;
    // 源节点已访问
    final[v0] = TRUE;
    //开始主循环
    for(int v = 1;v < G.numNodes;v++) {
        //k用于保存下标，若没找到则默认-1结束算法
        int min = INFINITY,k = -1;
        for(int w = 0;w < G.numNodes;w++) {
            if(final[w] == FALSE && shortPath[w] < min) {
                k = w;
                min = shortPath[w];
            }
        }
        //若没找到则默认-1结束算法
        if(k == -1) {
            break;
        } else {
            // 标记该节点为已访问
            final[k] = TRUE;
        }
        // 更新当前最短路径与距离
        for(int w = 0;w < G.numNodes;w++) {
            //如果经过顶点k到w的路径G.arc[k][w]比现在这条路径还要短
            if(final[w] == FALSE && (min + G.arc[k][w] < shortPath[w])) {
                shortPath[w] = min + G.arc[k][w];
                // 记录路径
                pathArc[w] = k;
            }
        }
    }
}
//最短路径-弗洛伊德（Floyd）算法
//列出邻接矩阵，然后从初点开始作为中间点k，
//查看v到k到w所需的路径是否比上一次更小，若小则更新矩阵内容，直到所有的点全做过中间点
//其中在每次变换更新时同时记录一个矩阵，存储v到w时，w的前一个点（最后生成的表通过不断查找前驱可得到完整的最短路径）
int pathArcs[MAXVEX][MAXVEX];
int shortPaths[MAXVEX][MAXVEX];
void Floyd(MGraph G) {
    for(int v = 0;v < G.numNodes;v++) {
        for(int w = 0;w < G.numNodes;w++) {
            shortPaths[v][w] = G.arc[v][w];
            pathArcs[v][w] = w;
        }
    }
    //k为中间点，v源点w终点
    for(int k = 0;k < G.numNodes;k++) {
        for(int v = 0;v < G.numNodes;v++) {
            for(int w = 0;w < G.numNodes;w++) {
                if(shortPaths[v][w] > shortPaths[v][k] + shortPaths[k][w]) {
                    shortPaths[v][w] = shortPaths[v][k] + shortPaths[k][w];
                    pathArcs[v][w] = pathArcs[v][k];
                }
            }
        }
    }
}
//设计算法实现函数firstadj(G, v)（返回第一个与v连接的点）
VertexType firstAdj(MGraph G,VertexType v) {
    for(int i = 0;i < G.numNodes;i++) {
        int weight = G.arc[v-1][i];
        if(weight != INFINITY && weight != 0) {
            return i+1;
        }
    }
    return -1;
}
//设计算法实现函数nextadj(G, v, w)（返回与v相邻并在w之后的下一个顶点）。
VertexType nextAdj(MGraph G,VertexType v,VertexType w) {
    //从 w 的下一个位置开始，寻找下一个与 v 相邻的顶点
    for (int i = w; i < G.numNodes; i++) {
        int weight = G.arc[v-1][i]; 
        if (weight != INFINITY && weight != 0) {  
            return i + 1;  
        }
    }
    return -1; 
}
//设计算法求无向图顶点v的度
//任一无向图中各顶点的度的和一定为偶数。因为出入度为2
int NoDegree(MGraph G,VertexType v) {
    int count = 0;
    for(int i = 0;i < G.numNodes;i++) {
        int weight = G.arc[v-1][i];
        if (weight != INFINITY && weight != 0) {
            count++;
        }
    }
    return count*2;   
}
//设计算法求有向图顶点v的入度、出度和度
typedef struct {
    int total,in,out;
} Degree;

Degree HaveDegree(MGraph G,VertexType v) {
    Degree degree;
    degree.in = 0;
    degree.out = 0;
    for(int i = 0;i < G.numNodes;i++) {
        int weight = G.arc[v-1][i];
        if (weight != INFINITY && weight != 0) {
            degree.out++;
        }
    }
    for(int j = 0;j < G.numNodes;j++) {
        int weight = G.arc[j][v-1];
        if (weight != INFINITY && weight != 0) {
            degree.in++;
        }
    }
    degree.total = degree.in + degree.out;
    return degree;  
}
//设计算法以判断是否是无向图
Status isWuxiang(MGraph G) {
    for(int i = 0;i < G.numNodes;i++) {
        for(int j = 0;j < G.numNodes;j++) {
            if(G.arc[i][j] != G.arc[j][i]) {
                return FALSE;
            }
        }
    }
    return TRUE;
}
//设计算法以判断顶点vi到vj之间是否存在路径(vi可沿着到达vj就算有路径，中间不得中断)
void DFS3(MGraph G,VertexType v) {
    visited[v] = TRUE;
    for (int j = 0; j < G.numNodes; j++) {
        if (G.arc[v][j] != 0 && G.arc[v][j] != INFINITY && !visited[j]) {
            DFS3(G, j); 
        }
    }
}

Status isHaveEdge(MGraph G,VertexType vi,VertexType vj) {
    vi -= 1;
    vj -= 1;
    for(int i = 0;i < G.numNodes;i++) {
        visited[i] = FALSE;
    }
    DFS3(G,vi);
    return visited[vj];
}
//设计算法以求解二叉树中层次最小的一个叶子结点的值
VertexType TreeLeaf(MGraph G) {}
//有n个选手参加的单循环比赛要进行多少场比赛？试用图结构描述。若是主客场制的联赛，又要进行多少场比赛
//单循环每两人进行比赛一次，所以是完全图，次数n(n-1)/2；若为主客场则再*2，为n(n-1)

//生成BFS的邻接矩阵
void InitBFSArc(int Arc[MAXVEX][MAXVEX],MGraph G) {
    int num = G.numNodes;
    for(int i = 0;i < G.numNodes;i++) {
        for(int j = 0;j < G.numNodes;j++) {
            Arc[i][j] = INFINITY;
        }
    }
    for(int i = 0;i < G.numNodes;i++) {
        Arc[i][i] = 0;
    }
}

void BFSS(MGraph G,int i,Queue *Q,int Arc[MAXVEX][MAXVEX]) {
    visited[i] = TRUE;
    //入队
    Add(Q,i);
    
    printf("ADD %d ",i+1);
    while(Length(Q) != 0) {
        ElemType E;
        //出队
        DeAdd(Q,&E);
        for(int j = 0;j < G.numNodes;j++) {
            if(G.arc[E][j] != INFINITY && G.arc[E][j] != 0) {
                if(visited[j] == FALSE) {
                    visited[j] = TRUE;
                    ///printf("ADD %d ",j+1);
                    Arc[E][j] = G.arc[E][j];
                    //无向图，对称矩阵
                    Arc[j][E] = Arc[E][j];
                    Add(Q,j);
                }
            }
        } 
    }
}

void GetBFSArc(int Arc[MAXVEX][MAXVEX],MGraph G) {
    //初始化队列
    Queue Q;
    Init(&Q);
    //初始化邻接矩阵
    InitBFSArc(Arc,G);
    //初始化VISITED
    for(int i = 0;i < G.numNodes;i++) {
        visited[i] = FALSE;
    }
    for(int i = 0;i < G.numNodes;i++) {
        if(visited[i] == FALSE) {
            BFSS(G,i,&Q,Arc);
        }
    }
    for(int i = 0;i < G.numNodes;i++) {
        for(int j = 0;j < G.numNodes;j++) {
            printf("%d ",Arc[i][j]);
        }
        printf("\n");
    }
}
//DFS非递归写法-借助栈
void DFSNot(MGraph G) {
    Stack S;
    InitStack(&S);
    for(int i = 0;i < G.numNodes;i++) {
        visited[i] = FALSE;
    }
    for(int j = 0;j < G.numNodes;j++) {
        if(visited[j] == FALSE) {
            Push(&S,j);
            visited[j] = TRUE;
        }
        
        while(S.top != -1) {
            ElemType E;
            Pop(&S,&E);
            printf("%d ",E+1);
            for(int i = 0;i < G.numNodes;i++) {
                if(G.arc[E][i] != INFINITY && G.arc[E][i] != 0) {
                    if(visited[i] == FALSE) {
                        visited[i] = TRUE;
                        Push(&S,i);
                    }
                }
            }
        }
    }
}
//设计算法求解距离v最远的点


int main() {
    MGraph G;
    Status i;
    i = Create(&G);
 // i = CreateHuzhi(&G);
   // GetDFS(G);
    printf("\n*******\n");
  //  if(isConnected(G) == OK) {
  //      printf("IS CONNECTED");
  //  } else {
  //      printf("NOT CONNECTED");
 //   }
 //   printf("\n*******\n");
  //  printf("Edge count is %d",EdgeCounts(G));
   // printf("\n*******\n");
  //  if(isTreeBFS(G)) {
  //      printf("IS TREE");
  //  } else {
  //      printf("NOT TREE");
  //  }
   // printf("\n*******\n");
    //printf("ConnectedNum is %d",ConectedCount(G));
   // printf("\n*******\n");
    //GetBFS(G);
   // printf("\n*******\n");
   // printf("The farest node is %d",Farest(G));
   // printf("\n*******\n");
   // printf("The farest node is %d",MaxLeaf(G));
    //Prim(G);
    Edge edge[G.numEdges];
    TransferEdgeArr(G,edge);
    Kruskal(G,edge);
    //Dijkstra(G,0);
    //for(int i = 0;i < G.numNodes;i++) {
      //  printPath(0,i);
       // printf("\n");
    //}
  //  VertexType v;
  //  printf("Input node (1~%d)\n",G.numNodes);
   // scanf("%d",&v);
   // if(firstAdj(G,v) == -1 || v > G.numNodes || v < 1) {
  //      printf("No");
    //} else {
    //    printf("The node %d next is %d\n",v,firstAdj(G,v));
   //     printf("The node %d anext is %d\n",v,nextAdj(G,v,firstAdj(G,v)));
   //     //printf("The node %d degree is %d\n",v,NoDegree(G,v));
  //      printf("The node %d degreeIn is %d degreeOut is %d degree is %d\n",v,HaveDegree(G,v).in,HaveDegree(G,v).out,HaveDegree(G,v).total);
 //   }
   // if(!isWuxiang(G)) {
  //      printf("is Youxiang");
  //  } else {
  //      printf("is Wuxiang");
   // }
   // if(isHaveEdge(G,2,3) == TRUE) {
   //     printf("Have Way");
  //  } else {
   //     printf("No way");
   // }
   //GetDFS(G);
   //DFSPrint(G,1);
   //printf("\n*******\n");
   //DeleteVex(&G,2);
   //GetDFS(G);
   //i = isJoint(&G,5);
   //if(i) {
     //   printf("YES");
   //} else {
   // printf("NO");
   //}
  // i = isRootTreeBFS(G,1);
  // if(i) {
   // printf("YES");
   ///} else {
   // printf("NO");
   //}
   //int Arc[MAXVEX][MAXVEX];
   //GetBFSArc(Arc,G);
   ///DFSNot(G);
}
