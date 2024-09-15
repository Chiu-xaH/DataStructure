void GetHead(Tree T) {
    Push(T);
    while(!isEmpty(S)) {
        E = Pop(S);
        printf("%d",E->data);
        if(E->rightChild) Push(E->rightChild);
        if(E->leftChild) Push(E->leftChild);
    }
}

void GetMiddle(Tree T) {
    Tree tree = T;
    while(tree || !isEmpty(S)) {
        if(tree) {
            Push(tree);
            tree = tree->leftChild;
        } else {
            E = Pop(S);
            printf("%d",E->data);
            tree = E->rightChild;
        }
    }
}

void GetTail(Tree T) {
    Tree tree = T,prv = NULL;
    while(tree || !isEmpty(S)) {
        if(tree) {
            Push(tree);
            tree = tree->leftChild;
        } else {
            E = GetTop(S);
            if(E->rightChild == NULL || E->rightChild == prv) {
                printf("%d",E->data);
                prv = E;
                Pop(S);
            } else {
                tree = E->rightChild;
            }
        }
    }
}