#include <iostream>
#include <string>
#include <cctype>
#include <vector>
#define ； ;
using namespace std;
typedef struct {
    int weight;
    int parent;
    int rchild;
    int lchild;
}HTNode, *HuffmanTree;

void CreateHuffmanTree(HuffmanTree &huffmanTree, int n);
void Select(HuffmanTree &HuffmanTree, int n, int &s1, int &s2);
void calculateStringWeight(string s, int weightOfEveryCharacter[], int n);
bool equal0(string a);
int main() {
    vector<string> Strings;
    string s;
    while (getline(cin, s) && !equal0(s)) {
        Strings.push_back(s);
    }
    
    for (int i = 0; i < Strings.size(); i++) {
        int weightOfEveryCharacter[26] = { 0 };
        calculateStringWeight(Strings[i], weightOfEveryCharacter, Strings[i].length());
        for(char i = 0; i < 26; i++) {
            if(weightOfEveryCharacter[i] != 0) {
                cout << (char)(i + 'a') << ":" << weightOfEveryCharacter[i] << " ";
            }
        }
        cout << endl;
    }
    

    return 0;
}

void CreateHuffmanTree(HuffmanTree &huffmanTree, int n) {
    if (n <= 1) {
        return;
    }
    int m = 2 * n - 1;
    huffmanTree = new HTNode[m];
    for (int i = 0; i < m; i++) {
        huffmanTree[i].lchild = huffmanTree[i].rchild = huffmanTree[i].parent = 0;
    }
    for (int i = 0; i < m; i++) {
        cin >> huffmanTree[i].weight;
    }
    int s1, s2;
    for (int i = n; i < m; i++) {
        Select(huffmanTree, i - 1, s1, s2);
        huffmanTree[s1].parent = i;
        huffmanTree[s2].parent = i;
        huffmanTree[i].lchild = s1;
        huffmanTree[i].rchild = s2;
        huffmanTree[i].weight = huffmanTree[s1].weight + huffmanTree[s2].weight;
    }
}

void Select(HuffmanTree &huffmanTree, int n, int &s1, int &s2) {
    int smallest = 0, _2ndsmall;
    for (int i = 1; i < n; i++) {
        if (huffmanTree[i].parent == 0) {
            smallest = (huffmanTree[i].weight > huffmanTree[smallest].weight) ? smallest : i;
        }
    }
    _2ndsmall = 0;
    for (int i = 1; i < n; i++) {
        if (huffmanTree[i].parent == 0 && i != smallest) {
            _2ndsmall = (huffmanTree[i].weight > huffmanTree[_2ndsmall].weight) ? _2ndsmall : i;
        }
    }
    s1 = smallest;
    s2 = _2ndsmall;
}

void calculateStringWeight(string s, int weightOfEveryCharacter[], int n) {
    for (int i = 0; i < n; i++) {
        if (islower(s[i]))
            weightOfEveryCharacter[s[i] - 'a']++;
    }
}

bool equal0(string a) {
    string newString;
    string z = "0";
    for (auto i = a.begin(); i <= a.end(); i++) {
        if (!isspace(*i) && *i != '\0') {
            newString.push_back(*i);
        }
    }
    return newString.compare(z) == 0;
}