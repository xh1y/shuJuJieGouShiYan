#include <iostream>
#include <string>
#include <cctype>
#include <vector>
using namespace std;

typedef struct WordAndWeight {
    char data;
    int weight;
    string codes;
} WordAndWeight;

typedef struct {
    WordAndWeight wordAndWeight;
    int parent;
    int rchild;
    int lchild;
} HTNode, *HuffmanTree;


typedef vector<WordAndWeight> vec_waw;
void CreateHuffmanTree(HuffmanTree& huffmanTree, int n, vec_waw waw);
void Select(const HuffmanTree& HuffmanTree, int n, int& s1, int& s2);
void calculateStringWeight(string s, int weightOfEveryCharacter[], int n);
void huffmanChangeToCode(HuffmanTree huffmanTree, int nowRoot);
bool equal0(string a);
void huffmanDecode(string code, HuffmanTree huffmanTree, int size);
bool getValue(string code, HuffmanTree huffmanTree, int size);

int main() {
    vector<string> Strings;
    string s;
    while (getline(cin, s) && !equal0(s)) {
        Strings.push_back(s);
    }

    for (auto & String : Strings) {
        vec_waw waw;
        int* weightOfEveryCharacter = new int[26];
        for (int i = 0; i < 26; i++) {
            weightOfEveryCharacter[i] = 0;
        }

        calculateStringWeight(String, weightOfEveryCharacter, String.length());
        for (char i = 0; i < 26; i++) {
            if (weightOfEveryCharacter[i] != 0) {
                cout << (char)(i + 'a') << ":" << weightOfEveryCharacter[i] << " ";
                WordAndWeight p = {(char)(i + 'a'), weightOfEveryCharacter[i]};
                waw.push_back(p);
            }
        }
        cout << endl;
        HuffmanTree huffmanTree = new HTNode[waw.size() * 2];
        CreateHuffmanTree(huffmanTree, waw.size(), waw);
        for (int i = 1; i <= 2 * waw.size() - 1; i++) {
            cout << i << " " << huffmanTree[i].wordAndWeight.weight << " " << huffmanTree[i].parent << " " <<
                huffmanTree[i].lchild << " " << huffmanTree[i].rchild << " " << huffmanTree[i].wordAndWeight.data <<
                endl;
        }
        huffmanChangeToCode(huffmanTree, 2 * waw.size() - 1);
        for (int i = 1; i <= waw.size(); i++) {
            cout << huffmanTree[i].wordAndWeight.data << ":" << huffmanTree[i].wordAndWeight.codes << " ";
        }
        string newS = "";
        int size = waw.size();
        waw.clear();
        for (int i = 0; i <= size; i++) {
            waw.push_back(huffmanTree[i].wordAndWeight);
        }
        for (int i = 0; i < String.length(); i++) {
            for (int l = 0; l < waw.size(); l++) {
                if (String[i] == waw[l].data) {
                    newS += waw[l].codes;
                }
            }
        }

        cout << endl << newS << endl;
        huffmanDecode(newS, huffmanTree, size * 2 - 1);
        cout << endl;
        delete[] huffmanTree;
        delete[] weightOfEveryCharacter;
    }
    return 0;
}

void CreateHuffmanTree(HuffmanTree& huffmanTree, int n, vec_waw waw) {
    if (n <= 1) {
        return;
    }
    int m = 2 * n - 1;
    for (int i = 1; i <= m; i++) {
        huffmanTree[i].lchild = huffmanTree[i].rchild = huffmanTree[i].parent = 0;
    }
    for (int i = 1; i <= n; i++) {
        huffmanTree[i].wordAndWeight.weight = waw[i - 1].weight;
        huffmanTree[i].wordAndWeight.data = waw[i - 1].data;
    }
    int s1, s2;
    for (int i = n + 1; i <= m; i++) {
        Select(huffmanTree, i - 1, s1, s2);
        huffmanTree[s1].parent = i;
        huffmanTree[s2].parent = i;
        huffmanTree[i].lchild = s1;
        huffmanTree[i].rchild = s2;
        huffmanTree[i].wordAndWeight.weight = huffmanTree[s1].wordAndWeight.weight + huffmanTree[s2].wordAndWeight.
            weight;
    }
}

void Select(const HuffmanTree& huffmanTree, int n, int& s1, int& s2) {
    int smallest = 1;
    for (int i = 1; i <= n; ++i) {
        if (huffmanTree[i].parent == 0) {
            smallest = i;
            break;
        }
    }
    for (int i = 2; i <= n; i++) {
        if (huffmanTree[i].parent == 0) {
            smallest = (huffmanTree[i].wordAndWeight.weight > huffmanTree[smallest].wordAndWeight.weight)
                           ? smallest
                           : i;
        }
    }
    int _secondSmall = -1;
    for (int i = 1; i <= n; ++i) {
        if (huffmanTree[i].parent == 0 && i != smallest) {
            _secondSmall = i;
            break;
        }
    }
    for (int i = 2; i <= n; ++i) {
        if (huffmanTree[i].parent == 0 && i != smallest) {
            _secondSmall = (huffmanTree[i].wordAndWeight.weight > huffmanTree[_secondSmall].wordAndWeight.weight)
                            ? _secondSmall
                            : i;
        }
    }
    if (huffmanTree[_secondSmall].wordAndWeight.weight == huffmanTree[smallest].wordAndWeight.weight) {
        if (smallest > _secondSmall) {
            int temp = _secondSmall;
            _secondSmall = smallest;
            smallest = temp;
        }
    }
    s1 = smallest;
    s2 = _secondSmall;
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
    for (string::iterator i = a.begin(); i <= a.end(); i++) {
        if (!isspace(*i) && *i != '\0') {
            newString.push_back(*i);
        }
    }
    return newString == z;
}

void HuffmanDeCode(HuffmanTree HT, char s[], char a[], int n) {
    int i = 0;
    int f = 2 * n - 1;
    while (s[i] != '\0') {
        if (s[i] == '0')
            f = HT[f].lchild;
        else
            f = HT[f].rchild;
        if (f <= n) {
            printf("%c", a[f]);
            f = 2 * n - 1;
        }
        i++;
    }
}

void huffmanChangeToCode(HuffmanTree huffmanTree, int nowRoot) {
    string add = huffmanTree[nowRoot].wordAndWeight.codes;
    if (huffmanTree[nowRoot].lchild != 0) {
        add += "0";
        huffmanTree[huffmanTree[nowRoot].lchild].wordAndWeight.codes = add;
        huffmanChangeToCode(huffmanTree, huffmanTree[nowRoot].lchild);
        add.pop_back();
    }
    if (huffmanTree[nowRoot].rchild != 0) {
        add += '1';
        huffmanTree[huffmanTree[nowRoot].rchild].wordAndWeight.codes = add;
        huffmanChangeToCode(huffmanTree, huffmanTree[nowRoot].rchild);
        add.pop_back();
    }
}


void huffmanDecode(string code, HuffmanTree huffmanTree, int size) {
    int i = 1;
    int startPlace = 0;
    while (i < code.length()) {
        while (!getValue(code.substr(startPlace, i - startPlace), huffmanTree, size)) {
            i++;
        }
        startPlace = i;
        i = startPlace + 1;
    }
}

bool getValue(string code, HuffmanTree huffmanTree, int size) {
    HuffmanTree s = new HTNode;
    s = &huffmanTree[size];
    for (int i = 0; i < code.length(); i++) {
        if (code[i] == '0') {
            s = &huffmanTree[s->lchild];
        } else {
            s = &huffmanTree[s->rchild];
        }
    }
    if (islower(s->wordAndWeight.data)) {
        cout << s->wordAndWeight.data;
        delete s;

        return true;
    }
    delete s;
    return false;
}