#define _CRT_SECURE_NO_WARNINGS 1

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_BOOKS 100
#define MAX_NAME 50
#define MAX_ID 50

// 定义图书结构体
typedef struct {
    char id[MAX_ID];
    char name[MAX_NAME];
    float price;
} Book;

// 定义顺序表结构
typedef struct {
    Book books[MAX_BOOKS];
    int length;
} SeqList;

void initSeqList(SeqList* L) {
    L->length = 0;
}


void inputSeqList(SeqList* L) {
    Book newBook;
    printf("请输入图书信息（书号 书名 价格），输入 '0 0 0' 结束：\n");
    while (L->length < MAX_BOOKS) {
        //读取用户输入
        if (scanf("%19s%49s%f", newBook.id, newBook.name, &newBook.price) != 3) {
            printf("输入错误，请重新输入\n");
            while (getchar() != '\n')
                continue;
        }

        //检查是否输入结束符 '0 0 0'
        if (strcmp(newBook.id, "0") == 0 && strcmp(newBook.name, "0") == 0 && newBook.price == 0) {
            break;
        }
        // 只有在不是 '0 0 0' 的情况下才添加图书
        L->length++;
        L->books[L->length] = newBook;
    }

}
void printDetailSL(SeqList* L) {
    if (L->length == 0) {
        printf("空表\n");
    }
    printf("%d\n", L->length);
    for (int i = 0; i < L->length; i++) {
        if (strcmp(L->books[i].id, "0") != 0 && strcmp(L->books[i].name, "0") != 0
            && (L->books->price != 0)
            ) {
            printf("%15s %15s %.2f\n", L->books[i].id, L->books[i].name, L->books[i].price);
        }
    }
}

void addSeqList(SeqList* L) {
    printf("请输入图书的书号、书名和价格，输入0 0 0结束输入\n");
    inputSeqList(L);
    printf("图书总数:%d\n", L->length);
    printDetailSL(L);
}
float calculateAverage(SeqList* L) {
    float sum = 0;
    float average = 0;
    const int n = L->length;
    if (n == 0) {
        printf("图书列表为空，无法计算平均价格。\n");
    }
    for (int i = 0; i <= n; i++) {
        sum += L->books[i].price;
    }
    average = sum / n;
    return average;
}
void printChangeSL(SeqList* L, float average) {
    for (int i = 0; i < L->length; i++) {
        if (L->books[i].price < average) {
            L->books[i].price = L->books[i].price * (1 + 0.2);
        }
        else {
            L->books[i].price = L->books[i].price * (1 - 0.1);
        }
    }
}
float FindMax(SeqList* L) {
    float max = L->books[0].price;
    for (int i = 1; i < L->length; i++) {
        if (L->books[i].price > max) {
            max = L->books[i].price;
        }
    }
    return max;
}
void InsertBook(SeqList* L) {
    int position = 0;
    scanf("%d", &position);
    printf("%d", position);
}
void DeleteBook(SeqList* L) {
    int position = 0;
    scanf("%d", &position);
    printf("%d", position);
}
int main() {
    //顺序表实现
    float average = 0;
    //第一步   创建和输出
    SeqList myBooks;
    initSeqList(&myBooks);
    inputSeqList(&myBooks);
    printDetailSL(&myBooks);
    // printChangeSL(&myBooks, average);
    //第二步   基于顺序存储结构的图书信息表的修改
    average = calculateAverage(&myBooks);
    printf("图书平均价格为: %.2f\n", average);
    printChangeSL(&myBooks, average);
    //第三步  图书信息表的最贵图书的查找
    FindMax(&myBooks);
    //第四步 基于顺序存储结构的图书信息表的新图书的入库
    InsertBook(&myBooks);
    //第五步 基于顺序存储结构的图书信息表的旧图书的出库
    DeleteBook(&myBooks);
    return 0;
}