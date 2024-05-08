// // 数据结构实验1
// #define _CRT_SECURE_NO_WARNINGS

// #include<stdio.h>
// #include <stdlib.h>
// #include<string.h>
// #include <algorithm>

// using namespace std;//排序函数
// #define TURE 1
// #define FALSE 0
// #define OK 1
// #define ERROR 0
// #define INFEASIBLE -1
// #define OVERFLOW -2
// #define LIST_MAXSIZE 1000//定义图表的最大长度

// //定义图书表的顺序储存结构
// //定义图书信息
// typedef struct {
//     char no[20];//ISBN
//     char name[50];//书名
//     float price;//价格
// } Book;



// //定义顺序储存结构类型
// typedef struct {
//     Book *elem;//储存空间基地址
//     int length;//当前图书个数
// } SqList;
// typedef int ElemType;

// //初始化一个顺序表
// ElemType InitList_SqList(SqList &amp;L) {
//     L.elem = (Book *) malloc(LIST_MAXSIZE * sizeof(Book));//分配空间
//     if (!L.elem)//分配失败
//     {
//         exit(OVERFLOW);
//     }
//     L.length = 0;//空表长度为0
//     return OK;
// }

// //顺序表输入
// ElemType ListInsert(SqList &amp;L) {
//     int i = 1;
//     while (1) {
//         if (i > LIST_MAXSIZE)//输入图书信息数超过最大值，退出	
//         {
//             exit(OVERFLOW);
//         }
//         scanf("%s %s %f", L.elem[i].no, L.elem[i].name, &amp;L.elem[i].price);//输入图书数据 		
//         if (strcmp(L.elem[i].no, "0") == 0 & amp;&amp; strcmp(L.elem[i].name, "0") == 0 & amp;&amp; L.elem[i].price == 0) {
//             break;//输入结束标志0 0 0，表示停止输入
//         }
//         i++;
//     }
//     L.length = i - 1;
//     return i - 1;
// }

// //顺序表输出
// ElemType ListOutput(SqList &amp;L) {
//     for (int i = 1; i <= L.length; i++) {
//         printf("%s %s %.2f\n", L.elem[i].no, L.elem[i].name, L.elem[i].price);//输出图书信息表 		
//     }
//     return OK;
// }


// //顺序表修改价格
// ElemType SqList_Price(SqList &amp;L) {
//     float avg = 0;//平均价格 
//     for (int i = 1; i <= L.length; i++) {
//         avg += L.elem[i].price;//计算所有书的总价格 
//     }
//     avg /= L.length;//所有书的平均价格=总价/书本数量 
//     for (int i = 1; i <= L.length; i++) {
//         if (L.elem[i].price >= avg)//高于或等于平均价格的图书价格提高 10%
//         {
//             L.elem[i].price *= 1.1;
//         } else if (L.elem[i].price < avg)//低于平均价格的图书价格提高20%
//         {
//             L.elem[i].price *= 1.2;
//         }
//     }
//     printf("%.2f\n", avg);//输出平均价格 
//     return OK;
// }

// //顺序表找最贵的书
// ElemType SqList_Max(SqList &amp;L) {
//     int n;//图书数目 
//     printf("请输入数据：\n");
//     scanf("%d", &amp;n);//输入图书数目 
//     InitList_SqList(L); //初始化线性表 	
//     L.length = n;//给线性表中的图书数目赋值 
//     if (n < 1 || n > LIST_MAXSIZE)
//         return OK;
//     int i = 1;
//     while (i <= n) {
//         scanf("%s %s %f", L.elem[i].no, L.elem[i].name, &amp;L.elem[i].price);//输入图书信息表 
//         i++;
//     }
//     int maxprice[LIST_MAXSIZE];//最贵图书在线性表中的编号 
//     int len = 0, max = 0;//len:最贵图书的数目  max：最贵图书价格
//     printf("\n");
//     printf("--------------------------------------------\n");
//     printf("\n");
//     printf("输出的结果为：\n");
//     for (int i = 1; i <= n; i++)//查找最贵图书并记录其在线性表中的编号 
//     {
//         if (L.elem[i].price > max)//找到更贵的图书 
//         {
//             len = 1;//更贵图书的数目记为1 
//             maxprice[len] = i;//记录更贵图书在线性表中的编号 
//             max = L.elem[i].price;//修改最贵图书价格 
//         } else if (max == L.elem[i].price)//找到下一本最贵图书
//         {
//             len++;//最贵图书的数目加1 
//             maxprice[len] = i;//记录更贵图书在线性表中的编号			
//         }
//     }
//     printf("%d\n", len);//输出最贵图书的数目
//     for (int i = 1; i <= len; i++)//输出最贵图书的信息 
//     {
//         int j;
//         j = maxprice[i];
//         printf("%s %s %.2f\n", L.elem[j].no, L.elem[j].name, L.elem[j].price);//根据编号输出最贵图书的信息 
//     }
//     return OK;
//     //也可以采用顺序表删除
// }



// //顺序表新书入库
// ElemType SqList_Enter(SqList &amp;L) {
//     int n, j, i;
//     Book in_b;
//     printf("请输入数据\n");
//     scanf("%d", &amp;n);
//     L.length = n;
//     for (j = 1; j <= n + 1; j++) {
//         scanf("%s %s %f", &amp;L.elem[j].no, &amp;L.elem[j].name, &amp;L.elem[j].price);//输入图书信息表 
//         if (strcmp(L.elem[i].no, "0") == 0 & amp;&amp; strcmp(L.elem[i].name, "0") == 0 & amp;&amp; L.elem[i].price == 0) {
//             break;
//         }
//     }
//     /*for (j = 1; j <= n; j++) {
//         scanf("%s %s %f", L.elem[j].no, L.elem[j].name, &amp;L.elem[j].price);

//     }*/

//     scanf("%d", &amp;i);
//     if ((i < 1) || (i > L.length + 1) || (i == LIST_MAXSIZE)) {
//         printf("\n");
//         printf("--------------------------------------------\n");
//         printf("\n");
//         printf("抱歉，入库位置非法!\n");//i值不合法
//         return ERROR;
//     } else {
//         scanf("%s %s %f", &amp;in_b.no, &amp;in_b.name, &amp;in_b.price);
//         printf("\n");
//         printf("--------------------------------------------\n");
//         printf("\n");
//         printf("输出的结果为：\n");
//         for (j = L.length; j >= i; j--) {
//             L.elem[j + 1] = L.elem[j];//插入位置及之后的元素右移
//         }
//         L.elem[i] = in_b;//将新元素e放入第i个位置
//         ++L.length;//表长加1
//         printf("%d\n", L.length);
//         for (j = 1; j <= L.length; j++) {
//             printf("%s %s %.2f\n", L.elem[j].no, L.elem[j].name, L.elem[j].price);//输出图书信息表 		
//         }

//         return OK;
//     }
// }

// //顺序表旧书出库
// ElemType SqList_Output(SqList &amp;L) {
//     int n, j, i;
//     printf("请输入数据\n");
//     scanf("%d", &amp;n);

//     L.length = n;
//     for (j = 1; j <= n + 1; j++) {
//         scanf("%s %s %f", &amp;L.elem[j].no, &amp;L.elem[j].name, &amp;L.elem[j].price);//输入图书信息表 
//         if (strcmp(L.elem[i].no, "0") == 0 & amp;&amp; strcmp(L.elem[i].name, "0") == 0 & amp;&amp; L.elem[i].price == 0) {
//             break;
//         }
//     }
//     scanf("%d", &amp;i);
//     if ((i < 1) || (i > L.length)) {
//         printf("\n");
//         printf("--------------------------------------------\n");
//         printf("\n");
//         printf("抱歉，出库位置非法!\n");//i值不合法
//         return ERROR;
//     } else {
//         printf("\n");
//         printf("--------------------------------------------\n");
//         printf("\n");
//         printf("输出的结果为：\n");
//         for (j = i + 1; j <= n; j++) {
//             L.elem[j - 1] = L.elem[j];//删除位置及之后的元素左移
//         }
//         --L.length;//表长减1
//         printf("%d\n", L.length);
//         for (j = 1; j <= L.length; j++) {
//             printf("%s %s %.2f\n", L.elem[j].no, L.elem[j].name, L.elem[j].price);//输出图书信息表 		
//         }
//         return OK;
//     }
// }

// int main() {
//     int a;
//     printf("问题如下：\n");
//     printf("1、基于顺序表存储结构的图书信息表的创建和输出？\n");
//     printf("2、基于顺序表存储结构的图书信息表的修改？\n");
//     printf("3、基于顺序表存储结构的图书信息表的最贵图书的查找？\n");
//     printf("4、基于顺序表存储结构的图书信息表的新图书的入库？\n");
//     printf("5、基于顺序表存储结构的图书信息表的旧图书的出库？\n");
//     printf("请输入你想查看的问题（输入数字）:\n");
//     scanf("%d", &amp;a);
//     if (a > 0 & amp;&amp; a < 11) {//顺序表
//         switch (a) {
//         case 1: {//顺序表的创建和输出
//             SqList L;
//             InitList_SqList(L);
//             printf("请输入数据：\n");
//             int i;
//             i = ListInsert(L);
//             printf("\n");
//             printf("--------------------------------------------\n");
//             printf("\n");
//             printf("输出的结果为：\n");
//             printf("%d\n", i);
//             ListOutput(L);
//             break;
//         }

//         case 2: {//顺序表修改价格
//             SqList L;
//             InitList_SqList(L);
//             printf("请输入数据：\n");
//             ListInsert(L);
//             printf("\n");
//             printf("--------------------------------------------\n");
//             printf("\n");
//             printf("输出的结果为：\n");
//             SqList_Price(L);
//             ListOutput(L);
//             break;
//         }

//         case 3: {//找出最贵的书
//             SqList L;
//             SqList_Max(L);
//             break;
//         }

//         case 4: {//新图书的入库
//             SqList L;
//             InitList_SqList(L);
//             SqList_Enter(L);
//             break;
//         }
//         case 5: {//旧书出库
//             SqList L;
//             InitList_SqList(L);
//             SqList_Output(L);
//             break;
//         }

//         }
//     }



//     system("pause");
//     return 0;
// }