#include<stdio.h>
#include<stdlib.h>

typedef struct TreeNode{
    char data;
    struct TreeNode* lchild;
    struct TreeNode* rchild;
    int flag;
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
        (*T)->flag = 0;
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

Stack* getTop(Stack* s){
    if(!isEmpty(s)){
        Stack* node = s->next;
        return node;
    }
    else{
        return NULL;
    }
}

void postOrder(TreeNode* T){
    Stack* s = initStack();
    TreeNode* node = T;
    while(node || !isEmpty(s)){
        if(node){
            push(node, s);
            node = node->lchild;
        }
        else{
            TreeNode* top = getTop(s)->data;
            if(top->rchild && top->rchild->flag == 0){
                top = top->rchild;
                push(top, s);
                node = top->lchild;
            }
            else{
                top = pop(s)->data;
                printf("%c ", top->data);
                top->flag = 1;
            }
        }
    }
}

int main(int argc, char* argv[]){
    TreeNode* T;
    int index = 0;
    createTree(&T, argv[1], &index);
    postOrder(T);
    printf("\n");
    return 0;
}