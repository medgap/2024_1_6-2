#include<stdio.h>
#include<stdlib.h>

typedef struct TreeNode{
    char data;
    struct TreeNode* lchild;
    struct TreeNode* rchild;
}TreeNode;

typedef struct QueueNode{
    TreeNode* data;
    struct QueueNode* pre;
    struct QueueNode* next;
}QueueNode;

void createTree(TreeNode** T, char* data, int* index){
    char ch = data[*index];
    *index += 1;
    if(ch == '#'){
        *T = NULL;
    }
    else{
        *T = (TreeNode*)malloc(sizeof(TreeNode));
        (*T)->data = ch;
        createTree(&((*T)->lchild), data, index);
        createTree(&((*T)->rchild), data, index);
    }
}

QueueNode* initQueue(){
    QueueNode* q = (QueueNode*)malloc(sizeof(QueueNode));
    q->data = NULL;
    q->pre = q;
    q->next = q;
    return q;
}

void enQueue(QueueNode* q, TreeNode* data){
    //tail
    QueueNode* node = (QueueNode*)malloc(sizeof(QueueNode));
    node->data = data;
    node->pre = q->pre;
    node->next = q;
    node->pre->next = node;
    q->pre = node;
}

int isEmpty(QueueNode* q){
    if(q->next == q)
        return 1;
    return 0;
}

TreeNode* deQueue(QueueNode* q){
    if(!isEmpty(q)){
        QueueNode* node = q->next;
        node->next->pre = q;
        q->next = node->next;
        return node->data;
    }
    else{
        return NULL;
    }
}

void LevelTraverse(TreeNode* T, QueueNode* q){
    enQueue(q,T);
    while(!isEmpty(q)){
        TreeNode* node = deQueue(q);
        printf("%c ", node->data);
        if(node->lchild)
            enQueue(q, node->lchild);
        if(node->rchild)
            enQueue(q, node->rchild);
    }
}

int main(int argc, char* argv[]){
    TreeNode* T;
    int index = 0;
    createTree(&T, argv[1], &index);
    QueueNode* q = initQueue();
    LevelTraverse(T,q);
    return 0;
}