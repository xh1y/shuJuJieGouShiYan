#include <iostream>
#include <string>
#include <vector>
using namespace std;

void f(vector<int> &v) {
    v[0] = 3;
}
int main() {
    vector<int> s;
    for(int i = 0; i < 5; i++) 
        s.push_back(i);
    f(s);
    cout << s[0];
}