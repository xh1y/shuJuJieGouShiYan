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

typedef vector<bool> vec_int;
typedef vector<vec_int> vec_vec_int;
typedef vector<Group> vec_grp;

// typedef struct vec_vec_int {
    // vec_int points; 
//     vec_vec_int value;
// } vec_vec_int;

void getGraph(vec_vec_int& graph, Group group);
void useBFS(vec_vec_int graph, int start, int total);
int firstAdjVex(vec_vec_int graph, int u);
int nextAdjVex(vec_vec_int graph, int u, int w);
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
        vec_vec_int graph(groups[question].peopleNum, vec_int(groups[question].peopleNum, false));
        // for (int i = 0; i < groups[question].peopleNum; i++) {
        //     for (int j = 0; j < groups[question].peopleNum; j++) {
        //         graph[i][j] = false;
        //     }
        // }
        getGraph(graph, groups[question]);
        for(int i = 0; i < graph.size(); i++) {
            for(int j = 0; j < graph[i].size(); j++) {
                cout << setw(3) << graph[i][j] << " ";
            }
            cout << endl;
        }
        for (int i = 0; i < graph.size(); i++) {
            useBFS(graph, i, graph.size());
        }
    }
}

void getGraph(vec_vec_int& graph, Group group) {
    for (int i = 0; i < group.relationNum; i++) {
        graph[group.relations[i].person_a - 1][group.relations[i].person_b - 1] = true;
        graph[group.relations[i].person_b - 1][group.relations[i].person_a - 1] = true;
    }
}

void useBFS(vec_vec_int graph, int start, int total) {
    int notOverSeven = 1;
    bool* visited = new bool[total + 1];
    for(int i = 0; i < total + 1; i++) {
        visited[i] = false;
    }
    visited[start] = true;
    queue<int> q;
    q.push(start);
    int* level = new int[total + 1];
    level[0] = 1;
    for (int len = 1; len < 6 && !q.empty(); len++) {
        for (int i = 0; i < level[len - 1]; i++) {
            int u = q.front();
            q.pop();
            for (int w = firstAdjVex(graph, u); w >= 0; w = nextAdjVex(graph, u, w)) {
                if (!visited[w]) {
                    visited[w] = true;
                    notOverSeven++;
                    level[len]++;
                    q.push(w);
                }
            }
            
        }
    }
    cout << start + 1 << ": " << setprecision(2) <<  notOverSeven   << endl;
    delete[] visited;
    delete[] level;
}

int firstAdjVex(vec_vec_int graph, int u) {
    // vector<int> next;
    for (int j = 0; j < graph[u].size(); j++) {
        if (graph[u][j] != false) {
            // next.push_back(j);
            return j;
            break;
        }
    }

    return -1;
}

int nextAdjVex(vec_vec_int graph, int u, int w) {
    // bool to_w = false;
    for (int j = w + 1; j < graph[u].size(); j++) {
        if (graph[u][j] == true) {
            return j;
            break;
        }
        // if (j == w) {
        //     to_w = true;
        // }
    }

    return -1;
}