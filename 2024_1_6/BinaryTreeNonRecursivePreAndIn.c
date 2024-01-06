#include<stdio.h>
#include<stdlib.h>

typedef struct TreeNode{
    char data;
    struct TreeNode* lchild;
    struct TreeNode* rchild;
}TreeNode;

typedef struct Stack{
    TreeNode* data;
    struct Stack* next;
}Stack;

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

Stack* initStack(){
    Stack* s = (Stack*)malloc(sizeof(Stack));
    s->data = NULL;
    s->next = NULL;
    return s;
}

void push(TreeNode* data, Stack* s){
    Stack* node = (Stack*)malloc(sizeof(Stack));
    node->next = s->next;
    s->next = node;
    node->data = data;
}

int isEmpty(Stack* s){
    if(s->next == NULL)
        return 1;
    return 0;
}

Stack* pop(Stack* s){
    if(!isEmpty(s)){
        Stack* node = s->next;
        s->next = node->next;
        return node;
    }
    else{
        return NULL;
    }
}

void preOrder(TreeNode* T){
    Stack* s = initStack();
    TreeNode* node = T;
    while(!isEmpty(s) || node){
        if(node){
            push(node, s);
            printf("%c ", node->data);
            node = node->lchild;
        }
        else{
            node = pop(s)->data;
            node = node->rchild;
        }
    }
}

void inOrder(TreeNode* T){
    Stack* s = initStack();
    TreeNode* node = T;
    while(!isEmpty(s) || node){
        if(node){
            push(node, s);
            node = node->lchild;
        }
        else{
            node = pop(s)->data;
            printf("%c ", node->data);
            node = node->rchild;
        }
    }
}

int main(int argc, char* argv[]){
    TreeNode* T;
    int index = 0;
    createTree(&T, argv[1], &index);
    preOrder(T);
    printf("\n");
    inOrder(T);
    printf("\n");
    return 0;
}