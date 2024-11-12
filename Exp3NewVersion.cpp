#include <iostream>
#include <iomanip>
#include <string>
#include <vector>

using namespace std;

int kmp(string s, string t, int pos, int next[]);
void getNext(string t, int next[]);

typedef struct virusAndPerson {
    string virus;
    string person;
} vap;

typedef vector<vap> vec_vap;

int main() {
    int num;
    string virus, person;
    vec_vap v;
    while (cin >> virus >> person && virus != "0" && person != "0") {
        vap a;
        a.virus = virus;
        a.person = person;
        v.push_back(a);
    }

    for (auto & i : v) {
        string vir = i.virus;
        bool flag = false;
        int virLen = i.virus.length();
        i.virus += i.virus;
        string temp;
        for (int j = 0; j < virLen; j++) {
            temp = i.virus.substr(j, virLen);
            int* next = new int[temp.length() + 1];
            getNext(temp, next);
            flag = kmp(i.person, temp, 0, next) != -1;
            delete[] next;
            if (flag) {
                break;
            }
        }
        if (flag) {
            cout << left << "Yes" << endl;
        }
        else {
            cout << left << "No" << endl;
        }
    }
    return 0;
}

int kmp(string s, string t, int pos, int next[]) {
    int i = pos;
    int j = 0;
    const int sl = s.length();
    const int tl = t.length();
    while (i < sl && j < tl) {
        if (j == -1 || s[i] == t[j]) {
            i++;
            j++;
        }
        else {
            j = next[j];
        }
    }
    if (j == tl) {
        return i - j;
    }
    else {
        return -1;
    }
}

void getNext(string t, int next[]) {
    int i = 0;
    int j = -1;
    next[0] = -1;
    while (i < t.length() - 1) {
        if (j == -1 || t[i] == t[j]) {
            i++;
            j++;
            next[i] = j;
        }
        else {
            j = next[j];
        }
    }
}
