#include <iostream>
#include <fstream>
#include <iomanip>
#include <string>

using namespace std;

int kmp(string s, string t, int pos, int next[]);
void getNext(string t, int next[]);

int main() {
    ifstream inFile("input.txt");
    ofstream outFile("output.txt");
    int num;
    string virus, person;
    inFile >> num;
    outFile << std::left << setfill(' ') << setw(10) << "Virus" << setw(20) << "Person" << '\t' << "Effected" << endl;
    while (num--) {
        inFile >> virus;
        inFile >> person;

        string vir = virus;
        bool flag = false;
        int virLen = virus.length();
        virus += virus;
        string temp;
        for (int i = 0; i < virLen; i++) {
            temp = virus.substr(i, virLen);
            int *next = new int[temp.length() + 1];
            getNext(temp, next);
            flag = kmp(person, temp, 0, next) != -1;
            delete[] next;
            if (flag) {
                break;
            }
        }
            if (flag) {
                outFile << left << setfill(' ') << setw(10) << vir << setw(20) << person << "\t" << "Yes" << endl;
            } else {
                outFile << left << setfill(' ') << setw(10) << vir << setw(20) << person << "\t" << "No" << endl;
            }
    }
    return 0;
}

int kmp(string s, string t, int pos, int next[]) {
    int i = pos;
    int j = 0;
    int sl = s.length();
    int tl = t.length();
    while (i < sl && j < tl) {
        if (j == -1 || s[i] == t[j]) {
            i++;
            j++;
        } else {
            j = next[j];
        }
    }
    if (j == tl) {
        return i - j; // Return the starting position of the match
    } else {
        return -1; // Return -1 if not found
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
        } else {
            j = next[j];
        }
    }
}