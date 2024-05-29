#include <iostream>
#include <iomanip>
#include <vector>
#include <queue>

using namespace std;

typedef struct relation {
    int person_a;
    int person_b;
} relation;

typedef vector<relation> vec_rel;

typedef struct Group {
    int peopleNum;
    int relationNum;
    vector<relation> relations;
} Group;

typedef vector<bool> vec_bool;
typedef vector<vec_bool> vec_vec_bool;
typedef vector<Group> vec_grp;

void getGraph(vec_vec_bool& graph, Group group);
void useBFS(vec_vec_bool graph, int start, int total);
// int firstAdjVex(vec_vec_bool graph, int u);
// int nextAdjVex(vec_vec_bool graph, int u, int w);
int main() {
    int people, relations;
    vec_grp groups;
    while (cin >> people >> relations && not (people == 0 and relations == 0)) {
        Group group;
        group.peopleNum = people;
        group.relationNum = relations;
        // for(int i = 0; i < group.peopleNum)
        for (int i = 0; i < group.relationNum; i++) {
            int a, b;
            cin >> a >> b;
            relation temp = { a, b };
            group.relations.push_back(temp);
        }
        groups.push_back(group);
    }

    for (int question = 0; question < groups.size(); question++) {
        vec_vec_bool graph(groups[question].peopleNum, vec_bool(groups[question].peopleNum, false));
        getGraph(graph, groups[question]);
        for (int i = 0; i < graph.size(); i++) {
            useBFS(graph, i, graph.size());
        }
    }
}

void getGraph(vec_vec_bool& graph, Group group) {
    for (int i = 0; i < group.relationNum; i++) {
        graph[group.relations[i].person_a - 1][group.relations[i].person_b - 1] = true;
        graph[group.relations[i].person_b - 1][group.relations[i].person_a - 1] = true;
    }
}

void useBFS(vec_vec_bool graph, int start, int total) {
    bool* visited = new bool[total + 1];
    for (int i = 0; i < total + 1; i++) {
        visited[i] = false;
    }
    visited[start] = true;
    queue<int> q;
    vector<int> vi;

    int count = 1;
    int levelNow = 0;
    q.push(start);
    int t;
    visited[start] = true;
    int level = 0, last = start, tail;//level表示在第几层目前  一开始初始为0  last这一层的最后一个元素  tail：进队列的最后一个元素 
    while (!q.empty()) {
        t = q.front();
        q.pop();
        for (int i = 0; i < graph[t].size(); i++) {
            if (graph[t][i]) {
                vi.push_back(i);
            }
        }
        for (int i = 0;i < vi.size();i++) {
            if (!visited[vi[i]]) {
                q.push(vi[i]);
                visited[vi[i]] = true;
                count++;
                tail = vi[i];
            }
        }
        if (t == last) {
            levelNow++;
            last = tail;
        }
        if (levelNow == 6)
            break;
    }
    double res = (count * 1.0) / total;
    cout.setf(ios_base::fixed, ios_base::floatfield);
    cout << start + 1 << ": " << setprecision(2) << res * 100 << "%" << endl;
}