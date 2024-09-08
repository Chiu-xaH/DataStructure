#include <stdio.h>
#include <stdlib.h>

#define OK 1
#define ERROR 0

typedef int Status;
typedef char ElemType;

typedef enum {
    ATOM,//原子
    LIST//表
} ElemTag;

typedef struct GLNode {
    ElemTag tag;
    //tag为0原子结点，为1列表结点
    union {
        ElemType atom;
        struct GLNode *subList;//指向下一节点
    } data;
    struct  GLNode *next;//指向下一节点
} GLNode,*GList;

union {
    ElemType atom;
    struct GLNode *subList;//指向下一节点
} data;

Status Init(GList *G) {
    (*G) = (GList)malloc(sizeof(GLNode));
    (*G)->next = NULL;
    return OK;
}

Status CreateATOM(GList *G,ElemType E) {
    GList list = *G;
    GList new = (GList)malloc(sizeof(GLNode));
    GList old = list->next;
    
    new->tag = ATOM;
    new->data.atom = E;
    list->next = new;
    new->next = old;

    return OK;
}

Status CreateList(GList *G,GList *SubG) {
    GList list = *G;
    GList new = (GList)malloc(sizeof(GLNode));
    GList old = list->next;
    
    new->tag = LIST;
    new->data.subList = *SubG;
    list->next = new;
    new->next = old;

    return OK;
}

ElemType GetHead(GList *G){
    GList list = (*G)->next;
    if(list->tag == ATOM) {
        return list->data.atom;
    } else if(list->tag == LIST) {
        GetHead(&list->data.subList);
    }
}

ElemType GetTail(GList *G) {
    GList list = (*G);
    while(list->next) {
        list = list->next;
    }
    if(list->tag == ATOM) {
        return list->data.atom;
    } else if(list->tag == LIST) {
        GetTail(&list->data.subList);
    }
}

GList Head(GList G) {
    if (G == NULL || G->next == NULL) {
        return NULL;
    }
    return G->next;
}

GList Tail(GList G){
    return G->next->next;
}

Status Get(GList *G) {
    GList list = (*G)->next;
    printf("( ");
    while(list) {
        if(list->tag == ATOM) {
            printf("%c ",list->data.atom);
        } else if(list->tag == LIST) {
            Get(&list->data.subList);
        }
        list = list->next;
    }
    printf(") ");
    return OK;
}

int main() {
    //( ( ( A B ) ( C D ) ) ( E ( F G ) ) )
    Status i;
    ElemType E;
    GList G,G1,G2,G3,G4,G5,G6;
    i = Init(&G);
    i = Init(&G1);
    i = Init(&G2);
    i = Init(&G3);
    i = Init(&G4);
    i = Init(&G5);
    i = Init(&G6);
    i = CreateATOM(&G1,'B');
    i = CreateATOM(&G1,'A');
    i = CreateATOM(&G2,'D');
    i = CreateATOM(&G2,'C');
    i = CreateList(&G3,&G2);
    i = CreateList(&G3,&G1);

    i = CreateATOM(&G4,'G');
    i = CreateATOM(&G4,'F');
    i = CreateList(&G5,&G4);
    i = CreateATOM(&G5,'E');
  
    i = CreateList(&G6,&G5);
    i = CreateList(&G6,&G3);

    i = Get(&G5);
   // ElemType e;
   printf("\n*******\n");
    //E = GetHead(&G6);
   // printf("\nHead is %c",E);
   GList list = Tail(G5);
   Get(&list);
  // GList list2 = Head(list);
   printf("\nHead is %c",list->data);
}