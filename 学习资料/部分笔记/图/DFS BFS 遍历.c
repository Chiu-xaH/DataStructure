void DFS(MGraph G,int i) {
    visited[i] = TRUE;
    printf("%d",G.vex[i]);
    for(int j = 0;j < G.numNodes;j++) {
        if( G.arc[i][j] != INFINITY && G.arc[i][j] != 0) {
            if(visited[j] == FALSE) {
                DFS(G,j);
            }
        }
    }
}

void DFSPrint(MGraph G) {
    for(int i = 0;i < G.numNodes;i++) {
        visited[i] = FALSE;
    }
    for(int i = 0;i < G.numNodes;i++) {
        if(visited[i] == FALSE) {
            DFS(G,i);
        }
    }
}

void BFSPrint(Queue *Q,MGraph G,int i) {
    Add(Q,i);
    while(!isEmpty(Q)) {
        int node;
        DeAdd(Q,&node);
        printf("%d",node);
        for(int j = 0;j < G.numNodes;j++) {
            if(G.arc[node][j] != INFINITY && G.arc[node][j] != 0) {
                if(visited[j] == FALSE) {
                    visited[j] = true;
                    Add(Q,j);
                }
            }
        }
    }
}

void BFS(MGraph G) {
    Queue Q;
    for(int i = 0;i < G.numNodes;i++) {
        visited[i] = FALSE;
    }
    for(int i = 0;i < G.numNodes;i++) {
        if(visited[i] == FALSE) {
            BFSPrint(&Q,G,i);
        }
    }
}