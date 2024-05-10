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