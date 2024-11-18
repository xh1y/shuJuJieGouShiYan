#include<stdio.h>
#include<string.h>
#include<ctype.h>
int num[26] = {0}; //记录不同字符个数
typedef struct {
    char str[100];
} S;

typedef enum {
    false, true
} bool;

typedef struct {
    int weight;
    int parent;
    int leftchild;
    int rightchild;
} N;

void count(char str[]) {
    int i = 0; //记录每个字符坐标
    for (i = 0; i < strlen(str); i++) {
        if (islower(str[i])) {
            //判断是否输入是小写字母
            num[str[i] - 'a']++;
        }
    }
    for (i = 0; i < 26; i++) {
        if (num[i]) {
            printf("%c:%d ", i + 97, num[i]);
        }
    }
}

int opt(N data[]) {
    int i = 0;
    int min = __INT_MAX__;
    int potmin;
    bool find = false;
    for (i = 0; data[i].weight != 0; i++) {
        if (data[i].parent == -1) {
            min = data[i].weight;
            potmin = i;
            find = true;
            break;
        }
    }
    for (i = 0; data[i].weight != 0; i++) {
        if (data[i].parent == -1 && min >= data[i].weight) {
            min = data[i].weight;
            potmin = i;
            find = true;
        }
    }
    data[potmin].parent = find ? i : -1;
    return find ? min : -1;
}

N data[52];

void final_state(char str[]) {
    int i = 0;
    int j = 0;
    for (i = 0; i < 52; i++) {
        data[i].weight = 0;
        data[i].parent = -1;
        data[i].leftchild = -1;
        data[i].rightchild = -1;
    }
    for (i = 0; i < 26; i++) {
        if (num[i]) {
            data[j++].weight = num[i];
        }
    }
    int total = 0;
    for (i = 0; data[i].weight != 0; i++) {
        total += data[i].weight;
    }
    while (data[i].weight != total) {
        int a = opt(data);
        int b = opt(data);
        if (b == -1) {
            break;
        }
        data[i].weight = a + b;
        for (int m = 0; m < i; m++) {
            if (a == data[m].weight && data[m].parent == i && data[i].leftchild == -1) {
                data[i].leftchild = m;
            }
            if (b == data[m].weight && data[m].parent == i && data[i].leftchild != m) {
                data[i].rightchild = m;
            }
        }
        i++;
    }
    for (i = 0; data[i].weight != 0; i++) {
        printf("%d %d %d %d %d\n", i,
               data[i].weight,
               data[i].parent ,
               data[i].leftchild ,
               data[i].rightchild );
    }
}

void getCode(int current_position, char a[][26]) {
    char child[100] = {0};
    strcpy(child, a[current_position]);
    if (data[current_position].leftchild != -1) {
        strcat(child, "0");
        strcat(a[data[current_position].leftchild], child);
        getCode(data[current_position].leftchild, a);
    }
    for (int i = 0; i < 100; i++) {
        child[i] = 0;
    }
    strcpy(child, a[current_position]);
    if (data[current_position].rightchild != -1) {
        strcat(child, "1");
        strcat(a[data[current_position].rightchild], child);
        getCode(data[current_position].rightchild, a);
    }
}

void code(char str[]) {
    int i = 0;
    char a[100][26] = {0};
    for (i = 0; data[i].weight != 0; i++) {
        ;
    }
    getCode(i - 1, a);
    int j = 0;
    for (i = 0; i < 26; i++) {
        if (num[i]) {
            printf("%c:%s ", i + 97, a[j++]);
        }
    }
    printf("\n");
    char n = str[0];
    j = 0;
    for (i = 0; i < strlen(str); i++) {
        if (n != str[i]) {
            n = str[i];
            j++;
        }
        printf("%s", a[j]);
    }
}

int main() {
    S a[100];
    int i;
    for (i = 0; ; i++) {
        scanf("%s", a[i].str);
        if (strcmp(a[i].str, "0") == 0) {
            break;
        }
    }
    for (int j = 0; j < i; j++) {
        count(a[j].str);
        printf("\n");
        final_state(a[j].str);
        printf("\n");
        code(a[j].str);
        printf("\n");
        printf("%s\n", a[j].str);
        for (int x = 0; x < 26; x++) {
            num[x] = 0;
        }
    }
    return 0;
}