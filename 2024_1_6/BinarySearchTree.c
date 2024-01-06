#include<stdio.h>
#include<stdlib.h>

typedef struct TreeNode{
    char data;
    struct TreeNode* lchild;
    struct TreeNode* rchild;
}TreeNode;

TreeNode* bst(TreeNode* T, int key){
    if(T){
        if(key == T->data){
            return T;
        }
        else if(key < T->data)
            return bst(T->lchild, key);
        else if(key > T->data)
            return bst(T->rchild, key);
    }
}

void bstInsert(TreeNode** T, int key){
    if(*T == NULL){
        *T = (TreeNode*)malloc(sizeof(TreeNode));
        (*T)->data = key;
        (*T)->lchild = NULL;
        (*T)->rchild = NULL;
    }
    else if(key < (*T)->data)
        bstInsert(&((*T)->lchild), key);
    else if(key == (*T)->data)
        return;
    else
        bstInsert(&((*T)->rchild), key);
}

void preOrder(TreeNode* T){
    if(T){
        printf("%d ", T->data);
        preOrder(T->lchild);
        preOrder(T->rchild);
    }
}

int main(int argc, char* argv[]){
    TreeNode* T = NULL;
    int nums[6] = {8,6,10,9,11,23};
    for(int i = 0; i < 6; i++){
        bstInsert(&T,nums[i]);
    }
    preOrder(T);
    printf("\n");
    return 0;
}