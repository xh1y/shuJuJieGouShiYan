#include <iostream>
#include <string>
#include <cctype>
#include <vector>
using namespace std;
typedef struct WordAndWeight {
    char data;
    int weight;
    string codes;
} WordAndWeight; // C++ 中struct wordAndWeight可简写成wordAndWeight

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
string subreplace(string resource_str, string sub_str, string new_str);
void CreateHuffmanTree(HuffmanTree &huffmanTree, int n, vec_waw waw);
void Select(HuffmanTree &HuffmanTree, int n, int &s1, int &s2);
void calculateStringWeight(string s, int weightOfEveryCharacter[], int n);
void huffmanChangeToCode(HuffmanTree huffmanTree, int nowRoot);
void huffmanDecode(string code, vec_waw waw);
bool equal0(string a);
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
        huffmanDecode(newS, waw);
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

void huffmanDecode(string code, vec_waw waw) {
    string before = code;
    vec_waw copy = waw;
    for(int i = 1; i < waw.size() - 1; i++) {
        for(int j = i + 1; j < waw.size(); j++) {
            if ((waw[i].codes.length() == waw[j].codes.length() and waw[i].codes.compare(waw[j].codes) > 0) or waw[i].codes.length() > waw[j].codes.length()) {
                WordAndWeight temp;
                temp = waw[i];
                waw[i] = waw[j];
                waw[j] = temp;
            }
        }
    }
    
    for (int i = waw.size() - 1; i >= 1; i--) {
        string emptyString = "";
        emptyString.push_back(waw[i].data);
        before = subreplace(before, waw[i].codes, emptyString);
    }
    cout << before << endl;
}

string subreplace(string resource_str, string sub_str, string new_str) {
    string dst_str = resource_str;
    string::size_type pos = 0;
    while ((pos = dst_str.find(sub_str)) != string::npos) { //find函数在找不到指定值得情况下会返回string::npos
        dst_str.replace(pos, sub_str.length(), new_str);
    }
    return dst_str;
}