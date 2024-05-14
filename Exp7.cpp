#include <iostream>
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
//     vec_int points; 
//     vec_vec_int value;
// } vec_vec_int;

void getGraph(vec_vec_int &g);
int main() {
    int people, relations;
    vec_grp groups;
    while(cin >> people >> relations && not (people == 0 and relations == 0)) {
        Group group;
        group.peopleNum = people;
        group.relationNum = relations;
        // for(int i = 0; i < group.peopleNum)
        for(int i = 0; i < group.relationNum; i++) {
            int a, b;
            cin >> a >> b;
            relation temp = {a, b};
            group.relations.push_back(temp);
        }
        groups.push_back(group);
    }

    for(int question = 0; question < groups.size(); question++) {
        vec_vec_int graph(groups[question].peopleNum, vec_int(groups[question].peopleNum, 0));
        for(int i = 0; i < groups[question].peopleNum; i++) {
            for(int j = 0; j < groups[question].peopleNum; j++) {
                graph[i][j] = false;
            }
        }
        getGraph(graph, groups[question]);
    }
}

void getGraph(vec_vec_int &graph, Group group) {
    for (int i = 0; i < group.relationNum; i++) {
        graph[group.relations[i].person_a - 1][group.relations[i].person_b - 1] = true;
        graph[group.relations[i].person_b - 1][group.relations[i].person_a - 1] = true;
    }
}

