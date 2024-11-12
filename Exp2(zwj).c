#include <stdio.h>
#include <stdlib.h>
#define MAX_SIZE 100
typedef  struct {

    int *top;
    int *base;
    int stacksize;
}SqStack;
//ָ��top  ջ��Ԫ����˳��ջ��λ��
//ָ��base ջ��Ԫ����˳��ջ��λ��
void initStack(SqStack *s) {
    s->base = (int *)malloc(MAX_SIZE * sizeof(int));
    if(!s->base) {
        return;
    }
    s->top = s->base;
    s->stacksize = MAX_SIZE;
    printf("˳��ջ��ʼ�����,%d\n", s->stacksize);
}
//�ж�ջ�Ƿ�Ϊ��
void IsEmpty(SqStack *s) {
    if(s->top == s->base) {
        printf("��ջ");
    }
}
void isFull(SqStack *s) {
    if(s->top - s->base >= s->stacksize) {
        printf("ջ��");
    }
}
//��ջ�ĺ���
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
    printf("ջ�Ѿ��ݻ����\n");
    printf("%d",s->stacksize);
}
//��ջ�ĺ���
void pop(SqStack *s,int e) {
    if(s->stacksize == 0) {
        return;
    }
    else {
        s->top--;
        e=*s->top;
    }
}
//ȡջ��Ԫ��

int main() {
    int num;
    int e;
    printf("������һ����\n");
    scanf("%d",&num);
    SqStack s;
    initStack(&s);
    //��ջ
    // display(&s);
    push(&s, num);
    // //��ջ
    // pop(&s,e);
    // distroy(&s);
    return  0;
}