#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
int j = 0;

// int success[100] = {0};

typedef struct {
    char virus[100];
    char people[100];
} S;

char* substr(const char a_[], const int n) {
    char* a = (char*)calloc(100, sizeof(char));
    int i = j;
    int k = 0;
    for (k = 0; k < n; k++) {
        a[k] = a_[i];
        i++;
    }
    a[n] = '\0';
    return a;
}

char* reverse(char virus[]) {
    char a_[200];
    strcpy(a_, virus);
    // char b_[100];
    char* b_ = (char*)calloc(100, sizeof(char));
    strcat(a_, a_); //将病毒DNA延长至两倍
    j++;
    char* p = substr(a_, strlen(virus));
    return p;
}

bool compare(char people[], char virus[]) {
    int p = 0;
    int q = 0;
    for (int m = 0; m < strlen(people);) {
        p = m;
        for (q = 0; q < strlen(virus);) {
            if (people[p] == virus[q]) {
                p++;
                q++;
            } else {
                m++;
                q = 0;
                break;
            }
        }
        if (q == strlen(virus)) {
            return true;
        }
    }
    return false;
}

void Virus_detection(S a[], int i) {
    int num = i; //共有多少组数据
    int total = i;
    i = 0;
    bool success[100];
    while (num--) //依次检测每对病毒 DNA 和人的 DNA 是否匹配
    {
        success[i] = compare(a[i].people, a[i].virus);
        if (success[i]) {
            i++;
        } else {
            while (!success[i]) {
                char reverse_virus[100];
                char* p = reverse(a[i].virus);
                strcpy(reverse_virus, p);
                success[i] = compare(a[i].people, reverse_virus);
                if (success[i]) {
                    i++;
                    j = 0;
                    break;
                }
                if (j == strlen(a[i].virus)) {
                    j = 0;
                    i++;
                    break;
                }
                free(p);
            }
        }
    }

    for (int m = 0; m < total; m++) {
        printf("%s", success[m] == 1 ? "YES\n" : "NO\n");
    }
}

int main() {
    S a[100];
    // = {
    // {"baa", "bbaabbba"},
    // {"baa", "aaabbbba"},
    // {"aabb", "abceaabb"},
    // {"aabb", "abaabcea"},
    // {"abcd", "cdabbbab"},
    // {"abcd", "cabbbbab"},
    // {"abcde", "bcdedbda"},
    // {"acc", "bdedbcda"},
    // {"cde", "cdcdcdec"},
    // {"cced", "cdccdcce"},
    // {"bcd", "aabccdxdxbxa"},
    // {"abb", "bbbbbbbbabbbbbb"},
    // {"abbab", "abbabaab"},
    // {"baa", "cacdveabacsd"},
    // {"abe", "def"},
    // {"0", "0"}
    // };
    int i;
    for (i = 0; ; i++) {
        scanf("%s %s", a[i].virus, a[i].people);
        if (strcmp(a[i].virus, "0") == 0 && strcmp(a[i].people, "0") == 0) {
            break;
        }
    }
    Virus_detection(a, i);
    return 0;
}
