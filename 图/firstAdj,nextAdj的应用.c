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

//DFS////////////////////////////////////////////////////////////////////

/*精髓：
    //找到第一个与 v 相邻的顶点
    int w = firstAdj(G, v);
    //递归访问所有与 v 相邻的顶点
    while (w != -1) {
        if (!visited[w]) {
            DFS(G, w, visited);或入队
        }
        w = nextAdj(G, v, w)；
    }

*/
void DFS(MGraph G, int v, int visited[]) {
    // 标记当前顶点 v 已访问
    visited[v-1] = 1;
    printf("%d ", v);  // 输出顶点 v
    
    // 找到第一个与 v 相邻的顶点
    int w = firstAdj(G, v);
    
    // 递归访问所有与 v 相邻的顶点
    while (w != -1) {
        if (!visited[w-1]) {  // 如果顶点 w 未访问过
            DFS(G, w, visited);  // 递归进行深度优先搜索
        }
        w = nextAdj(G, v, w);  // 找到与 v 相邻的下一个顶点
    }
}

// 对整个图进行深度优先遍历
void DFSTraverse(MGraph G) {
    int visited[MAXNODES] = {0};  // 初始化所有顶点为未访问状态

    // 遍历所有顶点，确保每个顶点都被访问到
    for (int v = 1; v <= G.numNodes; v++) {
        if (!visited[v-1]) {  // 如果顶点 v 未访问过
            DFS(G, v, visited);  // 从顶点 v 开始深度优先搜索
        }
    }
}

//BFS/////////////////////////////////////////////////////////////////////
void BFS(MGraph G, VertexType v) {
    Queue Q;
    InitQueue(&Q);  // 初始化队列
    printf("%d ", v);  // 输出当前顶点
    visited[v-1] = TRUE;  // 标记为已访问
    Enqueue(&Q, v);  // 当前顶点入队

    while (!IsEmpty(&Q)) {
        VertexType u = Dequeue(&Q);  // 出队一个顶点
        VertexType w = firstAdj(G, u);  // 获取第一个相邻顶点

        while (w != -1) {  // 如果存在相邻顶点
            if (!visited[w-1]) {  // 如果相邻顶点未访问
                printf("%d ", w);  // 输出顶点
                visited[w-1] = TRUE;  // 标记为已访问
                Enqueue(&Q, w);  // 将相邻顶点入队
            }
            w = nextAdj(G, u, w);  // 获取下一个相邻顶点
        }
    }
}

// 主函数，遍历所有顶点进行BFS
void BFSTraverse(MGraph G) {
    for (int i = 0; i < G.numNodes; i++) {
        visited[i] = FALSE;  // 初始化访问状态
    }

    for (int i = 1; i <= G.numNodes; i++) {  // 遍历所有顶点
        if (!visited[i-1]) {
            BFS(G, i);  // 对未访问的顶点进行BFS
        }
    }
}





//关节点////////////////////////////////////////////////////////////////////
int numComponents;      // 记录连通分量的数量

// 深度优先搜索辅助函数，跳过关节点v
void DFS(MGraph G, int v, int skip) {
    visited[v-1] = 1;  // 标记顶点 v 为已访问

    // 找到第一个与 v 相邻的顶点
    int w = firstAdj(G, v);

    while (w != -1) {
        if (w != skip && !visited[w-1]) {  // 跳过关节点，并检查未访问的顶点
            DFS(G, w, skip);  // 递归访问
        }
        w = nextAdj(G, v, w);  // 找到下一个相邻顶点
    }
}

// 判断顶点 v 是否为关节点
bool isArticulationPoint(MGraph G, int v) {
    // 初始化访问数组
    for (int i = 0; i < G.numNodes; i++) {
        visited[i] = 0;
    }

    // 找到 v 的第一个相邻顶点 w，如果没有相邻点，则 v 不是关节点
    int w = firstAdj(G, v);
    if (w == -1) return false;

    // 从 v 的一个相邻顶点 w 开始进行DFS遍历，跳过顶点 v
    DFS(G, w, v);

    // 检查是否有未访问的顶点
    for (int i = 0; i < G.numNodes; i++) {
        if (i != v-1 && !visited[i]) {
            return true;  // 如果有顶点未被访问，则 v 是关节点
        }
    }
    return false;  // 如果所有顶点都访问到了，则 v 不是关节点
}