#include <iostream>
#include <fstream>
#include <string>
#include <iomanip>
// using namespace std;
using std::cin, std::cout, std::endl, std::string, std::ifstream, std::ofstream, std::setw, std::setfill;

int kmp(string s, string t, int pos, int next[]);
void getNext(string t, int next[]);
void virus();
void kmpTest() {
    string s = "aabccdxdxbxa";
    string t = "abc";
    int *next = new int[t.length() + 1];
    getNext(t, next);
    cout << kmp(s, t, 0, next);
}

int main() {
    // virus();
    kmpTest();
    return 0;
}

int kmp(string s, string t, int pos, int next[]) {
    int i = pos;
    int j = 0;
    while (i < s.length() && j < t.length()) {
        if (j == -1 || s[i] == t[j]) {
            i++;
            j++;
        } else {
            j = next[j];
        }
    }
    if (j >= t.length()) {
        return i - j + pos; // Return the starting position of the match
    } else {
        return -1; // Return -1 if not found
    }
}

void getNext(string t, int next[]) {
    int i = 0;
    next[0] = -1;
    int j = -1;
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

void virus() {
    ifstream inFile("input.txt");
    ofstream outFile("output.txt");
    int num;
    string virus, person;
    inFile >> num;
    while(num--) {
        inFile >> virus;
        inFile >> person;

        string vir = virus;
        bool flag = false;
        int virLen = virus.length();   
        // for(int i = virLen, j = 0; j < virLen; j++) {
            virus += virus;  
        // }
        string temp;
        for(int i = 0; i < virLen; i++) {
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
            outFile << std::left << setfill(' ') << setw(10) << vir << setw(10) << person << "\t" << "Yes" << endl;
        } else {
            outFile << std::left << setfill(' ') << setw(10) << vir << setw(10) << person << "\t" << "No" << endl;
        }

    }
}

