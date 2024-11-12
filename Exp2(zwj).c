#include <stdio.h>
#include <stdlib.h>
#define MAX_SIZE 100
typedef  struct {

    int *top;
    int *base;
    int stacksize;
}SqStack;
//指针top  栈顶元素在顺序栈的位置
//指针base 栈底元素在顺序栈的位置
void initStack(SqStack *s) {
    s->base = (int *)malloc(MAX_SIZE * sizeof(int));
    if(!s->base) {
        return;
    }
    s->top = s->base;
    s->stacksize = MAX_SIZE;
    printf("顺序栈初始化完毕,%d\n", s->stacksize);
}
//判断栈是否为空
void IsEmpty(SqStack *s) {
    if(s->top == s->base) {
        printf("空栈");
    }
}
void isFull(SqStack *s) {
    if(s->top - s->base >= s->stacksize) {
        printf("栈满");
    }
}
//入栈的函数
void push(SqStack *s, int x) {
    if(s->top - s->base==s->stacksize) {
        return;
    }
    *s->top = x;
    printf("%d,%d\n", *s->top, s->stacksize);
    s->top++;
}
void distroy(SqStack *s) {
    free(s->base);
    s->base = NULL;
    s->top=NULL;
    s->stacksize = 0;
    printf("栈已经摧毁完毕\n");
    printf("%d",s->stacksize);
}
//出栈的函数
void pop(SqStack *s,int e) {
    if(s->stacksize == 0) {
        return;
    }
    else {
        s->top--;
        e=*s->top;
    }
}
//取栈顶元素

int main() {
    int num;
    int e;
    printf("请输入一个数\n");
    scanf("%d",&num);
    SqStack s;
    initStack(&s);
    //入栈
    // display(&s);
    push(&s, num);
    // //出栈
    // pop(&s,e);
    // distroy(&s);
    return  0;
}