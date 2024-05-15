```cpp
void huffmanDecode(string code, vec_waw waw, HuffmanTree huffmanTree, int size) {
    string before = code;
    vec_waw copy = waw;
    for(int i = 1; i < waw.size() - 1; i++) {
        for(int j = i + 1; j < waw.size(); j++) {
            if ((waw[i].codes.compare(waw[j].codes) > 0)) {
                WordAndWeight temp;
                temp = waw[i];
                waw[i] = waw[j];
                waw[j] = temp;
            }
        }
    }
    
    // for(int i = 0; i < code.length(); i++) {
    //     for() 
    // }
    // cout << before << endl;
    int i = 1;
    while(i < code.length()) {
        // cout << waw[i].codes << ": " << waw[i].data << endl;
        int startPlace = 0;
        while(!getValue(code.substr(startPlace, i - startPlace), huffmanTree, size)) {
            i++;
        }
        startPlace = i + 1;
        i = startPlace + i;
    }
}

bool getValue(string code, HuffmanTree huffmanTree, int size) {
    auto p = huffmanTree[size - 1];
    for(int i = 0; i < code.length(); i++) {
        if(code[i] == '0') {
            p = huffmanTree[p.lchild];
        } else {
            p = huffmanTree[p.rchild];
        }
    }
    if(islower(p.wordAndWeight.data)) {
        cout << p.wordAndWeight.data;
        return true;
    } else {
        return false;
    }
}
```
## question 7
10 9
1 2
2 3
3 4
4 5
5 6
6 7
7 8
8 9
9 10
10 8
1 2
2 3
3 4
4 5
5 6
6 7
7 8
9 10
0 0

## question 6
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

## question 4
aaaaaaabbbbbccdddd
aabccc
0