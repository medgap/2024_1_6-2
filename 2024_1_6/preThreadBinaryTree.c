#include<stdio.h>
#include<stdlib.h>

typedef struct TreeNode{
    char data;
    struct TreeNode* lchild; 
    struct TreeNode* rchild; 
    int ltag;
    int rtag;
}TreeNode;

void createTree(TreeNode** T, char* data, int* index){
    char ch = data[*index];
    *index += 1;
    if(ch == '#'){
        *T = NULL;
    }
    else{
        *T = (TreeNode*)malloc(sizeof(TreeNode));
        (*T)->data = ch;
        (*T)->ltag = 0;
        (*T)->rtag = 0;
        createTree(&((*T)->lchild), data, index);
        createTree(&((*T)->rchild), data, index);
    }
}

void preThreadTree(TreeNode* T, TreeNode** pre){
    if(T){
        //do sth.
        if(T->lchild == NULL){
            T->ltag = 1;
            T->lchild = *pre;
        }
        if(*pre && (*pre)->rchild == NULL){
            (*pre)->rtag = 1;
            (*pre)->rchild = T;
        }
        *pre = T;
        if(T->ltag == 0)
            preThreadTree(T->lchild, pre);
        if(T->rtag == 0)
            preThreadTree(T->rchild, pre);
    }
}

TreeNode* getNext(TreeNode* T){
    if(T->rtag == 0){
        if(T->ltag == 0)
            return T->lchild;
        else
            return T->rchild;
    }
    else{
        return T->rchild;
    }
}

int main(int argc, char* argv[]){
    TreeNode* T;
    TreeNode* pre = NULL;
    int index = 0;
    createTree(&T, argv[1], &index);
    preThreadTree(T, &pre);
    pre->rtag = 1;
    pre->rchild = NULL;
    for(TreeNode* node = T; node != NULL; node = getNext(node)){
        printf("%c ", node->data);
    }
    printf("\n");
    return 0;
}