//判断是否是关节点
Status visited[MAX];

void DFS(MGraph G,int i,int skip) {
    visited[i] = TRUE;
    for(int j = 0;j < G.numNodes;j++) {
        if(G.arc[i][j] != INFINITY && G.arc[i][j] != 0) {
            if(visited[j] == FALSE && j != skip) {
                DFS(G,j,skip);
            }
        }
    }
}

int ConnectedNum(MGraph G) {
    int count = 0;
    for (int i = 0; i < G.numNodes; i++) {
        visited[i] = FALSE;
    }
    for (int i = 0; i < G.numNodes; i++) {
        if (visited[i] == FALSE) {
            count++;
            DFS(G, i, -1);  // -1表示不跳过任何顶点
        }
    }
    return count;
}

Status isJoint(MGraph G,int vex) {
    int count = 0;
    for(int i = 0;i < G.numNodes;i++) {
        visited[i] = FALSE;
    }
    for(int i = 0;i < G.numNodes;i++) {
        if(visited[i] == FALSE && i != vex) {
            count++;
            DFS(G,j,vex);
        }
    }
    //如果连通分量相比原来增加则返回true
    return (count > ConnectedNum(G));
}