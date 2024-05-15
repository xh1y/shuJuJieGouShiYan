#include <iostream>
#include <vector>
#include <algorithm>
#include <queue>
#include <numeric>
using namespace std;
vector<vector<int>> Edge;
vector<int>visit;
int N, M, sum = 1;
void BFS(int x) {
    queue<int>Q;
    Q.push(x);
    int t;
    visit[x] = true;
    int level = 0, last = x, tail;//level表示在第几层目前  一开始初始为0  last这一层的最后一个元素  tail：进队列的最后一个元素 
    while (!Q.empty()) {
        t = Q.front();
        Q.pop();
        for (int i = 0;i < Edge[t].size();i++) {
            if (!visit[Edge[t][i]]) {
                Q.push(Edge[t][i]);
                visit[Edge[t][i]] = true;
                sum++;//进行个数统计 
                tail = Edge[t][i];//tail不断往后移一直到该层的最后一个节点 
            }
        }
        if (t == last) {//当前弹出的节点是本层的最后一个节点 
            level++;//层数加1 进入下一层 
            last = tail;//last指向下一层的最后一个节点 
        }
        if (level == 6)//当达到6层 跳出即可 
            return;
    }
}
int main() {
    cin >> N >> M;
    Edge.resize(N + 1);
    visit.resize(N + 1);
    for (int i = 0;i < M;i++) {
        int a, b;
        cin >> a >> b;
        Edge[a].push_back(b);
        Edge[b].push_back(a);
    }
    for(int i = 0; i < Edge.size(); i++) {
        for(int j = 0; j < Edge[i].size(); j++) {
            cout << Edge[i][j] << " ";
        }
        cout << endl;
    }
    for (int i = 1;i <= N;i++) {
        BFS(i);
        double res = (sum * 1.0) / N;
        printf("%d: %.2f%%", i, res * 100);//若用printf输出的时候  使用%%输出--% 
        if (i != N)
            cout << endl;
        sum = 1;
        visit.clear();
        for (int x = 1;x <= N;x++)//visit清零  为下一个节点的访问做准备 
            visit[x] = false;
    }
    return 0;
}
