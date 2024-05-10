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
    // char data;
    // int weight;
    WordAndWeight wordAndWeight;
    int parent;
    int rchild;
    int lchild;
    // string decode;
}HTNode, *HuffmanTree;


typedef vector<WordAndWeight> vec_waw;
// string subreplace(string resource_str, string sub_str, string new_str);
void CreateHuffmanTree(HuffmanTree &huffmanTree, int n, vec_waw waw);
void Select(HuffmanTree &HuffmanTree, int n, int &s1, int &s2);
void calculateStringWeight(string s, int weightOfEveryCharacter[], int n);
void huffmanChangeToCode(HuffmanTree huffmanTree, int nowRoot);
// void huffmanDecode(string code, vec_waw waw);
bool equal0(string a);
void huffmanDecode(string code, HuffmanTree huffmanTree, int size);
bool getValue(string code, HuffmanTree huffmanTree, int size);
int main() {
    vector<string> Strings;
    string s;
    while (getline(cin, s) && !equal0(s)) {
        Strings.push_back(s);
    }

    for (int j = 0; j < Strings.size(); j++) {
        vector<WordAndWeight> waw;
        int *weightOfEveryCharacter = new int[26];
        for (int i = 0; i < 26; i++) {
            weightOfEveryCharacter[i] = 0;
        }

        calculateStringWeight(Strings[j], weightOfEveryCharacter, Strings[j].length());
        for (char i = 0; i < 26; i++) {
            if (weightOfEveryCharacter[i] != 0) {
                cout << (char) (i + 'a') << ":" << weightOfEveryCharacter[i] << " ";
                WordAndWeight p = { (char) ((char) i + 'a'), weightOfEveryCharacter[i] };
                waw.push_back(p);
            }
        }
        cout << endl;
        HuffmanTree huffmanTree = new HTNode[waw.size() * 2];
        CreateHuffmanTree(huffmanTree, waw.size(), waw);
        for (int i = 1; i <= 2 * waw.size() - 1; i++) {
            cout << i << " " << huffmanTree[i].wordAndWeight.weight << " " << huffmanTree[i].parent << " " << huffmanTree[i].lchild << " " << huffmanTree[i].rchild << " " << huffmanTree[i].wordAndWeight.data << endl;
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
        for (int i = 0; i < Strings[j].length(); i++) {
            for (int l = 0; l < waw.size(); l++) {
                if (Strings[j][i] == waw[l].data) {
                    newS += waw[l].codes;
                }
            }
        }

        cout << endl << newS << endl;
        huffmanDecode(newS,  huffmanTree, size * 2 - 1);
        cout << endl;
        delete[] huffmanTree;
        delete[] weightOfEveryCharacter;
    }
    return 0;
}

void CreateHuffmanTree(HuffmanTree &huffmanTree, int n, vec_waw waw) {
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
        huffmanTree[i].wordAndWeight.weight = huffmanTree[s1].wordAndWeight.weight + huffmanTree[s2].wordAndWeight.weight;
    }
}

void Select(HuffmanTree &huffmanTree, int n, int &s1, int &s2) {
    int smallest = 1, _2ndsmall;
    for (int i = 1; i <= n; ++i) {
        if (huffmanTree[i].parent == 0) {
            smallest = i;
            break;
        }
    }
    for (int i = 2; i <= n; i++) {
        if (huffmanTree[i].parent == 0) {
            smallest = (huffmanTree[i].wordAndWeight.weight > huffmanTree[smallest].wordAndWeight.weight) ? smallest : i;
        }
    }
    _2ndsmall = -1;
    for (int i = 1; i <= n; ++i) {
        if (huffmanTree[i].parent == 0 && i != smallest) {
            _2ndsmall = i;
            break;
        }
    }
    for (int i = 2; i <= n; ++i) {
        if (huffmanTree[i].parent == 0 && i != smallest) {
            _2ndsmall = (huffmanTree[i].wordAndWeight.weight > huffmanTree[_2ndsmall].wordAndWeight.weight) ? _2ndsmall : i;
        }
    }
    if (huffmanTree[_2ndsmall].wordAndWeight.weight == huffmanTree[smallest].wordAndWeight.weight) {
        if(smallest > _2ndsmall) {
            int temp = _2ndsmall;
            _2ndsmall = smallest;
            smallest = temp;
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



void huffmanDecode(string code,  HuffmanTree huffmanTree, int size) {
    // string before = code;
    // vec_waw copy = waw;
    // for (int i = 1; i < waw.size() - 1; i++) {
    //     for (int j = i + 1; j < waw.size(); j++) {
    //         if ((waw[i].codes.compare(waw[j].codes) > 0)) {
    //             WordAndWeight temp;
    //             temp = waw[i];
    //             waw[i] = waw[j];
    //             waw[j] = temp;
    //         }
    //     }
    // }

    // for(int i = 0; i < code.length(); i++) {
    //     for() 
    // }
    // cout << before << endl;
    int i = 1;
    int startPlace = 0;
    while (i < code.length()) {
        // cout << waw[i].codes << ": " << waw[i].data << endl;
        while (!getValue(code.substr(startPlace, i - startPlace), huffmanTree, size)) {
            i++;
        }
        startPlace = i;
        i = startPlace + 1;
    }
}

bool getValue(string code, HuffmanTree huffmanTree, int size) {
    // const auto root = huffmanTree[size];
    // HTNode &p = root;
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
        return true;
    } else {
        return false;
    }
    delete s;
}