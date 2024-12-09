#include<stdio.h>
#include<stdbool.h>
#include <stdlib.h>

#define MVNum 100
#define MaxInt 32767

typedef struct {
    int Vexnum;//顶点数
    int arcnum; //边数
    char vex[MVNum]; //顶点表
    int arcs[MVNum][MVNum];//邻接矩阵，权重为整数
}AMGraph;

void print(AMGraph G, int Path[]) {
    char s;
    int i = 1;
    char stack[MVNum] = { 0 };
    int length = 0;
    // while (i<G.Vexnum) {
    //     s = G.vex[i];
    //     if (Path[i] != -1)
    //     printf("%c ", s);
    //     i++;
    // }
    i = G.Vexnum - 1;
    while (i != 0) {
        // printf("%c ", G.vex[i]);
        stack[length++] = G.vex[i];
        i = Path[i];
    }
    stack[length++] = G.vex[0];
    for (int i = length - 1; i >= 0; i--) {
        printf("%c ", stack[i]);
    }
}

void ShortestPath_DIJ(AMGraph G,int v0) {
    int v = 0;
    bool S[MVNum];
    int D[MVNum];
    int Path[MVNum];
    for (v = 0; v < G.Vexnum; v++) {
        S[v] = false;
        D[v] = G.arcs[v0][v];
        if (D[v] < MaxInt) {
            Path[v] = v0;//如果v0和v之间有弧，则将v的前驱置为v0
        }
        else {
            Path[v] = -1;
        }
    }
    S[v0] = true;//将v0加入S
    D[v0] = 0;//源点到源点的距离为0
    int i=0;
    int w=0;
    for (i = 1; i < G.Vexnum; i++) {//对其余n-1个顶点，依次进行计算
        int min = MaxInt;
        for (w = 0; w < G.Vexnum; w++) {
            if (!S[w] && D[w] < min) {//选择一条当前最短路径，终点为v
                v = w;
                min = D[w];
            }
        }
        S[v] = true;//将v加入S
        for (w = 0; w < G.Vexnum; w++) {//更新从v0出发到集合v-S上所有顶点的最短路径长度
            if (!S[w] && (D[v] + G.arcs[v][w] < D[w])) {
                D[w] = D[v] + G.arcs[v][w];//更新D[w]
                Path[w] = v;//更改w的前驱为v
            }
        }
    }
    printf("%d\n", D[w - 1]);
    print(G, Path);
}

int LocateVex(AMGraph *G,char v1) {
    int i = 0;
    for (i = 0; i < G->Vexnum; i++) {
        if (v1 == G->vex[i]) {
            break;
        }
    }
    return i;
}

void  Create_UDN(AMGraph *G){
    scanf("%d %d", &G->Vexnum, &G->arcnum);
    if (G->arcnum == G->Vexnum && G->arcnum == 0) {
        exit(0);
    }
    int i = 0;
    int j = 0;
    int k = 0;
    getchar();
    for (i = 0; i < G->Vexnum; i++) {//各城市信息
        scanf("%c",&G->vex[i]);
        getchar();
    }
    for (i = 0; i < G->Vexnum; i++) {//初始化邻接矩阵，边的权值均置为极大值
        for (j = 0; j < G->Vexnum; j++) {
            G->arcs[i][j] = MaxInt;
        }
    }
    char v1;
    char v2;
    int w;
    // getchar();
    for (k = 0; k < G->arcnum; k++) {//构造邻接矩阵
        scanf("%c %c %d", &v1, &v2, &w);
        getchar();
        i = LocateVex(G, v1);
        j = LocateVex(G, v2);
        G->arcs[i][j] = w;
        // G->arcs[j][i] = w;
    }
}

int main()
{
    AMGraph G;
    char m;
    char n;
    while (1) {
        Create_UDN(&G);//创建无向网
        scanf("%c %c", &m, &n);//输入起点和终点
        if (m == '0' && n == '0') {
            break;
        }
        int i = 0;
        ShortestPath_DIJ(G,0);//用迪杰斯特拉算法求有向网的v0顶点到其余顶点的最短路径
    }
    return 0;
}

/*
3 3
A B C
A B 1
B C 1
C A 3
A C
6 8
A B C D E F
A F 100
A E 30
A C 10
B C 5
C D 50
D E 20
E F 60
D F 10
A F
0 0
 */